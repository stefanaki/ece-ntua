#include <cstring>
#include <iostream>

using namespace std;

struct subarraySum {
  long sum;
  int length;

  subarraySum(int s = 0, int l = 0) : sum(s), length(l) {}
};

int main(int argc, char **argv) {
  int N, K, i, j, k, start;
  int right;
  int result = -1;
  int *p, *sumsMap;
  subarraySum *prevSums;

  scanf("%d %d", &N, &K);

  p = new int[N];
  sumsMap = new int[K + 1];
  prevSums = new subarraySum[N];
  memset(sumsMap, -1, sizeof(int) * (K + 1));

  for (i = 0; i < N; ++i)
    scanf("%d", &p[i]);

  // Trivial cases:
  // 1) Exists p[i] = K, the result is of length 1
  // 2) Every element is greater than K, the result does not exist
  for (i = 0; i < N; ++i)
    if (p[i] == K) {
      printf("1\n");
      return 0;
    }

  start = 0;
  while (start < N && p[start] > K)
    ++start;

  if (start == N) {
    printf("-1\n");
    return 0;
  }

  sumsMap[0] = 0;
  right = 0;
  for (i = start; i < N; ++i) {
    long sum = 0;
    for (j = i; j < N; ++j) {
      sum += p[j];
      if (sum > K)
        break;
      if (sum <= K && sumsMap[K - sum] != -1) {
        if (result == -1 || (j - i + 1 + sumsMap[K - sum]) < result)
          result = j - i + 1 + sumsMap[K - sum];
      }
    }

    if (p[i] <= K) {
      for (k = right; k <= i; ++k) {
        long sum = prevSums[N - k - 1].sum + p[i];
        int length = prevSums[N - k - 1].length + 1;

        if (sum > K)
          ++right;
        else {
          prevSums[N - k - 1] = subarraySum(sum, length);
          if (sumsMap[sum] == -1 || length < sumsMap[sum]) {
            sumsMap[sum] = length;
          }
        }
      }
    }
  }

  printf("%d\n", result);

  delete[] p;
  delete[] sumsMap;
  delete[] prevSums;
  return 0;
}