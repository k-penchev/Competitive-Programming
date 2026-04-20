#include <iostream>
#include <algorithm>
#include <vector>
#include <random>

struct Treap
{
    struct Node
    {
        int key;
        int priority;
        Node * left;
        Node * right;

        Node()
        {
            key = priority = -1;
            left = right = NULL;
        }

        Node(int _key)
        {
            key = _key;
            priority = rand();
            left = right = NULL;
        }
    };

    Node * root;

    std::pair<Node *, Node *> split(Node * root, int splitter)
    {
        if(!root)
        {
            return {NULL, NULL};
        }

        if(root->key < splitter)
        {
            auto result = split(root->right, splitter);
            root->right = result.first;   
            
            Node * a = root;
            Node * b = result.second;    
            return {a, b};
        }
        else
        {
            auto result = split(root->left, splitter);
            root->left = result.second;   
            
            Node * a = result.first;      
            Node * b = root;
            return {a, b};
        }
    }

    Node * merge(Node * a, Node * b)
    {
        if(!a) return b;
        if(!b) return a;

        if(a->priority > b->priority)
        {
            a->right = merge(a->right, b);
            return a;
        }
        else
        {
            b->left = merge(a, b->left);
            return b;
        }
    }

    void insert(int key)
    {
        Node * newNode = new Node(key);
        auto result = split(root, key);
        root = merge(merge(result.first, newNode), result.second);
    }
};

Treap treap;

void solve()
{
    
}

void fastIO()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);
}

int main()
{
    fastIO();
    solve();

    return 0;
}
