#include <iostream>
#include <vector>
using namespace std;

// Covid times. Only sit in  train at minimum distance of 1 from other person.
// Among possible seats, choose randomly one.
// Question: give expected number of passangers, and the complexity as well.

// eg: [0, 0, 0], n = 3.
// 3 possible places to seat, each with probability 1/3.
// [1, 0, 0] -> [1, 0, 1] = 2 passangers
// [0, 1, 0] = 1 passanger
// [0, 0, 1] -> [1, 0, 1] = 2 passangers
// That gives:
// Expected = 2*1/3 + 1/3 + 2*1/3 = 5/3 ~= 1.6667

// First approach: backtracking.
// n * (n-2) * () ... that is O(n!) more or less, or n^(n/2)
// better: O((n!)^(1/2))
// Even with memoization it is bad.
// But can do better, other approach below dealing only with number of seats n.
bool CanSeat(const vector<int>& train, int pos) {
  if (train[pos]) {
    return false;
  }
  if(pos > 0 && train[pos-1]) {
    return false;
  }
  if(pos+1 < int(train.size()) && train[pos+1]) {
    return false;
  }

  return true;
}

double ExpectedNumber(vector<int>& train) {
  double acc_child = 0;
  int n_child = 0;
  int n_passengers = 0;
  for (int i = 0; i < int(train.size()); ++i) {
    if (train[i]) {
      ++n_passengers;
    }
    if (!CanSeat(train, i)) {
      continue;
    }
    train[i] = 1;
    ++n_child;
    acc_child += ExpectedNumber(train);
    train[i] = 0;
  }

  if (!n_child) {
    return n_passengers;
  }

  return acc_child/n_child;
}

// Better approach below.
// Size of the train is n.
// Complexidade da PD: tamanho do cache * time de calcular uma cell
//   eg: se n * m o tamanho de memo, e cada vez vc itera n, complexidade final é O(m * n^2)
// Aqui abaixo: O(n^2) acredito.
double ExpectedNumber(int n, vector<double>& memo) {
  if (n <= 0) {
    return 0;
  }

  if(memo[n]) {
    return memo[n];
  }
  
  double acc_child = 0;
  for (int i = 0; i < n; ++i) {
    // If person sits at position i, it is like train of size i-1 to its left and size n-i-2 to its right, plus 1 for the person sitting there.
    acc_child += ExpectedNumber(i-1, memo) + ExpectedNumber(n-i-2, memo) + 1;
  }

  memo[n] = acc_child / n;
  return memo[n];
}

int main() {
  int size_train = 3;
  vector<int> train(size_train, 0);
  cout << "Ans: " << ExpectedNumber(train) << endl;

  vector<double> memo(size_train+1, 0);
  cout << "Ans2: " << ExpectedNumber(size_train, memo) << endl;
  return 0;
}
