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

typedef pair<int, int> pii;

const int MAXN = 11;

int N;
int arr[MAXN];

int main(){
  FILEIO("comparator");
  IOS;

  while(cin>>N && N)
  {
    for(int i=0; i<N; i++)
      cin>>arr[i];
    int r0 = -1, l1 = -1;
    for(int i=0; i<N; i++)
      if(arr[i] == 0) r0 = i;
    for(int i=N-1; i>=0; i--)
      if(arr[i] == 1) l1 = i;
    if(r0 == -1 || l1 == -1 || r0 < l1)
    {
      cout<<-1<<endl;
      continue;
    }

    int n0 = 0, n1 = 0;
    for(int i=0; i<N; i++)
      if(arr[i] == 0) n0++;
      else n1++;

    vector<pii> vec;
    for(int i=0; i<N; i++)
      for(int j=i+1; j<N; j++)
        if(arr[i] == arr[j])
          vec.PB(MP(i, j));

    for(int i=0; i<N; i++)
      for(int j=i+1; j<N; j++)
        if(i != r0 && i != l1 && j != r0 && j != l1)
          vec.PB(MP(i, j));

    for(int i=0; i<l1; i++)
      vec.PB(MP(i, r0));
    for(int i=0; i<l1; i++)
      vec.PB(MP(i, l1));
    for(int i=N-1; i>r0; i--)
      vec.PB(MP(l1, i));
    for(int i=N-1; i>r0; i--)
      vec.PB(MP(r0, i));

    for(int i=r0-1; i>=n0; i--)
      vec.PB(MP(l1, i));
    for(int i=l1+1; i<=n0-1; i++)
      vec.PB(MP(i, r0));
    for(int i=n0; i<=r0-1; i++)
      vec.PB(MP(i, r0));
    for(int i=n0-1; i>=l1+1; i--)
      vec.PB(MP(l1, i));

    cout<<vec.size()<<endl;
    for(auto i: vec)
      cout<<i.F+1<<" "<<i.S+1<<endl;

    /*for(int i=0; i<(1<<N); i++)
    {
      int x[N];
      for(int j=0; j<N; j++)
        x[j] = !!(i&(1<<j));

      for(auto j: vec)
        if(x[j.F] > x[j.S])
          swap(x[j.F], x[j.S]);
      
      bool ok = true;
      for(int j=0; j<N; j++)
        for(int k=j+1; k<N; k++)
          if(x[j]>x[k])
            ok = false;
      if(!ok)
      {
        for(int j=0; j<N; j++)
          cout<<(i&(1<<j))<<" ";
        cout<<endl;
      }
    }*/
  }

	return 0;
}

