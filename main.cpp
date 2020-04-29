//
//  main.cpp
//  test
//
//  Created by 沈佳锋 on 2020/4/29.
//  Copyright © 2020 沈佳锋. All rights reserved.
//

#include <stdio.h>
#include "Coding.h"
#include <memory.h>
#include <iostream>

int main()
{
    uint32_t a;
    memset(&a, 0xff, sizeof(uint32_t));
    std::cout << a << std::endl;
    a = 5000000;
    uint32_t e = getVarint32Length(a);
    std::cout <<  e << std::endl;
    for(int i = 0; i < 32; ++i)
    {
        std::cout << (a & (1 << i) ? 1 : 0);
    }
    std::cout << std::endl;
    char * b = static_cast<char*>(malloc(50));
    
    uint32_t c;
    encodeVarint32(b, a);
    for(int i = 0; i < 5; ++i)
    {
        std::cout << static_cast<uint32_t>(b[i] & 255) << std::endl;
    }
    
    
    getVarInt32PtrFallback(b, b + 5, &c);
    std::cout << c << std::endl;
    std::cin >> a;
    
    return 0;
}
