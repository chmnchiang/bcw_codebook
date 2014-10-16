#include <bits/stdc++.h>
using namespace std;
#define _SZ(n) memset((n),0,sizeof(n))
#define _SMO(n) memset((n),-1,sizeof(n))
#define _MC(n,m) memcpy((n),(m),sizeof(n))
#define _F first
#define _S second
#define _MP make_pair
#define _PB push_back
#define FOR(x,y) for(__typeof(y.begin())x=y.begin();x!=y.end();x++)
#define IOS ios_base::sync_with_stdio(0)
 
#ifdef ONLINE_JUDGE
#define FILEIO(name) \
	freopen(name".in", "r", stdin); \
    freopen(name".out", "w", stdout);
#else
#define FILEIO(name)
#endif
// Let's Fight!
 
typedef long long LL;
 
const int MXN = 130005;
const int MX = 300005;
const int HASH = 12721;
const int MOD = 999997771;
const int LOG = 17;
struct query_t{
	int ti,sj,id;
};
struct tTree_t{
	int tp, prvID, prvID2;
	char ch;
	int l,r,len;
}tTree[MXN];
vector<int> E[MXN];
vector<query_t> q[MXN];

int sa[MXN],rk[MXN],rk2[MXN],fa[LOG][MXN],sCh[MXN],cmpLv;
pair<int,int> azRange[30];
int N,nq;
int tID,sID;
int ans[MXN];

inline int getRank(int id){
	if (id == 0) return 0;
	if (id >= sID) while(1);
	return rk[id];
}
bool comp0(int a, int b){
	return sCh[a] < sCh[b];
}
bool comp1(int a, int b){
	if (getRank(a) == getRank(b)){
		return getRank(fa[cmpLv][a]) < getRank(fa[cmpLv][b]);
	}
	return getRank(a) < getRank(b);
}
void suffix_array(){
	sCh[1] = 0;
	for (int i=1; i<sID; i++){
		sa[i] = i;
		rk[i] = sCh[i];
	}
	sort(sa+1,sa+sID,comp0);
	cmpLv = 0;
	for (int len = 1; len < MXN; len <<= 1){
		sort(sa+1,sa+sID,comp1);
		int r = 1;
		rk2[sa[1]] = r;
		for (int i=2; i<sID; i++){
			if (comp1(sa[i-1],sa[i])){
				rk2[sa[i]] = ++r;
			} else {
				rk2[sa[i]] = r;
			}
		}
		for (int i=1; i<sID; i++){
			rk[i] = rk2[i];
		}
		cmpLv++;
	}
}

