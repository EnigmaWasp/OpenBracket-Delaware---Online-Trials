#include <iostream>
#include <string>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

int main() {
	// your code goes here
	string s;
	cin >> s;
	string sample = "abcde@hogwarts.com";
	if (s.length() != sample.length()) {
		cout << "No" << endl;
		return 0;
	}

	if (s.substr(5) != sample.substr(5)) {
		cout << "No" << endl;
		return 0;
	}
	for (int i = 0; i < 5; i++)
		if (!(s[i]>='a' && s[i] <= 'z'))
		{
			cout << "No" << endl;
			return 0;
		}

	cout << "Yes" << endl;
	return 0;
}
