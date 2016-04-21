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

typedef long long ll;
typedef pair<ll, ll> pll;
typedef pair<ll, int> pli;
const int MXM = 1000005;
const ll H1 = 72127, H2 = 12721;
const ll MOD = 999888733;
//const ll H = 10;
//const ll MOD = 1e6+3;

ll N,M;
int ip[MXM];
pll pw[MXM];
pli mp[MXM];
pll hp1[1<<15], hp2[1<<15];
//int st[MXM];
vector<ll> va;

inline pll operator+(pll a, pll b)
{
  pll ret = {a.F+b.F, a.S+b.S};
  if(ret.F >= MOD) ret.F -= MOD;
  if(ret.S >= MOD) ret.S -= MOD;
  return ret;
}
inline pll operator-(pll a, pll b)
{
  pll ret = {a.F-b.F, a.S-b.S};
  if(ret.F < 0) ret.F += MOD;
  if(ret.S < 0) ret.S += MOD;
  return ret;
}
inline pll operator*(pll a, pll b) {return {a.F*b.F % MOD, a.S*b.S % MOD};}

inline pll zpow(ll p, pll a={H1, H2}) {
  pll ret = {1, 1};
  pll cur = a; 
  p %= MOD-1;
  while(p)
  {
    if(p&1LL)
      ret = ret * cur;
    cur = cur * cur;
    p >>= 1;
  }
  return ret;
}

inline pll ypow(ll p)
{
  p %= MOD-1;
  return hp1[p&0x7fff] * hp2[p>>15];
}

inline pll zrev(pll x) {
  return zpow(MOD-2, x);
}
void check(ll S, ll K) {
 //if(N>=100000)  cout << "CHECK " << S << " " << K << endl;
  //vector<ll> vv;
	//REP(i,M) {
		//ll L = (S+i*K)%N;
    //vv.PB(L);
	//}
  //sort(ALL(vv));
  //if(vv != va) return;
	cout << S << " " << K << endl;
	exit(0);
}

int count(pll x)
{
  ll y = (x.F<<32) | x.S;
  auto it = lower_bound(mp, mp+M, pli(y, -1));
  if(it == mp+M || it->F != y) return -1;
  return it->S;
}

bool scount(int x)
{
  auto it = lower_bound(ip, ip+M, x);
  return it != ip+M && (*it) == x;
}

void solve() {
	if (M == 1) {
		cout << ip[0] << " " << 1 << endl;
		return;
	}
	vector<int> deq;
	REP(i,M) {
		deq.push_back(ip[i]);
    //va.PB(ip[i]);
	}

	pll sum = {0, 0};
	REP(i,M) {
		pw[i] = ypow(ip[i]);
    //st[i] = ip[i];
    mp[i] = {(pw[i].F<<32) | pw[i].S, ip[i]};
		sum = sum + pw[i];
	}

  //sort(st, st+M);
  sort(mp, mp+M);

  ll g = 0;
  for(int i=1; i<M; i++)
    g = __gcd(g, (ll)ip[i]-ip[0]);
  if(M * g == N)
    check(ip[0], g);

	pll oris = sum;
	ll lstd = 0;
  pll zpn = ypow(N);
  pll rzpn = zrev(zpn);
  pll ozone = pll(1, 1) - zpn;
	REP1(i,1,M-1) {
    //if(i%50000==0) cout<<i<<"XD"<<endl;
		ll d = ip[i] - ip[0];
		sum = sum * ypow(d-lstd);
		while (!deq.empty() and deq.back()+d >= N) {
      sum = sum + ypow(deq.back()+d-N) * ozone;
			deq.pop_back();
		}

		lstd = d;
    if(__gcd(d, N) != g) continue;

    bool ok = true;
    int nc = 0;
    for(int j=0; j<M && j<10; j++)
      if(!scount((ip[j]+d)%N))
      {
        nc++;
        if(nc>=2)
        {
          ok=false;
          break;
        }
      }
    if(!ok) continue;

		ll D = M * d % N;
		if (D == 0) {
			//if(sum == oris)
				//check(ip[0], d);
		} else {
      pll zpd = ypow(D);
			pll alpha = zpd - pll(1, 1);
			pll dh = sum - oris;
			pll dz = dh * zrev(alpha);
      int c = count(dz);
      if(c != -1) {
        check(c, d);
			}
			
			alpha = zpd * rzpn - pll(1, 1);
			dz = dh * zrev(alpha);
      c = count(dz);
      if(c != -1) {
        check(c, d);
			}
		}
	}
	cout << "-1 -1" << endl;
}
void pre()
{
  for(int i=0; i<(1<<15); i++)
  {
    hp1[i] = zpow(i);
    hp2[i] = zpow(i<<15);
  }
}

int main() {
	//IOS;
  pre();

  int nn, mm;
  scanf("%d%d", &nn, &mm);
  N = nn, M = mm;
	REP(i,M) {
    scanf("%d", &ip[i]);
	}

	solve();

	return 0;
}
