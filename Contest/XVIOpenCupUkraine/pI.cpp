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

typedef pair<int, int> pii;
typedef multiset<int> msi;

const int MAX = 262144;
const int LG = 18;

int ct[MAX], he[MAX], rk[MAX], sa[MAX], tsa[MAX], tp[MAX][2];
int N, Q;
string s;
int rmq[LG][MAX];
map<pii, int> mpimp;
msi seg[MAX*2];

void suffix_array(const char *ip){

	int len = strlen(ip);
	int alp = 256;

	memset(ct, 0, sizeof(ct));
	for(int i=0;i<len;i++) ct[ip[i]+1]++;
	for(int i=1;i<alp;i++) ct[i]+=ct[i-1];
	for(int i=0;i<len;i++) rk[i]=ct[(int)ip[i]];

	for(int i=1;i<len;i*=2){
		for(int j=0;j<len;j++){
			if(j+i>=len) tp[j][1]=0;
			else tp[j][1]=rk[j+i]+1;
			
			tp[j][0]=rk[j];
		}
		memset(ct, 0, sizeof(ct));
		for(int j=0;j<len;j++) ct[tp[j][1]+1]++;
		for(int j=1;j<len+2;j++) ct[j]+=ct[j-1];
		for(int j=0;j<len;j++) tsa[ct[tp[j][1]]++]=j;

		memset(ct, 0, sizeof(ct));
		for(int j=0;j<len;j++) ct[tp[j][0]+1]++;
		for(int j=1;j<len+1;j++) ct[j]+=ct[j-1];
		for(int j=0;j<len;j++) sa[ct[tp[tsa[j]][0]]++]=tsa[j];

		rk[sa[0]]=0;
		for(int j=1;j<len;j++){
			if( tp[sa[j]][0] == tp[sa[j-1]][0] &&
				tp[sa[j]][1] == tp[sa[j-1]][1] )
				rk[sa[j]] = rk[sa[j-1]];
			else
				rk[sa[j]] = j;
		}
	}

	for(int i=0,h=0;i<len;i++){
		if(rk[i]==0) h=0;
		else{
			int j=sa[rk[i]-1];
			h=max(0,h-1);
			for(;ip[i+h]==ip[j+h];h++);
		}
		he[rk[i]]=h;
	}
}

int lcp(int x, int y)
{
  if(x > y) swap(x, y);
  if(x == y) return MAX;

  int len = y - x;
  int lv = __lg(len);
  return min(rmq[lv][x+1], rmq[lv][y+1-(1<<lv)]);
}

void add_seg(int sn, int lb, int rb, int pos, int val)
{
  if(pos < lb or pos >= rb) return;

  if(rb - lb == 1)
  {
    seg[sn].insert(val);
  }
  else
  {
    seg[sn].insert(val);
    int mb = (lb + rb) / 2;
    add_seg(2*sn, lb, mb, pos, val);
    add_seg(2*sn+1, mb, rb, pos, val);
  }
}

void del_seg(int sn, int lb, int rb, int pos, int val)
{
  if(pos < lb or pos >= rb) return;

  if(rb - lb == 1)
  {
    seg[sn].erase(seg[sn].lower_bound(val));
  }
  else
  {
    seg[sn].erase(seg[sn].lower_bound(val));
    int mb = (lb + rb) / 2;
    del_seg(2*sn, lb, mb, pos, val);
    del_seg(2*sn+1, mb, rb, pos, val);
  }
}

void get_msi(int sn, int lb, int rb, int l, int r, vector<msi*> &vec)
{
  if(rb <= l or r <= lb) return;
  if(l <= lb and rb <= r)
  {
    vec.PB(seg + sn);
  }
  else
  {
    int mb = (lb + rb) / 2;
    get_msi(2*sn, lb, mb, l, r, vec);
    get_msi(2*sn+1, mb, rb, l, r, vec);
  }
}

int get_count(int lb, int rb, int x, int k)
{
  //cout<<"GC "<<lb<<" "<<rb<<" "<<x<<" "<<k<<endl;
  vector<msi*> vec;
  get_msi(1, 0, N, lb, rb, vec);

  int n = vec.size();
  vector<msi::iterator> vit;
  for(auto m: vec)
    vit.PB((*m).lower_bound(x));

  //for(int i=0; i<n; i++){for(auto z: *vec[i]) cout<<z<<",";cout<<endl;}

  int cur = -1;
  for(int i=0; i<k; i++)
  {
    int mn = MAX, idx = -1;
    for(int j=0; j<n; j++)
    {
      msi &m = *vec[j];
      auto &it = vit[j];
      if(it == m.end()) continue;
      int val = *it;
      if(val < mn)
      {
        mn = val;
        idx = j;
      }
    }
    if(idx == -1) return -1;
    cur = mn;
    vit[idx]++;
  }

  return cur;
}

int query(int p, int x, int k)
{
  int v = rk[p];
  int lb = v, rb = v;
  for(int i=MAX/2; i>=1; i>>=1)
  {
    if(lb-i>=0 and lcp(v, lb-i) >= x) lb -= i;
    if(rb+i<N and lcp(v, rb+i) >= x) rb += i;
  }
  rb++;

  //cout<<p<<" "<<x<<" v "<<v<<" : "<<lb<<"~"<<rb<<endl;

  int ans = get_count(lb, rb, x, k);
  return ans;
}

void pre()
{
  N = s.size();
  suffix_array(s.c_str());

  for(int i=0; i<N; i++)
    rmq[0][i] = he[i];

  for(int i=1; i<LG; i++)
  {
    int m1 = (1<<i);
    int m2 = (m1>>1);
    for(int j=0; j+m1<=N; j++)
      rmq[i][j] = min(rmq[i-1][j], rmq[i-1][j+m2]);
  }
  //for(int i=0; i<N; i++) cout<<i<<" : "<<s.substr(sa[i])<<endl;
}

int normalize(int v, int x)
{
  for(int i=MAX/2; i>=1; i>>=1)
  {
    if(v-i>=0 and lcp(v, v-i) >= x)
      v -= i;
  }
  return v;
}

int main() {
  IOS;

  cin>>s;
  reverse(ALL(s));

  pre();

  cin>>Q;
  for(int i=0; i<Q; i++)
  {
    int t, x, p, k;
    cin>>t>>x>>p;
    p = N-p-1;

    if(t == 1 or t == 2)
    {
      int v = normalize(rk[p], x);
      //cout<<v<<" "<<x<<endl;
      pii vx({v, x});

      if(t == 1)
      {
        if(!mpimp[vx])
        {
          add_seg(1, 0, N, v, x);
          mpimp[vx] = true;
        }
      }
      else
      {
        if(mpimp[vx])
        {
          mpimp[vx] = false;
          del_seg(1, 0, N, v, x);
        }
      }
    }
    else
    {
      cin>>k;
      int ans = query(p, x, k);
      cout<<ans<<"\n";
    }
  }

  return 0;
}
