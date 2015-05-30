//bcw0x1bd2 {{{
#include<bits/stdc++.h>
using namespace std;
#define SZ(x) ((int)(x).size())
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

const int MXN = 51400;

struct Point{
  int x,y,c;
};
struct Rectangle{
  int x1,y1,x2,y2;
  Rectangle () {}
  Rectangle (int _x1, int _y1, int _x2, int _y2) :
    x1(_x1), y1(_y1), x2(_x2), y2(_y2) {}
};
struct Answer{
  int k;
  Rectangle rec[3];
};
struct Node{
  int v,tag,y;
}tree1[MXN*4], tree2[MXN*4];

int tp;
int N;
int suffix[3][MXN];
Point pt[MXN];
Answer ans;

void push(int id, Node tree[]){
  if (!tree[id].tag) return ;
  int lc=id*2+1, rc=id*2+2;
  tree[lc].tag += tree[id].tag;
  tree[lc].v += tree[id].tag;
  tree[rc].tag += tree[id].tag;
  tree[rc].v += tree[id].tag;
  tree[id].tag = 0;
}
void pull(int id, Node tree[]){
  int lc=id*2+1, rc=id*2+2;
  if (tree[lc].v >= tree[rc].v) tree[id] = tree[lc];
  else tree[id] = tree[rc];
  tree[id].tag = 0;
}
void init(int l, int r, int id, Node tree[]){
  if (l == r){
    tree[id].v = tree[id].tag = 0;
    tree[id].y = l;
    return ;
  }
  int mid = (l+r)/2, lc=id*2+1, rc=id*2+2;
  init(l,mid,lc,tree);
  init(mid+1,r,rc,tree);
  pull(id, tree);
}
void update(int l, int r, int fl, int fr, int v, int id, Node tree[]){
  if (l == fl && r == fr){
    tree[id].tag += v;
    tree[id].v += v;
    return ;
  }
  int mid = (l+r)/2, lc=id*2+1, rc=id*2+2;
  push(id,tree);
  if (fr <= mid) update(l,mid,fl,fr,v,lc,tree);
  else if (mid < fl) update(mid+1,r,fl,fr,v,rc,tree);
  else {
    update(l,mid,fl,mid,v,lc,tree);
    update(mid+1,r,mid+1,fr,v,rc,tree);
  }
  pull(id,tree);
}

