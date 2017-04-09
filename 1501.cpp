#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string convert(const string &var) {
        string converted;
        bool up = false;
        for(auto c : var) {
            if(c == '_') {
                up = true;
            }
            else {
                if(up) {
                    converted.push_back(toupper(c));
                    up = false;
                }
                else if(isupper(c)) {
                    converted.push_back('_');
                    converted.push_back(tolower(c));
                }
                else {
                    converted.push_back(c);
                }
            }
        }
        return converted;
    }
};

int main() {
    Solution s;
    int N;
    cin >> N;
    string var;
    for(int i = 0; i < N; ++ i) {
        cin >> var;
        cout << s.convert(var) << endl;
    }
    return 0;
}
