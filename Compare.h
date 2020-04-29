//
//  Compare.h
//  test
//
//  Created by 沈佳锋 on 2020/4/29.
//  Copyright © 2020 沈佳锋. All rights reserved.
//

#ifndef Compare_h
#define Compare_h
#include "Slice.h"

class Comparator
{
public:
    virtual int compare(Slice &a, Slice &b) = 0;
    virtual ~Comparator() = default;
};

#endif /* Compare_h */
