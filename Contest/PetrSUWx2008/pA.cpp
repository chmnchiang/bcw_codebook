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
#define loop(i, a, b) for (auto (i)=(a); (i) != (b); (i) += ((b) < (a) ? -1 : 1))

const int MXN = 300005;
const int LEN = 5000005;

struct Orc {
	string nm;
	int pt;
	vector<int> vec;
}ip[MXN];

int N,M,K,rem[MXN];
int pri[256];
vector<string> army[MXN];
int slen;
char str[LEN];

int gn(int &id) {
	assert(id < slen);
	while (id < slen and !isdigit(str[id])) {
		id++;
	}
	int res = 0;
	while (id < slen and isdigit(str[id])) {
		res = res * 10 + str[id] - '0';
		id++;
	}
	return res;
}
bool comp(Orc x, Orc y) {
	return x.pt > y.pt;
}
bool comp_str(string x, string y) {
	int lx = SZ(x);
	int ly = SZ(y);
	REP(i,min(lx,ly)) {
		int a = pri[(int)x[i]];
		int b = pri[(int)y[i]];
		if (a != b) return a < b;
	}
	return lx < ly;
}
int main() {
	FILEIO("army");
	scanf("%d%d%d",&N,&M,&K);
	REP(i,M) scanf("%d",&rem[i]);
	fgets(str,LEN,stdin);
	REP(i,N) {
		fgets(str,LEN,stdin);
		slen = strlen(str);
		int pos = 0;
		int lst = 0;
		while (pos < slen and !isdigit(str[pos])) {
			if (str[pos] != ' ') lst = pos;
			pos++;
		}
		ip[i].pt = gn(pos);
		int m = gn(pos);
		REP(_,m) {
			ip[i].vec.PB(gn(pos)-1);
		}

		str[lst+1] = 0;
		ip[i].nm = string(str);
	}
	sort(ip,ip+N,comp);
	REP(i,N) {
		for (auto id:ip[i].vec) {
			if (rem[id] > 0) {
				rem[id]--;
				army[id].PB(ip[i].nm);
				break;
			}
		}
	}

	REP(i,256) pri[i] = 1029384756;
	int step = 0;
	pri[' '] = step++;
	REP(i,26) {
		pri['A'+i] = step++;
		pri['a'+i] = step++;
	}

	REP(i,M) sort(ALL(army[i]), comp_str);
	REP(i,M) {
		for (auto it:army[i]) printf("%s\n", it.c_str());
		puts("");
	}

	return 0;
}
