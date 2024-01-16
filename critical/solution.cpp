#include <algorithm>
#include <cstdio>
#include <queue>
#include <vector>

int main() {
  int N, M;
  scanf("%d %d", &N, &M);

  std::vector<std::vector<int>> adj(N + M);
  std::vector<int> deg(N + M);
  for (int j = 0; j < M; ++j) {
    int u, v;
    scanf("%d %d", &u, &v);
    --u, --v;

    adj[u].push_back(j + N);
    adj[j + N].push_back(v);
    ++deg[j + N];
    ++deg[v];
  }

  // For the dominator's tree
  std::vector<int> depth(N + M);
  std::vector<std::vector<int>> par(32 - __builtin_clz(N + M), std::vector<int>(N + M));
  std::vector<int> ans(N + M);
  for (int i = 0; i < N + M; ++i) {
    par[0][i] = i;
    if (i >= N) ans[i] = 1;
  }

  auto lca = [&](int u, int v) {
    if (depth[u] < depth[v]) std::swap(u, v);
    while (depth[u] != depth[v]) u = par[__builtin_ctz(depth[u] - depth[v])][u];
    if (u == v) return u;
    for (int i = (int) par.size() - 1; i >= 0; --i) {
      if (par[i][u] != par[i][v]) {
        u = par[i][u];
        v = par[i][v];
      }
    }
    return par[0][u];
  };

  std::queue<int> q;
  q.push(0);

  while (q.size()) {
    int u = q.front();
    q.pop();

    for (int v : adj[u]) {
      if (par[0][v] == v) {
        par[0][v] = u;
      } else {
        par[0][v] = lca(u, par[0][v]);
      }
      --deg[v];
      if (deg[v] == 0) {
        q.push(v);
        for (int i = 1; i < (int) par.size(); ++i) {
          par[i][v] = par[i - 1][par[i - 1][v]];
        }
        depth[v] = depth[par[0][v]] + 1;
        ans[v] += ans[par[0][v]];
      }
    }
  }

  for (int i = 0; i < N; ++i) {
    printf("%d", ans[i]);
    printf("%c", " \n"[i == N - 1]);
  }
  return 0;
}
