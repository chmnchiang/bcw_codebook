#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
#define FZ(n) memset((n),0,sizeof(n))
#define FMO(n) memset((n),-1,sizeof(n))
#define F first
#define S second
#define PB push_back
#define ALL(x) begin(x),end(x)
#define SZ(x) ((int)(x).size())
#define IOS ios_base::sync_with_stdio(0); cin.tie(0)
#define REP(i,x) for (int i=0; i<(x); i++)
#define REP1(i,a,b) for (int i=(a); i<=(b); i++)
#ifdef ONLINE_JUDGE
#define FILEIO(name) \
    freopen(name".in", "r", stdin); \
    freopen(name".out", "w", stdout);
#else
#define FILEIO(name)
#endif
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

#define loop(i, a, b) for (auto (i)=(a); (i)!=(b); (i) += ((b) < (a) ? -1 : 1))
#define au auto
template<typename T>
using Vec = vector<T>;
using pii = pair<int,int>;
int S;
Vec<int> ip;
Vec<int> op;
const double OKr = 1.051/0.949;
const double EPS = 1e-4;

map<int,int> mp;
void pre() {
	mp[0x01] = 0;
	mp[0x11] = 1;
	mp[0x09] = 2;
	mp[0x18] = 3;
	mp[0x05] = 4;
	mp[0x14] = 5;
	mp[0x0C] = 6;
	mp[0x03] = 7;
	mp[0x12] = 8;
	mp[0x10] = 9;
	mp[0x04] = 10;
	mp[0x06] = -1;
}

const string BAD = "bad code";
const string BADC = "bad C";
const string BADK = "bad K";

char toChar(int v) {
	if (v < 10) return '0'+v;
	if (v == 10) return '-';
	cout << v << endl;
	assert(false);
}

bool check(double x) {
	op.clear();
	double mn1 = x*0.95, mn2 = x*1.05, mx1 = x*2*0.95, mx2 = x*2*1.05;
	for (auto y: ip) {
		if (mn1 < y+EPS and y < mn2+EPS) op.PB(0);
		else if (mx1 < y+EPS and y < mx2+EPS) op.PB(1);
		else return false;
	}
	return true;
}

string calc() {
	//int mn=*min_element(ALL(ip)), mx=*max_element(ALL(ip));
	//cout << mn << ' ' << mx << endl;
	//if (1.0*mx/mn > 2.2 or 1.0*mx/mn < 1.8) return BAD;
	op.clear();
	bool ok = false;
	for (auto x: ip) {
		if (ok = check(x)) break;
		if (ok = check(x/0.95)) break;
		if (ok = check(x/1.05)) break;
		if (ok = check(x/2.0/0.95)) break;
		if (ok = check(x/2.0)) break;
		if (ok = check(x/2.0/1.05)) break;
	}
	if (!ok) return BAD;
	int L = SZ(op);
	//cout << "Hao" << endl;
	if ((L+1)%6) return BAD;
	//cout << "Hao" << endl;
	int N = (L+1)/6;
	if (N<=4) return BAD;
	int t = op[0]*16+op[1]*8+op[2]*4+op[3]*2+op[4];
	if (mp.find(t) == mp.end() or mp[t] != -1) 
		reverse(ALL(op));
	//cout << "Hao" << endl;

	int c = 0;
	int k = 0;
	int M = N-4;
	string ret;
	loop (i, 0, N) {
		int bg = i*6;
		int val=0;
		loop (j, 0, 5) {
			val<<=1;
			val+=op[bg+j];
		}
		if (mp.find(val) == mp.end()) return BAD;

		if (i != N-1 and op[bg+5]) return BAD;

		if (i == 0 or i == N-1) {
			if (mp[val] != -1) return BAD;
		} else if (i < N-3) {
			int v = mp[val];
			c += ((M-i)%10+1)*v; c%=11;
			k += ((M-i+1)%9+1)*v; k%=11;
			ret += toChar(mp[val]);
			//cout << toChar(mp[val]) << endl;
		} else if (i == N-3) {
			if (mp[val] != c) return BADC;
			k += ((M-i+1)%9+1)*c; k%=11;
		} else if (i == N-2) {
			if (mp[val] != k) return BADK;
		}
	}
	return ret;
}

int main() {
	pre();
	IOS;
	int cas=0;
	while (true) {
		cin>>S;
		if (!S) break;
		ip.resize(S);
		loop (i, 0, S) {
			cin>>ip[i];
		}
		cas++;
		cout<<"Case "<<cas<<": "<<calc()<<endl;
	}

	return 0;
}

