#include "csvdatadata.h"
#include <QDebug>


//------------------------------------------------------------------------------
// Constructor and Destructor

CCsvdataData::CCsvdataData()
    : CData()
{

}


//------------------------------------------------------------------------------
// Public Functions

CDataPointer CCsvdataData::clone() const
{
    qWarning() << "Cloning not implemented.";
    return CDataPointer();
}


//------------------------------------------------------------------------------
// Private Functions

