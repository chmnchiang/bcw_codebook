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

typedef long long i64;
const int MX = 500000;
int T;
int lv[MX];
int lst[MX];

i64 solve(string s) {
	//cout << "s = " << s << endl;
	int len = s.length();
	int sm = 0;
	int mn = 0;
	FZ(lv);
	for (int i=0; i<len; i++) {
		if (s[i] == 'a') {
			if (sm < 0) {
				lv[-sm] += (i - lst[-sm])/2 + 1;
				//cout << sm << ' ' << lv[-sm] << endl;
			}
			sm ++;
		} else {
			sm --;
			if (sm < 0) {
				lst[-sm] = i;
			}
		}
		mn = min(mn, sm);
	}

	i64 ans = 1029384756102938LL;
	i64 q = 0;
	for (int i=mn; i<=0; i++) {
		ans = min(ans, (-i)*2LL+q);
		q += lv[-i];
	//	cout << -i << ' ' << q << endl;
	}
	//cout << ans << endl;
	return ans;
}

int main() {
	IOS;
	cin >> T;
	for (int cas=1; cas<=T; cas++) {
		string S;
		cin >> S;
		int L = S.length();
		int sm = -1;
		for (int i=0; i<L; i++) {
			if (S[i] == 'a') sm++;
			else sm --;
		}

		
		string s = "";
		for (int i=0; i<abs(sm); i++) {
			if (sm > 0) s += "+";
			else s += "a";
		}
		if (sm > 0) S = S + s;
		else S = s + S;

		int fa = -1, len = S.length();
		for (int i=0; i<len; i++) {
			if (S[i] == 'a') {
				fa = i;
				break;
			}
		}

		i64 ans = 1029384756102938ll;
		if (fa != -1) {
			string ss = "";
			//cout << fa << endl;
			for (int i=0; i<fa; i++) {
				ss += S[i];
			}
			for (int i=fa+1; i<len; i++) {
				ss += S[i];
			}
			ans = min(ans, solve(ss)+fa);
		}

		S += "+";
		ans = min(ans, solve(S)+2);
		cout << "Case " << cas << ": " << ans+abs(sm) << endl;
	}

    return 0;
}

