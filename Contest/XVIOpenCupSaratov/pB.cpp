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

const int MAXN = 55;

int N, M, E, S;
int arr[MAXN][MAXN];
int deg1[MAXN], deg2[MAXN];

bool A[MAXN][MAXN];
bool b[MAXN];
bool x[MAXN];

bool check()
{
  for(int i=0; i<N; i++)
    for(int j=0; j<M; j++)
      A[i][j] = arr[i][j] % 2;
  for(int i=0; i<N; i++)
    b[i] = (i == S);

  vector<int> pivs;
  int rank = 0;
  for(int i=0; i<M; i++)
  {
    int piv = -1;
    for(int j=rank; j<N; j++)
    {
      if(A[j][i])
      {
        piv = j;
        break;
      }
    }
    if(piv == -1) continue;
    pivs.PB(i);
    swap(A[piv], A[rank]);
    swap(b[piv], b[rank]);
    for(int j=0; j<N; j++)
    {
      if(j == rank) continue;
      if(!A[j][i]) continue;
      for(int k=0; k<M; k++)
        A[j][k] ^= A[rank][k];
      b[j] ^= b[rank];
    }
    rank++;
  }

  for(int i=rank; i<N; i++)
    if(b[i])
      return false;

  for(int i=0; i<rank; i++)
    x[pivs[i]] = b[i];
  return true;
}

void play_lose()
{
  int cur = S;
  while(1)
  {
    if(deg1[cur] == 0)
    {
      cout<<"Player 2 wins"<<endl;
      break;
    }
    int ci = -1;
    for(int i=0; i<M; i++)
    {
      if(arr[cur][i] == 0) continue;
      ci = i;
      break;
    }
    cout<<ci+1<<endl;
    arr[cur][ci]--;
    deg1[cur]--;
    deg2[ci]--;

    int xx;
    cin>>xx;
    xx--;

    cur = xx;
    arr[cur][ci]--;
    deg1[cur]--;
    deg2[ci]--;
  }
}

void play_win()
{
  int cur = S;
  while(1)
  {
    int ci = -1;
    for(int i=0; i<M; i++)
    {
      if(!x[i] || arr[cur][i] == 0) continue;
      ci = i;
      break;
    }
    if(ci == -1) break;
    cout<<ci+1<<endl;
    arr[cur][ci]--;
    deg1[cur]--;
    deg2[ci]--;

    if(!deg2[ci])
    {
      cout<<"Player 1 wins"<<endl;
      break;
    }

    int xx;
    cin>>xx;
    xx--;

    cur = xx;
    arr[cur][ci]--;
    deg1[cur]--;
    deg2[ci]--;
  }
}

int main() {
  IOS;
  cin>>N>>M>>E>>S;
  S--;
  for(int i=0; i<E; i++)
  {
    int a, bb;
    cin>>a>>bb;
    a--;
    bb--;
    arr[a][bb]++;
    deg1[a]++;
    deg2[bb]++;
  }

  bool can_win = check();
  if(can_win)
    play_win();
  else
    play_lose();

  return 0;
}
