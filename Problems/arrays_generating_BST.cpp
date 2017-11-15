#include <iostream>
#include <vector>
#include <algorithm>

/*

 -- Problem statement: Find all the possible arrays that can generate a given BST

 (Problem 4.9 of Cracking the Coding Interview - 6th Edition)

*/

using namespace std;

struct node
{
  int data;
  struct node *left, *right;
};

// A utility function to create a new BST node
struct node *newNode(int item)
{
    struct node *temp =  (struct node *)malloc(sizeof(struct node));
    temp->data = item;
    temp->left = temp->right = NULL;
    return temp;
}

/* A utility function to insert a new node with given data in BST */
struct node* insert(struct node* node, int data)
{
    /* If the tree is empty, return a new node */
    if (node == NULL) return newNode(data);

    /* Otherwise, recur down the tree */
    if (data < node->data)
        node->left  = insert(node->left, data);
    else if (data > node->data)
        node->right = insert(node->right, data);

    /* return the (unchanged) node pointer */
    return node;
}

void weave(vector<int> v1, vector<int> v2, vector<int> curr, vector<vector<int>> &sols) {
    bool b1 = v1.empty();
    bool b2 = v2.empty();

    if(b1 & b2) {
        sols.push_back(curr);
        return;
    }
    if(!b1) {
        int i1 = v1.back();
        v1.pop_back();
        curr.push_back(i1);
        weave(v1, v2, curr, sols);

        v1.push_back(i1);
        curr.pop_back();
    }
    if(!b2) {
        int i2 = v2.back();
        v2.pop_back();
        curr.push_back(i2);
        weave(v1, v2, curr, sols);
    }
}

vector<vector<int>> getPossibilities(node* bst) {
    vector<vector<int>> sol;
    int root = bst->data;

    if(bst->left == NULL && bst->right == NULL) {
        vector<int> v;
        v.push_back(root);
        sol.push_back(v);
        return sol;
    }

    vector<vector<int>> fromLeft = getPossibilities(bst->left);
    vector<vector<int>> fromRight = getPossibilities(bst->right);

    for(int i=0; i<fromLeft.size(); ++i)
        for(int j=0; j<fromRight.size(); ++j){
            vector<vector<int>> partial;
            vector<int> curr;
            weave(fromLeft[i], fromRight[j], curr, partial);
            for(int k=0; k<partial.size(); ++k){
                partial[k].push_back(root);
                sol.push_back(partial[k]);
            }
        }

    return sol;
}

int main () {
    node* bst = newNode(2);
    insert(bst, 1);
    insert(bst, 3);
    vector<vector<int>> solution;

    solution = getPossibilities(bst);

    cout << "Size of the solution: " << solution.size() << endl;
    cout << "And the possible arrays are: " << endl;

    for(vector<int> v : solution) {
        reverse(v.begin(), v.end());
        for(int i : v) {
            cout << i << " ";
        }
        cout << endl;
    }

    return 0;
}
