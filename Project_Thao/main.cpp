#include <iostream>
#include "SkewHeap.h"

using namespace std;

int main()
{
    SkewHeap *tree = new SkewHeap();
    tree->Push(20);
    tree->Push(66);
    tree->Push(37);
    tree->Push(74);
    tree->Push(89);
    tree->Push(28);
    tree->Push(29);
    tree->Push(32);
    tree->Push(18);

    tree->Print();
    cout << "\n\n";
    cout << "Top is: " << tree->Top() << "\n";
    tree->Pop();
    tree->Print();
    cout << "\n";
    tree->PrintPreOrder();
    tree->PrintInOrder();
    tree->PrintPostOrder();

    while (tree->Size() > 1)
    {
        Node *tmp = tree->Pop();
    }
    cout << "\n\n";
    tree->Print();
    cout << "\n\n";

    delete tree;
    return 0;
}