#include <bits/stdc++.h>
using namespace std;

int N, M;
vector<string> board;
vector<vector<pair<int, int>>> ha;
map<tuple<vector<string>, int, int, int, int>, int> cache; // key: board, hp, buff, x, y
int gmhp = 0;

class Solution {
public:
//    int nearestMonster(const set<pair<int, int>> &openable) {
//        for(auto &op : openable) {
//            if(board[op.first][op.second] == 'M' || board[op.first][op.second] == 'S') {
//                return 1;
//            }
//        }
//        auto mark = board;
//        queue<pair<int, int>> q;
//        queue<int> dist;
//        for(auto &op : openable) {
//            q.push(op);
//            dist.push(1);
//            mark[op.first][op.second] = 0;
//        }
//        while(!q.empty()) {
//            auto op = q.front();
//            int d = dist.front();
//            q.pop();
//            dist.pop();
//
//            int x, y;
//            tie(x, y) = op;
//            pair<int, int> may[] = {
//                    make_pair(x-1, y),
//                    make_pair(x+1, y),
//                    make_pair(x, y-1),
//                    make_pair(x, y+1),
//            };
//
//            for(int i = 0; i < 4; ++ i) {
//                tie(x, y) = may[i];
//                if(x >= 0 && x < N && y >= 0 && y < M && mark[x][y] != 0) {
//                    if(board[x][y] == 'S' || board[x][y] == 'M') {
//                        return d + 1;
//                    }
//                    else {
//                        mark[x][y] = 0;
//                        q.push(may[i]);
//                        dist.push(d+1);
//                    }
//                }
//            }
//        }
//        return numeric_limits<int>::max();
//    }
//
//    vector<vector<pair<int, int>>> buildStartupPath(int x, int y) {
//        vector<vector<pair<int, int>>> paths;
//        if(nearestMonster(set<pair<int, int>>{make_pair(x, y)}) < 6) {
//            auto mark = board;
//            map<pair<int, int>, pair<int, int>> prefix;
//            queue<pair<int, int>> visited;
//            visited.push(make_pair(x, y));
//            mark[x][y] = 0;
//            vector<pair<int, int>> monsters;
//            while (!visited.empty()) {
//                auto op = visited.front();
//                visited.pop();
//
//                tie(x, y) = op;
//                pair<int, int> may[] = {
//                        make_pair(x-1, y),
//                        make_pair(x+1, y),
//                        make_pair(x, y-1),
//                        make_pair(x, y+1),
//                };
//                for(int i = 0; i < 4; ++ i) {
//                    tie(x, y) = may[i];
//                    if(x >= 0 && x < N && y >= 0 && y < M && mark[x][y] != 0) {
//                        prefix[may[i]] = op;
//                        mark[x][y] = 0;
//                        if(board[x][y] == '.') {
//                            visited.push(may[i]);
//                        }
//                        else if(board[x][y] == 'S' && board[x][y] == 'M') {
//                            monsters.push_back(may[i]);
//                        }
//                    }
//                }
//            }
//            for(auto &op : monsters) {
//                vector<pair<int, int>> path{op};
//                while(prefix.find(path.back()) != prefix.end()) {
//                    path.push_back(prefix[path.back()]);
//                }
//                paths.push_back(path);
//            }
//        }
//        return paths;
//    }

