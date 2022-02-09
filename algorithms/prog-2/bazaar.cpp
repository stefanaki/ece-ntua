#include <climits>
#include <iostream>
#include <vector>

#define MAX_N 5001

using namespace std;

// Knapsack item structure used in the Knapsack problem implementation
struct knapsackItem {
  int weight;
  int price;

  knapsackItem(int w, int p) : weight(w), price(p) {}
};

int N, M;
vector<knapsackItem> A1, A2, A3, B1, B2, B3, C1, C2, C3;
int A[MAX_N] = {0}, B[MAX_N] = {0}, C[MAX_N] = {0};
int set1[MAX_N] = {0}, set2[MAX_N] = {0}, set3[MAX_N] = {0};

// In order to compute the minimum cost of buying exactly n items from
// a salesman using their i first offered packages we have to compute the
// following discrete Knapsack-like formula:
// dpArray[i, n] = min(dpArray[i - 1, n], dpArray[i - 1, n - w_i] + p_i)

// Knapsack implementation for the formula above
void knapsack(int *dpArray, const vector<knapsackItem> &items) {
  int totalWeight = 0;

  for (int i = 1; i <= N; ++i)
    dpArray[i] = INT_MAX;
  for (long unsigned int i = 0; i < items.size(); ++i) {
    int curWeight = items[i].weight, curPrice = items[i].price;
    totalWeight += items[i].weight;
    for (int j = min(N, totalWeight); j >= 1; --j) {
      if (j - curWeight < 0)
        dpArray[j] = min(dpArray[j], dpArray[0] + curPrice);
      else
        dpArray[j] = min(dpArray[j], dpArray[j - curWeight] + curPrice);
    }
  }
  return;
}

// After computing the minimum cost of buying 1 <= i <= N
// number of items of type A, B, C from the every salesman,
// we compute the minimum cost of buying 1 <= j <= N number
// of items from every salesman and create the set that
// combines items of specific type from all three Knapsacks
void createSet(int *set) {
  for (int i = 0; i <= N; ++i) {
    if (A[i] == INT_MAX || B[i] == INT_MAX || C[i] == INT_MAX) {
      set[i] = INT_MAX;
    } else {
      set[i] = A[i] + B[i] + C[i];
    }
  }
  return;
}

int main() {
  int q, p;
  string s;
  int res = INT_MAX;

  cin >> N >> M;

  for (int i = 0; i < M; ++i) {
    cin >> s >> q >> p;

    // Storing each seller's identical items in the same array
    if (s[0] == '1') {
      if (s[1] == 'A')
        A1.push_back(knapsackItem(q, p));
      else if (s[1] == 'B')
        B1.push_back(knapsackItem(q, p));
      else
        C1.push_back(knapsackItem(q, p));
    } else if (s[0] == '2') {
      if (s[1] == 'A')
        A2.push_back(knapsackItem(q, p));
      else if (s[1] == 'B')
        B2.push_back(knapsackItem(q, p));
      else
        C2.push_back(knapsackItem(q, p));
    } else {
      if (s[1] == 'A')
        A3.push_back(knapsackItem(q, p));
      else if (s[1] == 'B')
        B3.push_back(knapsackItem(q, p));
      else
        C3.push_back(knapsackItem(q, p));
    }
  }

  knapsack(A, A1);
  knapsack(B, B1);
  knapsack(C, C1);
  createSet(set1);
  knapsack(A, A2);
  knapsack(B, B2);
  knapsack(C, C2);
  createSet(set2);
  knapsack(A, A3);
  knapsack(B, B3);
  knapsack(C, C3);
  createSet(set3);

  for (int i = 0; i <= N; ++i) {
    for (int j = N - i; j >= 0; --j) {
      if (set1[i] == INT_MAX || set2[j] == INT_MAX ||
          set3[N - j - i] == INT_MAX)
        continue;
      if (res > set1[i] + set2[j] + set3[N - j - i])
        res = set1[i] + set2[j] + set3[N - j - i];
    }
  }

  if (res == INT_MAX)
    cout << -1 << endl;
  else
    cout << res << endl;
}
