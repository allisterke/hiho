#include <algorithm>
#include <array>
#include <atomic>
#include <bitset>
#include <cassert>
#include <cctype>
#include <cerrno>
#include <cfenv>
#include <cfloat>
#include <chrono>
#include <cinttypes>
#include <climits>
#include <clocale>
#include <cmath>
#include <complex>
#include <condition_variable>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstdbool>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctgmath>
#include <ctime>
#include <cwchar>
#include <cwctype>
#include <deque>
#include <exception>
#include <forward_list>
#include <fstream>
#include <functional>
#include <future>
#include <initializer_list>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <mutex>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <random>
#include <ratio>
#include <regex>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <system_error>
#include <thread>
#include <tuple>
#include <typeindex>
#include <typeinfo>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <valarray>
#include <vector>
using namespace std;

class Solution {
public:
    int maxFontSize(int N, int P, int W, int H, vector<int> &pg) {
        for(int S = min(W, H); S > 0; S --) {
            if(checkVisible(S, N, P, W, H, pg)) {
                return S;
            }
        }
        return 0;
    }
//    int maxFontSize0(int N, int P, int W, int H, vector<int> &pg) {
//        int mins = 0, maxs = min(W, H) + 1;
//        while(mins < maxs) {
//            int mid = (mins + maxs) / 2;
//            if(checkVisible(mid, N, P, W, H, pg)) {
//                mins = mid + 1;
//            }
//            else {
//                maxs = mid;
//            }
//        }
//        return maxs - 1;
//    }
private:
    bool checkVisible(int S, int N, int P, int W, int H, vector<int> &pg) {
        int lines = 0;
        for(auto p : pg) {
            lines += usedLines(S, W, p);
        }
        int pc = H / S;
        return (lines % pc == 0 ? lines / pc : lines / pc + 1) <= P;
    }

    int usedLines(int S, int W, int characters) {
        if(S <= 0) {
            return 0;
        }
        int lc = W / S;
        return characters % lc == 0 ? characters / lc : characters / lc + 1;
    }
};

int main() {
    int T, N, P, W, H;
    vector<int> pg;
    Solution s;
    cin >> T;
    for(int t = 0; t < T; ++ t) {
        cin >> N >> P >> W >> H;
        pg.resize(N);
        for(int n = 0; n < N; ++ n) {
            cin >> pg[n];
        }
        cout << s.maxFontSize(N, P, W, H, pg) << endl;
    }
    return 0;
}