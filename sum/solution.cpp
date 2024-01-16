#include <bits/stdc++.h>
using namespace std;

// easier to type
const int MOD = 998244353;
const int N = 1e5 + 5;

struct DP {
    int sum;
    int ways;

    DP(int _s = 0, int _w = 0) {
        sum = _s;
        ways = _w;
    }

    DP operator +(DP other) const {
        return DP((sum + other.sum) % MOD, (ways + other.ways) % MOD);
    }

    DP operator *(DP other) const {
        int retSum = 1ll * sum * other.ways % MOD;
        retSum = (retSum + 1ll * ways * other.sum) % MOD;
        int retWays = 1ll * ways * other.ways % MOD;
        return DP(retSum, retWays);
    }

    void decWays() {
        ways--;
        if (ways < 0) ways += MOD;
    }

    string toString() {
        ostringstream out;
        out << "sum " << sum << " ways " << ways;
        return out.str();
    }
};

int n;
vector<int> adj[N];
DP upwardDP[N][2]; // [v][i] means sum and ways of v's subtree where v must be taken if i = 1, and not taken otherwise

long long globalAns = 0;

void read() {
    scanf("%d", &n);
    for (int i = 1 ; i < n ; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
}

void dfs1(int now, int prv) {
    upwardDP[now][0] = DP(0, 1);
    upwardDP[now][1] = DP(1, 1);

    for (int nex : adj[now]) {
        if (nex == prv) continue;
        dfs1(nex, now);
        upwardDP[now][0] = upwardDP[now][0] * (upwardDP[nex][0] + upwardDP[nex][1]);
        upwardDP[now][1] = upwardDP[now][1] * upwardDP[nex][0];
    }

    // printf("now %d --- 0 %s --- 1 %s\n", now, upwardDP[now][0].toString().c_str(), upwardDP[now][1].toString().c_str());
}

// result[0]: all v in chld must be not taken in the independent set
// result[1]: no restriction
array<vector<DP>, 2> buildPrefixDP(vector<int> chld) {
    vector<DP> prefix0, prefix1;
    for (int v : chld) {
        DP combined = upwardDP[v][0] + upwardDP[v][1];
        DP onlyZero = upwardDP[v][0];
        if (!prefix0.empty()) {
            combined = combined * prefix1.back();
            onlyZero = onlyZero * prefix0.back();
        }
        prefix0.push_back(onlyZero);
        prefix1.push_back(combined);
    }
    return {prefix0, prefix1};
}

void dfs2(int now, int prv, DP zero, DP one) {
    vector<int> chld;
    for (int nex : adj[now]) {
        if (nex == prv) continue;
        chld.push_back(nex);
    }

    array<vector<DP>, 2> prefix = buildPrefixDP(chld);
    reverse(chld.begin(), chld.end());
    array<vector<DP>, 2> suffix = buildPrefixDP(chld);
    reverse(chld.begin(), chld.end());
    reverse(suffix[0].begin(), suffix[0].end());
    reverse(suffix[1].begin(), suffix[1].end());

    for (int i = 0 ; i < chld.size() ; i++) {
        int v = chld[i];

        // calc contribution of this edge
        long long edgeContrib = 0;
        for (int j = 0 ; j < 2 ; j++) {
            DP parentDP = zero;
            if (j == 1) parentDP = one;
            // combine with prefix child dp
            if (i > 0) {
                if (j == 0) parentDP = parentDP * prefix[1][i-1];
                else parentDP = parentDP * prefix[0][i-1];
            }
            // and with suffix child dp
            if (i+1 < chld.size()) {
                if (j == 0) parentDP = parentDP * suffix[1][i+1];
                else parentDP = parentDP * suffix[0][i+1];
            }
            // exactly one way where no node is taken at all
            if (j == 0) parentDP.decWays();

            for (int k = 0 ; k < 2 ; k++) {
                if (j == 1 && k == 1) continue;

                DP vDP = upwardDP[v][k];
                // same reasoning as above
                if (k == 0) vDP.decWays();

                DP edgeDP = vDP * parentDP;
                edgeContrib = (edgeContrib + edgeDP.sum) % MOD;
            }
        }
        // printf("%d - %d contrib %lld\n", now, v, edgeContrib);
        globalAns = (globalAns + edgeContrib) % MOD;

        DP parentZero = zero;
        DP parentOne = one;
        if (i > 0) {
            parentZero = parentZero * prefix[1][i-1];
            parentOne = parentOne * prefix[0][i-1];
        }
        if (i+1 < chld.size()) {
            parentZero = parentZero * suffix[1][i+1];
            parentOne = parentOne * suffix[0][i+1];
        }

        DP newZero = DP(0, 1) * (parentZero + parentOne);
        DP newOne = DP(1, 1) * parentZero;
        dfs2(v, now, newZero, newOne);
    }
}

int main() {
    read();
    dfs1(1, -1);
    dfs2(1, -1, DP(0, 1), DP(1, 1));
    printf("%lld\n", globalAns);
    return 0;
}
