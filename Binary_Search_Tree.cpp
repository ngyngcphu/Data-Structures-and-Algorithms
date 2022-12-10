#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

class Node
{
public:
    int data{};
    Node* left{};
    Node* right{};
    Node(int data) : data{ data }
    {
    }
};

class BinarySearchTree
{
private:
    Node* root{};

protected:
    bool isValidBSTRec(Node*, Node*, Node*); //Time: O(N), Space: O(N)
    bool addRec(Node*&, int); //Time: O(N), Space: O(H)
    bool removeRec(Node*&, int);
    int getMinNode(Node*);
    int getMaxNode(Node*);
    bool findRec(Node*, int);
    void sumRec(Node*, int l, int r, int& sum);
    int kthSmallestRec(Node*, int k, int& count);

public:
    BinarySearchTree() : root{ nullptr }
    {
    }
    bool isValidBST();
    bool add(int);
    bool remove(int);
    int getMin();
    int getMax();
    bool find(int);
    int sum(int, int);
    vector<int> levelAlterTraverse();
    int kthSmallest(int k);
    Node* subtreeWithRange(Node* root, int lo, int hi);
};

bool BinarySearchTree::isValidBSTRec(Node* node, Node* left, Node* right)
{
    if (!node)
    {
        return true;
    }
    if (left && node->data <= left->data)
    {
        return false;
    }
    if (right && node->data > right->data)
    {
        return false;
    }
    return isValidBSTRec(node->left, left, node) && isValidBSTRec(node->right, node, right);
}

bool BinarySearchTree::addRec(Node*& node, int value)
{
    if (!node)
    {
        node = new Node{ value };
        return true;
    }
    if (value < node->data)
    {
        return addRec(node->left, value);
    }
    else
    {
        return addRec(node->right, value);
    }
}

bool BinarySearchTree::removeRec(Node*& node, int value)
{
    if (!node)
    {
        return false;
    }
    if (value < node->data)
    {
        return removeRec(node->left, value);
    }
    else if (value > node->data)
    {
        return removeRec(node->right, value);
    }
    else
    {
        if (!node->left)
        {
            Node* tmp{ node };
            node = node->right;
            delete tmp;
            return true;
        }
        else if (!node->right)
        {
            Node* tmp{ node };
            node = node->left;
            delete tmp;
            return true;
        }
        else
        {
            Node* p{ node->left };
            while (p->right)
            {
                p = p->right;
            }
            node->data = p->data;
            return removeRec(node->left, p->data);
        }
    }
}

int BinarySearchTree::getMinNode(Node* node)
{
    if (!node)
    {
        return -1;
    }
    while (node->left)
    {
        node = node->left;
    }
    return node->data;
}

int BinarySearchTree::getMaxNode(Node* node)
{
    if (!node)
    {
        return -1;
    }
    while (node->right)
    {
        node = node->right;
    }
    return node->data;
}

bool BinarySearchTree::findRec(Node* node, int i)
{
    if (!node)
    {
        return false;
    }
    if (i < node->data)
    {
        return findRec(node->left, i);
    }
    else if (i > node->data)
    {
        return findRec(node->right, i);
    }
    return true;
}

void BinarySearchTree::sumRec(Node* node, int l, int r, int& sum)
{
    if (!node)
    {
        return;
    }
    if (l <= node->data && node->data <= r)
    {
        sum += node->data;
    }
    sumRec(node->left, l, r, sum);
    sumRec(node->right, l, r, sum);
}

int BinarySearchTree::kthSmallestRec(Node* node, int k, int& count)
{
    if (!node)
    {
        return -1;
    }
    int left { kthSmallestRec(node->left, k, count) };
    if (left != -1)
    {
        return left;
    }
    ++count;
    if (count == k)
    {
        return node->data;
    }
    return kthSmallestRec(node->right, k, count);
}

bool BinarySearchTree::isValidBST()
{
    return isValidBSTRec(root, nullptr, nullptr);
}

bool BinarySearchTree::add(int value)
{
    return addRec(root, value);
}

bool BinarySearchTree::remove(int value)
{
    return removeRec(root, value);
}

int BinarySearchTree::getMin()
{
    return getMinNode(root);
}

int BinarySearchTree::getMax()
{
    return getMaxNode(root);
}

bool BinarySearchTree::find(int i)
{
     return findRec(root, i);
}

int BinarySearchTree::sum(int l, int r)
{
    int sum{};
    sumRec(root, l, r, sum);
    return sum;
}

vector<int> BinarySearchTree::levelAlterTraverse()
{
    if (!root)
    {
        return {};
    }
    vector<int> ans;
    queue<Node*> q;
    q.push(root);
    bool flag{ false };
    while (!q.empty())
    {
        int size = q.size();
        vector<int> level;
        for (int i{ 0 }; i < q.size(); ++i)
        {
            Node* node{ q.front() };
            q.pop();
            level.push_back(node->data);
            if (node->left)
            {
                q.push(node->left);
            }
            if (node->right)
            {
                q.push(node->right);
            }
        }
        flag = !flag;
        if (!flag)
        {
            reverse(level.begin(), level.end());
        }
        for (int i{ 0 }; i < (int)level.size(); ++i)
        {
            ans.push_back(level[i]);
        }
    }
    return ans;
}

int BinarySearchTree::kthSmallest(int k)
{
    int count{};
    return kthSmallestRec(root, k, count);
}

Node* BinarySearchTree::subtreeWithRange(Node* root, int lo, int hi)
{
    if (!root)
    {
        return nullptr;   
    }
    root->left = subtreeWithRange(root->left, lo, hi);
    root->right = subtreeWithRange(root->right, lo, hi);
    if (root->data < lo)
    {
       Node* rChild = root->right;
       delete root;
       return rChild;
    }
    if (root->data > hi)
    {
       Node* lChild = root->left;
       delete root;
       return lChild;
    }
    return root;
}