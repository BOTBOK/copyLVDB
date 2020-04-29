//
//  Slice.h
//  test
//
//  Created by 沈佳锋 on 2020/4/29.
//  Copyright © 2020 沈佳锋. All rights reserved.
//

#ifndef Slice_h
#define Slice_h
#include <stdint.h>

class Slice
{
    char *data_;
    uint32_t size_;
public:
    Slice(char *data, uint32_t s):data_(data), size_(s){}
    char * data(){return data_;}
    uint32_t size(){return size_;}
};
#endif /* Slice_h */
