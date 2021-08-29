#include <fstream>
#include <iostream>
#include <vector>

/*
 * loop_rooms.cpp
 */

 /*
  * Giorgos Stefanakis
  * Fragiskos Kondilis
  */

using namespace std;

// recursive function that explores every room of
// the maze which leads to a good room (dfs logic)
void find_good_maze_rooms(vector<vector<char>> &m, vector<vector<bool>> &v,
                          int i, int j, const int &rows, const int &cols,
                          int &r) {
  if (i - 1 >= 0) {
    if (m[i - 1][j] == 'D' && !v[i - 1][j]) {
      ++r;
      v[i - 1][j] = true;
      find_good_maze_rooms(m, v, i - 1, j, rows, cols, r);
    }
  }
  if (j - 1 >= 0) {
    if (m[i][j - 1] == 'R' && !v[i][j - 1]) {
      ++r;
      v[i][j - 1] = true;
      find_good_maze_rooms(m, v, i, j - 1, rows, cols, r);
    }
  }
  if (i + 1 < rows) {
    if (m[i + 1][j] == 'U' && !v[i + 1][j]) {
      ++r;
      v[i + 1][j] = true;
      find_good_maze_rooms(m, v, i + 1, j, rows, cols, r);
    }
  }
  if (j + 1 < cols) {
    if (m[i][j + 1] == 'L' && !v[i][j + 1]) {
      ++r;
      v[i][j + 1] = true;
      find_good_maze_rooms(m, v, i, j + 1, rows, cols, r);
    }
  }
}

int main(int argc, char **argv) {
  int N, M, i, j, result = 0;
  char x;
  vector<vector<char>> maze;
  vector<vector<bool>> visited;
  ifstream file;
  file.open(argv[1]);

  if (!(file.is_open()))
    return 1;

  while (!file.eof()) {
    file >> N >> M;
    for (i = 0; i < N; ++i) {
      vector<char> temp1;
      vector<bool> temp2;
      for (j = 0; j < M; ++j) {
        file >> x;
        temp1.push_back(x);
        temp2.push_back(false);
      }
      maze.push_back(temp1);
      visited.push_back(temp2);
    }
  }

  for (i = 0; i < N; ++i) { // checking for good rooms on first and last columns
    if (maze[i][0] == 'L') {
      visited[i][0] = true;
      ++result;
    }
    if (maze[i][M - 1] == 'R') {
      visited[i][M - 1] = true;
      ++result;
    }
  }

  for (j = 0; j < M; ++j) { // checking for good rooms on first and last rows
    if (maze[0][j] == 'U') {
      visited[0][j] = true;
      ++result;
    }
    if (maze[N - 1][j] == 'D') {
      visited[N - 1][j] = true;
      ++result;
    }
  }

  for (i = 0; i < N; ++i) {
    if (visited[i][0] == true)
      find_good_maze_rooms(maze, visited, i, 0, N, M, result);
    if (visited[i][M - 1] == true)
      find_good_maze_rooms(maze, visited, i, M - 1, N, M, result);
  }

  for (j = 0; j < M; ++j) {
    if (visited[0][j] == true)
      find_good_maze_rooms(maze, visited, 0, j, N, M, result);
    if (visited[N - 1][j] == true)
      find_good_maze_rooms(maze, visited, N - 1, j, N, M, result);
  }

  result = N * M - result;
  cout << result << endl;

  file.close();
  return 0;
}
