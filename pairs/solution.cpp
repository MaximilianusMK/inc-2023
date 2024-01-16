#include <bits/stdc++.h>
using namespace std;

const int kMaxLogSqrtA = 20;
const int kMaxSqrtA = 1 << kMaxLogSqrtA;

int even(long long x) {
  int ret = 0;
  for (int i = 0; i < kMaxLogSqrtA; ++i) {
    ret |= (x >> i) & (1 << i);
  }
  return ret;
}

// Subset transform
void zeta(vector<int> &a) {
  int N = a.size();
  for (int len = 1; len < N; len <<= 1) {
    for (int i = 0; i < N; i += len * 2) {
      for (int j = 0; j < len; ++j) {
        a[i + j + len] += a[i + j];
      }
    }
  }
}

int main() {
  int N;
  scanf("%d", &N);

  vector<int> A(N);
  vector<int> cnt(kMaxSqrtA);
  for (int i = 0; i < N; ++i) {
    long long a;
    scanf("%lld", &a);
    A[i] = even(a);
    ++cnt[A[i]];
  }

  zeta(cnt);

  long long ans = 0;
  for (int i = 0; i < N; ++i) {
    ans += cnt[kMaxSqrtA - 1 - A[i]];
    if (A[i] == 0) --ans;
  }
  ans /= 2;
  printf("%lld\n", ans);
  return 0;
}
