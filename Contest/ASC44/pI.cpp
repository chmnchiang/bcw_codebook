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
typedef pair<LL,LL> pll;

const int MX = 100005;

struct Exam{
	LL d,p,id;
}exam[MX];

int N,M;
pll yap[MX];

bool operator < (const Exam &a, const Exam &b){
	return a.p < b.p;
}

int main(){
	FILEIO("intelligent");
	IOS;
	while (cin >> N && N){
		for (int i=0; i<N; i++){
			cin >> exam[i].d >> exam[i].p;
			exam[i].id = i+1;
		}
		cin >> M;
		for (int i=0; i<M; i++){
			cin >> yap[i].F >> yap[i].S;
		}
		sort(yap,yap+M);
		sort(exam,exam+N,[](Exam a, Exam b){ return a.d < b.d; });
		priority_queue<Exam, vector<Exam> > pq;
		LL cur = 0;
		LL leftDay = 0;
		for (int i=0, j=0; i<N; i++){
			leftDay += exam[i].d - cur - 1;
			while (j < M && yap[j].F < exam[i].d){
				leftDay -= yap[j].S - yap[j].F + 1;
				j++;
			}
			if (leftDay >= exam[i].p){
				leftDay -= exam[i].p;
				pq.push(exam[i]);
			} else if (!pq.empty()){
				Exam tmp = pq.top();
				if (leftDay < leftDay + tmp.p + 1 - exam[i].p){
					leftDay = leftDay + tmp.p + 1 - exam[i].p;
					pq.pop();
					pq.push(exam[i]);
				} else {
					leftDay++;
				}
			} else {
				leftDay++;
			}
			cur = exam[i].d;
		}
		vector<int> ans;
		while (!pq.empty()){
			ans.PB(pq.top().id);
			pq.pop();
		}
		sort(ans.begin(), ans.end());
		cout << ans.size() << "\n";
		for (int i=0; i<(int)ans.size(); i++){
			cout << ans[i] << ((i==(int)ans.size()-1) ? '\n' : ' ');
		}
	}
	return 0;
}

