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

const int MX = 20290;
int T;
//string ip;
int lst[MX];
int pnt[MX];

int judge(string s) {
	int len = s.length();
	for (int i=0; i<=len; i++) {
		lst[i] = 0;
		pnt[i] = 0;
	}

	int k = 0;
	int mn = 0;
	for (int i=0; i<len; i++) {
		if (s[i] == '*') {
			k --;
			int nk = -k;
			lst[nk] = i;
			if (k < 0) {
				mn = min(mn, k);
			}
		} else {
			if (k < 0) {
				int nk = -k;
				pnt[nk] += (i - lst[nk]) / 2 + 1;
			}
			k++;
		}
	}

	int ans = 1029384756;
	int tt = 0;
	for (int i=-mn; i>=0; i--) {
		ans = min(ans, i+tt);
		tt += pnt[i];
	}
	return ans;
}

int solve(string ip) {
	//cout << ip << endl;
	int len = ip.length();
	int nstar = 0, ndig = 0;
	for (int i=0; i<len; i++) {
		if (isdigit(ip[i])) {
			ip[i] = '1';
			ndig ++;
		} else {
			nstar ++;
		}
	}
	if (not nstar) {
		return 0;
	}

	int ans = 0;
	int t = max(0, nstar - ndig + 1);
	string s = "";
	for (int i=0; i<t; i++) {
		s += "1";
		ndig ++;
		ans ++;
	}
	ip = s + ip;
	len = ip.length();

	if (ip[len-1] == '1') {
		ans ++;
		int j=-1;
		for (int k=0; k<len; k++) {
			if (ip[k] == '*') {
				j = k; break;
			}
		}
		swap(ip[j], ip[len-1]);
	}



	t = 0;
	for (int i=0; i<len; i++) {
		if (ip[i] == '1') {
			t++;
		} else {
			t--;
			if ((t <= 0 and i) or (t < 0 and (i == 0))) {
				t += 2;
				int j=-1;
				for (int k=len-1; k>=0; k--) {
					if (ip[k] == '1') {
						j = k; break;
					}
				}
				swap(ip[i], ip[j]);
				ans ++;
			}
		}
	}


	return ans;
}

int main() {
    IOS;
	cin >> T;
	while (T--) {
		string ip;
		cin >> ip;
		int ans = solve(ip);
		cout << ans << endl;
	}

    return 0;
}
