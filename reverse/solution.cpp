#include <bits/stdc++.h>
using namespace std;

#define MOD 1000000007LL

int n,q;
char s[10007],t[10007];

int main() {
	scanf("%d",&n);
	scanf("%s",&s);
	scanf("%d",&q);
	while (q--) {
		scanf("%s",&t);
		
		long long hash_s = 0;
		long long hash_t = 0;
		long long power27 = 1;
		
		for (int i = 0; i < n; i++) {
			hash_t = (hash_t * 27 + t[i] - 'A' + 1) % MOD;
			hash_s = (hash_s + power27 * (s[n-1-i] - 'A' + 1)) % MOD;
			power27 = (power27 * 27) % MOD;
			assert(power27 != 1);
			
			if (hash_s == hash_t) {
				hash_s = 0;
				hash_t = 0;
				power27 = 1;
			}
		}
		
		if (power27 == 1) printf("YES\n"); else printf("NO\n");
	}
}