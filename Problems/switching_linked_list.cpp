#include <iostream>
#include <utility>

using namespace std;

/*
  Given a linked list return a new one, switching begin and end nodes:

  ex:
  Input: L0 -> L1 -> L2 -> L3 -> L4
  Output: L0 -> L4 -> L1 -> L3 -> L2
*/

class Node {
 public:
  int val;
  Node* next;
  Node(int v = 0, Node* n = NULL): val(v), next(n) {}
  int size() {
    int count = 1;
    Node* tmp = next;
    while (tmp != NULL) {
      ++count;
      tmp = tmp->next;
    }
    return count;
  }
  void print() {
    cout << val << " ";
    Node* tmp = next;
    while (tmp != NULL) {
      cout << tmp->val << " ";
      tmp = tmp->next;
    }
    cout << endl;
  }
};

// Know this method by heart! (70% of the questions are linked lists!)
Node* inverse(Node* head) {
  Node* res = new Node();
  while (head != NULL) {
    Node* tmp = head->next;
    head->next = res->next;
    res->next = head;
    head = tmp;
  }
  return res->next;
}

pair<Node*, Node*> breakTwoHalves(Node* l) {
  int size = l->size();
  int middle = size/2; // index of the beginning of the 2nd half, counting from 0
  Node* h1 = l;
  Node* h2;
  Node* tmp = l;
  int count = 0;
  while (count <= middle-2) {
    tmp = tmp->next;
    ++count;
  }

  h2 = tmp->next;
  tmp->next = NULL;

  pair<Node*, Node*> res (h1, h2);
  return res;
}

// Merging into the first one, alternating positions
void merge(struct Node *p, struct Node *q) {
  struct Node *p_curr = p, *q_curr = q;
  struct Node *p_next, *q_next;

  // While there are available positions in p
  while (p_curr != NULL && q_curr != NULL) {
    // Save next pointers
    p_next = p_curr->next;
    q_next = q_curr->next;

    // Make q_curr as next of p_curr
    q_curr->next = p_next;  // Change next pointer of q_curr
    p_curr->next = q_curr;  // Change next pointer of p_curr

    // Just for the case that we are at the end of p but we still have one node from q to add
    if (p_next == NULL) {
      if (q_next != NULL) {
        p_curr = p_curr->next;
        p_curr->next = q_next;
      }
    }

    // Update current pointers for next iteration
    p_curr = p_next;
    q_curr = q_next;
  }
}

Node* switching(Node* l) {
  Node *h1, *h2;
  pair<Node*, Node*> halves;
  halves = breakTwoHalves(l);
  h1 = halves.first;
  h2 = halves.second;

  cout << "h1: ";
  h1->print();
  cout << "h2: ";
  h2->print();

  h2 = inverse(h2);
  cout << "inverse h2: ";
  h2->print();

  merge(h1, h2);
  return h1;
}


int main() {
  // Input: L0 -> L1 -> L2 -> L3 -> L4
  // Output: L0 -> L4 -> L1 -> L3 -> L2
  Node* l = new Node(0, new Node(1, new Node(2, new Node(3, new Node(4)))));
  cout << "Input: ";
  l->print();

  Node* res = switching(l);
  cout << endl << "Output: ";
  res->print();

  return 0;
}