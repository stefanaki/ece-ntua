#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct portal {
  int a;
  int b;
  int width;
};

struct universe {
  int parent;
  int rank;
};

bool comparePortals(const portal &p1, const portal &p2) {
  return p1.width < p2.width;
}

int findWithPathCompression(universe *u, int i) {
  if (u[i].parent == i)
    return i;
  else
    return u[i].parent = findWithPathCompression(u, u[i].parent);
}

void unionByRank(universe *u, int i, int j) {
  int iRoot = findWithPathCompression(u, i);
  int jRoot = findWithPathCompression(u, j);

  if (iRoot == jRoot)
    return;

  if (u[iRoot].rank < u[jRoot].rank) {
    u[iRoot].parent = jRoot;
  } else if (u[iRoot].rank > u[jRoot].rank) {
    u[jRoot].parent = iRoot;
  } else {
    u[iRoot].parent = jRoot;
    ++u[jRoot].rank;
  }

  return;
}

// N different Mortys/Universes,
// M available portals
int main(int argc, char **argv) {
  int N, M;
  int *mortys;
  int result = -1;
  portal *openPortals;
  universe *universes;

  scanf("%d %d", &N, &M);
  mortys = new int[N + 1];
  universes = new universe[N + 1];
  openPortals = new portal[M];

  for (int i = 1; i < N + 1; ++i) {
    scanf("%d", &mortys[i]);
    universes[i].parent = i;
    universes[i].rank = 0;
  }

  for (int i = 0; i < M; ++i)
    scanf("%d %d %d", &openPortals[i].a, &openPortals[i].b,
          &openPortals[i].width);

  if (!is_sorted(openPortals, openPortals + M, comparePortals))
    sort(openPortals, openPortals + M, comparePortals);

  // Binary search on openPortals
  int left = 0, right = M - 1;
  while (left <= right) {
    int mid = (left + right) / 2;

    for (int i = mid; i < M; ++i)
      unionByRank(universes, openPortals[i].a, openPortals[i].b);

    bool found = true;
    for (int i = 1; i < N + 1; ++i) {
      if (findWithPathCompression(universes, mortys[i]) !=
          findWithPathCompression(universes, i)) {
        found = false;
        break;
      }
    }

    if (found) {
      result = openPortals[mid].width;
      left = mid + 1;

      for (int i = 1; i < N + 1; ++i) {
        universes[i].parent = i;
        universes[i].rank = 0;
      }
    } else {
      right = mid - 1;
    }
  }

  cout << result << endl;

  delete[] mortys;
  delete[] openPortals;
  delete[] universes;
  return 0;
}
