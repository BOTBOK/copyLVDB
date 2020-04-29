//
//  Coding.h
//  test
//
//  Created by oldman on 2020/4/28.
//  Copyright © 2020 oldman. All rights reserved.
//

#ifndef Coding_h
#define Coding_h
#include <stdint.h>
#include <stdio.h>

/**
    varint32编码，节省int类型的空间
 */
char *encodeVarint32(char *dst, uint32_t v);

/**
 varin解码
 */
const char *getVarInt32PtrFallback(const char *p, const char *limit, uint32_t *value);

/**
 varint32解码
 */
inline const char* getVarint32Ptr(const char *p, const char *limit, uint32_t *value)
{
    if(p < limit)
    {
        uint8_t tValue = *reinterpret_cast<const uint8_t *>(p);
        if((tValue & 128) == 0)
        {
            *value = tValue;
            return ++p;
        }
    }
    return getVarInt32PtrFallback(p, limit, value);
}

/**
 getVarint32Length
 */
inline uint32_t getVarint32Length(uint32_t v)
{
    uint32_t i = 0;
    while(true)
    {
        ++i;
        if(v > 128)
        {
            v >>= 7;
        }
        else
        {
            return i;
        }
    }
}

#endif /* Coding_h */
