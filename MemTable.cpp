//
//  MemTable.cpp
//  test
//
//  Created by 沈佳锋 on 2020/4/29.
//  Copyright © 2020 沈佳锋. All rights reserved.
//

#include "MemTable.h"
#include "Slice.h"
#include "Coding.h"
#include <memory.h>

void MemTable::add(SequenceNum s, KeyType type, Slice &key, Slice &value)
{
    uint32_t keySize = key.size();
    uint32_t valSize = value.size();
    uint32_t interKeySize = keySize  + 8; //八个字节存放s和type
    uint32_t mLength = getVarint32Length(interKeySize) + interKeySize + getVarint32Length(valSize) + valSize;
    
    char *keyM = static_cast<char*>(malloc(mLength));
    
    keyM = encodeVarint32(keyM, interKeySize);
    
}

