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

typedef long long ll;

const int MAXN = 35;

ll ans[MAXN];

class State
{
	public:
		int n;
		int A;
		int l;
		vector<int> vec;
		State() {};
		State (int _n, int _A, int _l, vector<int> _vec){
			n = _n; A = _A; l = _l; vec = _vec;
		}
		bool operator < (const State &b) const{
			return tie(n,A,l,vec) < tie(b.n, b.A, b.l, b.vec);
		}
};

map<State, ll> mp;

void make_dp()
{
	vector<int> v;
	v.PB(0);
	mp[State(1, 0, 0, v)] = 1;

	while(!mp.empty())
	{
		State st = mp.begin()->F;
		ll num = mp.begin()->S;
		mp.erase(mp.begin());
		
		if(st.n > 32) continue;

		ans[st.n] += num;

		//cout<<st.n<<" "<<st.A<<" "<<st.l<<" Alpha"<<endl;

		for (int y=st.l; y<=st.A+1; y++)
		{
			State st2 = st;
			if(y > st2.vec.back())
			{
				while(!st2.vec.empty() && st2.vec.back() <= y)
				{
					if(st2.vec.back() < y) st2.l = st2.vec.back();
					st2.vec.pop_back();
				}
				st2.vec.PB(y);
				st2.A++;
				st2.n++;
			}
			else
			{
				if(st2.vec.back() > y)
					st2.vec.PB(y);
				st2.n++;
			}

			mp[st2] += num;
		}
	}
}

int main(){
	make_dp();

	//for(int i=0; i<MAXN; i++)
	//	cout<<i<<" "<<ans[i]<<endl;
	
	FILEIO("catalian");

	int N;
	int cnt = 0;
	while(cin>>N && N)
	{
		cnt += 1;
		cout<<"Case #"<<cnt<<": "<<ans[N]<<endl;
	}

	return 0;
}

