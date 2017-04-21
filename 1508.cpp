#include <bits/stdc++.h>
using namespace std;

using LL = long long int;

struct Point {
    LL x, y;
    bool operator==(Point &b) {
        return x == b.x && y == b.y;
    }
};

const double pi = asin(1.0) * 2;

class Solution {
private:
    double getAngle(LL x1, LL y1, LL x2, LL y2) {
        if(x2 >= x1) {
            return asin((y2 - y1)/hypot(x1 - x2, y1 - y2));
        }
        else if(y2 >= y1) {
            return pi - asin((y2 - y1)/hypot(x1 - x2, y1 - y2));
        }
        else {
            return asin((y1 - y2)/hypot(x1 - x2, y1 - y2)) - pi;
        }
    }

    vector<pair<double, double>> getRange(LL x1, LL y1, LL x2, LL y2, LL R) {
        LL distance = (x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2);
        double angle = getAngle(x1, y1, x2, y2);
        if(distance == 4 * R * R) {
            return vector<pair<double, double>>{make_pair(angle, angle)};
        }
        else {
            double offset = acos(sqrt(distance)/2/R);
            double start = angle - offset;
            double end = angle + offset;
            if(start >= -pi && end <= pi) {
                return vector<pair<double, double>>{make_pair(start, end)};
            }
            else if(start < -pi) {
                return vector<pair<double, double>>{make_pair(start + 2*pi, pi),
                    make_pair(-pi, end)};
            }
            else {
                return vector<pair<double, double>>{make_pair(start, pi),
                    make_pair(-pi, end - 2*pi)};
            }
        }
    }
public:
    int solve(vector<Point> &points, LL R) {
        int opt = 0;
        for(int i = 0; i < points.size(); ++ i) {
            vector<pair<double, int>> ranges;
            for(int j = 0; j < points.size(); ++ j) {
                if(points[i] == points[j]) {
                    ranges.emplace_back(-pi, 0);
                    ranges.emplace_back(pi, 1);
                }
                else if((points[i].x - points[j].x)*(points[i].x - points[j].x) + (points[i].y - points[j].y)*(points[i].y - points[j].y) <= 4*R*R){
                    for (auto &p : getRange(points[i].x, points[i].y, points[j].x, points[j].y, R)) {
                        ranges.emplace_back(p.first, 0);
                        ranges.emplace_back(p.second, 1);
                    }
                }
            }
            make_heap(ranges.begin(), ranges.end(), greater<pair<double, int>>());
            int acc = 0;
            for(int i = 0; i < ranges.size(); ++ i) {
                ranges[0].second == 0 ? ++ acc : -- acc;
                opt = max(opt, acc);
                pop_heap(ranges.begin(), ranges.begin() + ranges.size() - i, greater<pair<double, int>>());
            }
        }
        return opt;
    }
};

int main() {
    int N;
    LL R;
    cin >> N >> R;
    vector<Point> points(N);
    for(auto &p : points) {
        cin >> p.x >> p.y;
    }
    Solution s;
    cout << s.solve(points, R) << endl;
    return 0;
}
