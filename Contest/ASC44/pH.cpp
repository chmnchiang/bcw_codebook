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

const int MX = 212;
#define konkon NULL
struct Data{
	int zero;
	int one;
	int id;
	Data *lc, *rc;

	Data () { lc = konkon; rc = konkon; }
	Data (int z, int o, int i=-1) :zero(z), one(o), id(i) { lc = konkon; rc = konkon; }

	int sum() {
		return one + zero;
	}
};

int N;
vector<Data*> v[MX];
vector<Data*> temp[MX];
string ans[MX];

void dfs(Data *d, string s) {
	if(d->lc) dfs(d->lc, s+"0");
	if(d->rc) dfs(d->rc, s+"1");
	if(d->id != -1) {
		ans[d->id] = s;
	}
	delete d;
}
int main(){
	FILEIO("huffman");
	
	while(cin >> N and N) {

		for(int i=0; i<MX; i++) v[i].clear();

		int MV = 0;
		for(int i=0; i<N; i++) {
			int o, z; cin >> z >> o;
			Data *d = new Data(z, o, i);
			v[d->sum()].PB(d);
			MV = max(MV, d->sum());
		}

		bool fg = 1;

		for(int i=MV; i>=1; i--) {
			//cout << i << endl;
			int csz = v[i].size();
			for(int j=0; j<=i; j++) temp[j].clear();
			for(int j=0; j<csz; j++) {
				//cout << "ones: " << v[i][j]->one << endl;
				temp[v[i][j]->one].PB(v[i][j]);
			}

			for(int j=0; j<=i; j++) {
				//cout << '*' << j << endl;
				int sz = temp[j].size();
				if(!sz) continue;
				if(sz and j == i) {
					fg = 0;
					break;
				}
				while(temp[j].size()) {
					if(temp[j+1].size()) {
						Data *d1 = temp[j].back(); temp[j].pop_back();
						Data *d2 = temp[j+1].back(); temp[j+1].pop_back();
						Data *df = new Data(d2->zero, d1->one);
						df->lc = d1;
						df->rc = d2;
						//cout << d2->id << ' ' << d1->id << endl;
						v[df->sum()].PB(df);
						//cout << df->sum() << ' ' << df->one << endl;
					} else {
						fg = 0; break;
					}
				}

				if(!fg) break;
			}
			if(!fg) break;
		}
		if(v[0].size() != 1) fg = 0;
		if(not fg){
			cout << "No" << endl;
			continue;
		}
		cout << "Yes" << endl;
		dfs(v[0][0], "");

		for(int i=0; i<N; i++) {
			cout << ans[i] << endl;
		}
	}
	
	return 0;
}

