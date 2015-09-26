#include "plotnode.h"
#include "data/datafactory.h"
#include "data/messagedata.h"
#include "tabledata/tabledata.h"
#include <QProcess>
#include <QDebug>
#include <QFile>


//------------------------------------------------------------------------------
// Constructor and Destructor
QProcess *CPlotNode::anise_process = new QProcess();

CPlotNode::CPlotNode(const CNodeConfig &config, QObject *parent/* = 0*/)
    : CNode(config, parent)
{

}


//------------------------------------------------------------------------------
// Public Functions

void CPlotNode::configure(CNodeConfig &config)
{
    // Set a Description of this node.
    config.setDescription("Plots numberical data onto a graph or plots it from a file");

    // Add parameters
    config.addFilename("file", "Input File", "File to be read from disk.");
    config.setCategory("Plot");
    // Add the gates.
    config.addInput("in", "table");
    //config.addOutput("out", "misc");
}


//------------------------------------------------------------------------------
// Protected Functions

bool CPlotNode::start()
{
    qDebug() << "Start called.";
    return true;
}

bool CPlotNode::data(QString gate_name, const CConstDataPointer &data)
{
    Q_UNUSED(gate_name);
    QVector<QString> x(101), y(101);
    // Process framework messages.
    if(data->getType() == "table") {
        // Process table data.
        auto table = data.staticCast<const CTableData>();
        qint32 rows = table->rowCount();
        qint32 attribute_count = table->colCount();
        QString filename = "test.dat";
        QFile file(filename);
        QStringList output;
        for (int i=0; i<rows; i++)
        {
            QList<QVariant> const &row = table->getRow(i);
            x[i] = row[0].toString();
            y[i] = row[1].toString();
            QString line = x[i]+" "+y[i];
            output.append(line);
        }
        if (file.open(QIODevice::ReadWrite))
        {
                QTextStream stream(&file);
                for(QString str:output){
                stream << str << endl;
                }
        }
        QString exe = "gnuplot";
        QString plotFileName = "test.txt";
        QFile plotFile(plotFileName);
        QString dat = "set terminal pngcairo\n"
                       "set output 'scatter_plot.png'\n"
                       "set key inside left top vertical Right noreverse enhanced autotitles box linetype -1 linewidth 1.000\n"
                       "set samples 50, 50\n"
                       "plot \"test.dat\" using 1:2 title 'Scatter Plot'";
        if (plotFile.open(QIODevice::ReadWrite))
        {
                QTextStream stream(&plotFile);
                stream << dat << endl;
        }
        QString cmd = exe + " " + plotFileName;
        qDebug() << "Done";
        anise_process->start(cmd);
        anise_process->waitForFinished();
        file.close();
        plotFile.close();
        file.remove();
        plotFile.remove();
        return true;
    }
    return false;
}

