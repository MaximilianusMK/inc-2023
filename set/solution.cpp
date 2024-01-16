#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1e5;
const int INF = 1e9;

int N;
vector<int> adj[MAXN + 5];

int DP[MAXN + 5][2];

int f(int cur, bool can, int prev) {
  int &ret = DP[cur][can];
  if (ret != -1) return ret;
  int take = can ? 1 : -INF;
  int skip = 0;
  for (auto &next: adj[cur]) {
    if (next == prev) continue;
    take += f(next, false, cur);
    skip += f(next, true, cur);
  }
  return ret = max(take, skip);
}

int main() {
  cin >> N;
  for (int i = 0; i < N - 1; i++) {
    int u, v;
    cin >> u >> v;
    u--; v--;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  if (N == 2) {
    cout << 0 << endl;
    return 0;
  }
  memset(DP, -1, sizeof DP);
  cout << (long long)(N - 1) * (long long)(f(0, true, -1)) << endl;
  return 0;
}