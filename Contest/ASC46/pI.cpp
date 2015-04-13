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

const int MX = 100005;

int req[MX];
int N,M;
int at[MX];
int ip[MX], bs[MX];
int bln[MX];
set<int> st[4], empty;

void outA(int x){
  int id = M++;
  at[id] = x;
  for (int i=0; i<bs[id]; i++){
    empty.erase(x+i);
    ip[x+i] = id;
  }
  printf("A %d\n", x);
  fflush(stdout);
}
void move_set(int id, int x, int y){
	st[x].erase(id);
	st[y].insert(id);
}
void outM3(int x, int y){
  x = at[ip[x]];
  int xid = ip[x];
  if (bs[xid] == 3)
    st[3].erase(x);
  for (int i=0; i<bs[xid]; i++){
    empty.insert(x+i);
  }

  at[xid] = y;
  if (bs[xid] == 3)
    st[3].insert(y);
  for (int i=0; i<bs[xid]; i++){
    ip[y+i] = xid;
    empty.erase(y+i);
  }
  printf("M %d %d\n", x, y);
  fflush(stdout);
}
void outD(){
  printf("D\n");
  fflush(stdout);
}


int main(){
  scanf("%d", &N);
  for (int i=1; i<=N; i++){
    if (i&1){
      st[0].insert(i);
      bln[i] = i;
    } else {
      bln[i] = i-1;
    }
    empty.insert(i);
  }
  M = 1;
  FZ(ip); FZ(at); FZ(bs);
  int cmd=0;
	int T=0;
  while (~scanf("%d", &cmd) && cmd){
		T++;
    if (cmd > 0){ // insert
      bs[M] = cmd;
			req[T] = M;
      if (cmd == 1){
        if (!st[1].empty()){
          int x = *st[1].begin();
					move_set(x,1,2);
          outA(x+1);
        } else {
          int x = *st[0].begin();
					move_set(x,0,1);
          outA(x);
        }
      } else if (cmd == 2){
        int x = *st[0].begin();
				move_set(x,0,2);
        outA(x);
      } else if (cmd == 3){
        int x = *empty.rbegin();
        x -= 2;
        st[3].insert(x);
        outA(x);
      }
    } else { // remove
      cmd = req[-cmd];
      int x = at[cmd];
      for (int i=0; i<bs[cmd]; i++){
        ip[x+i] = 0;
        empty.insert(x+i);
      }
      if (bs[cmd] == 1){
        if (st[1].count(x)){ // bu man zu
					move_set(x,1,0);
          if (!st[2].empty() && *st[2].rbegin() > x){
            int y = *st[2].rbegin();
            if (ip[y] == ip[y+1]){
              outM3(y,x);
            } else {
              outM3(y,x);
              outM3(y+1,x+1);
            }
						move_set(y,2,0);
						move_set(x,0,2);
          }
        } else { // man zu
					st[2].erase(bln[x]);
          int tx = (x & 1) ? x+1 : x-1;
          if (!st[1].empty()){ // bu man zu exist
            if ((st[2].empty() || *st[2].rbegin() < x) && *st[1].begin() < x){
              int y = *st[1].begin();
              outM3(tx,y+1);
							st[0].insert(bln[x]);
							move_set(y,1,2);
            } else if (!st[2].empty() && *st[2].rbegin() > *st[1].begin()){
              int y = *st[2].rbegin();
							int z = *st[1].begin();
              if (ip[y] == ip[y+1]){
                outM3(z,x);
                outM3(y,z);
              } else {
                outM3(y,x);
                outM3(y+1,z+1);
							}
							move_set(z,1,2);
							st[2].insert(bln[x]);
							move_set(y,2,0);
						} else if (*st[1].begin() > x){  // bu man zu last
							int y = *st[1].begin();
							outM3(y,x);
							st[2].insert(bln[x]);
							move_set(y,1,0);
						} else {
						}
					} else {
						if (tx != bln[tx])
							outM3(tx, bln[tx]);
						st[1].insert(bln[x]);
					}
				}
			} else if (bs[cmd] == 2){
				st[2].erase(x);
				st[0].insert(x);
				if ((!st[1].empty() && *st[1].begin() > x) || (!st[2].empty() && *st[2].rbegin() > x)){
					if (!st[2].empty() && (st[1].empty() || *st[2].rbegin() > *st[1].begin())){
						int y = *st[2].rbegin();
						if (ip[y] == ip[y+1]){
							outM3(y,x);
						} else {
							outM3(y,x);
							outM3(y+1,x+1);
						}
						move_set(y,2,0);
						move_set(x,0,2);
					} else {
						int y = *st[1].begin();
						outM3(y,x);
						move_set(y,1,0);
						move_set(x,0,1);
					}
				}
			} else {
				st[3].erase(x);
				if (!st[3].empty() && *st[3].begin() < x)
					outM3(*st[3].begin(), x);
			}
			outD();
		}
#ifndef ONLINE_JUDGE
		for (int i=1; i<=N; i++)
			printf("%d ", ip[i]);
		puts("");
#endif
	}
	return 0;
}

