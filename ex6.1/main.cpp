#include <bits/stdc++.h>

using namespace std;

const int N = 1e7 + 5;

map <int, vector <int>> mp;

vector<vector<int>> mp1(2000000, vector<int>());

int main() {

    int n;
    cin >> n;

    for (int i = 1; i <= n; i ++) {
        int b, c;
        cin >> b >> c;
        b *= 1e6;
        b += 1e6 - c - 1;
//        mp[b].push_back(i);
        mp1[b].push_back(i);
    }

//    vector <int> ans;
//    for (auto it : mp) {
//        vector <int> tmp = it.second;
//        for (int i = tmp.size() - 1; i >= 0; i --) {
//            ans.push_back(tmp[i]);
//        }
//    }

    vector <int> ans1;
    for (auto it1 : mp1) {
        for (int i = it1.size(); i >= 0; i--) {
            ans1.push_back((it1[i]));
        }
    }

//    reverse(ans.begin(), ans.end());

    reverse(ans1.begin(), ans1.end());

    /*for (int i = 0; i < ans.size(); i ++) {
        cout << ans[i] << " ";
    }*/

    for (int i = 0; i < ans1.size(); i ++) {
        cout << ans1[i] << " ";
    }

    return 0;
}