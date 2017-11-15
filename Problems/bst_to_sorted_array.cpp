#include <iostream>
#include <vector>

using namespace std;

/*

 -- Problem: Convert a BST into a sorted array

*/

struct node
{
  int key;
  struct node *left, *right;
};

// A utility function to create a new BST node
struct node *newNode(int item)
{
    struct node *temp =  (struct node *)malloc(sizeof(struct node));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

/* A utility function to insert a new node with given key in BST */
struct node* insert(struct node* node, int key)
{
    /* If the tree is empty, return a new node */
    if (node == NULL) return newNode(key);

    /* Otherwise, recur down the tree */
    if (key < node->key)
        node->left  = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);

    /* return the (unchanged) node pointer */
    return node;
}

vector<int> fillArray(struct node* bst) {
    vector<int> sol;
    if(bst == NULL) return sol;

    vector<int> fromLeft = fillArray(bst->left);
    for(int i=0; i < fromLeft.size(); ++i) {
        sol.push_back(fromLeft[i]);
    }

    sol.push_back(bst->key);

    vector<int> fromRight = fillArray(bst->right);
    for(int i=0; i < fromRight.size(); ++i) {
        sol.push_back(fromRight[i]);
    }

    return sol;
}


int main()
{
    node* n = newNode(4);
    insert(n, 3);
    insert(n, 1);
    insert(n, 6);
    insert(n, 5);

    vector<int> sol = fillArray(n);

    for (int i = 0; i < sol.size(); ++i) {
        cout << sol[i] << " ";
    }

    return 0;
}