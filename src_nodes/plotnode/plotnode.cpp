#include "plotnodenode.h"
#include "data/datafactory.h"
#include "data/messagedata.h"
#include <QDebug>


//------------------------------------------------------------------------------
// Constructor and Destructor

CPlotnodeNode::CPlotnodeNode(const CNodeConfig &config, QObject *parent/* = 0*/)
    : CNode(config, parent)
{

}


//------------------------------------------------------------------------------
// Public Functions

void CPlotnodeNode::configure(CNodeConfig &config)
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

bool CPlotnodeNode::start()
{
    qDebug() << "Start called.";

    return true;
}

void CPlotnodeNode::data(QString gate_name, const CConstDataPointer &data)
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

