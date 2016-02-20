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
#include <sys/resource.h>
void increase_stack_size() {
  const rlim_t ks = 64*1024*1024;
  struct rlimit rl;
  int res=getrlimit(RLIMIT_STACK, &rl);
  if(res==0){
    if(rl.rlim_cur<ks){
      rl.rlim_cur=ks;
      res=setrlimit(RLIMIT_STACK, &rl);
    }
  }
}

typedef long long ll;

const int MAXN = 10101;

ll N;
int n1, a1, n2, a2;

ll ten[MAXN];

void make_ten()
{
	ten[1] = 1 % N;
	for(int i=2; i<MAXN; i++)
		ten[i] = (ten[i-1] * 10 + 1) % N;
}

bool check()
{
	if(n1+n2 <= 5)
	{
		ll val = 0;
		for(int i=0; i<n1; i++)
			val = val * 10 + a1;
		for(int i=0; i<n2; i++)
			val = val * 10 + a2;
		if(val == N) return false;
	}

	ll res = (ten[n1+n2] - ten[n2]) * a1 + ten[n2] * a2;
	res %= N;
	return res == 0;
}

void calc()
{
	make_ten();
	unordered_set<ll> st[20];

	for(int all=1; all<MAXN; all++)
	{
		for(a1=1; a1<=9; a1++)
		{
			ll th = (ten[all] * a1) % N;
			bool any = false;
			for(a2=0; a2<=9; a2++)
			{
				if(a1 == a2) continue;
				int t = 10 + a1 - a2;
				if(st[t].count(th))
					any = true;
			}
			if(!any) continue;
			for(n1=1; n1<all; n1++)
			{
				n2 = all - n1;
				for(a2=0; a2<a1; a2++)
				{
					if(check()) return;
				}
			}
			for(n1=all-1; n1>=1; n1--)
			{
				n2 = all - n1;
				for(a2=a1+1; a2<=9; a2++)
				{
					if(check()) return;
				}
			}
//			cout<<all<<" QQ ";
		}
		for(int i=-9; i<=9; i++)
		{
			ll z = (ten[all] * i) % N;
			if(z<0) z += N;
			st[10+i].insert(z);
		}
	}
	assert(false);
}

int main() {
	IOS;
	increase_stack_size();

//	for(N=1; N<=99999; N++)
	while(cin>>N && N)
	{
		calc();
		cout<<N<<": "<<n1<<" "<<a1<<" "<<n2<<" "<<a2<<endl;
	}

    return 0;
}

