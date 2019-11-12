#include <iostream>
#include <vector>

using namespace std;

void printVector(const vector<int> &arr) {
	for(int i = 0; i < arr.size(); i++) {
		cout << arr[i];
		if(i < arr.size() - 1) {
			cout << ", ";
		}
	}
	cout << endl;
}

template<class T>
void printVector(const vector<T> &v, function<void(const T&)>  printEl) {
	for(int i = 0; i < v.size(); i++) {
		printEl(v[i]);
		if(i < v.size() - 1) {
			cout << ", ";
		}
	}
	cout << endl;
}

void printMatrix(const vector<vector<int>> &m) {
	for(int i = 0; i < m.size(); i++) {
		printVector(m[i]);
	}
}

// Definition for singly-linked list (from InterviewBit)
struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x = 0) : val(x), next(NULL) {} // on the website there is no default to 0
};

ListNode* generateList(const vector<int> &v) {
	ListNode* h = new ListNode();

	ListNode *aux = h;
	for(int i = 0; i < v.size(); ++i) {
		aux->val = v[i];
		if(i != v.size() - 1) {
			aux->next = new ListNode();
			aux = aux->next;
		}
	}

	return h;
}

/* Utility function to print a singly linked list */
void printList(ListNode* head) {
    ListNode* temp = head;
    while (temp != NULL) {
        cout << temp->val << " ";
        temp = temp->next;
    }
    cout << endl;
}

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

void printInorder(TreeNode* t) {
	if(t == nullptr) {
		cout << "#";
		return;
	}

	printInorder(t->left);
	cout << " " << t->val << " ";
	printInorder(t->right);
}

