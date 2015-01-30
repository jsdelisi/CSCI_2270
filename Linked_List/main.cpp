#include <iostream>

using namespace std;

struct node {
    int key;
    node *next;
};

class LinkedList {
    struct node {
        int key;
        node *next;
    };
    public:
        LinkedList();
        LinkedList(int i);
        LinkedList(int arr[]);
        node head();
        void add_to_end(int key);
        void add(int key, int index);
        int size();
        bool remove(int index);
        bool remove(node n);
};



int main()
{
    node *x = new node;
    node *head;
    head = x;
    x->key = 5;
    x->next = NULL;
    cout << x->key << endl;

    node *n1 = new node;
    n1->key = 6;
    x -> next = n1;
    cout << "key of n1: " << head->next->key << endl;
    return 0;
}
