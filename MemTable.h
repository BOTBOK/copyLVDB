//
//  MemTable.hpp
//  test
//
//  Created by 沈佳锋 on 2020/4/29.
//  Copyright © 2020 沈佳锋. All rights reserved.
//

#ifndef MemTable_h
#define MemTable_h

#include <stdio.h>
#include "Compare.h"
#include "SkipList.h"

#define SequenceNum uint32_t

enum KeyType { KEY_DELETE = 0x0, KEY_VALUE = 0x1 };

class InterKeyComparator
{
    Comparator *comparator_;
public:
    InterKeyComparator(Comparator *c): comparator_(c){}
    int compare(char *a, char *b)
    {
        return 0;
    }
    int operator()(char *a, char *b)
    {
        return 0;
    }
};

class MemTable
{
private:
    SkipList<char *, InterKeyComparator> list_;
public:
    void add(SequenceNum s, KeyType type, Slice &key, Slice &value);
};

#endif /* MemTable_h*/
