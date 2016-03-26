//bcw0x1bd2 {{{
#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
#define F first
#define S second
#define MP make_pair
#define PB push_back
#define IOS ios_base::sync_with_stdio(0); cin.tie(0);
#define SZ(x) ((int)((x).size()))
#define ALL(x) begin(x),end(x)
#define REP(i,x) for (int i=0; i<(x); i++)
#define REP1(i,a,b) for (int i=(a); i<=(b); i++)

typedef long long lll;
typedef pair<int,int> pii;
typedef pair<lll,lll> pll;
typedef long double ld;

#ifdef DARKHH
#define FILEIO(name)
#else
#define FILEIO(name) \
  freopen(name".in", "r", stdin); \
  freopen(name".out", "w", stdout);
#endif

#ifdef DARKHH
template<typename Iter>
ostream& _out(ostream &s, Iter b, Iter e) {
    s << "[ ";
    for ( auto it=b; it!=e; it++ ) s << *it << " ";
    s << "]";
    return s;
}
template<typename A, typename B>
ostream& operator << (ostream &s, const pair<A,B> &p) { return s<<"("<<p.first<<","<<p.second<<")"; }
template<typename T>
ostream& operator << (ostream &s, const vector<T> &c) { return _out(s,ALL(c)); }
template<typename T, size_t N>
ostream& operator << (ostream &s, const array<T,N> &c) { return _out(s,ALL(c)); }
template<typename T>
ostream& operator << (ostream &s, const set<T> &c) { return _out(s,ALL(c)); }
template<typename A, typename B>
ostream& operator << (ostream &s, const map<A,B> &c) { return _out(s,ALL(c)); }
#endif
// }}}
// Let's Fight! ~OAO~~

#define loop(i, a, b) for (auto (i)=(a); (i)!=(b); (i)+=((a)>(b)?-1:1))

struct Con
{
    char a, b, c, d;
};

const int MX = 55;
int N, M;
int ip[MX][MX], iq[MX][MX];
int sr[MX], sc[MX];
vector<Con> vec[5];

int cnt(int i, int j, int k, int l)
{
    return iq[i][k] + iq[i][l] + iq[j][k] + iq[j][l];
}

void clear(int i, int j)
{
    iq[i][j] = 0;
    for(int k=0; k<M; k++)
    {
        for(int l=0; l<N; l++)
        {
            if(k == i || l == j) continue;
            int a = min(i, k), b = max(i, k), c = min(j, l), d = max(j, l);
            int v = cnt(a, b, c, d);
            if(v == 0) continue;
            vec[v].PB({a, b, c, d});
        }
    }
}

int calc()
{
    for(int i=0; i<M; i++)
        for(int j=0; j<N; j++)
            iq[i][j] = ip[i][j];

    for(int i=0; i<M; i++)
    {
        for(int j=i+1; j<M; j++)
        {
            for(int k=0; k<N; k++)
            {
                for(int l=k+1; l<N; l++)
                {
                    int zz = cnt(i, j, k, l);
                    if(zz == 0) continue;
                    vec[zz].PB({i, j, k, l});
                }
            }
        }
    }

    int ans = 0;

    while(1)
    {
        bool any = false;
        for(int z=1; z<=4; z++)
        {
            while(!vec[z].empty())
            {
                Con c = vec[z].back();
                vec[z].pop_back();
                int i = c.a, j = c.b, k = c.c, l = c.d;
                if(cnt(i, j, k, l) != z) continue;

                if(iq[i][k])
                    clear(i, k);
                if(iq[i][l])
                    clear(i, l);
                if(iq[j][k])
                    clear(j, k);
                if(iq[j][l])
                    clear(j, l);
                ans++;
                any = true;
                break;
            }
            if(any) break;
        }
        if(!any) break;

//        cout<<i<<" "<<j<<" "<<k<<" "<<l<<endl;
//        for(int a=0; a<M; a++){for(int b=0; b<N; b++)cout<<iq[a][b];cout<<endl;}cout<<endl;
    }

    return ans;
}

int main() {
  FILEIO("vader");
  IOS;

  cin >> M >> N;
  loop (i, 0, M) {
      string s; cin >> s;
      loop (j, 0, N) {
         ip[i][j] = (s[j] == 'i');
         sr[i] += (s[j] == 'i');
         sc[j] += (s[j] == 'i');
      }
  }

  int ssrr = 0, sscc = 0;
  loop (i, 0, M) {
      sr[i] = min(sr[i], N-1);
      ssrr += sr[i];
  }
  loop (i, 0, N) {
      sc[i] = min(sc[i], M-1);
      sscc += sc[i];
  }

  int ans = 0;
  loop (i, 0, M) {
      loop (j, i+1, M) {
          int t = ssrr - sr[i] - sr[j];
          int q = 0;
          loop (k, 0, N) {
              q += (ip[i][k] or ip[j][k]);
          }
          t += min(q, N-1);
          ans = max(ans, t);
      }
  }
  //cout << ans << endl;
  //ans = 0;

  loop (i, 0, N) {
      loop (j, i+1, N) {
          int t = sscc - sc[i] - sc[j];
          int q = 0;
          loop (k, 0, M) {
              q += (ip[k][i] or ip[k][j]);
          }
          t += min(q, M-1);
          ans = max(ans, t);
      }
  }

  ans = calc();

  cout << ans << endl;

  return 0;
}

