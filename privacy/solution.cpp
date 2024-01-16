/*
solution for `privacy'

complexity
  time  : O(n lg n)
  memory: O(n)

expected verdict:
  AC
*/
#pragma GCC optimize "-O2"
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;

const int maxn = 100005;
const int inf  = 2000000005;

struct tpoint { int x, y, id; };
bool y_desc (const tpoint &a, const tpoint &b) {
  return a.y != b.y ? a.y > b.y : a.x < b.x;
}

struct tscore { int id, value; };

int n;
tpoint point[maxn];

vector<tscore> closest[maxn];
bool operator < (const tscore &a, const tscore &b) {
  return a.value != b.value ? a.value < b.value : a.id < b.id;
}
bool operator == (const tscore &a, const tscore &b) {
  return a.id == b.id;
}

vector<tscore> BIT[maxn];

vector<tscore> best_two(vector<tscore> arr) {
  sort(arr.begin(), arr.end());
  arr.resize(2);
  return arr;
}

void reset(int nn) {
  for (int i = 0; i <= nn; ++i)
    BIT[i] = {{-1, inf}, {-1, inf}};
}

void add(int x, tscore p) {
  x++;
  while (x <= n) {
    BIT[x].push_back(p);
    BIT[x] = best_two(BIT[x]);
    x += x & -x;
  }
}

vector<tscore> query(int x) {
  vector<tscore> ret = {{-1, inf}, {-1, inf}};
  x++;
  while (x > 0) {
    ret.insert(ret.end(), BIT[x].begin(), BIT[x].end());
    ret = best_two(ret);
    x -= x & -x;
  }
  return ret;
}

void rotate(tpoint &a) { swap(a.x, a.y); a.y = -a.y; }


int main(int argc, char *argv[]) {
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d %d", &point[i].x, &point[i].y);
    point[i].id = i;
  }

  for (int k = 0; k < 4; ++k) {
    vector<pii> x;
    for (int i = 0; i < n; ++i)
      x.push_back({-point[i].x, point[i].id});
    sort(x.begin(), x.end());

    vector<int> order(n);
    for (int i = 0; i < n; ++i)
      order[x[i].second] = i;
    
    sort(point, point+n, y_desc);

    reset(n);

    for (int i = 0; i < n; ++i) {
      vector<tscore> pts = query(order[point[i].id]);

      for (auto &p : pts) if (p.id != -1) {
        closest[point[i].id].push_back({p.id, p.value-point[i].x-point[i].y});
        closest[p.id].push_back({point[i].id, p.value-point[i].x-point[i].y});
      }

      add(order[point[i].id], {point[i].id, point[i].x+point[i].y});
    }

    for (int i = 0; i < n; ++i) rotate(point[i]);
  }

  for (int i = 0; i < n; ++i) {
    sort(closest[i].begin(), closest[i].end());
    unique(closest[i].begin(), closest[i].end());
    closest[i].resize(2);
  }

  int ans = inf;

  for (int i = 0; i < n; ++i) {
    int a = point[i].id;
    int b = closest[a][0].id;
    int cost = closest[a][0].value;
    if (closest[a][0].value == closest[b][0].value) {
      ans = min(ans, closest[a][1].value);
      ans = min(ans, closest[b][1].value);
    }
  }

  printf("%d\n", ans);

  return 0;
}