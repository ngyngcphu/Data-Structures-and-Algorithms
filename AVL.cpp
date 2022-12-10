#include <iostream>
#include <cmath>
#include <queue>

using namespace std;

enum BalanceValue
{
    LH = -1,
    EH = 0,
    RH = 1
};

void printNSpace(int n)
{
    for (int i{0}; i < n - 1; ++i)
    {
        cout << " ";
    }
}

void printInterger(int n)
{
    cout << n << " ";
}

template <class T>
class AVLTree
{
public:
    class Node;

private:
    Node *root;
    void rotateLeft(Node *&);
    void rotateRight(Node *&);
    bool balanceLeft(Node *&);
    bool balanceRight(Node *&);
    bool insertRec(Node *&, const T &value);

    bool deleteBalanceLeft(Node *&);
    bool deleteBalanceRight(Node *&);
    bool removeRec(Node *&, const T &value);

protected:
    int getHeightRec(Node *node)
    {
        if (!node)
        {
            return 0;
        }
        int lh{getHeightRec(node->pLeft)};
        int rh{getHeightRec(node->pRight)};
        return (lh > rh ? lh : rh) + 1;
    }

public:
    AVLTree() : root{nullptr} {}
    ~AVLTree() {}

    int getHeight()
    {
        return getHeightRec(root);
    }

    void printTreeStructure()
    {
        int height{getHeight()};
        if (!root)
        {
            cout << "nullptr\n";
            return;
        }
        queue<Node *> q;
        q.push(root);
        Node *temp{};
        int count{};
        int maxNode{1};
        int level{0};
        int space = pow(2, height);
        printNSpace(space / 2);
        while (!q.empty())
        {
            temp = q.front();
            q.pop();
            if (!temp)
            {
                cout << " ";
                q.push(nullptr);
                q.push(nullptr);
            }
            else
            {
                cout << temp->data;
                q.push(temp->pLeft);
                q.push(temp->pRight);
            }
            printNSpace(space);
            ++count;
            if (count == maxNode)
            {
                cout << endl;
                count = 0;
                maxNode *= 2;
                ++level;
                space /= 2;
                printNSpace(space / 2);
            }
            if (level == height)
            {
                return;
            }
        }
    }

    void insert(const T &value);
    void remove(const T &value);

    class Node
    {
    private:
        T data{};
        Node *pLeft{};
        Node *pRight{};
        BalanceValue balance{};
        friend class AVLTree<T>;

    public:
        Node(T value) : data{value}, pLeft{nullptr}, pRight{nullptr}, balance{EH}
        {
        }
        ~Node() {}
    };
};

template <class T>
void AVLTree<T>::rotateLeft(Node *&root)
{
    Node *temp{root->pRight};
    root->pRight = temp->pLeft;
    temp->pLeft = root;
    root = temp;
}

template <class T>
void AVLTree<T>::rotateRight(Node *&root)
{
    Node *temp{root->pLeft};
    root->pLeft = temp->pRight;
    temp->pRight = root;
    root = temp;
}

template <class T>
bool AVLTree<T>::balanceLeft(Node *&root)
{
    if (root->balance == EH)
    {
        root->balance = LH;
        return true;
    }
    else if (root->balance == RH)
    {
        root->balance = EH;
        return false;
    }
    else
    {
        if (root->pLeft->balance == LH)
        {
            rotateRight(root);
            root->balance = EH;
            root->pRight->balance = EH;
        }
        else if (root->pLeft->balance == RH)
        {
            rotateLeft(root->pLeft);
            rotateRight(root);
            if (root->balance == EH)
            {
                root->pLeft->balance = EH;
                root->pRight->balance = EH;
            }
            else if (root->balance == LH)
            {
                root->balance = EH;
                root->pLeft->balance = EH;
                root->pRight->balance = RH;
            }
            else
            {
                root->balance = EH;
                root->pLeft->balance = LH;
                root->pRight->balance = EH;
            }
        }
        return false;
    }
}

template <class T>
bool AVLTree<T>::balanceRight(Node *&root)
{
    if (root->balance == EH)
    {
        root->balance = RH;
        return true;
    }
    else if (root->balance == LH)
    {
        root->balance = EH;
        return false;
    }
    else
    {
        if (root->pRight->balance == RH)
        {
            rotateLeft(root);
            root->balance = EH;
            root->pLeft->balance = EH;
        }
        else if (root->pRight->balance == LH)
        {
            rotateRight(root->pRight);
            rotateLeft(root);
            if (root->balance == EH)
            {
                root->pLeft->balance = EH;
                root->pRight->balance = EH;
            }
            else if (root->balance == LH)
            {
                root->balance = EH;
                root->pLeft->balance = EH;
                root->pRight->balance = RH;
            }
            else
            {
                root->balance = EH;
                root->pLeft->balance = LH;
                root->pRight->balance = EH;
            }
        }
        return false;
    }
}

