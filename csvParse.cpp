#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <istream>
 
using std::cout;
using std::endl;
 
std::vector<std::string> csv_read_row(std::istream &in, char delimiter);
std::vector<std::string> csv_read_row(std::string &in, char delimiter);
 
int main(int argc, char *argv[])
{
    std::ifstream in("input.csv");
    if (in.fail()) return (cout << "File not found" << endl) && 0;
    while(in.good())
    {
        std::vector<std::string> row = csv_read_row(in, ',');
        for(int i=0, leng=row.size(); i<leng; i++)
            cout << "[" << row[i] << "]" << "\t";
        cout << endl;
    }
    in.close();
 
    std::string line;
    in.open("input.csv");
    while(getline(in, line)  && in.good())
    {
        std::vector<std::string> row = csv_read_row(line, ',');
        for(int i=0, leng=row.size(); i<leng; i++)
            cout << "[" << row[i] << "]" << "\t";
        cout << endl;
    }
    in.close();
 
    return 0;
}
 
std::vector<std::string> csv_read_row(std::string &line, char delimiter)
{
    std::stringstream ss(line);
    return csv_read_row(ss, delimiter);
}
 
std::vector<std::string> csv_read_row(std::istream &in, char delimiter)
{
    std::stringstream ss;
    bool inquotes = false;
    std::vector<std::string> row;//relying on RVO
    while(in.good())
    {
        char c = in.get();
        if (!inquotes && c=='"') //beginquotechar
        {
            inquotes=true;
        }
        else if (inquotes && c=='"') //quotechar
        {
            if ( in.peek() == '"')//2 consecutive quotes resolve to 1
            {
                ss << (char)in.get();
            }
            else //endquotechar
            {
                inquotes=false;
            }
        }
        else if (!inquotes && c==delimiter) //end of field
        {
            row.push_back( ss.str() );
            ss.str("");
        }
        else if (!inquotes && (c=='\r' || c=='\n') )
        {
            if(in.peek()=='\n') { in.get(); }
            row.push_back( ss.str() );
            return row;
        }
        else
        {
            ss << c;
        }
    }
}

                QString segment = "normal(x," + gausses[col_count-col_count].toString()
                        + "," + gausses[col_count-(col_count-1)].toString() + ","
                        + gausses[col_count-(col_count-1)+1].toString() + ")";
                QString line = "normal(x," + gausses[col_count-col_count].toString()
                        + "," + gausses[col_count-(col_count-1)].toString() + ")";
                plot_lines.append(line);
                plot_gmm.append(segment);
            }

            for (int i=0; i<plot_lines.size(); i++)
            {
                if(!normals.isEmpty())
                {
                    normals = normals+","+plot_lines[i];
                    gmm = gmm + "+" + plot_gmm[i];

                } else if(normals.isEmpty())
                {
                    normals = plot_lines[i];
                    gmm = plot_gmm[i];
                }

            }

            QList<QVariant> const &min_max = table->getRow(0);
            datamin = min_max[col_count-2].toString();
            datamax = min_max[col_count-1].toString();

            QString gPlot = terminalSet+
                    "set output 'gauss_plot.png'\n"                    
                    "set clip two\n"
                    "set style fill  transparent solid 0.50 noborder\n"
                    "set key title 'Gaussian Distribution'\n"
                    "set key inside left top vertical Right reverse enhanced autotitle nobox\n"
                    "set key noinvert samplen 1 spacing 1 width 0 height 0 \n"
                    "set style data lines\n"
                    "set style function filledcurves y1=0\n"
                    "set boxwidth 0.1\n"
                    "set xrange"+"["+datamin+":"+datamax+"]\n"
                    "normal(x, mu, sd) = (1/(sd*sqrt(2*pi)))*exp(-(x-mu)**2/(2*sd**2))\n"
                    "plot "+ normals;
            QString gPlot_1 = terminalSet+
                    "set output 'gauss_plot.png'\n"
                    "set clip two\n"
                    "set style fill  transparent solid 0.50 noborder\n"
                    "set key title 'Gaussian Distribution'\n"
                    "set key inside left top vertical Right reverse enhanced autotitle nobox\n"
                    "set key noinvert samplen 1 spacing 1 width 0 height 0 \n"
                    "set style data lines\n"
                    "set style function filledcurves y1=0\n"
                    "set boxwidth 0.1\n"
                    "set xrange"+"["+datamin+":"+datamax+"]\n"
                    "normal(x, mu, sd, prob) = prob*(1/(sd*sqrt(2*pi)))*exp(-(x-mu)**2/(2*sd**2))\n"
                    "plot "+ gmm;
            // "normal(x,-0.25,0.95),normal(x,1.5,0.05)";
            QString exe = "gnuplot";
            QString plotFileName = "guassPlot.gnu";
            QFile plotFile(plotFileName);
            if (plotFile.open(QIODevice::ReadWrite))
            {
                    QTextStream stream(&plotFile);
                    stream << gPlot << endl;
            }
            QString cmd = exe + " " + plotFileName;
            anise_process->start(cmd);
            anise_process->waitForFinished();
            plotFile.close();
            QString plotFileName_1 = "gmmPlot.gnu";
            QFile plotFile_1(plotFileName_1);
            if (plotFile_1.open(QIODevice::ReadWrite))
            {
                    QTextStream stream(&plotFile_1);
                    stream << gPlot_1 << endl;
            }
            QString cmd_1 = exe + " " + plotFileName_1;
            anise_process->start(cmd_1);
            anise_process->waitForFinished();
            plotFile_1.close();
