#ifndef CSVDATA_H
#define CSVDATA_H

#include "data/data.h"

class CCsvData: public CData
{
public:
    explicit CCsvData();
    virtual CDataPointer clone() const;
};

#endif // CSVDATA_H

