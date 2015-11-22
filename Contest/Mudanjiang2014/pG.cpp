#include<bits/stdc++.h>
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

#define y1 ___y1
#define y0 ___Y0

struct Bigint{
  static const int LEN = 15;
  static const int BIGMOD = 10000;

  int s;
  int vl, v[LEN];
  //  vector<int> v;
  Bigint() : s(1) { vl = 0; }
  Bigint(long long a) {
    s = 1; vl = 0;
    if (a < 0) { s = -1; a = -a; }
    while (a) {
      push_back(a % BIGMOD);
      a /= BIGMOD;
    }
  }
  Bigint(string str) {
    s = 1; vl = 0;
    int stPos = 0, num = 0;
    if (!str.empty() && str[0] == '-') {
      stPos = 1;
      s = -1;
    }
    for (int i=SZ(str)-1, q=1; i>=stPos; i--) {
      num += (str[i] - '0') * q;
      if ((q *= 10) >= BIGMOD) {
        push_back(num);
        num = 0; q = 1;
      }
    }
    if (num) push_back(num);
  }

  int len() const {
    return vl;
    //    return SZ(v);
  }
  bool empty() const { return len() == 0; }
  void push_back(int x) {
    v[vl++] = x;
    //    v.PB(x);
  }
  void pop_back() {
    vl--;
    //    v.pop_back();
  }
  int back() const {
    return v[vl-1];
    //    return v.back();
  }
  void n() {
    while (!empty() && !back()) pop_back();
  }
  void resize(int nl) {
    vl = nl;
    fill(v, v+vl, 0);
    //    v.resize(nl);
    //    fill(ALL(v), 0);
  }

  void print() const {
    if (empty()) { putchar('0'); return; }
    if (s == -1) putchar('-');
    printf("%d", back());
    for (int i=len()-2; i>=0; i--) printf("%.4d",v[i]);
  }
  friend std::ostream& operator << (std::ostream& out, const Bigint &a) {
    if (a.empty()) { out << "0"; return out; } 
    if (a.s == -1) out << "-";
    out << a.back();
    for (int i=a.len()-2; i>=0; i--) {
      char str[10];
      snprintf(str, 5, "%.4d", a.v[i]);
      out << str;
    }
    return out;
  }

  int cp3(const Bigint &b)const {
    if (s != b.s) return s > b.s;
    if (s == -1) return -(-*this).cp3(-b);
    if (len() != b.len()) return len()>b.len()?1:-1;
    for (int i=len()-1; i>=0; i--)
      if (v[i]!=b.v[i]) return v[i]>b.v[i]?1:-1;
    return 0;
  }
  bool operator < (const Bigint &b)const{ return cp3(b)==-1; }
  bool operator == (const Bigint &b)const{ return cp3(b)==0; }
  bool operator > (const Bigint &b)const{ return cp3(b)==1; }

  Bigint operator - () const {
    Bigint r = (*this);
    r.s = -r.s;
    return r;
  }
  Bigint operator + (const Bigint &b) const {
    if (s == -1) return -(-(*this)+(-b));
    if (b.s == -1) return (*this)-(-b);
    Bigint r;
    int nl = max(len(), b.len());
    r.resize(nl + 1);
    for (int i=0; i<nl; i++) {
      if (i < len()) r.v[i] += v[i];
      if (i < b.len()) r.v[i] += b.v[i];
      if(r.v[i] >= BIGMOD) {
        r.v[i+1] += r.v[i] / BIGMOD;
        r.v[i] %= BIGMOD;
      }
    }
    r.n();
    return r;
  }
  Bigint operator - (const Bigint &b) const {
    if (s == -1) return -(-(*this)-(-b));
    if (b.s == -1) return (*this)+(-b);
    if ((*this) < b) return -(b-(*this));
    Bigint r;
    r.resize(len());
    for (int i=0; i<len(); i++) {
      r.v[i] += v[i];
      if (i < b.len()) r.v[i] -= b.v[i];
      if (r.v[i] < 0) {
        r.v[i] += BIGMOD;
        r.v[i+1]--;
      }
    }
    r.n();
    return r;
  }
  Bigint operator * (const Bigint &b) {
    Bigint r;
    r.resize(len() + b.len() + 1);
    r.s = s * b.s;
    for (int i=0; i<len(); i++) {
      for (int j=0; j<b.len(); j++) {
        r.v[i+j] += v[i] * b.v[j];
        if(r.v[i+j] >= BIGMOD) {
          r.v[i+j+1] += r.v[i+j] / BIGMOD;
          r.v[i+j] %= BIGMOD;
        }
      }
    }
    r.n();
    return r;
  }
  Bigint operator / (const Bigint &b) {
    Bigint r;
    r.resize(max(1, len()-b.len()+1));
    int oriS = s;
    Bigint b2 = b; // b2 = abs(b)
    s = b2.s = r.s = 1;
    for (int i=r.len()-1; i>=0; i--) {
      int d=0, u=BIGMOD-1;
      while(d<u) {
        int m = (d+u+1)>>1;
        r.v[i] = m;
        if((r*b2) > (*this)) u = m-1;
        else d = m;
      }
      r.v[i] = d;
    }
    s = oriS;
    r.s = s * b.s;
    r.n();
    return r;
  }
  Bigint operator % (const Bigint &b) {
    return (*this)-(*this)/b*b;
  }
};

