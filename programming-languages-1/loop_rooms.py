#!/usr/bin/python3
# -*- coding: utf-8 -*-

# loop_rooms.py

# Giorgos Stefanakis
# Fragiskos Kondilis

import sys

def find_good_maze_rooms(i, j):
    global maze, visited, N, M, result
    if i - 1 >= 0:
        if maze[i - 1][j] == 'D' and visited[i - 1][j] == 0:
            result += 1
            visited[i - 1][j] = 1
            find_good_maze_rooms(i - 1, j)
    if j - 1 >= 0:
        if maze[i][j - 1] == 'R' and visited[i][j - 1] == 0:
            result += 1
            visited[i][j - 1] = 1
            find_good_maze_rooms(i, j - 1)
    if i + 1 < N:
        if maze[i + 1][j] == 'U' and visited[i + 1][j] == 0:
            result += 1
            visited[i + 1][j] = 1
            find_good_maze_rooms(i + 1, j)
    if j + 1 < M:
        if maze[i][j + 1] == 'L' and visited[i][j + 1] == 0:
            result += 1
            visited[i][j + 1] = 1
            find_good_maze_rooms(i, j + 1)
    return


sys.setrecursionlimit(100000)
lines = open(sys.argv[1]).read().splitlines()
(N, M) = map(int, lines[0].split())
maze = list(map(list, lines[1:]))
result = 0

visited = []
for i in range(N):
    col = []
    for j in range(M):
        col.append(0)
    visited.append(col)

for i in range(N):
    if maze[i][0] == 'L':
        visited[i][0] = 1
        result += 1
    if maze[i][M - 1] == 'R':
        visited[i][M - 1] = 1
        result += 1
for j in range(M):
    if maze[0][j] == 'U':
        visited[0][j] = 1
        result += 1
    if maze[N - 1][j] == 'D':
        visited[N - 1][j] = 1
        result += 1

for i in range(N):
    if visited[i][0] == 1:
        find_good_maze_rooms(i, 0)
    if visited[i][M - 1] == 1:
        find_good_maze_rooms(i, M - 1)
for j in range(M):
    if visited[0][j] == 1:
        find_good_maze_rooms(0, j)
    if visited[N - 1][j] == 1:
        find_good_maze_rooms(N - 1, j)

print(N * M - result)
