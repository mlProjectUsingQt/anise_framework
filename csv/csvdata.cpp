#include "csvdata.h"
#include <QDebug>


//------------------------------------------------------------------------------
// Constructor and Destructor

CCsvData::CCsvData()
    : CData()
{

}


//------------------------------------------------------------------------------
// Public Functions

CDataPointer CCsvData::clone() const
{
    qWarning() << "Cloning not implemented.";
    return CDataPointer();
}


//------------------------------------------------------------------------------
// Private Functions

