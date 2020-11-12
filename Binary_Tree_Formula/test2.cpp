#include <bits/stdc++.h>
using namespace std;

int main(){
	string s;
	cin >> s;
	for(int i = 0; i < s.length(); i++)
		if(s[i] == '+') s.assign(s, i + 1, s.length());
	cout << s << endl;
}