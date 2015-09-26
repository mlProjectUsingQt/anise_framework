#include "plotnode.h"
#include "data/datafactory.h"
#include "data/messagedata.h"
#include <QDebug>


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
    //config.setDescription("");

    // Add parameters
    //config.addFilename("file", "Input File", "File to be read from disk.");

    // Add the gates.
    //config.addInput("in", "misc");
    //config.addOutput("out", "misc");
}


//------------------------------------------------------------------------------
// Protected Functions

bool CPlotNode::start()
{
    qDebug() << "Start called.";

    return true;
}

void CPlotNode::data(QString gate_name, const CConstDataPointer &data)
{
    qDebug() << "Data received.";

    // Process framework messages.
    if(data->getType() == "message") {
        auto pmsg = data.staticCast<const CMessageData>();
        QString msg = pmsg->getMessage();
        qDebug() << "Received message:" << msg;
        if(msg == "error") {
            commitError("out", "Could not get tcp file data.");
            return;
        }
    }
}

