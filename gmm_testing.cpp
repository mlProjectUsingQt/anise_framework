#include <iostream>
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <math.h>

#define MAX_SEGMENTS 40
int main()
//int argc;
//char *argv[];
{
	
	FILE *stream; 
  	void  free_vector(), erhand();
	float Normi(), Normr(), *in_vector, *vector(int ,int);
  	float *labs, datamin, datamax;
  	float *orig_vector, p, pmax, ival, mlikedenom, in_value;
  	double mu[MAX_SEGMENTS], sd[MAX_SEGMENTS];
  	double loglik_old, loglik_new, conv_crit, segment_probs[MAX_SEGMENTS];
  	double dsegment_number, segment_probs_total, denom[256];
  	double mu_numer, mu_denom, sd_numer, sd_denom, loglik_sum;
  	double dnorm_lookup[256][MAX_SEGMENTS], delta_lookup[256][MAX_SEGMENTS];
  	int i, j, k, iseg, segment_number, n;
  	int iter_counter, max_iterations, current_breakpoint, current_total, done;
  	int greyscale_histogram[256], initial_breakpoints[(MAX_SEGMENTS+1)];
  	int sd_counter[MAX_SEGMENTS], mu_counter[MAX_SEGMENTS];
  	int empty_levels, initialization_multiplier, initialization_error;
  	int cardinality[MAX_SEGMENTS];

	segment_number = 3; 
	std::cout<<"Number of clusters wanted:"<<segment_number<<".\n";
	n = 10; 
	std::cout<<"Number of input data values:"<<n<<".\n";

	/*if ((stream = fopen(argv[3],"r")) == NULL)  
	{
     		fprintf(stderr, "Program %s : cannot open file %s\n",
                argv[0], argv[3]);
     		fprintf(stderr, "Exiting to system.");
  	}*/	
	
	orig_vector = vector(0,n-1); /* Input data */
  	in_vector = vector(0,n-1); /* Input data */
  	labs = vector(0,n-1);      /* Used later for cluster labels */
	
	/*for (i = 0; i < n; i++)  
	{
		fscanf(stream, "%f", &in_value);
      		orig_vector[i] = in_value;
  	}*/

	for (i = 0; i < 10; i++) 
	{
		
		std::cout << orig_vector[i] << "\n";//printf("%5.1f", orig_vector[i]); 
	}

	for (i = 0; i < n; i++) in_vector[i] = orig_vector[i];

	datamin  = 1.0E30;
  	datamax  = -1.0E30;

  	for (i = 0; i < n; i++)  {
      		if (in_vector[i] < datamin) datamin = in_vector[i];
      		if (in_vector[i] > datamax) datamax = in_vector[i];
  	}

	/* delta_lookup is prob of a datum (we're using histogram) with
   	value j being in segment i.
   	mu, sd, and segment_probs are the estimated mean, standard deviation, 
   	and mixture probability for each segment. */

   	loglik_old      = 0;              /* Some initializations */
   	loglik_new      = 1;
   	max_iterations  = 200;
   	dsegment_number = segment_number; /* explicit type conversion */
	
	/* Rescale values to 0..255 */
   	for (i = 0; i < n; i++) 
	{
       	in_vector[i] = 255.0*(in_vector[i]-datamin)/(datamax-datamin);
	}	
   	/* Initialize delta_lookup to the starting guess 
      	the starting guess is found by dividing the histogram of greyscale 
      	levels into equally sized pieces, so initially each segment will 
      	have the same segment probability.*/	
	
	/* Find cardinality of each greyscale level (histogram bin card.) */
   	empty_levels=0;

	for (i=0; i<256; i++) 
	{
       		greyscale_histogram[i] = 0;
       		for (j=0; j<n; j++) {
           		if ((int)in_vector[j]==i) greyscale_histogram[i] += 1; 
       		}
   		if (greyscale_histogram[i]==0) empty_levels+=1;
   	}
	for (i=0; i<256; i++) 
	{
		std::cout<<greyscale_histogram[i] <<"/n";
	}
	//printf("%d ",greyscale_histogram[i]);

   /* For the initial segmentation, there are a total of n values to be 
      divided (roughly) equally among number_segment initial segments. 
      Thus we want about n/number_segment values in each bin.  We use
      initial_breakpoints to store the breakpoints of our binning. 

      Note that this will not give a good result when all the points 
      are in one histogram bin.  Warning: problems if hist. sparse! 

      We should check to make sure the number of unique non-zero grey 
      levels (or non-empty histogram bins) is larger than segment_number.  
      If not, this should fail gracefully.  */ 

   initial_breakpoints[0]              = -1; 
   initial_breakpoints[segment_number] = 256;
   current_breakpoint                  = -1;
   initialization_error                = 0;

   for (i=1; i<(segment_number); i++) {
       current_total = 0;
       done = 0;
       while (done==0) {
             current_breakpoint += 1;
             if (current_breakpoint==255) initialization_error+=1;
             current_total += greyscale_histogram[current_breakpoint];
             if (current_total >= (n/segment_number) ) {
                initial_breakpoints[i] = current_breakpoint;
                done = 1;
             }
       }
       if (current_total==0) initialization_error+=1;
   }

   initialization_multiplier = 1;           
   while (initialization_error > 0) {

         initial_breakpoints[0]              = -1;
         initial_breakpoints[segment_number] = 256;
         current_breakpoint                  = -1;
         initialization_error                = 0;
         initialization_multiplier           = initialization_multiplier*2;

         for (i=1; i<(segment_number); i++) {
             current_total = 0;
             done = 0;
             while (done==0) {
                   current_breakpoint += 1;
                   if (current_breakpoint==255) initialization_error+=1;
                   current_total += greyscale_histogram[current_breakpoint];

                   if (initialization_multiplier == 0) {
                      //printf("Pathological case in histogram. Stopping.\n");
                      //exit(1);
                   }
                   if (initialization_multiplier >= 4096) {
                      //printf("Pathological case in histogram. Stopping.\n");
                      //exit(1);
		   }

                   if (current_total >= (int)((float)n/
                   ( (float)initialization_multiplier *
                     (float)segment_number ))) {
                      initial_breakpoints[i] = current_breakpoint;
                      done = 1;
		   }
	     }
             if (current_total==0) initialization_error+=1;
	 }
   }                                            

   /* Check here that the init breaks are valid.  If not, probably trying
      to fit more segments than unique greyscale values (or non-zero
      histogram bins). */

   for (i=0; i<(segment_number); i++) {
       for (j=0; j<256; j++) {
           if ( (j>initial_breakpoints[i]) &&
                (j<= initial_breakpoints[(i+1)])) {
              delta_lookup[j][i] = 1.0; }
           else delta_lookup[j][i] = 0.0;
       }
   }

   /* End of initializing delta_lookup*/

}



float *vector(int n0, int n)
//int n0, n;
  /* Allocates a float vector with range [n0..n]. */
{
      float *v;
      v = (float *) malloc ((unsigned) (n-n0+1)*sizeof(float));
      return v-n0;                                             
}
