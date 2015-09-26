#include "plotnode.h"
#include "data/datafactory.h"
#include "data/messagedata.h"
#include <QDebug>
#include <QFile>


//------------------------------------------------------------------------------
// Constructor and Destructor

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
    qDebug()<<"in plot node";
    qDebug()<<data;
    // Process framework messages.
    if(data->getType() == "table") {

        qDebug() << "PlotNode works";
        return true;
    }
}

