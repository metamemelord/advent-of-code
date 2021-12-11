#include<iostream>
#include<iomanip>
#include<vector>
#include<set>
#include<algorithm>
#include<utility>
	
using namespace std;

bool safe(int i, int j) {
  return i >= 0 && i < 10 && j >= 0 && j < 10;
}

void pprint(const vector<vector<int>> &x) {
  for(auto k: x) {
    for(auto j: k) cout << setw(2) << j << ' ';
    cout << '\n';
  }
  cout << '\n';
}

vector<pair<int, int>> get10s(const vector<vector<int>> &x) {
  vector<pair<int, int>> tens;
  for (int i=0; i<10; i++) 
    for (int j=0; j<10; j++) 
      if (x[i][j] == 10) {
        tens.push_back({i, j});
      }
  return tens;
}

int get0s(const vector<vector<int>> &x) {
  int count = 0;
  for (int i=0; i<10; i++) 
    for (int j=0; j<10; j++) 
      count += !x[i][j];
  return count;
}

int dx[] = {1,  1,  0, -1, -1, -1, 0, 1};
int dy[] = {0, -1, -1, -1,  0,  1, 1, 1}; 
vector<pair<int, int>> processNeighbours(vector<vector<int>> &x, pair<int, int> p) {
  vector<pair<int, int>> flashers;
  for(int i=0;i<8;i++) {
    if(safe(p.first + dx[i], p.second + dy[i])) {
      x[p.first + dx[i]][p.second + dy[i]]++;
      if(x[p.first + dx[i]][p.second + dy[i]] == 10) flashers.push_back({p.first + dx[i], p.second + dy[i]});
    }
  }
  return flashers;
}

void reset(vector<vector<int>> &x) {
  for (int i=0; i<10; i++) 
    for (int j=0; j<10; j++) 
      if (x[i][j] > 10) x[i][j] = 0;
}

void genInc(vector<vector<int>> &x) {
  for (int i=0; i<10; i++)
    for (int j=0; j<10; j++)
      x[i][j]++;
}

pair<int, int> solve(vector<vector<int>> &x) {
  long long ans = 0;
  int _gen = 0;
  for(_gen = 0; get0s(x) != 100; _gen++) {
    genInc(x);
    vector<pair<int, int>> s;
    do {
      s = get10s(x);
      for (int idx=0; idx < s.size(); idx++) {
	      auto flashSite = s[idx];
	      x[flashSite.first][flashSite.second]++;
	      auto moreFlashers = processNeighbours(x, flashSite);
	      for(auto flasher: moreFlashers) s.push_back(flasher);
      } 
      if (_gen < 100)
      	ans += s.size();
    } while(s.size());
    reset(x);
  }
  return {ans, _gen};
}

int main() {
  vector<vector<int>> x;

#ifdef FINPUT
  freopen("input.txt", "r", stdin);
  string s;
  for (int i=0;i<10;i++) {
    cin >> s;
    vector<int> row;
    for (auto k: s) row.push_back(k - '0');
    x.push_back(row);
  }
#else
  x = {
    {5,4,8,3,1,4,3,2,2,3},
    {2,7,4,5,8,5,4,7,1,1},
    {5,2,6,4,5,5,6,1,7,3},
    {6,1,4,1,3,3,6,1,4,6},
    {6,3,5,7,3,8,5,4,7,8},
    {4,1,6,7,5,2,4,6,4,5},
    {2,1,7,6,8,4,1,7,2,1},
    {6,8,8,2,8,8,1,1,3,4},
    {4,8,4,6,8,4,8,5,5,4},
    {5,2,8,3,7,5,1,5,2,6},
  };
#endif

  auto ans = solve(x);
  cout << ans.first << endl << ans.second << endl;
  return 0;
}
