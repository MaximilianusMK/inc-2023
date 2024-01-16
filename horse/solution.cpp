#include<stdio.h>
#include<queue>
#include<algorithm>

using namespace std;

struct dt {
	int v, p;
};


bool comp(const dt &first, const dt &second){
	// if(first.v == second.v){
	// 	return first.p > second.p;
	// }
	return first.v < second.v;
}

int main(){
	int n,m;
	int space[200010];
	dt data[200010];

	scanf("%d %d", &m, &n);
	
	for(int j=0; j<m; j++){
		scanf("%d %d", &data[j].v, &data[j].p);
	}

    for(int i=0; i<n; i++){
		scanf("%d", &space[i]);
	}

	sort(space, space+n);
	sort(data, data+m, comp);

	// for(int i=0; i<n; i++){
	// 	printf("%d ", space[i]);
	// }
	// printf("\n");

	// for(int j=0; j<m; j++){
	// 	printf("%d %d\n", data[j].v, data[j].p);
	// }

	priority_queue<int> pq;

	long long ans = 0;
	int now = 0;
	for(int i=0; i<n; i++){
		// printf("++ %d %d %d\n", now, data[i].p, data[i].v);
		while(now < m && data[now].v <= space[i]){
			pq.push(data[now].p);
			now++;
		}
		if(!pq.empty()){
			int top = pq.top();
			pq.pop();

			ans += top;
		}
		// printf("%lld\n", ans);
	}
	printf("%lld\n", ans);
	return 0;
}