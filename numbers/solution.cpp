#include <bits/stdc++.h>
using namespace std;

using Poly = vector<int>;

const int MOD = 998244353;

int power(int x, int y) {
  int ret = 1;
  for (; y; y >>= 1) {
    if (y & 1) ret = 1LL * ret * x % MOD;
    x = 1LL * x * x % MOD;
  }
  return ret;
}

namespace FFT {

const int LN = 21;
const int N = 1 << LN;

const int PRIMITIVE_ROOT = 3; // Primitive root modulo `MOD`.

int root[N];

void init_fft() {
  const int UNITY = power(PRIMITIVE_ROOT, (MOD-1) >> LN);
  root[0] = 1;
  for (int i = 1; i < N; ++i) {
    root[i] = 1LL * UNITY * root[i-1] % MOD;
  }
}

// n is the length of polynom
void fft(int n, vector<int> &a, bool invert) {
  for (int i = 1, j = 0; i < n; ++i) {
    int bit = n >> 1;
    for (; j & bit; bit >>= 1) j ^= bit;
    j ^= bit;
    if (i < j) swap(a[i], a[j]);
  }

  for (int len = 2; len <= n; len <<= 1) {
    int wlen = (invert ? root[N - N/len] : root[N/len]);
    for (int i = 0; i < n; i += len) {
      int w = 1;
      for (int j = 0; j < len >> 1; ++j) {
        int u = a[i + j], v = 1LL * a[i + j + len/2] * w % MOD;

        a[i + j] = (u + v) % MOD;
        a[i + j + len/2] = (u - v + MOD) % MOD;
        w = 1LL * w * wlen % MOD;
      }
    }
  }

  if (invert) {
    int inv = power(n, MOD-2);
    for (int i = 0; i < n; ++i) a[i] = 1LL * a[i] * inv % MOD;
  }
}

} // namespace FFT

Poly multiply_small(Poly a, Poly b) {
  Poly c(a.size() + b.size() - 1);
  for (int i = 0; i < a.size(); ++i) {
    for (int j = 0; j < b.size(); ++j) {
      c[i+j] = (1LL * a[i] * b[j] + c[i+j]) % MOD;
    }
  }
  return c;
}

vector<int> multiply_large(vector<int> a, vector<int> b) {
  int deg = a.size() + b.size() - 2;
  int len = (deg == 0 ? 1 : 1 << (32 - __builtin_clz(deg)));
  a.resize(len); b.resize(len);
  FFT::fft(len, a, false); FFT::fft(len, b, false);
  a.resize(len);
  for (int i = 0; i < len; ++i) a[i] = 1LL * a[i] * b[i] % MOD; 
  FFT::fft(len, a, true);
  a.resize(deg + 1);
  return a;
}

Poly operator * (Poly a, Poly b) {
  if (1LL * a.size() * b.size() <= 5000) return multiply_small(a, b);
  return multiply_large(a, b);
}

Poly operator - (Poly a, Poly b) {
  if (a.size() < b.size()) a.resize(b.size());
  for (int i = 0; i < b.size(); ++i) a[i] = (a[i] - b[i] + MOD) % MOD;
  return a;
}

Poly differentiate(Poly a) {
  for (int i = 0; i + 1 < a.size(); ++i) a[i] = 1LL * a[i + 1] * (i + 1) % MOD;
  a.pop_back();
  return a;
}

Poly integral(Poly a) {
  a.resize(a.size() + 1);
  for (int i = (int) a.size() - 1; i > 0; --i) a[i] = 1LL * a[i - 1] * power(i, MOD-2) % MOD;
  a[0] = 0;
  return a;
}

// Q' = 2Q - PQ^2
Poly inverse(int n, Poly a) {
  a.resize(n*2);
  Poly res = {power(a[0], MOD-2)};
  for (int len = 2; len < n << 1; len <<= 1) {
    vector<int> tmp = res * res * Poly(a.begin(), a.begin() + len);
    res.resize(len);
    for (int i = 0; i < len; ++i) res[i] = (2LL * res[i] - tmp[i] + MOD) % MOD;
  }
  res.resize(n);
  return res;
}

// integral P'/P
Poly log(int n, Poly a) {
  vector<int> ret = differentiate(a) * inverse(n, a);
  ret.resize(n-1);
  return integral(ret);
}

// Q' = Q - (log(Q) - P) Q
Poly exp(int n, Poly a) {
  // Assume a[0] = 0
  Poly res = {1};
  a.resize(n*2);
  for (int len = 2; len < n << 1; len <<= 1) {
    res = res - (log(len, res) - Poly(a.begin(), a.begin() + len)) * res;
    res.resize(len);
  }
  res.resize(n);
  return res;
}

int main() {
  FFT::init_fft();
  int N, K;
  scanf("%d %d", &N, &K);
  K -= N;

  vector<int> inv(N + K), fact(N + K), ifact(N + K);
  fact[0] = ifact[0] = 1;
  for (int i = 1; i < N + K; ++i) {
    inv[i] = power(i, MOD - 2);
    fact[i] = 1LL * fact[i - 1] * i % MOD;
    ifact[i] = 1LL * ifact[i - 1] * inv[i] % MOD;
  }

  auto C = [&](int n, int k) {
    if (k < 0 || k > n) return 0;
    int res = 1LL * ifact[k] * ifact[n - k] % MOD * fact[n] % MOD;
    return res;
  };

  Poly P(K + 1);
  for (int i = 1; i <= N; ++i) {
    for (int j = i; j <= K; j += i) {
      P[j] = (P[j] + MOD - inv[j / i]) % MOD;
    }
  }

  P = exp(K + 1, P);
  int ans = 0;
  for (int i = 0; i <= K; ++i) {
    ans = (ans + 1LL * P[i] * C(N - 1 + K - i, N - 1)) % MOD;
  }
  printf("%d\n", ans);
  return 0;
}
