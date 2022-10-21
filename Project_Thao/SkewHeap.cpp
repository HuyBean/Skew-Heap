#include "SkewHeap.h"

/*---Node---*/
Node::Node(int d, Node *l, Node *r)
{
    data = d;
    left = l;
    right = r;
}

Node *Node::Clone()
{
    Node *result = new Node(data);
    if (left)
    {
        result->left = left->Clone();
    }
    if (right)
    {
        result->right = right->Clone();
    }
    return result;
}

/*---SkewHeap---*/
SkewHeap::SkewHeap()
{
    root = 0;
    heap_size = 0;
}

SkewHeap::SkewHeap(int arr[], const int &n)
{
    root = 0;
    heap_size = 0;
    for (int i = 0; i < n; ++i)
    {
        Push(arr[i]);
    }
}

int SkewHeap::Size()
{
    return heap_size;
}

bool SkewHeap::Empty()
{
    return !heap_size;
}

void SkewHeap::Push(int data)
{
    Node *new_node = new Node(data);
    if (Empty())
    {
        root = new_node;
        heap_size++;
    }
    else
    {
        root = Merge(root, new_node);
        heap_size++;
    }
}

Node *SkewHeap::Pop()
{
    Node *result = root;

    if (Empty())
    {
        return 0;
    }

    if (heap_size == 1)
    {
        root = 0;
        heap_size--;
        return result;
    }

    if (!root->right)
    {
        root = root->left;
    }
    else
    {
        root = Merge(root->left, root->right);
    }

    result->left = 0;
    result->right = 0;

    heap_size--;

    return result;
}

int SkewHeap::Top()
{
    return root->data;
}

int GetLevel(Node *root)
{
    if (!root)
    {
        return 0;
    }
    int left = GetLevel(root->left);
    int right = GetLevel(root->right);
    return 1 + ((left > right) ? left : right);
}

#include <queue>
// Using BFS with queue
void SkewHeap::Print(std::ostream &out)
{
    std::queue<Node *> node_queue;
    int id = 0;
    int exp = 1;
    int level = 1;
    int max_level = GetLevel(root);
    node_queue.push(root);
    Node *current;

    while (level <= max_level)
    {
        id++;
        current = node_queue.front();
        node_queue.pop();

        if (!current)
        {
            out << "? ";
            node_queue.push(0);
            node_queue.push(0);
        }
        else
        {
            out << current->data << " ";
            node_queue.push(current->left);
            node_queue.push(current->right);
        }
        if (id == exp)
        {
            out << "\n";
            id = 0;
            exp *= 2;
            level++;
        }
    }
}

SkewHeap *SkewHeap::Clone()
{
    SkewHeap *result = new SkewHeap();
    if (Empty())
    {
        return result;
    }
    result->root = root->Clone();
    result->heap_size = Size();
    return result;
}

void WritePreOrder(Node *p, std::ostream &out)
{
    if (!p)
    {
        return;
    }
    out << p->data << " ";
    WritePreOrder(p->left, out);
    WritePreOrder(p->right, out);
}
void SkewHeap::PrintPreOrder(std::ostream &out)
{
    WritePreOrder(root, out);
    out << "\n";
}

void WriteInOrder(Node *p, std::ostream &out)
{
    if (!p)
    {
        return;
    }
    WriteInOrder(p->left, out);
    out << p->data << " ";
    WriteInOrder(p->right, out);
}

void SkewHeap::PrintInOrder(std::ostream &out)
{
    WriteInOrder(root, out);
    out << "\n";
}

void WritePostOrder(Node *p, std::ostream &out)
{
    if (!p)
    {
        return;
    }
    WritePostOrder(p->left, out);
    WritePostOrder(p->right, out);
    out << p->data << " ";
}

void SkewHeap::PrintPostOrder(std::ostream &out)
{
    WritePostOrder(root, out);
    out << "\n";
}

void ClearNode(Node *node)
{
    if (!node)
    {
        return;
    }
    ClearNode(node->left);
    ClearNode(node->right);
    delete node;
}

void SkewHeap::Clear()
{
    if (!root || Empty())
    {
        return;
    }
    ClearNode(root);
    root = 0;
    heap_size = 0;
}

void Swap(Node *&a, Node *&b)
{
    Node *tmp = a;
    a = b;
    b = tmp;
}

Node *Merge(Node *left, Node *right)
{
    Node *root = (left->data < right->data) ? left : right;
    Node *another = (left->data < right->data) ? right : left;
    if (!root->right)
    {
        root->right = another;
    }
    else
    {
        root->right = Merge(root->right, another);
    }
    Swap(root->left, root->right);
    return root;
}

SkewHeap *MergeTrees(SkewHeap *left, SkewHeap *right)
{
    SkewHeap *result = new SkewHeap();
    if (!left)
        return right->Clone();
    if (!right)
        return left->Clone();

    left = left->Clone();
    right = right->Clone();
    result->heap_size = left->Size() + right->Size();
    result->root = Merge(left->root, right->root);

    delete left;
    delete right;
    return result;
}
