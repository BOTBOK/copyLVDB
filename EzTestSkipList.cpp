#include "SkipList.h"
#include <iostream>



class Com
{
public:
    int operator()(const int &a, const int &b)
    {
        return a - b;
    }
};
void ezTestSkipList()
{
    Com com;
    SkipList<int, Com> skipList(com);
    for(int i = 0; i < 99999; ++i)
    {
        std::random_device rd;
        int tmp = rd();
        tmp = tmp / 2;
        if(i % 9999 == 1)
            std::cout << i << std::endl;
        skipList.insert(tmp);
    }
    
    SkipList<int, Com>::Interator it(&skipList);
    for(auto i = 0; i < 99998; ++i)
    {
        it.next();
        std::cout << it.getNode()->key << std::endl;
    }
    
    int b;
    std::cin >> b;
}


