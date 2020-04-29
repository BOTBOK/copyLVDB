//
//  Coding.cpp
//  test
//
//  Created by 沈佳锋 on 2020/4/28.
//  Copyright © 2020 沈佳锋. All rights reserved.
//

#include "Coding.h"

char *encodeVarint32(char *dst, uint32_t v)
{
    uint8_t *ptr = reinterpret_cast<uint8_t *>(dst);
    const uint32_t B = 128;
    
    if(v < B)
    {
        (*ptr++) = v;
    }
    else if((v >> 7) < B)
    {
        (*ptr++) = v | B;
        (*ptr++) = v >> 7;
    }
    else if((v >> 14) < B)
    {
        (*ptr++) = v | B;
        (*ptr++) = (v >> 7) | B;
        (*ptr++) = (v >> 14);
    }
    else if((v >> 21) < B)
    {
        (*ptr++) = v | B;
        (*ptr++) = (v >> 7) | B;
        (*ptr++) = (v >> 14) | B;
        (*ptr++) = (v >> 21);
    }
    else
    {
        (*ptr++) = v | B;
        (*ptr++) = (v >> 7) | B;
        (*ptr++) = (v >> 14) | B;
        (*ptr++) = (v >> 21) | B;
        (*ptr++) = (v >> 28);
    }
    
    return reinterpret_cast<char*>(ptr);
}

const char *getVarInt32PtrFallback(const char *p, const char *limit, uint32_t *value)
{
    uint32_t tValue = 0;
    for(int shift = 0; shift <=28 && p < limit; shift += 7)
    {
        const uint8_t byte = *reinterpret_cast<const uint8_t *>(p);
        ++p;
        if(byte & 128)
        {
            tValue |= (byte & 127) << shift;
        }
        else
        {
            tValue |= byte << shift;
            *value = tValue;
            return p;
        }
    }
    return nullptr;
}
