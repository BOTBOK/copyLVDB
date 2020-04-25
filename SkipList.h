//
//  SkipList.h
//  test
//
//  Created by 沈佳锋 on 2020/4/25.
//  Copyright © 2020 沈佳锋. All rights reserved.
//

#ifndef SkipList_h
#define SkipList_h
#include <atomic>

template<typename Key, class Comparaor>
class SkipList
{
private:
    Comparaor compare_;
   
    SkipList(SkipList&) = delete;
    SkipList & operator=(SkipList&) = delete;
    
    int kMaxHeight_ = 12;
public:
    explicit SkipList(Comparaor comparaor):compare_(comparaor), head_(nullptr){}

    int randomInt()
    {
        return 3;
    }
    
    Node * findBigerNode(Key key, Node **prve)
    {
        Node *next = nullptr;
        x = head_;
        i = kMaxHeight_;
        while(true)
        {
            //assert(next ==  nullptr || i >= 0)
            next = x->nextNode(i);
            if(compare_(next->key, key) > 0)
            {
                x = next;
            }
            else
            {
                if(prve != nullptr) {prev[i] = x;}
                if(i == 0)
                {
                    return next;
                }
                else
                {
                    --i;
                }
            }
        }
    }
    
    Node * newNode(int height, Key key)
    {
        /**
                    这边申请的内存大小为一个node的大小 + height-1 个automic<Node*>的大小
         automic<Node*>内存空间紧跟着node空间，这两个个内存空间是连续的，
         其中node结构体中最后一个数据是automic<Node*>数组，且数组大小为1，通过下标访问，如果指针下标为1则数组访问越界，
            但这时正好指向了申请的内存空间automic<Node*>的首地址。指着，如果指针下标为2则访问的就是automic<Node*>内存空间的第二个地址t
         通过这种方式，使得内存空间申请次数减少，达到提高效率的作用。
         
         只不过这边没有初始化std::atomic<Node*> 只初始化了Node
         */
        void * unInitMem = malloc(sizeof(Node) + sizeof(std::atomic<Node*>) * (height - 1));
        return new (unInitMem) Node(key);
    }
    
    void insert(Key key)
    {
        int height = randomInt();
        Node *prev[kMaxHeight_]; //这边是栈上的内存，所以初始值微nullptr
        
        Node * node = newNode(height, key)；
        Node *nextNode = findBigerNode(key, prev);
        for(int i = 0; i < height; ++i)
        {
            node->setNextNode(i, prev[i]->nextNode(i));
            prev[i]->setNextNode(i, node);
        }
    }
    
    struct Node
    {
        Key const key_;
        
        explicit Node(Key key):key_(key) {};
        
        Node* nextNode(int i)
        {
            assert(i >= 0);
            return next_[i].load(std::memory_order_acquire);
        }
        
        void setNextNode(int i, Node* pNode)
        {
            assert(i >= 0);
            next_[i].store(pNode, std::memory_order_release);
        }
    private :
        std::atomic<Node*> next_[1];
    };
    
private:
    Node * head_;
};

#endif /* SkipList_h */
