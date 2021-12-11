#include<iostream>
#include<fstream>
#include<vector>
#include<map>
#include<stack>
#include<string>
#include<algorithm>

using namespace std;

bool is_opening(char ch) {
  return ch == '(' || ch == '<' || ch == '{' || ch == '[';
}

char opening(char ch) {
  switch (ch) {
    case '>':
      return '<';
    case '}':
      return '{';
    case ']':
      return '[';
    case ')':
      return '(';
  }
  return '\0';
}

char closing(char ch) {
  switch (ch) {
    case '<':
      return '>';
    case '{':
      return '}';
    case '[':
      return ']';
    case '(':
      return ')';
  }
  return '\0';
}

map<char, int> costs;
map<char, int> scores;

pair<int, long long> solve(const vector<string> &x) {
  int ans1 = 0;
  vector<long long> ans2;
  for (auto &k: x) {
    bool corrupt = false;
    stack<char> st;
    for (char ch: k) {
      if (is_opening(ch)) {
        st.push(ch);
      } else {
        char opening_ch = opening(ch);
        if (st.top() != opening_ch) {
          ans1 += costs[ch]; 
          corrupt = true;
        }
        st.pop();
      }
    }


    if (!corrupt) {
      long long score = 0;
      while(!st.empty())
      {
        score *= 5;
        score += scores[closing(st.top())];
        st.pop();
      }

      ans2.push_back(score);
    }
  } 

  sort(ans2.begin(), ans2.end());
  
  return make_pair(ans1, ans2[ans2.size()/2]);
}

int main() {
  costs[')'] = 3;
  costs[']'] = 57;
  costs['}'] = 1197;
  costs['>'] = 25137;
  
  scores[')'] = 1;
  scores[']'] = 2;
  scores['}'] = 3;
  scores['>'] = 4;
  
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
  x.push_back("[({(<(())[]>[[{[]{<()<>>");
  x.push_back("[(()[<>])]({[<{<<[]>>(");
  x.push_back("{([(<{}[<>[]}>{[]{[(<()>");
  x.push_back("(((({<>}<{<{<>}{[]{[]{}");
  x.push_back("[[<[([]))<([[{}[[()]]]");
  x.push_back("[{[{({}]{}}([{[{{{}}([]");
  x.push_back("{<[[]]>}<{[{[{[]{()[[[]");
  x.push_back("[<(<(<(<{}))><([]([]()");
  x.push_back("<{([([[(<>()){}]>(<<{{");
  x.push_back("<{([{{}}[<[[[<>{}]]]>[]]");
#endif

  auto ans = solve(x);

  cout << ans.first << '\n' << ans.second << '\n';
}
