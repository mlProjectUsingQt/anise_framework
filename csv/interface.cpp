#include "interface.h"
#include "csvdata.h"

extern "C"
{
CData *maker()
{
    return new CCsvData();
}
}

