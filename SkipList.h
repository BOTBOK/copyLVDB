//
//  SkipList.h
//  test
//
//  Created by oldman on 2020/4/25.
//  Copyright © 2020 oldman. All rights reserved.
//

#ifndef SkipList_h
#define SkipList_h
#include <atomic>
#include <assert.h>
#include <random>

#define MAX_HEIGHT (12)

template<typename Key, class Comparator>
class SkipList
{
private:
    Comparator compare_;
    const int kMaxHeight_;
    
    SkipList(SkipList&) = delete;
    SkipList &operator=(SkipList&) = delete;
    
    struct Node;
    
    /**
     链表（跳跃表）表头节点
     */
    Node *head_;
    
    /**
     生成随机数
     */
    int randomInt();
    
    /**
     找到与key值相等或者比key大的Node（恰好比key大，该node的前一个node比key小）
     param[in]        Key key值。
     param[out]      Node **prev 可以理解为Node* 数组，跳跃表每一层比key小的Node节点，所组成的数组
     */
    Node * findNodeOrGreaterNode(Key key, Node **prev);
    
    /**
     新建高度为height的Node节点
     param[in]      Key key值
     param[in]      int height跳跃表中该节点的高度
     */
    Node * newNode(Key key, int height);
    
public:
    
    class Interator
    {
        SkipList *list_;
        Node *node_;
    public:
        explicit Interator(SkipList *list):list_(list), node_(list_->head_->nextNode(0)){}
        
        void next()
        {
            node_ = node_->nextNode(0);
        }
        
        Node* getNode()
        {
            return node_;
        }
    };
    
    /**
     初始化函数
     param[in]  比较模版，类或者函数
     */
    explicit SkipList(Comparator comparator);
    
    /**
     插入key
     param[in] 插入key值
     */
    void insert(Key key);
};

template<typename Key, class Comparator>
struct SkipList<Key, Comparator>::Node
{
    Key key;
    explicit Node(Key tKey):key(tKey) {};
    Node *nextNode(int i)
    {
        assert(i >= 0);
        return next_[i].load(std::memory_order_acquire);
    }
    void setNextNode(Node *node, int i)
    {
        assert(i >= 0);
        next_[i].store(node, std::memory_order_release);
    }
private:
    std::atomic<Node*> next_[1];
};

template<typename Key, class Comparator>
/*此处使用typename是告诉编译器Node是一个类而不是成员变量*/
typename SkipList<Key, Comparator>::Node * SkipList<Key, Comparator>::newNode(Key key, int height)
{
    /**
     没有内存池，目前直接从堆上申请内存,
            申请内存有讲究啊，Node结构体的最后一个符号是automic<Node*>的数组，大小为1，可以看成指向automic<Node*>的指针，
            这边在Node的基础上申请了超出height-1的std::atomic<Node*>的内存空间，将Node结构体中的automic<Node*>数组扩展，大小为height
     */
    void *memArea = malloc(sizeof(Node) + sizeof(std::atomic<Node*>) * (height - 1));
    /*placement new 操作*/
    return new (memArea) Node(key);
}

/**
初始化函数
param[in]  比较模版，类或者函数
*/
template<typename Key, class Comparator>
SkipList<Key, Comparator>::SkipList(Comparator comparator):compare_(comparator), kMaxHeight_(MAX_HEIGHT)
{
    /*模版中的任何key，传0都可以*/
    head_ = newNode(0, kMaxHeight_);
    Node *tmpNode = nullptr;
    for(int i = 0; i < kMaxHeight_; ++i)
    {
        head_->setNextNode(tmpNode, i);
    }
}
  

template<typename Key, class Comparator>
typename SkipList<Key, Comparator>::Node * SkipList<Key, Comparator>::findNodeOrGreaterNode(Key key, Node **prev)
{
    /**定义prevNode和nextNode，key值在中间，将head_看成无穷小，nullptr看成无穷大*/
    Node *prevNode = head_;
    Node *nextNode = nullptr;
    
    int i = kMaxHeight_ - 1;
    while(true)
    {
        nextNode = prevNode->nextNode(i);
        if(nextNode == nullptr || compare_(key, nextNode->key) < 0)
        {
            if(nullptr != prev) {prev[i] = prevNode;}
        
            if(i == 0)
            {
                return nextNode;
            }
            else
            {
                --i;
            }
        }
        else
        {
            prevNode = nextNode;
        }
    }
}

template<typename Key, class Comparator>
void  SkipList<Key, Comparator>::insert(Key key)
{
    int height = randomInt();
    Node* prev[MAX_HEIGHT]; //栈上数据，初始化都为nullptr
    
    Node *x = newNode(key, height);
    
    findNodeOrGreaterNode(key, prev);
    
    for(int i = 0; i < height; ++i)
    {
        x->setNextNode(prev[i]->nextNode(i), i);
        prev[i]->setNextNode(x, i);
    }
}

template<typename Key, class Comparator>
inline int SkipList<Key, Comparator>::randomInt()
{
    std::random_device rd;
    int index = rd();
    index = index > 0? index: -index;
    return index % 11 + 1;
}

#endif /* SkipList_h */
