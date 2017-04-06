#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long int solve(vector<int> &nums) {
        long long int maxm = 0;
        int mask = 0;
        for(int i = 20; i >= 0; -- i) {
            mask |= (1 << i);
            map<int, int> prefix;
            for(auto n : nums) {
                ++ prefix[n & mask];
            }
            if(prefix.size() == 1) { // all match
                continue;
            }
            auto smallit = prefix.begin();
            auto largeit = prefix.rbegin();
            if(largeit->second > 1) {
                vector<int> tmp;
                for(auto n : nums) {
                    if((n & mask) == largeit->first) {
                        tmp.push_back(n);
                    }
                }
                swap(nums, tmp);
                continue;
            }
            else {
                auto it = find_if(begin(nums), end(nums), [=](const int n) { return (n & mask) == largeit->first; });
                for(auto n : nums) {
                    if(n != *it) {
                        maxm = max(maxm, (long long int)n * *it * (n & *it));
                    }
                }
                nums.erase(it);
            }
        }
        if(nums.size() > 1) {
            maxm = max(maxm, (long long int)nums[0] * nums[0] * nums[0]);
        }
        return maxm;
    }
};

int main() {
    Solution s;
    int T, N;
    vector<int> nums;
    cin >> T;
    for(int i = 0; i < T; ++ i) {
        cin >> N;
        nums.resize(N);
        for(int j = 0; j < N; ++ j) {
            cin >> nums[j];
        }
        cout << s.solve(nums) << endl;
    }
    return 0;
}