typedef Bigint ll;

const int IT = 5;
const int IT2 = 30;

ll R;
long long S, x0, y0, x1, y1, x2, y2;
ll RR;

typedef pair<long long, long long> pii;

pii gcd(long long a, long long b){
  if(b == 0LL) return make_pair(1LL, 0LL);
  else{
    long long p = a / b;
    pii q = gcd(b, a % b);
    return make_pair(q.second, q.first - q.second * p);
  }
}

void input(ll &x)
{
  int y;
  cin>>y;
  x = y;
}
void input(long long &x)
{
  int y;
  cin>>y;
  x = y;
}

ll eval(ll x, ll y)
{
  return x*x+y*y;
}

long long calc(long long a, long long b, long long c)
{
  long long g = __gcd(a, b);
  if(c % g != 0) return 0;
  a /= g;
  b /= g;
  c /= g;
  pii p = gcd(a, b);

  ll cx = (ll)p.F * c, cy = (ll)p.S * c;

  ll dodo = (cx * b - cy * a) / (a * a + b * b);
  cx = cx - dodo * b;
  cy = cy + dodo * a;

  //cout<<cx<<" "<<cy<<endl;

  ll curd = eval(cx, cy);

  for(int i=IT; i>=0; i--)
  {
    ll z = 1LL;
    ll nx = cx + (ll)b * z;
    ll ny = cy - (ll)a * z;
    ll nd = eval(nx, ny);
    if(nd < curd)
    {
      curd = nd;
      cx = nx;
      cy = ny;
    }
  }
  for(int i=IT; i>=0; i--)
  {
    ll z = 1LL;
    ll nx = cx - (ll)b * z;
    ll ny = cy + (ll)a * z;
    ll nd = eval(nx, ny);
    if(nd < curd)
    {
      curd = nd;
      cx = nx;
      cy = ny;
    }
  }

  ll ass = (ll)a * cx + (ll)b * cy - c;
  assert(ass == 0);

  //cout<<cx<<" "<<cy<<endl;
  if(curd > RR) return 0;

  //cout<<a<<" "<<b<<" "<<c<<endl;
  //cout<<cx<<" "<<cy<<endl;

  long long ans = 1;
  long long lb = 0;
  for(int i=IT2; i>=0; i--)
  {
    long long z = 1LL<<i;
    long long q = lb + z;
    ll nx = cx + (ll)b * q;
    ll ny = cy - (ll)a * q;
    ll nd = eval(nx, ny);
    if(nd < RR+1)
    {
      lb += z;
    }
  }
  ans += lb;
  lb = 0;
  for(int i=IT2; i>=0; i--)
  {
    long long z = 1LL<<i;
    long long q = lb + z;
    ll nx = cx - (ll)b * q;
    ll ny = cy + (ll)a * q;
    ll nd = eval(nx, ny);
    if(nd < RR+1)
    {
      lb += z;
    }
  }
  ans += lb;

  return ans;
}

int main() {
  IOS;
  int T;
  cin>>T;
  while(T--)
  {
    input(S); input(x0); input(y0); input(R); input(x1); input(y1); input(x2); input(y2);
    RR = R * R;
    x1 = x1 - x0;
    y1 = y1 - y0;
    x2 = x2 - x0;
    y2 = y2 - y0;

    long long a = y1 - y2;
    long long b = x2 - x1;
    long long c1 = S - (x1 * y2 - x2 * y1);
    long long c2 = -S - (x1 * y2 - x2 * y1);

    long long ans = calc(a, b, c1) + calc(a, b, c2);
    cout<<ans<<endl;
  }

  return 0;
}