template <class T>
bool AVLTree<T>::insertRec(Node *&root, const T &value)
{
    if (!root)
    {
        root = new Node{value};
        return true;
    }
    if (value < root->data)
    {
        bool higher{insertRec(root->pLeft, value)};
        if (higher)
        {
            return balanceLeft(root);
        }
        else
        {
            return false;
        }
    }
    else
    {
        bool higher{insertRec(root->pRight, value)};
        if (higher)
        {
            return balanceRight(root);
        }
        else
        {
            return false;
        }
    }
}

template <class T>
bool AVLTree<T>::deleteBalanceLeft(Node *&root)
{
    if (root->balance == EH)
    {
        root->balance = LH;
        return false;
    }
    else if (root->balance == RH)
    {
        root->balance = EH;
        return true;
    }
    else
    {
        if (root->pLeft->balance == LH)
        {
            rotateRight(root);
            root->balance = EH;
            root->pRight->balance = EH;
            return true;
        }
        else if (root->pLeft->balance == RH)
        {
            rotateLeft(root->pLeft);
            rotateRight(root);
            if (root->balance == EH)
            {
                root->pLeft->balance = EH;
                root->pRight->balance = EH;
            }
            else if (root->balance == LH)
            {
                root->balance = EH;
                root->pLeft->balance = EH;
                root->pRight->balance = RH;
            }
            else
            {
                root->balance = EH;
                root->pLeft->balance = LH;
                root->pRight->balance = EH;
            }
            return true;
        }
        else
        {
            rotateRight(root);
            root->balance = RH;
            root->pRight->balance = LH;
        }
        return false;
    }
}

template <class T>
bool AVLTree<T>::deleteBalanceRight(Node *&root)
{
    if (root->balance == EH)
    {
        root->balance = RH;
        return false;
    }
    else if (root->balance == LH)
    {
        root->balance = EH;
        return true;
    }
    else
    {
        if (root->pRight->balance == RH)
        {
            rotateLeft(root);
            root->balance = EH;
            root->pLeft->balance = EH;
            return true;
        }
        else if (root->pRight->balance == LH)
        {
            rotateRight(root->pRight);
            rotateLeft(root);
            if (root->balance == EH)
            {
                root->pLeft->balance = EH;
                root->pRight->balance = EH;
            }
            else if (root->balance == LH)
            {
                root->balance = EH;
                root->pLeft->balance = EH;
                root->pRight->balance = RH;
            }
            else
            {
                root->balance = EH;
                root->pLeft->balance = LH;
                root->pRight->balance = EH;
            }
            return true;
        }
        else
        {
            rotateLeft(root);
            root->balance = LH;
            root->pLeft->balance = RH;
            return false;
        }
    }
}

template <class T>
bool AVLTree<T>::removeRec(Node *&root, const T &value)
{
    if (!root)
    {
        return false;
    }
    if (value < root->data)
    {
        bool shorter{removeRec(root->pLeft, value)};
        if (shorter)
        {
            return balanceRight(root);
        }
        else
        {
            return false;
        }
    }
    else if (value > root->data)
    {
        bool shorter{removeRec(root->pRight, value)};
        if (shorter)
        {
            return balanceLeft(root);
        }
        else
        {
            return false;
        }
    }
    else
    {
        Node *dltNode{root};
        if (!root->pLeft)
        {
            root = root->pRight;
            delete dltNode;
            return true;
        }
        else if (!root->pRight)
        {
            root = root->pLeft;
            delete dltNode;
            return true;
        }
        else
        {
            Node *p{root->pLeft};
            while (p->pRight)
            {
                p = p->pRight;
            }
            root->data = p->data;
            bool shorter{removeRec(root->pLeft, p->data)};
            if (shorter)
            {
                return balanceRight(root);
            }
            else
            {
                return false;
            }
        }
    }
}

template <class T>
void AVLTree<T>::insert(const T &value)
{
    insertRec(root, value);
}

template <class T>
void AVLTree<T>::remove(const T &value)
{
    removeRec(root, value);
}

int main()
{
    // AVLTree<int> avl{};
    // for (int i{ 0 }; i < 9; ++i)
    // {
    //     avl.insert(i);
    // }
    // avl.printTreeStructure();

    // AVLTree<int> avl{};
    // for (int i{ 10 }; i >= 0; --i)
    // {
    //     avl.insert(i);
    // }
    // avl.printTreeStructure();

    // AVLTree<int> avl{};
    // int arr[]{10, 52, 98, 32, 68, 92, 40, 13, 42, 63};
    // for (int i{0}; i < 10; ++i)
    // {
    //     avl.insert(arr[i]);
    // }
    // avl.remove(10);
    // avl.printTreeStructure();

    AVLTree<int> avl{};
    int arr[] = {10, 52, 98, 32, 68, 92, 40, 13, 42, 63, 99, 100};
    for (int i{0}; i < 12; ++i)
    {
        avl.insert(arr[i]);
    }
    avl.remove(13);
    avl.printTreeStructure();
}