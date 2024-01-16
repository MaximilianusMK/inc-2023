#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

int solve(){
    LL n, m, k;
    scanf("%lld%lld%lld", &n, &m, &k);

    // no cut required.
    if(k == n * m) return 0;

    // if(k % n == 0), k / n <= m. The other already handled in k > n * m;
    // if(k % m == 0), k / m <= n. The other already handled in k > n * m;
    if((k % n) == 0 || (k % m) == 0) return 1;

    // check through rows with m columns 
    // (can be slightly optimized but no need for this task, for readability reason)
    for(LL i = 1;i < n; ++i){
        LL cutted_rows = i * m;
        if((k % i) == 0 && k <= cutted_rows) return 2;
        LL remains = k - cutted_rows;
        if(remains > 0 && (remains % (n - i)) == 0) return 2;
    }

    // check through columns with n columns 
    // (can be slightly optimized but no need for this task, for readability reason)
    for(LL i = 1;i < m; ++i){
        LL cutted_cols = i * n;
        if((k % i) == 0 && k <= cutted_cols) return 2;
        LL remains = k - cutted_cols;
        if(remains > 0 && (remains % (m - i)) == 0) return 2;
    }

    // you can make any number from 1 to N * M with at most 3 cuts.
    return 3;
}

int main(){
    printf("%d\n", solve());
    return 0;
}