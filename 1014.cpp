#include <bits/stdc++.h>
using namespace std;

struct Trie {
    array<Trie*, 26> next;
    int count;
    Trie() : next{}, count(0) {}
};

class Solution {
private:
    Trie *trie;
public:
    Solution() : trie(new Trie) {}

    void addWord(const string &word) {
        Trie *t = trie;
        for(auto c : word) {
            ++ t->count;
            int index = c - 'a';
            if(t->next[index] == nullptr) {
                t->next[index] = new Trie;
            }
            t = t->next[index];
        }
        ++ t->count;
    }

    int countPrefix(const string &prefix) {
        Trie *t = trie;
        for(auto c : prefix) {
            int index = c - 'a';
            t = t->next[index];
            if(!t) {
                break;
            }
        }
        return t ? t->count : 0;
    }
};

int main() {
    Solution s;
    int N, M;
    string word;
    cin >> N;
    for(int i = 0; i < N; ++ i) {
        cin >> word;
        s.addWord(word);
    }
    cin >> M;
    for(int j = 0; j < M; ++ j) {
        cin >> word;
        cout << s.countPrefix(word) << endl;
    }
    return 0;
}
