#include <bits/stdc++.h>
using namespace std;

struct Trie {
    Trie *next[2];
    int index;

    Trie() : index(numeric_limits<int>::max()), next {} {
    }
};

class Solution {
private:
    Trie *allow, *deny;
    int rules;
public:
    Solution() : allow(new Trie), deny(new Trie), rules(0) {}

    inline vector<int> & getBits(int n) {
        static vector<int> bits(8);
        for(int i = 0; i < 8; ++ i) {
            bits[7 - i] = n & 1;
            n >>= 1;
        }
        return bits;
    }

    inline vector<int> & getPrefix(const string &subnet) {
        static vector<int> prefix(32);
        prefix.clear();

        int i = 0;
        for(int j = 0; j < 4 && i < subnet.length(); ++ i, ++ j) {
            int n = 0;
            for(; i < subnet.length() && isdigit(subnet[i]); ++ i) {
                n = n*10 + subnet[i] - '0';
            }
            auto bits = getBits(n);
            prefix.insert(prefix.end(), bits.begin(), bits.end());
        }
        if(i < subnet.length()) {
            int n = 0;
            for(; i < subnet.length(); ++ i) {
                n = n*10 + subnet[i] - '0';
            }
            prefix.resize(n);
        }
        return prefix;
    }

    void addRule(const string& type, const string &subnet) {
        addRuleToTrie(type == "allow" ? allow : deny, getPrefix(subnet), rules ++);
    }

    void addRuleToTrie(Trie *t, vector<int>& prefix, int index) {
        for(auto n : prefix) {
            if(t->next[n] == nullptr) {
                t->next[n] = new Trie;
            }
            t = t->next[n];
        }
        t->index = min(t->index, index);
    }

    bool checkAllowed(const string &ip) {
        auto &prefix = getPrefix(ip);
        int ai = checkIndex(allow, prefix);
        int di = checkIndex(deny, prefix);
        return ai == di || ai < di ? true : false;
    }

    int checkIndex(Trie *t, vector<int> &prefix) {
        int index = numeric_limits<int>::max();
        for(auto n : prefix) {
            index = min(index, t->index);
            if(t->next[n] != nullptr) {
                t = t->next[n];
            }
            else {
                break;
            }
        }
        return index = min(index, t->index);
    }
};

int main() {
    int N, M;
    cin >> N >> M;
    string type, subnet;
    Solution s;
    for(int i = 0; i < N; ++ i) {
        cin >> type >> subnet;
        s.addRule(type, subnet);
    }
    for(int i = 0; i < M; ++ i) {
        cin >> subnet;
        cout << (s.checkAllowed(subnet) ? "YES" : "NO") << endl;
    }
}