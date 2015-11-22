#include<bits/stdc++.h>
using namespace std;
#define FZ(n) memset((n),0,sizeof(n))
#define FMO(n) memset((n),-1,sizeof(n))
#define F first
#define S second
#define PB push_back
#define ALL(x) begin(x),end(x)
#define SZ(x) ((int)(x).size())
#define IOS ios_base::sync_with_stdio(0); cin.tie(0)
template<typename A, typename B>
ostream& operator <<(ostream &s, const pair<A,B> &p) {
  return s<<"("<<p.first<<","<<p.second<<")";
}
template<typename T>
ostream& operator <<(ostream &s, const vector<T> &c) {
  s<<"[ ";
  for (auto it : c) s << it << " ";
  s<<"]";
  return s;
}
// Let's Fight!

typedef long long LL;

LL N, N10;
LL ip, best, cost;
string ans;

LL calc(LL a, LL b){
	return min(abs(a-b), N10 - abs(a-b));
}

int main() {
    IOS;
	string str;
	cin >> str;
	N = str.length();
	ip = 0;
	N10 = 1;
	for (int i=0; i<N; i++) {
		ip = ip*10 + str[i]-'0';
		N10 *= 10;
	}
	best = 99999999999LL;
	cost = -1;
	for (int i=1; i<(1<<10); i++) {
		int nl, lst[10];
		nl = 0;
		for (int j=0; j<10; j++) {
			if (i & (1<<j)) lst[nl++] = j;
		}
		if (nl != N) continue;
		do {
			LL x = 0;
			string tmp = "";
			for (int j=0; j<N; j++) {
				x = x * 10 + lst[j];
				tmp += char(lst[j] + '0');
			}
			LL y = calc(x, ip);
			if (y > cost || y == cost && x < best) {
				best = x;
				cost = y;
				ans = tmp;
			}
		} while (next_permutation(lst, lst+nl));
	}
	cout << ans << endl;

    return 0;
}

