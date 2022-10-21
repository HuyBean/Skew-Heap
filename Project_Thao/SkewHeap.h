#ifndef SKEW_HEAP
#define SKEW_HEAP
#include <iostream>

struct Node
{
    int data;
    Node *left;
    Node *right;
    Node(int d = 0, Node *l = 0, Node *r = 0);
    Node *Clone();
};

struct SkewHeap
{
    Node *root;
    int heap_size;

    SkewHeap();
    SkewHeap(int arr[], const int &n);

    int Size();
    bool Empty();

    void Push(int data);
    Node *Pop();
    int Top();
    void Print(std::ostream &out = (std::ostream &)std::cout);
    SkewHeap *Clone();

    void PrintPreOrder(std::ostream &out = (std::ostream &)std::cout);
    void PrintInOrder(std::ostream &out = (std::ostream &)std::cout);
    void PrintPostOrder(std::ostream &out = (std::ostream &)std::cout);

    void Clear();
};

Node *Merge(Node *left, Node *right);
SkewHeap *MergeTrees(SkewHeap *left, SkewHeap *right);
#endif
