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
typedef long long i64;

struct Point{
  typedef long long T;
  T x, y;
  
  Point() : x(0), y(0) {}
  Point(T _x, T _y) : x(_x), y(_y) {}

  bool operator < (const Point &b) const{
    return tie(x,y) < tie(b.x,b.y);
  }
  bool operator == (const Point &b) const{
    return tie(x,y) == tie(b.x,b.y);
  }
  Point operator + (const Point &b) const{
    return Point(x+b.x, y+b.y);
  }
  Point operator - (const Point &b) const{
    return Point(x-b.x, y-b.y);
  }
  T operator * (const Point &b) const{
    return x*b.x + y*b.y;
  }
  T operator % (const Point &b) const{
    return x*b.y - y*b.x;
  }
  Point operator * (const T &b) const{
    return Point(x*b, y*b);
  }
  T abs(){
    return sqrt(abs2());
  }
  T abs2(){
    return x*x + y*y;
  }
};
long long cross(Point o, Point a, Point b){
  return (a-o) % (b-o);
}

vector<Point> convex_hull(vector<Point> pt){
  int top=0;
  vector<Point> stk(2*pt.size());
  for (int i=0; i<(int)pt.size(); i++){
    while (top >= 2 && cross(stk[top-2],stk[top-1],pt[i]) <= 0)
      top--;
    stk[top++] = pt[i];
  }
  for (int i=pt.size()-2, t=top+1; i>=0; i--){
    while (top >= t && cross(stk[top-2],stk[top-1],pt[i]) <= 0)
      top--;
    stk[top++] = pt[i];
  }
  stk.resize(top-1);
  return stk;
}

vector<Point> convex_hull_half(vector<Point> pt, bool fg){
  sort(pt.begin(),pt.end());
  int top=0;
  vector<Point> stk(2*pt.size());
  for (int i=0; i<(int)pt.size(); i++){
    while (top >= 2 && cross(stk[top-2],stk[top-1],pt[i]) <= 0)
      top--;
    stk[top++] = pt[i];
  }
  for (int i=pt.size()-2, t=top+1; i>=0; i--){
    while (top >= t && cross(stk[top-2],stk[top-1],pt[i]) <= 0)
      top--;
    stk[top++] = pt[i];
  }
  stk.resize(top-1);
  return stk;
}

int N;
vector<Point> pt, convex;

int main(){
  FILEIO("average");
  cin >> N;

  for(int i=0; i<N; i++) {
    int a, b;
    cin >> a >> b;
    pt.PB(Point(a, b));
  }
  sort(pt.begin(), pt.end());

  convex = convex_hull(pt);
  int conv_size = convex.size();

  if(conv_size == 2) {
    cout << "2/1" << endl;
    return 0;
  }

  int x_max = pt[0].x, half_id = -1;
  for(int i=0; i<conv_size; i++) {
    if(convex[i] == pt[N-1]) {
      half_id = i;
      break;
    }
  }

  //cout << convex[0].x << ' ' << convex[0].y << endl;
  

  vector<Point> z;
  i64 ans = 0;
  for(int i=1; i<N; i++) {
    z.PB(pt[i]);
  }
  sort(z.begin(), z.end());
  //cout << convex_hull(z).size() << endl;
  ans += convex_hull(z).size();

  z.clear();
  for(int i=0; i<N-1; i++) {
    z.PB(pt[i]);
  }
  //cout << convex_hull(z).size() << endl;
  ans += convex_hull(z).size();
  //cout << "half: " << half_id << endl;

  int lid = 0, rid = 0;
  for(int i=1; i<half_id; i++) {
    int lx = convex[i-1].x, rx = convex[i+1].x;
    while(rid < N and pt[rid].x <= rx) {
      rid ++;
    }
    while(lid < rid and pt[lid].x < lx) {
      lid ++;
    }

    z.clear();
    for(int j=lid; j<rid; j++) {
      if(pt[j] == convex[i]) continue;
      z.PB(pt[j]);
    }

    vector<Point> temp;
    temp = convex_hull(z);
    bool meet = false;
    for(int j=0; j<(int)temp.size(); j++) {
      if(not meet){
        if(temp[j] == convex[i-1]) meet = true;
        continue;
      }
      //cout << i << endl;
      //cout << temp[j].x << ' ' << temp[j].y << endl;
      if(temp[j] == convex[i+1]) break;
      ans += 1;
      //cout << "+1 " << ans << endl;
      
    }
    ans += conv_size - 1;
  }

  lid = 0, rid = 0;
  for(int i=conv_size-1; i>half_id; i--) {
    int lx = convex[i+1].x, rx = convex[i-1].x;
    while(rid < N and pt[rid].x <= rx) {
      rid ++;
    }
    while(lid < rid and pt[lid].x < lx) {
      lid ++;
    }

    z.clear();
    for(int j=lid; j<rid; j++) {
      if(pt[j] == convex[i]) continue;
      z.PB(pt[j]);
    }

    vector<Point> temp;
    temp = convex_hull(z);
    temp.PB(temp[0]);
    bool meet = false;
    for(int j=int(temp.size())-1; j>=0; j--) {
      if(not meet){
        if(i+1 < conv_size)
          if(temp[j] == convex[i+1]) meet = true;
        if(i+1 == conv_size)
          if(temp[j] == convex[0]) meet = true;
        continue;
      }
      if(temp[j] == convex[i-1]) break;
      ans += 1;
      //cout << "+1 " << ans << endl;
    }
    ans += conv_size - 1;
  }
  ans += 1LL * (N - conv_size) * conv_size;
  i64 g = __gcd(ans, (i64)N);
  cout << ans/g << "/" << N/g << endl;

	return 0;
}