void init(){
	nq = 0;
	tID = 2;
	sID = 2;
	_SZ(fa);
}
int trash;
void input(){
	init();
	trash = scanf("%d", &N);
	for (int i=0; i<N; i++){
		int cmd;
		trash = scanf("%d", &cmd);
		if (cmd == 1){
			int prvID;
			char str[10];
			trash = scanf("%d%s", &prvID, str);
			E[prvID]._PB(sID);
			fa[0][sID] = prvID;
			sCh[sID] = str[0];
			sID++;
		} else if (cmd == 2){
			int dir;
			int prvID;
			char str[5];
			trash = scanf("%d%d%s", &dir,&prvID,str);
			if (dir == 0){
				tTree[tID].tp = 0;
				tTree[tID].prvID = prvID;
				tTree[tID++].ch = str[0];
			} else {
				tTree[tID].tp = 1;
				tTree[tID].prvID = prvID;
				tTree[tID++].ch = str[0];
			}
		} else if (cmd == 3){
			int a,b;
			trash = scanf("%d%d", &a, &b);
			tTree[tID].tp = 2;
			tTree[tID].prvID = a;
			tTree[tID++].prvID2 = b;
		} else if (cmd == 4){
			int ti,sj;
			trash = scanf("%d%d", &ti, &sj);
			q[sj]._PB((query_t){ti,sj,nq});
			nq++;
		}
	}
}
int moveUP(int u, int len){
	for (int i=0; i<LOG && len; i++){
		if (len & (1<<i)){
			len -= 1<<i;
			u = fa[i][u];
		}
	}
	return u;
}
int getL(int l, int r, int up, int cp){
	if (l == r) return l;
	while (l < r){
		int mid = (l+r) / 2;
		int id = moveUP(sa[mid],up);
		if (cp <= rk[id])
			r = mid;
		else
			l = mid+1;
	}
	return l;
}
int getR(int l, int r, int up, int cp){
	if (l == r) return l;
	while (l < r){
		int mid = (l+r) / 2;
		int id = moveUP(sa[mid],up);
		if (cp < rk[id])
			r = mid;
		else
			l = mid+1;
	}
	return l;
}
void prvSolve(){
	for (int i=1; i<LOG; i++){
		for (int j=1; j<sID; j++){
			fa[i][j] = fa[i-1][fa[i-1][j]];
		}
	}
	suffix_array();
	for (int i=0; i<30; i++)
		azRange[i] = _MP(sID,0);
	for (int i=1; i<sID; i++){
		if (sa[i] == 1) continue;
		int ch = sCh[sa[i]] - 'a';
		azRange[ch]._F = min(azRange[ch]._F,i);
		azRange[ch]._S = max(azRange[ch]._S,i);
	}
	for (int i=0; i<30; i++){
		azRange[i]._S++;
		if (azRange[i]._S == 1){
			azRange[i]._F = azRange[i]._S = sID;
		}
	}

	tTree[1].len = 0;
	tTree[1].l = 1;
	tTree[1].r = sID;
	for (int i=2; i<tID; i++){
		int id1 = tTree[i].prvID;
		int id2 = tTree[i].prvID2;
		if (tTree[i].tp == 0){
			tTree[i].len = tTree[id1].len + 1;
			int up = tTree[id1].len;
			char ch = tTree[i].ch;
			int l,r;
			l = tTree[id1].l;
			r = tTree[id1].r;
			if (l == r){
				tTree[i].l = tTree[i].r = l;
			} else {
				while (l < r){
					int mid = (l+r)/2;
					int id = moveUP(sa[mid],up);
					if (ch <= sCh[id])
						r = mid;
					else
						l = mid+1;
				}
				tTree[i].l = l;

				l = tTree[id1].l;
				r = tTree[id1].r;
				while (l < r){
					int mid = (l+r)/2;
					int id = moveUP(sa[mid],up);
					if (ch < sCh[id])
						r = mid;
					else
						l = mid+1;
				}

				tTree[i].r = r;
			}
		} else if (tTree[i].tp == 1){
			tTree[i].len = tTree[id1].len + 1;
			int ch = tTree[i].ch;
			int l = azRange[ch-'a']._F;
			int r = azRange[ch-'a']._S;
			if (id1 == 1){
				tTree[i].l = l;
				tTree[i].r = r;
			} else {
				tTree[i].l = getL(l,r,1,tTree[id1].l);
				tTree[i].r = getR(l,r,1,tTree[id1].r-1);
			}
		} else if (tTree[i].tp == 2){
			tTree[i].len = tTree[id1].len + tTree[id2].len;
			tTree[i].len = min(tTree[i].len,100005);
			if (tTree[i].len < 100000){
				int up = tTree[id2].len;
				int l = tTree[id2].l;
				int r = tTree[id2].r;
				tTree[i].l = getL(l,r,up,tTree[id1].l);
				tTree[i].r = getR(l,r,up,tTree[id1].r-1);
			} else {
				tTree[i].l = tTree[i].r = sID-1;
			}
		}
	}
}
int bit[MXN];
int lb(int a){ return a & -a; }
void update(int st, int v){
	for (int i=st; i<sID; i+=lb(i))
		bit[i] += v;
}
int query(int st){
	int res = 0;
	for (int i=st; i>0; i-=lb(i))
		res += bit[i];
	return res;
}
void DFS(int u){
	update(rk[u],1);
	FOR(it,q[u]){
		int id = it->ti;
		if (tTree[id].len == 0 || tTree[id].len > 100000)
			ans[it->id] = 0;
		else
			ans[it->id] = query(tTree[id].r-1) - query(tTree[id].l-1);
	}
	FOR(it,E[u])
		DFS(*it);
	update(rk[u],-1);
}
void solve(){
	DFS(1);
	for (int i=0; i<nq; i++)
		printf("%d\n", ans[i]);
}
int main(){
	input();
	prvSolve();
	solve();

	return 0;
}

