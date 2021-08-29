#include <algorithm>
#include <iostream>
using namespace std;

int main() {
  int N, K, i, j, count, result = -1;
  int *a;

  cin >> N >> K;
  a = new int[N];
  for (int i = 0; i < N; ++i)
    cin >> a[i];

  i = 0;
  j = 1;
  count = 1;

  while (j < N) {
    if (a[j] - a[i] <= 2 * K) {
      ++count;
      ++j;
    } else {
      --count;
      ++i;
    }
    result = max(count, result);
  }

  cout << result << endl;

  delete[] a;
}
