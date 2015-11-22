#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
#define FZ(n) memset((n),0,sizeof(n))
#define FMO(n) memset((n),-1,sizeof(n))
#define MC(n,m) memcpy((n),(m),sizeof(n))
#define F first
#define S second
#define MP make_pair
#define PB push_back
#define ALL(x) begin(x),end(x)
#define SZ(x) ((int)(x).size())
#define IOS ios_base::sync_with_stdio(0); cin.tie(0)
// Let's Fight!

int mp[26];
string ip;

char go(char c) {
	if (c == '_') return c;
	return char('A' + mp[(int)c-'A']);
}

int main() {
	IOS;
	int nT;
	cin >> nT;
	while (nT--) {
		cin >> ip;
		for (int i=0; i<26; i++)
			mp[i] = i;
		int S;
		cin >> S;
		for (int i=0; i<S; i++) {
			string s1, s2;
			cin >> s1 >> s2;
			int a = s2[0] - 'A';
			int b = s1[0] - 'A';
			for (int j=0; j<26; j++) {
				if (mp[j] == a)
					mp[j] = b;
			}
		}
		for (auto ch : ip) {
			cout << go(ch);
		}
		cout << endl;
	}

    return 0;
}

