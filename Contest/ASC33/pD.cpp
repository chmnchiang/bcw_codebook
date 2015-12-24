#include<bits/stdc++.h>
using namespace std;
#define REP(n,i) for(int (i)=0;(i)<(n);(i)++)
#define CDREP(n,i) for(int (i)=((n)−1);(i)>=0;(i)−−)
#define CDFOR(s,e,i) for(int i=((e)−1);(i)>=(s);(i)−−)
#define _SZ(n) memset((n),0,sizeof(n))
#define _SMO(n) memset((n),−1,sizeof(n))
#define _MC(n,m) memcpy((n),(m),sizeof(n))
#define _F first
#define _S second
#define _MP(a,b) make_pair((a),(b))
#define _PB(a) push_back((a))
#define FOR(x,y) for(__typeof(y.begin())x=y.begin();x!=y.end();x++)
#define IOS ios_base::sync_with_stdio(0);
#ifdef ONLINE_JUDGE
#define FILEIO(name) \
    freopen(name".in", "r", stdin); \
    freopen(name".out", "w", stdout);
#else
#define FILEIO(name)
#endif
//Let's Fight!

const int INF = 1029384756;

struct rule_t{
	int lowCnt,upCnt,len,u;
	char s[15];
	rule_t(){ lowCnt = upCnt = 0; }
}rule[1024];

int fail;
int N,eg[30][30];
int fr,bk,que[30],inq[30],vst[30],dis[30];
int epsilonOnly[30];

void input(){
	scanf("%d", &N);
	for (int i=0; i<N; i++){
		scanf("%s", rule[i].s);
		rule[i].len = strlen(rule[i].s);
		rule[i].u = rule[i].s[0] - 'A';
		for (int j=3; j<rule[i].len; j++){
			if (islower(rule[i].s[j]))
				rule[i].lowCnt++;
			else if (isupper(rule[i].s[j]))
				rule[i].upCnt++;
		}
	}
}
void build(){
	for (int i=0; i<30; i++){
		for (int j=0; j<30; j++){
			eg[i][j] = INF;
		}
	}
	fill(epsilonOnly,epsilonOnly+30,1);
	for (int t=0; t<100; t++){
		for (int i=0; i<N; i++){
			if (rule[i].lowCnt){
				epsilonOnly[rule[i].u] = 0;
			}
			for (int j=3; j<rule[i].len; j++){
				if (isupper(rule[i].s[j]) && !epsilonOnly[rule[i].s[j]-'A']){
					epsilonOnly[rule[i].u] = 0;
				}
			}
		}
	}
	for (int i=0; i<N; i++){
		vector<int> vec;
		for (int j=3; j<rule[i].len; j++){
			if (isupper(rule[i].s[j])){
				vec._PB(rule[i].s[j]-'A');
			}
		}
		int w = rule[i].lowCnt;
		int w2 = 0;
		for (auto v: vec){
			if (!epsilonOnly[v])
				w2++;
		}
		for (auto v : vec){
			if (w + w2 > 1){
				eg[rule[i].u][v] = -1;
			} else {
				eg[rule[i].u][v] = 0;
			}
		}
	}
}
void solve(){
	fail=0;
	fr = bk = 0;
	for (int i=0; i<30; i++){
		dis[i] = INF;
	}
	dis['S'-'A'] = 0;
	que[bk++] = 'S'-'A';
	_SZ(inq);
	inq['S'-'A'] = 1;
	while (fr != bk){
		int u =que[fr++];
		inq[u] = 0;
		if (vst[u] >= 514){
			fail = 1;
			break;
		}
		if (fr >= 30)
			fr -= 30;
		for (int v=0; v<30; v++){
			int w = eg[u][v];
			if (w == INF)
				continue;
			if (dis[v] > dis[u] + w){
				dis[v] = dis[u] + w;
				if (!inq[v]){
					inq[v] = 1;
					que[bk++] = v;
					if (bk >= 30)
						bk -= 30;
					vst[v]++;
				}
			}
		}
	}
	if (fail)
		puts("infinite");
	else
		puts("finite");
}

int main(){
	FILEIO("cyclic");
	input();
	build();
	solve();
	return 0;
}