    int open(int hp, int ap, int buff, set<pair<int, int>> openable, int x, int y, int monsters, vector<pair<int, int>> &path,
             bool clear = false) {
//        if(!path.empty()) {
//            tie(x, y) = path.back();
//            path.pop_back();
//        }

        if(hp <= gmhp) { // compare with global optimum
            return gmhp;
        }

        auto key = make_tuple(board, hp, buff, x, y);
        auto it = cache.find(key);
        if(it != cache.end()) {
            return it->second;
        }

        if (buff) {
            -- buff;
        }
        auto ch = board[x][y];
        board[x][y] = 0; // mark opened

        if (ch == 'M' || ch == 'S') {
            int h, a;
            tie(h, a) = ha[x][y];

            int defeat = ceil(1. * h / ap); // h % ap == 0) ? (h / ap) : (h / ap + 1);
            if(defeat <= buff) {
                buff -= defeat;
            }
            else {
                hp -= (defeat - buff) * a;
                buff = 0;
            }
//            while (hp > 0 && h > 0) {
//                h -= ap;
//                if (buff) {
//                    -- buff;
//                }
//                else {
//                    hp -= a;
//                }
//            }
            -- monsters;
        }

        int mhp = 0;
//        if (hp > 0 && checkMonsterExists(N, M, board)) {
//        if (hp > 0) {
        if(hp > 0 && monsters) {
            if (ch == 'S') { // refresh buff
                buff = 5;
            }

            openable.erase(make_pair(x, y));

            // detect more openable cells
            pair<int, int> may[] = {
                    make_pair(x-1, y),
                    make_pair(x+1, y),
                    make_pair(x, y-1),
                    make_pair(x, y+1),
            };
            for (int k = 0; k < 4; ++ k) {
                int i, j;
                tie(i, j) = may[k];
                if (i >= 0 && i < N && j >= 0 && j < M && board[i][j] != 0) {
                    openable.insert(may[k]);
                }
            }

            if(!path.empty()) {
                mhp = open(hp, ap, buff, openable, 0, 0, monsters, path);
            }
            else {

                // select another cell to open
                bool done = false;
                if (clear || !buff
//                    || buff <= nearestMonster(openable)
                        ) { // open all empty slate if no buff left or buff is not enough
                    for (auto &op : openable) {
                        if (board[op.first][op.second] == '.') {
                            mhp = open(hp, ap, buff, openable, op.first, op.second, monsters, path, clear);
                            done = true;
                            break;
                        }
                    }
                }

//                if(!buff && !done) { // defeat special monsters first if no buff left
//                    pair<int, int> minop;
//                    bool found = false;
//                    for(auto &op : openable) {
//                        if(board[op.first][op.second] == 'S' || board[op.first][op.second] == 'M') {
//                            if(!found || ceil(1.*ap/ha[op.first][op.second].first)*ha[op.first][op.second].second < ceil(1.*ap/ha[minop.first][minop.second].first)*ha[minop.first][minop.second].second) {
//                                minop = op;
//                                found = true;
//                            }
//                        }
//                    }
//                    if(found) {
//                        mhp = open(hp, ap, buff, openable, minop.first, minop.second, monsters, path);
//                        done = true;
//                    }
//                }

                if (!done) {
//                if(buff == 5) {
//                    for (auto &op : openable) {
//                        if(board[op.first][op.second] == 'M' || board[op.first][op.second] == 'S') {
//                            mhp = max(mhp, open(hp, ap, buff, openable, op.first, op.second, monsters, path));
//                        }
//                    }
//                }
//                else
                    {
                        for (auto &op : openable) {
                            mhp = max(mhp, open(hp, ap, buff, openable, op.first, op.second, monsters, path));
                        }
                    }
                }
            }
        }
        else if(hp > 0) {
            mhp = hp;
        }

        board[x][y] = ch; // restore board[x][y];

        cache[key] = mhp;

        gmhp = max(gmhp, mhp); // global optimum

        return mhp;
    }

    int solve(int hp, int ap) {
        int monsters = 0;
        for(int i = 0; i < N; ++ i) {
            for (int j = 0; j < M; ++j) {
                if (board[i][j] == 'M' || board[i][j] == 'S') {
                    ++ monsters;
                }
            }
        }
        for(int i = 0; i < N; ++ i) {
            for(int j = 0; j < M; ++ j) {
                if(board[i][j] == 'D') {
                    // one extra buff to open entrance
//                    auto paths = buildStartupPath(i, j);
//                    if(!paths.empty()) {
//                        int mhp = 0;
//                        for(auto &path : paths) {
//                            mhp = max(mhp, open(hp, ap, 6, set<pair<int, int>>{{i, j}}, 0, 0, monsters, path));
//                        }
//                        return mhp;
//                    }
//                    else
                    {
                        auto path = vector<pair<int, int>>();
                        return open(hp, ap, 6, set<pair<int, int>>{{i, j}}, i, j, monsters, path);
                    }
                }
            }
        }
        return hp;
    }
};

int main() {
    Solution s;

    cin >> N >> M;
    board = vector<string>(N);
    for(int i = 0; i < N; ++ i) {
        cin >> board[i];
    }

    ha = vector<vector<pair<int, int>>>(N, vector<pair<int, int>>(M, make_pair(-1, -1)));
    for(int i = 0; i < N; ++ i) {
        for(int j = 0; j < M; ++ j) {
            if(board[i][j] == 'S' || board[i][j] == 'M') {
                cin >> ha[i][j].first >> ha[i][j].second;
            }
        }
    }
    int hp, ap;
    cin >> hp >> ap;

    int r = s.solve(hp, ap);
    cout << (r > 0 ? to_string(r) : "DEAD") << endl;
    return 0;
}
