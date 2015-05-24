//bcw0x1bd2 {{{
#include<bits/stdc++.h>
using namespace std;
#define FZ(n) memset((n),0,sizeof(n))
#define FMO(n) memset((n),-1,sizeof(n))
#define MC(n,m) memcpy((n),(m),sizeof(n))
#define F first
#define S second
#define MP make_pair
#define PB push_back
#define FOR(x,y) for(__typeof(y.begin())x=y.begin();x!=y.end();x++)
#define IOS ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef ONLINE_JUDGE
#define FILEIO(name) \
  freopen(name".in", "r", stdin); \
  freopen(name".out", "w", stdout);
#else
#define FILEIO(name)
#endif

void RI() {}

template<typename... T>
void RI( int& head, T&... tail ) {
	    scanf("%d",&head);
			    RI(tail...);
}

mt19937 rng(0x5EED);
int randint(int lb, int ub) {
    return uniform_int_distribution<int>(lb, ub)(rng);
}
// Let's Fight! }}}

typedef long long LL;

const int MX = 20005;
const int S_LEN = 30;
const int MUL = 47;
const LL MOD = 999997771;

int N = 20000, tag[MX];;
string str[MX];
LL prefix[MX][50];
map<LL,vector<int>> mp;
map<pair<int,int>,int> off;
vector<pair<int,int>> E[MX];

void mod(LL &x){
	x %= MOD;
	if (x < 0) x += MOD;
}
LL fast_pow(LL x, LL y){
	if (!y) return 1;
	LL ret = fast_pow(x,y/2);
	ret = ret * ret % MOD;
	if (y & 1) ret = ret * x % MOD;
	return ret;
}
LL get_hash(int p, int l, int r){
	if (l == 0) return prefix[p][r];
	LL ret = prefix[p][r] - prefix[p][l-1] * fast_pow(MUL, r-l+1);
	mod(ret);
	return ret;
}
int check(int i, int j){
	for (int k=S_LEN; 50-k >= 0; k++){
		LL p1 = get_hash(i, 50-k, 49);
		LL p2 = get_hash(j, 0, k-1);
		if (p1 == p2) return k;
	}
	return -1;
}
int main(){
	FILEIO("genome");
	IOS;
	for (int i=0; i<N; i++){
		getline(cin,str[i]);
		LL v = 0;
		LL PN = 1;
		for (int j=0; j<S_LEN; j++){
			PN = PN*MUL % MOD;
			v = v * MUL + str[i][j];
			mod(v);
		}
		mp[v].PB(i);
		for (int j=S_LEN; j<50; j++){
			v = (v * MUL + str[i][j] - str[i][j-S_LEN] * PN);
			mod(v);
			mp[v].PB(i);
		}
		prefix[i][0] = str[i][0];
		for (int j=1; j<50; j++){
			prefix[i][j] = prefix[i][j-1] * MUL + str[i][j];
			mod(prefix[i][j]);
		}
	}
	for (auto it : mp){
		sort(it.S.begin(), it.S.end());
		it.S.resize(unique(it.S.begin(), it.S.end()) - it.S.begin());
	}
//	cout << "end resize" << endl;
	for (int i=0; i<N; i++){
		LL v = 0;
		for (int j=50-S_LEN; j<50; j++){
			v = v * MUL + str[i][j];
			mod(v);
		}
		vector<int> &vec = mp[v];
		for (auto it : vec){
			if (it == i) continue;
			int offset = check(i,it);
			if (offset != -1){
	//			cout << i << " " << it << " " << offset << endl;
	//			cout << str[i] << endl;
	//			cout << str[it] << endl;
				E[i].PB(MP(it,offset));
				off[MP(i,it)] = offset;
			}
		}
	}
//	cout << "start finding" << endl;
	FZ(tag);
	int opLen = 0;
	while (opLen < 49000){
		int len = 50;
		vector<int> vec;
		int lst = rand() % N;
		vec.PB(lst);
		while (len < 500){
			if (E[lst].size() == 0) break;
			int cnt = 0;
			int nxt;
			while (true){
				nxt = rand() % E[lst].size();
				if (!tag[E[lst][nxt].F]) break;
				cnt++;
				if (cnt > 50) break;
			}
			if (cnt > 50) break;
			len += 50 - E[lst][nxt].S;
			vec.push_back(E[lst][nxt].F);
			tag[E[lst][nxt].F] = 1;
			lst = E[lst][nxt].F;
		}
		for (auto it : vec)
			tag[it] = 0;
		if (len >= 500){
			cout << str[vec[0]];
			for (int i=1; i<(int)vec.size(); i++){
				for (int j = off[MP(vec[i-1],vec[i])]; j<50; j++)
					cout << str[vec[i]][j];
			}
			cout << endl;
			opLen += len;
		}
	}
	return 0;
}

