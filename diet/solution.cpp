#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  int n, m, k;
  cin >> n >> m >> k;

  vector<int> p;
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    p.push_back(x);
  }

  // Assume the diet_plan stop at day 0.
  int result = 0;

  for (int i = 0; i < n; i++) {
    // Copy the first "i" days of plan and
    // sort it in descending order.
    vector<int> tmp(p.begin(), p.begin() + i + 1);
    sort(tmp.begin(), tmp.end(), greater<int>());

    int total = 0;
    // Use biscuits for the top K days to reduce
    // milk consumptions.
    for (int j = k; j < tmp.size(); j++) {
      total += tmp[j];
    }

    // If the total consumption is bigger than
    // the amount of milk that we have, then break.
    if (total > m) {
      break;
    }
    // Otherwise, we can maintain our plan until
    // day "i + 1" (i is zero based).
    result = i + 1;
  }
  cout << result << endl;
  return 0;
}
