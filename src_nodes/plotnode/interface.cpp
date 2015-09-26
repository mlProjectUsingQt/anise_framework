#include "interface.h"
#include "plotnodenode.h"

extern "C"
{
void configure(CNodeConfig &config)
{
    CPlotnodeNode::configure(config);
}

CNode *maker(const CNodeConfig &config)
{
    return new CPlotnodeNode(config);
}
}

