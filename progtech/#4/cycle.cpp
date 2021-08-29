#include <iostream>
#include <list>
#include <vector>

using namespace std;

class Graph {
protected:
  int V;
  list<int> *adj;

  bool isCyclicUtil(int v, bool visited[], int stack[], int &k, int &start) const {
    if(!visited[v]) {
      visited[v] = true;
      stack[k] = v;
      k++;
    }

    list<int>::iterator i;
    for(i = adj[v].begin(); i != adj[v].end(); ++i) {
      if(!visited[*i] && isCyclicUtil(*i, visited, stack, k, start))
        return true;
      else {
        for(int j = 0; j < k; j++)
          if(stack[j] == *i) {
            start = j;
            return true;
          }
      }
    }

    stack[v] = -1;
    k--;
    return false;
  }

public:
  Graph(int V) : V(V), adj(new list<int>[V]) {}

  ~Graph() { delete[] adj; }

  void addEdge(int u, int v) { adj[u].push_back(v); }

  bool cycle(vector<int> &path) const {
    bool visited[V];
    int stack[V];

    for(int i = 0; i < V; i++) {
      visited[i] = false;
      stack[i] = -1;
    }

    int start = 0;

    for(int i = 0; i < V; i++) {
      int k = 0;
      if(isCyclicUtil(i, visited, stack, k, start)) {
        for(int j = start; j < k; j++)
          path.push_back(stack[j]);
        return true;
      }
    }

    return false;
  }
};

#ifndef CONTEST

int main() {
  int V, E;
  cin >> V >> E;
  Graph g(V);
  for(int i = 0; i < E; i++) {
    int u, v;
    cin >> u >> v;
    g.addEdge(u, v);
  }
  vector<int> path;
  bool c = g.cycle(path);
  if(c) {
    cout << "CYCLE: ";
    for(unsigned i = 0; i < path.size(); i++)
      cout << path[i] << (i == path.size() - 1 ? "\n" : " ");
  } else {
    cout << "NO CYCLE" << endl;
  }
}

#endif

