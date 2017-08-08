#include <bits/stdc++.h>
#include <utility>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>


using namespace std;

typedef pair<int, int> pii;



int main() {
    ios_base::sync_with_stdio(0);
	cin.tie(0);

    string s;
    int k;

    cin >> s >> k;

    const int ALPH_SIZE = 'z' - 'a' + 1;
    vector<int> num(ALPH_SIZE, 0);
    vector<pii> apear(ALPH_SIZE, {-1, -1});
    int l = s.length();
    for (int i = 0; i < l; i++)
    {
        num[s[i]-'a']++;
        if (apear[s[i]-'a'].first == -1) apear[s[i]-'a'].first = i;
        apear[s[i]-'a'].second = i;
    }

    s += "###";
    int start = 0;
    while (start < l)
    {
        char curL = 0;
        for (int i = 'z'; i >= 'a'; i--)
            if (num[i-'a'] >= k)
        {
            curL = i;
            break;
        }

        if (curL == 0) start = l;
        else
        {
            for (int i = num[curL-'a']; i > 0; i--)
                cout << curL;
            for (int i = start; i <= apear[curL-'a'].second; i++)
                num[s[i]-'a']--;
            start = apear[curL-'a'].second + 1;
        }
    }

    cout << endl;
	return 0;
}
