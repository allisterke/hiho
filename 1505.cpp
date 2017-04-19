#include <bits/stdc++.h>
using namespace std;

using LL = long long int;

class Solution {
public:
    LL solve(vector<int> &nums) {
        LL total = 0;
        unordered_map<int, LL> count;
        for(int i = 0; i < nums.size(); ++ i) {
            for(int j = i+1; j < nums.size(); ++ j) {
                ++ count[nums[i] + nums[j]];
            }
        }
        for(auto &kv : count) {
            if(kv.second >= 2) {
                total += kv.second * (kv.second - 1);
            }
        }

        unordered_map<int, LL> nc;
        for(auto n : nums) {
            ++ nc[n];
        }
        {
            auto tnc = nc;
            for(auto n : nums) {
                -- tnc[n];
                for(auto &kv : tnc) {
                    if(kv.second >= 2) {
                        total -= kv.second * (kv.second - 1);
                    }
                }
            }
        }
        {
            map<int, LL> left, right(nc.begin(), nc.end());
            for(int i = 0; i < nums.size(); ++ i) {
                -- right[nums[i]];
                if(i) {
                    ++ left[nums[i-1]];
                }
                for(map<int, LL>::iterator it1 = left.begin(), it2 = right.begin();
                    it1 != left.end() && it2 != right.end(); ) {
                    if(it1->first < it2->first) {
                        ++ it1;
                    }
                    else if(it1->first > it2->first) {
                        ++ it2;
                    }
                    else {
                        total -= it1->second * it2->second * 2;
                        ++ it1;
                        ++ it2;
                    }
                }
            }
        }
        {
            auto tnc = nc;
            for(auto it = nums.rbegin(); it != nums.rend(); ++ it) {
                auto n = *it;
                -- tnc[n];
                for(auto &kv : tnc) {
                    if(kv.second >= 2) {
                        total -= kv.second * (kv.second - 1);
                    }
                }
            }
        }
        return total;
    }
};

int main() {
    int N;
    cin >> N;
    vector<int> nums(N);
    for(auto &n : nums) {
        cin >> n;
    }
    Solution s;
    cout << s.solve(nums) << endl;
    return 0;
}
