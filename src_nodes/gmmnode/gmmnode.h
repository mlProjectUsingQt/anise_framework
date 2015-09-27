#ifndef GMMNODE_H
#define GMMNODE_H

#include "node/node.h"
#include "node/nodeconfig.h"
#include "rulesetdata/ruletypes.h"
#include "rulesetdata/consequent.h"
#include "rulesetdata/rule.h"
#include "rulesetdata/rulesetdata.h"
#include "tabledata/tabledata.h"
#include <QObject>
#include <QString>
#define MAX_SEGMENTS        40


class CGmmNode: public CNode
{
  Q_OBJECT

  typedef QMap<Antecedent, CRule> Ruleset;

  private:
    // Data Structures
    QSharedPointer<CRulesetData> m_ruleset;
    QSharedPointer<const CTableData> gmm_train_table;
    QSharedPointer<const CTableData> gmm_test_table;
    /**
    * Declaration for data training
    */
     QList<float> data_points;
     qint32 segmentNum = 3;
     qint32 numOfData;
     float *orig_vector, *in_vector,*labs;//original_vector, input_vector, labels
     float datamin  = 1.0E30, datamax  = -1.0E30, ival, pmax, mlikedenom, p;
     double loglik_old, loglik_new,dsegment_number,conv_crit, segment_probs_total,
            mu_numer, mu_denom, sd_numer, sd_denom, loglik_sum;
     double mu[MAX_SEGMENTS],sd[MAX_SEGMENTS], segment_probs[MAX_SEGMENTS], denom[256];
     double delta_lookup[256][MAX_SEGMENTS], dnorm_lookup[256][MAX_SEGMENTS];
     int max_iterations, segment_number =6, empty_levels, current_breakpoint,
         initialization_error,current_total, done, initialization_multiplier,
         iter_counter;
     int sd_counter[MAX_SEGMENTS], mu_counter[MAX_SEGMENTS],  greyscale_histogram[256],
         initial_breakpoints[(MAX_SEGMENTS+1)], cardinality[MAX_SEGMENTS];

    /**
    * Declaration for data testing
    */
    QList<float> test_data_points;
    qint32 numOfTestData;
    float *test_vector, *in_test_vector, *test_labs;
    /**
    * Flags for training and testing data
    */
    bool test = false;
    bool train = false;
    bool testInFile = false;

  public:
    // Constructor
    explicit CGmmNode(const CNodeConfig &config, QObject *parent = 0);
    // Set the configuration template for this Node.
    static void configure(CNodeConfig &config);

  protected:
    // Function called when the simulation is started.
    virtual bool start();
    // Receive data sent by other nodes connected to this node.
    virtual bool data(QString gate_name, const CConstDataPointer &data);
    //Converts the table data into a list
    //QList<QString> extractListFromTable(const QSharedPointer<const CTableData> &table);
    // Trains the data
    void trainData(const QSharedPointer<const CTableData> &table);
    // Test the data
    void testData(const QSharedPointer<const CTableData> &table);
    //Gaussian Mixture model to train the data
    void gmmTrain(const QList<qint32> &training_data);
    float* vector(int n0,int n);
    float Normi(int x, float mu, float sd);
    float Normr(float x, float mu, float sd);
    inline qint32 rnd() const;
    // Write rules to a file.
   // void dumpRules(const QList<QString> &header,
     //              const QString &filename);
};

//qint32 CGmmNode::rnd() const
//{
    // 30-31 bit random number
  //  return (qrand() + (qrand() << 15)) & 0x7fffffff;
//}

#endif // GMMNODE_H
