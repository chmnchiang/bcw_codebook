#include<bits/stdc++.h>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<vector>
#ifdef ONLINE_JUDGE
#define FILEIO(name) \
  freopen(name".in", "r", stdin); \
  freopen(name".out", "w", stdout);
#else
#define FILEIO(name)
#endif
using namespace std;
#define FZ(n) memset((n),0,sizeof(n))
#define FMO(n) memset((n),-1,sizeof(n))
#define MC(n,m) memcpy((n),(m),sizeof(n))
#define F first
#define S second
#define MP make_pair
#define PB push_back
#define FOR(x,y) for(__typeof(y.begin())x=y.begin();x!=y.end();x++)
#define IOS ios_base::sync_with_stdio(0); cin.tie(0)
// Let's Fight!

string S;
int len;

int main()
{
	FILEIO("decomposable");
	IOS;
	while(cin >> S) {
		len = S.length();
		int gp = 0;
		for(int i=1; i<len; i++) {
			if(S[i] != S[0]) {
				gp = i; break;
			}
		}
		if(gp == 0){
			cout << "NO" << endl;
			continue;
		}

		cout << "YES" << endl;
		cout << len+1 << '\n' << 1 << '\n' << len << '\n';
		for(int i=0; i<gp-1; i++) {
			int id = i+1;
			for(char c='a'; c<='z'; c++) {
				cout << (c==S[i] ? (id+1) : len+1) << (c == 'z' ? "" : " ");
			}
			cout << endl;
		}
		{
			int id = gp;
			for(char c='a'; c<='z'; c++) {
				if(c == S[gp]) {
					cout << id+1;
				} else if(c == S[gp-1]) {
					cout << id;
				} else {
					cout << len+1;
				}
				if(c != 'z') cout << ' ';
			}
			cout << endl;
		}
		for(int i=gp+1; i<len; i++) {
			int id = i;
			for(char c='a'; c<='z'; c++) {
				if(c == S[i]) {
					cout << id+1;
				} else {
					cout << len+1;
				}
				if(c != 'z') cout << ' ';
			}
			cout << endl;
		}

		{
			for(char c='a'; c<='z'; c++) {
				cout << len+1;
				if(c != 'z') cout << ' ';
			}
			cout << endl;
		}

		{
			int id = len+1;
			for(char c='a'; c<='z'; c++) {
				cout << id;
				if(c != 'z') cout << ' ';
			}
			cout << endl;
		}

		cout << len+1 << '\n' << 1 << '\n' << len << '\n';
		for(int i=0; i<len-1; i++) {
			int id = i+1;
			for(char c='a'; c<='z'; c++) {
				cout << (c==S[i] ? (id+1) : len+1) << (c == 'z' ? "" : " ");
			}
			cout << endl;
		}
		{
			int id = len;
			for(char c='a'; c<='z'; c++) {
				if(c == S[len-1]) {
					cout << id;
				} else {
					cout << len+1;
				}
				if(c != 'z') cout << ' ';
			}
			cout << endl;
		}
		{
			int id = len+1;
			for(char c='a'; c<='z'; c++) {
				cout << id;
				if(c != 'z') cout << ' ';
			}
			cout << endl;
		}
	}
	
	return 0;
}