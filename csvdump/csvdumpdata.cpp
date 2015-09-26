#include "csvdumpdata.h"
#include <QDebug>


//------------------------------------------------------------------------------
// Constructor and Destructor

CCsvdumpData::CCsvdumpData()
    : CData()
{

}


//------------------------------------------------------------------------------
// Public Functions

CDataPointer CCsvdumpData::clone() const
{
    qWarning() << "Cloning not implemented.";
    return CDataPointer();
}


//------------------------------------------------------------------------------
// Private Functions

