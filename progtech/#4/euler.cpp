#include <iostream>

using namespace std;

int main() {
  int N, M, x, y, i;
  int counter = 0, start = 0, end = 0;
  int *deg;

  cin >> N >> M;
  deg = new int[N];

  for(i = 0; i < N; i++)
    deg[i] = 0;

  for(i = 0; i < M; i++) {
    cin >> x >> y;
    deg[x]++;
    deg[y]++;
  }

  for(i = 0; i < N; i++) {
    if(deg[i] % 2 != 0) {
      counter++;
      if(counter > 2) {
        cout << "IMPOSSIBLE" << endl;
        return 0;
      } else if(start == 0)
        start = i;
      else
        end = i;
    }
  }

  if(end == 0 && start == 0) {
    cout << "CYCLE" << endl;
    return 0;
  }

  if(end == 0 && start != 0) {
    cout << "IMPOSSIBLE" << endl;
    return 0;
  }

  if(start > end)
    cout << "PATH " << end << " " << start << endl;
  else
    cout << "PATH " << start << " " << end << endl;

  delete[] deg;
  return 0;
}
