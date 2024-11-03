#include <algorithm>
#include <bit>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <deque>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <ranges>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

using ll = int64_t;
using vl = vector<ll>;
using vvl = vector<vl>;
using vs = vector<string>;
using Pos = pair<ll, ll>;

ll R, C;
vs M;
ll by, bx;
vvl Fire;

vl dx{-1, 1, 0, 0};
vl dy{0, 0, -1, 1};

ll solve() {
  queue<pair<Pos, ll>> Q{};
  M[by][bx] = 'x';
  Q.push({{by, bx}, 0});

  while (!Q.empty()) {
    auto [pos, t] = Q.front();
    auto [py, px] = pos;
    Q.pop();

    if (px == 0 || px == C - 1 || py == 0 || py == R - 1) return t;

    for (auto d = 0; d < 4; ++d) {
      const auto& nx = px + dx[d];
      const auto& ny = py + dy[d];

      if (nx < 0 || C <= nx || ny < 0 || R <= ny) continue;
      if (M[ny][nx] != '.') continue;
      if (Fire[ny][nx] <= t + 1) continue;

      M[ny][nx] = 'x';
      Q.push({{ny, nx}, t + 1});
    }
  }

  return -1;
}

void BfsFire() {
  queue<Pos> Q{};
  for (auto r = 0; r < R; ++r) {
    for (auto c = 0; c < C; ++c) {
      if (Fire[r][c] == 0) {
        Q.push({r, c});
      }
    }
  }

  while (!Q.empty()) {
    auto [pr, pc] = Q.front();
    Q.pop();

    const auto& t = Fire[pr][pc];

    for (auto d = 0; d < 4; ++d) {
      const auto& nr = pr + dy[d];
      const auto& nc = pc + dx[d];

      if (nr < 0 || R <= nr || nc < 0 || C <= nc) continue;
      if (M[nr][nc] != '.') continue;
      if (Fire[nr][nc] <= t + 1) continue;

      Fire[nr][nc] = t + 1;
      Q.push({nr, nc});
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  cin >> R >> C;
  M = vs(R);
  for (auto&& m : M) cin >> m;

  Fire = vvl(R, vl(C, std::numeric_limits<ll>::max()));

  for (auto i = 0; i < R; ++i) {
    for (auto j = 0; j < C; ++j) {
      if (M[i][j] == 'J') {
        by = i;
        bx = j;
        M[i][j] = '.';
      } else if (M[i][j] == 'F') {
        Fire[i][j] = 0;
      }
    }
  }

  BfsFire();

  const auto& ans = solve();
  if (ans < 0) {
    cout << "IMPOSSIBLE";
  } else {
    cout << ans + 1;
  }

  return 0;
}