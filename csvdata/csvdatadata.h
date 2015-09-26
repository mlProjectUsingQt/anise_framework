#ifndef CSVDATADATA_H
#define CSVDATADATA_H

#include "data/data.h"

class CCsvdataData: public CData
{
public:
    explicit CCsvdataData();
    virtual CDataPointer clone() const;
};

#endif // CSVDATADATA_H

