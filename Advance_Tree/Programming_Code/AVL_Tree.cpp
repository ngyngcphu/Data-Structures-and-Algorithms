#include <iostream>
#include <queue>

using namespace std;

enum BalanceValue
{
    LH = -1,
    EH = 0,
    RH = 1
};

template <class T>
class Node
{
public:
    T data;
    Node *left;
    Node *right;
    BalanceValue balance;
    Node(const T &val)
    {
        data = val;
        left = right = nullptr;
        balance = EH;
    }
};

template <class T>
class AVL
{
private:
    Node<T> *root;

protected:
    void printNSpace(int n)
    {
        for (int i = 0; i < n - 1; ++i)
        {
            cout << " ";
        }
    }

    int getHeightRec(Node *node)
    {
        if (!node)
        {
            return 0;
        }
        int leftHeight = getHeightRec(node->left);
        int rightHeight = getHeightRec(node->right);
        return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
    }

    Node<T> *rotateRight(Node<T> *&node)
    {
        Node<T> *temp = node->left;
        node->left = temp->right;
        temp->right = node;
        return temp;
    }
    Node<T> *rotateLeft(Node<T> *&node)
    {
        Node<T> *temp = node->right;
        node->right = temp->left;
        temp->left = node;
        return temp;
    }
    Node<T> *leftBalance(Node<T> *&node, bool &taller)
    {
        if (node->balance == EH)
        {
            node->balance = LH;
            taller = true;
        }
        else if (node->balance == RH)
        {
            node->balance = EH;
            taller = false;
        }
        else
        {
            if (node->left->balance == LH)
            {
                node = rotateRight(node);
                node->balance = EH;
                node->right->balance = EH;
                taller = false;
            }
            else if (node->left->balance == RH)
            {
                node->left = rotateLeft(node->left);
                node = rotateRight(node);
                if (node->balance == EH)
                {
                    node->left->balance = EH;
                    node->right->balance = EH;
                }
                else if (node->balance == LH)
                {
                    node->balance = EH;
                    node->left->balance = EH;
                    node->right->balance = RH;
                }
                else
                {
                    node->balance = EH;
                    node->left->balance = LH;
                    node->right->balance = EH;
                }
                taller = false;
            }
        }
        return node;
    }
    Node<T> *rightBalance(Node<T> *&node, bool &taller)
    {
        if (node->balance == EH)
        {
            node->balance = RH;
            taller = true;
        }
        else if (node->balance == LH)
        {
            node->balance = EH;
            taller = false;
        }
        else
        {
            if (node->right->balance == RH)
            {
                node = rotateLeft(node);
                node->balance = EH;
                node->left->balance = EH;
                taller = false;
            }
            else if (node->right->balance == LH)
            {
                node->right = rotateRight(node->right);
                node = rotateLeft(node);
                if (node->balance == EH)
                {
                    node->left->balance = EH;
                    node->right->balance = EH;
                }
                else if (node->balance == LH)
                {
                    node->balance = EH;
                    node->left->balance = EH;
                    node->right->balance = RH;
                }
                else
                {
                    node->balance = EH;
                    node->left->balance = LH;
                    node->right->balance = EH;
                }
                taller = false;
            }
        }
        return node;
    }
    Node<T> *removeLeftBalance(Node<T> *&node, bool &shorter)
    {
        if (node->balance == EH)
        {
            node->balance = LH;
            shorter = false;
        }
        else if (node->balance == RH)
        {
            node->balance = EH;
            shorter = true;
        }
        else
        {
            if (node->left->balance == LH)
            {
                node = rotateRight(node);
                node->balance = EH;
                node->right->balance = EH;
                shorter = true;
            }
            else if (node->left->balance == EH)
            {
                node = rotateRight(node);
                node->balance = RH;
                node->right->balance = LH;
                shorter = false;
            }
            else
            {
                node->left = rotateLeft(node->left);
                node = rotateRight(node);
                if (node->balance == EH)
                {
                    node->left->balance = EH;
                    node->right->balance = EH;
                }
                else if (node->balance == LH)
                {
                    node->balance = EH;
                    node->left->balance = EH;
                    node->right->balance = RH;
                }
                else 
                {
                    node->balance = EH;
                    node->left->balance = LH;
                    node->right->balance = EH;
                }
                shorter = true;
            }
        }
        return node;
    }
    Node<T> *removeRightBalance(Node<T> *&node, bool &shorter)
    {
        if (node->balance == EH)
        {
            node->balance = RH;
            shorter = false;
        }
        else if (node->balance == LH)
        {
            node->balance = EH;
            shorter = true;
        }
        else
        {
            if (node->right->balance == RH)
            {
                node = rotateLeft(node);
                node->balance = EH;
                node->left->balance = EH;
                shorter = true;
            }
            else if (node->right->balance == EH)
            {
                node = rotateLeft(node);
                node->balance = LH;
                node->left->balance = RH;
                shorter = false;
            }
            else
            {
                node->right = rotateRight(node->right);
                node = rotateLeft(node);
                if (node->balance == EH)
                {
                    node->left->balance = EH;
                    node->right->balance = EH;
                }
                else if (node->balance == LH)
                {
                    node->balance = EH;
                    node->left->balance = EH;
                    node->right->balance = RH;
                }
                else
                {
                    node->balance = EH;
                    node->left->balance = LH;
                    node->right->balance = EH;
                }
                shorter = true;
            }
        }
        return node;
    }
    Node<T> *insertRec(Node<T> *&node, const T &value, bool &taller)
    {
        if (!node)
        {
            node = new Node(value);
            taller = true;
            return node;
        }
        if (value < node->data)
        {
            node->left = insertRec(node->left, value, taller);
            if (taller)
            {
                node = leftBalance(node, taller);
            }
        }
        else
        {
            node->right = insertRec(node->right, value, taller);
            if (taller)
            {
                node = rightBalance(node, taller);
            }
        }
        return node;
    }
    Node<T> *removeRec(Node<T> *&node, const T &value, bool &shorter, bool &success)
    {
        if (!node)
        {
            success = false;
            shorter = false;
            return nullptr;
        }
        if (value < node->data)
        {
            node->left = removeRec(node->left, value, shorter, success);
            if (shorter)
            {
                node = removeRightBalance(node, shorter);
            }
        }
        else if (value > node->data)
        {
            node->right = removeRec(node->right, value, shorter, success);
            if (shorter)
            {
                node = removeLeftBalance(node, shorter);
            }
        }
        else
        {
            Node<T> *dltNode = node;
            if (!node->left)
            {
                node = node->right;
                delete dltNode;
                success = true;
                shorter = true;
            }
            else if (!node->right)
            {
                node = node->left;
                delete dltNode;
                success = true;
                shorter = true;
            }
            else
            {
                Node<T> *pMax = node->left;
                while (pMax->right)
                {
                    pMax = pMax->right;
                }
                node->data = pMax->data;
                node->left = removeRec(node->left, pMax->data, shorter, success);
                if (shorter)
                {
                    node = removeRightBalance(node, shorter);
                }
            }
        }
        return node;
    }

public:
    AVl()
    {
        this->root = nullptr;
    }
    int getHeight()
    {
        return getHeightRec(root);
    }
    void printTreeStructure()
    {
        
    }
    void insert(const T &value)
    {
        bool taller = false;
        insertRec(root, value, taller);
    }
    void remove(const T &value)
    {
        bool success = false;
        bool shorter = false;
        removeRec(root, value, shorter, success);
    }
};