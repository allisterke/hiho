#include <bits/stdc++.h>
using namespace std;

using LL = long long int;

class Solution {
public:
    int solve(int N, int S, double M, int T, vector<double> &init) {
        vector<double> h(init);

        int i = S;
        int j = S;
        while (M > 0) {
            for(; i > 0 && h[i-1] <= h[i]; -- i);
            double left = 0;
            int left_k = 0;
            if(i == 0) { // left need infinite water
                left = numeric_limits<int>::max();
            }
            else {
                if(h[i] == h[S]) {
                    left = 0;
                }
                else {
                    left_k = i + 1;
                    for (; h[i] == h[left_k]; ++left_k);
//                    left_k = upper_bound(h.begin() + i + 1, h.begin() + S, h[i]) - h.begin();
                    left = (left_k - i) * (min(h[i - 1], h[left_k]) - h[i]);
                }
            }

            for(; j < init.size() - 1 && h[j+1] <= h[j]; ++ j);
            double right = 0;
            int right_k = 0;
            if(j == init.size() - 1) { // right cannot hold any water;
                right = numeric_limits<int>::max();
            }
            else {
                if(h[j] == h[S]) {
                    right = 0;
                }
                else {
                    right_k = j-1;
                    for(; h[j] == h[right_k]; -- right_k);
//                    right_k = h.rend() - upper_bound(h.rend() - j - 1, h.rend() - S - 1, h[j]) - 1;
                    right = (j - right_k) * (min(h[j+1], h[right_k]) - h[j]);
                }
            }

            if(left == 0 && right == 0) {
                double real = (j - i + 1) * (min(h[i-1], h[j+1]) - h[S]);
                if(real >= M) {
                    for(int k = i; k <= j; ++ k) {
                        h[k] += M / (j - i + 1);
                    }
                    M = 0;
                }
                else {
                    for(int k = i; k <= j; ++ k) {
                        h[k] += real / (j - i + 1);
                    }
                    M -= real;
                }
            }
            else if(left == 0) {
                if(right == numeric_limits<int>::max()) {
                    break;
                }
                else {
                    if(right >= M) {
                        for(int k = right_k + 1; k <= j; ++ k) {
                            h[k] += M / (j - right_k);
                        }
                        M = 0;
                    }
                    else {
                        for(int k = right_k + 1; k <= j; ++ k) {
                            h[k] += right / (j - right_k);
                        }
                        M -= right;
                    }
                }
            }
            else if(right == 0) {
                if(left == numeric_limits<int>::max()) {
                    break;
                }
                else {
                    if(left >= M) {
                        for(int k = i; k < left_k; ++ k) {
                            h[k] += M / (left_k - i);
                        }
                        M = 0;
                    }
                    else {
                        for(int k = i; k < left_k; ++ k) {
                            h[k] += left / (left_k - i);
                        }
                        M -= left;
                    }
                }
            }
            else {
                if(left == numeric_limits<int>::max() && right == numeric_limits<int>::max()) {
                    break;
                }
                else if(left == numeric_limits<int>::max()) {
                    if(right >= M/2) {
                        for(int k = right_k + 1; k <= j; ++ k) {
                            h[k] += M / 2 / (j - right_k);
                        }
                        M = 0;
                    }
                    else {
                        for(int k = right_k + 1; k <= j; ++ k) {
                            h[k] += right / (j - right_k);
                        }
                        M -= right * 2;
                    }
                }
                else if(right == numeric_limits<int>::max()) {
                    if(left >= M/2) {
                        for(int k = i; k < left_k; ++ k) {
                            h[k] += M / 2 / (left_k - i);
                        }
                        M = 0;
                    }
                    else {
                        for(int k = i; k < left_k; ++ k) {
                            h[k] += left / (left_k - i);
                        }
                        M -= left * 2;
                    }
                }
                else {
                    double used = min(left, right);
                    if(used >= M/2) {
                        for(int k = i; k < left_k; ++ k) {
                            h[k] += M / 2 / (left_k - i);
                        }
                        for(int k = right_k + 1; k <= j; ++ k) {
                            h[k] += M / 2 / (j - right_k);
                        }
                        M = 0;
                    }
                    else {
                        for(int k = i; k < left_k; ++ k) {
                            h[k] += used / (left_k - i);
                        }
                        for(int k = right_k + 1; k <= j; ++ k) {
                            h[k] += used / (j - right_k);
                        }
                        M -= used * 2;
                    }
                }
            }
        }

        return floor(h[T] - init[T]);
    }
};

int main() {
    int N, S, M, T;
    cin >> N >> S >> M >> T;
    vector<double> init(N);
    for(auto &d : init) {
        cin >> d;
    }
    -- S;
    -- T;
    Solution s;
    cout << s.solve(N, S, M, T, init) << endl;
    return 0;
}
