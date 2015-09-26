#include "interface.h"
#include "csvdatadata.h"

extern "C"
{
CData *maker()
{
    return new CCsvdataData();
}
}