void set_answer(int k, Rectangle rec[]){
  if (ans.k < k){
    ans.k = k;
    if (tp == 0){
    } else if (tp == 1){
      for (int i=0; i<3; i++){
        rec[i].x1 *= -1;
        rec[i].x2 *= -1;
      }
    } else if (tp == 2){
      for (int i=0; i<3; i++){
        swap(rec[i].x1, rec[i].y1);
        swap(rec[i].x2, rec[i].y2);
      }
    } else if (tp == 3){
      for (int i=0; i<3; i++){
        rec[i].x1 *= -1;
        rec[i].x2 *= -1;
        swap(rec[i].x1, rec[i].y1);
        swap(rec[i].x2, rec[i].y2);
      }
    }
    for (int i=0; i<3; i++){
      if (rec[i].x1 > rec[i].x2) swap(rec[i].x1, rec[i].x2);
      if (rec[i].y1 > rec[i].y2) swap(rec[i].y1, rec[i].y2);
      ans.rec[i] = rec[i];
    }
  }
}
void solve(){
  sort(pt, pt+N,
      [](Point a, Point b){
        return tie(a.x, a.y) < tie(b.x, b.y);
      }
      );
  vector<int> seqX, seqY;
  for (int i=0; i<N; i++){
    seqX.PB(pt[i].x);
    seqY.PB(pt[i].y);
  }
  sort(seqX.begin(), seqX.end());
  seqX.resize(unique(seqX.begin(),seqX.end()) - seqX.begin());
  sort(seqY.begin(), seqY.end());
  seqY.resize(unique(seqY.begin(),seqY.end()) - seqY.begin());
  int nx = SZ(seqX);
  seqX.PB(1e9 + 5);
  int ny = SZ(seqY)-1;
  int lst[3] = {0,1,2};
  for (int t=0; t<3; t++){
    swap(lst[0],lst[t]);
    init(0,ny,0,tree1);
    init(0,ny,0,tree2);
    suffix[0][nx] = suffix[1][nx] = suffix[2][nx] = 0;
    for (int i=nx-1,p=N-1,zero=0,one=0,two=0; i>=0; i--){
      while (p >= 0 && pt[p].x >= seqX[i]){
        if (pt[p].c == lst[0]) zero++;
        else if (pt[p].c == lst[1]) one++;
        else if (pt[p].c == lst[2]) two++;
        p--;
      }
      suffix[lst[0]][i] = zero;
      suffix[lst[1]][i] = one; 
      suffix[lst[2]][i] = two;
    }
    for (int i=nx-1, tk, c1=0, x1=nx, c2=0, x2=nx, p=N-1; i>=0; i--){
      int zero = suffix[lst[0]][0] - suffix[lst[0]][i+1];
      // 0 1 2
      tk = c1 + zero + suffix[lst[1]][i];
      if (tk > ans.k){
        Rectangle rec[3];
        rec[lst[0]] = Rectangle(-2e9,-2e9,seqX[i],2e9);
        rec[lst[1]] = Rectangle(seqX[i], -2e9, seqX[x1], 2e9);
        rec[lst[2]] = Rectangle(seqX[x1], -2e9, 2e9, 2e9);
        set_answer(tk, rec);
      }
      if (c1 < suffix[lst[2]][i] - suffix[lst[1]][i+1]){
        c1 = suffix[lst[2]][i] - suffix[lst[1]][i+1];
        x1 = i;
      }
      // 0 2 1
      tk = c2 + zero + suffix[lst[2]][i];
      if (tk > ans.k){
        Rectangle rec[3];
        rec[lst[0]] = Rectangle(-2e9,-2e9,seqX[i],2e9);
        rec[lst[2]] = Rectangle(seqX[i], -2e9, seqX[x2], 2e9);
        rec[lst[1]] = Rectangle(seqX[x2], -2e9, 2e9, 2e9);
        set_answer(tk, rec);
      }
      if (c2 < suffix[lst[1]][i] - suffix[lst[2]][i+1]){
        c2 = suffix[lst[1]][i] - suffix[lst[2]][i+1];
        x2 = i;
      }
      // 0 2 
      // 0 1
      int lstP = p;
      while (p >= 0 && pt[p].x >= seqX[i]){
        int y = lower_bound(seqY.begin(),seqY.end(),pt[p].y) - seqY.begin();
        if (pt[p].c == lst[1]) update(0,ny,y,ny,1,0,tree1);
        else if (pt[p].c == lst[2]) update(0,ny,0,y,1,0,tree1);
        p--;
      }
      tk = zero + tree1[0].v;
      if (tk > ans.k){
        Rectangle rec[3];
        rec[lst[0]] = Rectangle(-2e9,-2e9,seqX[i],2e9);
        rec[lst[1]] = Rectangle(seqX[i], -2e9, 2e9, seqY[tree1[0].y]);
        rec[lst[2]] = Rectangle(seqX[i], seqY[tree1[0].y], 2e9, 2e9);
        set_answer(tk, rec);
      }
      // 0 1
      // 0 2
      p = lstP;
      while (p >= 0 && pt[p].x >= seqX[i]){
        int y = lower_bound(seqY.begin(),seqY.end(),pt[p].y) - seqY.begin();
        if (pt[p].c == lst[2]) update(0,ny,y,ny,1,0,tree2);
        else if (pt[p].c == lst[1]) update(0,ny,0,y,1,0,tree2);
        p--;
      }
      tk = zero + tree2[0].v;
      if (tk > ans.k){
        Rectangle rec[3];
        rec[lst[0]] = Rectangle(-2e9,-2e9,seqX[i],2e9);
        rec[lst[2]] = Rectangle(seqX[i], -2e9, 2e9, seqY[tree2[0].y]);
        rec[lst[1]] = Rectangle(seqX[i], seqY[tree2[0].y], 2e9, 2e9);
        set_answer(tk, rec);
      }
    }
  }
}
int main(){
  IOS;
  FILEIO("gold");
  while (cin >> N && N){
    for (int i=0; i<N; i++)
      cin >> pt[i].x >> pt[i].y >> pt[i].c;
    ans.k = 0;
    tp = 0;
    solve();
    for (int i=0; i<N; i++){
      pt[i].x *= -1;
    }
    tp = 1;
    solve();
    for (int i=0; i<N; i++){
      pt[i].x *= -1;
      swap(pt[i].x, pt[i].y);
    }
    tp = 2;
    solve();
    for (int i=0; i<N; i++){
      pt[i].x *= -1;
    }
    tp = 3;
    solve();
    cout << ans.k << "\n";
    for (int i=0; i<3; i++){
      cout << ans.rec[i].x1 << " " << ans.rec[i].y1 << " " << ans.rec[i].x2 << " " << ans.rec[i].y2 << "\n";
    }
  }

  return 0;
}

