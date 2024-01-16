#include <bits/stdc++.h>
using namespace std;

int t,n;
long long p;
long long a[10007];

int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d%lld", &n, &p);
		for (int i = 0; i < n; i++) scanf("%lld", &a[i]);
		
		// We can "itemize" each squares to multiple unit-length squares,
		// where the price will be: A[i], 3A[i], 5A[i], 7A[i], ...
		// Here, we want to binary search the strict upperbound of the price
		
		long long base_upp = 1;
		long long top_upp = 1000000000000000000LL; // Actually can be (2P-1)*A
		
		while (base_upp < top_upp) {
			long long mid_upp = (base_upp + top_upp) / 2;
			long long max_length = 0;
			
			// For each squares, find what is the largest possible length
			// i.e. Find max k where (2k-1)*a[i] <= mid_upp
			for (int i = 0; i < n; i++) {
				max_length += min(p, (mid_upp + a[i]) / (2 * a[i]));
			}
			if (max_length >= p) top_upp = mid_upp; else base_upp = mid_upp + 1;
		}
		long long upp = base_upp;
		
		long long total_cost = 0;
		long long total_length = 0;
		for (int i = 0; i < n; i++) {
			long long k = min(p, (upp + a[i]) / (2 * a[i]));		
			total_cost += k * k * a[i];
			total_length += k;
		}
		
		// Tricky: total_length can exceed p
		assert(total_length >= p);
		total_cost -= (total_length - p) * upp;
		printf("%lld\n", total_cost);
	}
}