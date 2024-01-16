#include <bits/stdc++.h>
using namespace std;

int N, M, K;
map<string, string> best;
vector<string> gold;

int main() { 
  ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
  cin >> N >> M >> K;
  for (int i = 0; i < N; i++) {
    string team, univ;
    cin >> team >> univ;
    if (i >= M && !best.count(univ) && gold.size() < K) {
      gold.push_back(team);
    }
    best[univ] = team;
  }
  cout << gold.size() << endl;
  for (auto &ans: gold) {
    cout << ans << endl;
  }
}
