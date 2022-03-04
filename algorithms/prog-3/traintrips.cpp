#include <iostream>
#include <set>
#include <vector>

#define D_MAX 10E3 + 1
#define S_MAX 10E9 + 1

using namespace std;

int N;
long unsigned int d = D_MAX;
unsigned long Q;
vector<unsigned long> distances, query(D_MAX, -1);
set<pair<unsigned long, int>> queue;

void dijkstra() {
  while (!queue.empty()) {
    pair<unsigned long, int> head = *queue.begin();
    int dist_sum = head.first;
    unsigned long current = head.second;

    queue.erase(head);

    for (auto d_i : distances) {
      int new_node = (current + d_i) % d;
      long unsigned int new_dist = dist_sum + d_i;

      if (new_dist < query[new_node] ||
          query[new_node] == (long unsigned int)-1) {
        queue.erase(make_pair(query[new_node], new_node));
        query[new_node] = new_dist;
        queue.insert(make_pair(query[new_node], new_node));
      }
    }
  }
}

int main() {
  cin >> N >> Q;
  for (int i = 0; i < N; ++i) {
    unsigned long d_i;
    cin >> d_i;
    distances.push_back(d_i);
    if (d_i < d) {
      d = d_i;
    }
  }

  query[0] = 0;
  queue.insert(make_pair(query[0], 0));
  dijkstra();

  for (long unsigned int i = 0; i < Q; ++i) {
    unsigned long q;
    cin >> q;
    if (query[q % d] > q)
      cout << "NO\n";
    else
      cout << "YES\n";
  }

  return 0;
}