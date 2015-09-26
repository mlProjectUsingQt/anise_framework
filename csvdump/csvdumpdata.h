#ifndef CSVDUMPDATA_H
#define CSVDUMPDATA_H

#include "data/data.h"

class CCsvdumpData: public CData
{
public:
    explicit CCsvdumpData();
    virtual CDataPointer clone() const;
};

#endif // CSVDUMPDATA_H

