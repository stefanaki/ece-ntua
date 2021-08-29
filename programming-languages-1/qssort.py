import sys
from collections import deque

# qssort.py

# Giorgos Stefanakis
# Fragiskos Kondilis

def perform_Q(q, s, m):
    if q != []:
        new_q = q[:]
        new_s = s[:]
        new_m = m[:] + "Q"

        temp = new_q.pop(0)
        new_s.append(temp)

        states.append((new_q, new_s, new_m))
    return


def perform_S(q, s, m):
    if s != []:
        new_q = q[:]
        new_s = s[:]
        new_m = m[:] + "S"

        temp = new_s.pop()
        new_q.append(temp)


        states.append((new_q, new_s, new_m))

        if new_s == [] and len(new_m) % 2 == 0 and new_q == sorted(new_q):
            global Sorted
            Sorted = True
    return

lines = open(sys.argv[1]).read().splitlines()
input_list = [int(i) for i in lines[1].split()]
N = int(lines[0])
visited = set()
stack = list()

if input_list == sorted(input_list):
    Sorted = True
    print("empty")
    sys.exit()

Sorted = False
visited.add((str(input_list), str([])))
first_element = input_list.pop(0)
stack.append(first_element)
states = deque([(input_list, stack, "Q")])

while not Sorted:
    for i in range(len(states)):
        parent = states.popleft()
        if (str(parent[0]), str(parent[1])) not in visited:
            perform_Q(parent[0], parent[1], parent[2])
            perform_S(parent[0], parent[1], parent[2])
            visited.add((str(parent[0]), str(parent[1])))
            if Sorted:
                break

print(states.pop()[2])
