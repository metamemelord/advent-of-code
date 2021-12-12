// https://ideone.com/NqugOu

#include<iostream>
#include <chrono>
#include<fstream>
#include<vector>
#include<map>
#include<set>
#include<stack>
#include<string>
#include<algorithm>

using namespace std;
using namespace std::chrono;

template <typename T, typename U>
bool contains(T col, U val)
{
    return col.find(val) != col.end();
}

pair<string, string> split_str(string s, char ch = '-') {
    int i = 0;
    for(char chr: s) {
        if (ch == chr)
            break;
        i += 1;
    }
    return {s.substr(0, i), s.substr(i+1, s.size()-i)};
}

bool is_upper(const string &s) {
    for(auto ch: s) if (ch < 'A' || ch > 'Z') return false;
    return true;
}

int dfs(const vector<int> x[], int N, long long mask, const set<int> &uppers, int term, int start) {
    if (N == term) return 1;

    int ans = 0;
    for (auto n: x[N]) {
        if(n == start) continue;
        if(contains(uppers, N) && contains(uppers, n)) continue;

        if (!contains(uppers, n)) {
            if (!(mask & 1 << n)) {
                ans += dfs(x, n, mask | 1 << n, uppers, term, start);
            }
        } else {
            ans += dfs(x, n, mask, uppers, term, start);
        }
    }
    return ans;
}

int dfs2(const vector<int> x[], int N, long long mask, long long smask, const set<int> &uppers, int term, int start) {
    if (N == term) return 1;

    int ans = 0;
    for (auto n: x[N]) {
        if(n == start) continue;
        if(contains(uppers, N) && contains(uppers, n)) continue;

        if (!contains(uppers, n)) {
            if (mask & 1 << n && smask > 0) continue;
            else if (mask & 1 << n) ans += dfs2(x, n, mask | 1 << n, smask | 1 << n, uppers, term, start);
            else ans += dfs2(x, n, mask | 1 << n, smask, uppers, term, start);
        } else {
            ans += dfs2(x, n, mask, smask, uppers, term, start);
        }
    }
    return ans;
}

pair<int, long long> solve(const vector<string> &x) {
    map<string, int> m;
    vector<int> adj[200];
    set<int> uppers;

    for(auto s: x) {
        auto k = split_str(s);
        if (!contains(m, k.first)) m[k.first] = m.size();
        if (!contains(m, k.second)) m[k.second] = m.size();
        if (is_upper(k.first)) uppers.insert(m[k.first]);
        if (is_upper(k.second)) uppers.insert(m[k.second]);

        adj[m[k.first]].push_back(m[k.second]);
        adj[m[k.second]].push_back(m[k.first]);
    }

    auto start = high_resolution_clock::now();

    int ans1 = dfs(adj, m["start"], 0, uppers, m["end"], m["start"]);
    int ans2 = dfs2(adj, m["start"], 0, 0, uppers, m["end"], m["start"]);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl;

    return {ans1, ans2};
}

int main() {
    vector<string> x;
    string s;
#ifdef FINPUT
    fstream file;
    file.open("input.txt", ios::in);

    while (file.peek() != EOF) {
        getline(file, s);
        x.push_back(s);
    }

    file.close();
#else
    x.push_back("fs-end");
    x.push_back("he-DX");
    x.push_back("fs-he");
    x.push_back("start-DX");
    x.push_back("pj-DX");
    x.push_back("end-zg");
    x.push_back("zg-sl");
    x.push_back("zg-pj");
    x.push_back("pj-he");
    x.push_back("RW-he");
    x.push_back("fs-DX");
    x.push_back("pj-RW");
    x.push_back("zg-RW");
    x.push_back("start-pj");
    x.push_back("he-WI");
    x.push_back("zg-he");
    x.push_back("pj-fs");
    x.push_back("start-RW");
#endif

    auto ans = solve(x);

    cout << ans.first << '\n' << ans.second << '\n';
}
