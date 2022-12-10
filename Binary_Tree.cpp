#include <iostream>
#include <string>
#include <sstream>
#include <queue>

using namespace std;


class Node
{
public:
    int key{}; //use for addNode
    int data{};
    Node* left{};
    Node* right{};
    Node(int data, int key = 0) : data { data }
    {
    }
};
class BinaryTree
{
private:
    Node* root{};

protected:
    int getSizeRec(Node*); // Time: O(N), Space: O(N)
    int countTwoChildrenNodesRec(Node *); // Time: O(N), Space: O(N)
    int getHeightRec(Node *); // Time: O(N), Space: O(N)
    Node* maxNodeRec(Node*&); // Time: O(N), Space: O(N)
    string preOrderRec(Node*);
    string inOrderRec(Node*);
    string postOrderRec(Node*);
    int sumOfLeafsRec(Node*, int);
    int sumDigitPathRec(Node*, int);
    void longestPathSumRec(Node*, int sum, int len, int& maxSum, int& maxLen);
    int lowestAncestorRec(Node*, int, int);

public:
    BinaryTree() : root{ nullptr }
    {
    }
    int getSize();
    int countTwoChildrenNodes();
    int getHeight();
    Node* maxNode();
    void levelOrderTraverse();
    void addNode(string posFromRoot, int key, int data); //Time: O(L), Space: O(L)
    string preOrder();
    string inOrder();
    string postOrder();
    int sumOfLeafs();
    int sumDigitPath();
    int longestPathSum();
    int lowestAncestor(int, int);
};

int BinaryTree::getSizeRec(Node *node)
{
    if (!node)
    {
        return 0;
    }
    return 1 + getSizeRec(node->left) + getSizeRec(node->right);
}

int BinaryTree::countTwoChildrenNodesRec(Node *node)
{
    if (!node)
    {
        return 0;
    }
    if (node->left && node->right)
    {
        return 1 + countTwoChildrenNodesRec(node->left) + countTwoChildrenNodesRec(node->right);
    }
    else if (!node->left)
    {
        return countTwoChildrenNodesRec(node->right);
    }
    else
    {
        return countTwoChildrenNodesRec(node->left);
    }
}

int BinaryTree::getHeightRec(Node *node)
{
    if (!node)
    {
        return 0;
    }
    int maxLeft{ getHeightRec(node->left) };
    int maxRight{ getHeightRec(node->right) };
    return 1 + (maxLeft > maxRight ? maxLeft : maxRight);
}

Node* BinaryTree::maxNodeRec(Node *&node)
{
    if (!node)
    {
        return nullptr;
    }
    Node* maxLeft{ maxNodeRec(node->left) };
    Node* maxRight{ maxNodeRec(node->right) };
    Node* maxNode{ node };
    if (maxLeft && maxLeft->data > maxNode->data)
    {
        maxNode = maxLeft;
    }
    if (maxRight && maxRight->data > maxNode->data)
    {
        maxNode = maxRight;
    }
    return maxNode;
}

string BinaryTree::preOrderRec(Node* node)
{
    stringstream ss{};
    if (!node)
    {
        return ss.str();   
    }
    ss << node->data << " ";
    ss << preOrderRec(node->left);
    ss << preOrderRec(node->right);
    return ss.str();
}

string BinaryTree::inOrderRec(Node* node)
{
    stringstream ss{};
    if (!node)
    {
        return ss.str();
    }
    ss << inOrderRec(node->left);
    ss << node->data << " ";
    ss << inOrderRec(node->right);
    return ss.str();
}

string BinaryTree::postOrderRec(Node* node)
{
    stringstream ss{};
    if (!node)
    {
        return ss.str();
    }
    ss << postOrderRec(node->left);
    ss << postOrderRec(node->right);
    ss << node->data << " ";
    return ss.str();
}

int BinaryTree::sumOfLeafsRec(Node* node, int sum)
{
    if (!node)
    {
        return sum;
    }
    if (!node->left && !node->right)
    {
        sum += node->data;
        return sum;
    }
    return sumOfLeafsRec(node->left, sum) + sumOfLeafsRec(node->right, sum);
}

int BinaryTree::sumDigitPathRec(Node* node, int sum)
{
    if (!node)
    {
        return 0;
    }
    sum = (10 * sum + node->data) % 27022001;
    if (!node->left && !node->right)
    {
        return sum;
    }
    return sumDigitPathRec(node->left, sum) % 27022001 + sumDigitPathRec(node->right, sum) % 27022001;
}

void BinaryTree::longestPathSumRec(Node* node, int sum, int len, int& maxSum, int& maxLen)
{
    if (!node)
    {
        if (maxLen < len)
        {
            maxLen = len;
            maxSum = sum;
        }
        else if (maxLen == len && maxSum < sum)
        {
            maxSum = sum;
        }
        return;
    }
    sum += node->data;
    len += 1;
    longestPathSumRec(node->left, sum, len, maxSum, maxLen);
    longestPathSumRec(node->right, sum, len, maxSum, maxLen);
}

int BinaryTree::lowestAncestorRec(Node* node, int a, int b)
{
    if (!node)
    {
        return -1;
    }
    if (a == node->data || b == root->data)
    {
        return root->data;
    }
    int left{ lowestAncestorRec(node->left, a, b) };
    int right{ lowestAncestorRec(node->right, a, b) };
    if (left != -1 && right != -1)
    {
        return root->data;
    }
    return (left != -1 ? left : right);
}

int BinaryTree::getSize()
{
    return getSizeRec(root);	
}

int BinaryTree::countTwoChildrenNodes()
{
    return countTwoChildrenNodesRec(root);
}

int BinaryTree::getHeight()
{
    return getHeightRec(root);
}

Node* BinaryTree::maxNode()
{
    return maxNodeRec(root);   
}

void BinaryTree::levelOrderTraverse()
{
    queue<Node*> q;
    q.push(root);
    while (!q.empty())
    {
        Node* p{ q.front() };
        cout << p->data << " ";
        q.pop();
        if (p->left)
        {
            q.push(p->left);
        }
        if (p->right)
        {
            q.push(p->right);
        }
    }
}

void BinaryTree::addNode(string posFromRoot, int key, int data)
{
    if (posFromRoot == "")
    {
        root = new Node{ data, key };
        return;
    }
    Node* walker{ root };
    int l = posFromRoot.size();
    for (int i{ 0 }; i < l - 1; ++i)
    {
        if (!walker)
        {
            return;
        }
        if (posFromRoot[i] == 'L')
        {
            walker = walker->left;
        }
        if (posFromRoot[i] == 'R')
        {
            walker = walker->right;
        }
    }
    if (posFromRoot[l - 1] == 'L')
    {
        walker->left = new Node{ data, key };
    }
    if (posFromRoot[l - 1] == 'R')
    {
        walker->right = new Node{ data, key };
    }
}

string BinaryTree::preOrder()
{
    return preOrderRec(root);
}

string BinaryTree::inOrder()
{
    return inOrderRec(root);
}

string BinaryTree::postOrder()
{
    return postOrderRec(root);
}

int BinaryTree::sumOfLeafs()
{
    return sumOfLeafsRec(root, 0);
}

int BinaryTree::sumDigitPath()
{
    return sumDigitPathRec(root, 0);
}

int BinaryTree::longestPathSum()
{
    int maxSum{};
    int maxLen{};
    longestPathSumRec(root, 0, 0, maxSum, maxLen);
    return maxSum;
}

int BinaryTree::lowestAncestor(int a, int b)
{
    return lowestAncestorRec(root, a, b);
}