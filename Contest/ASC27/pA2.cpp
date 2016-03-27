#include<bits/stdc++.h>
using namespace std;
#define FZ(n) memset((n),0,sizeof(n))
#define FMO(n) memset((n),-1,sizeof(n))
#define MC(n,m) memcpy((n),(m),sizeof(n))
#define F first
#define S second
#define MP make_pair
#define PB push_back
#define ALL(x) begin(x),end(x)
#define IOS do { ios_base::sync_with_stdio(0);cin.tie(0); } while (0)
#define SZ(x) ((int)(x).size())
#ifndef OFFLINE
    #define ONLINE_JUDGE
#endif
#ifdef ONLINE_JUDGE
#define FILEIO(name) \
    do { \
        freopen(name".in", "r", stdin); \
        freopen(name".out", "w", stdout); \
    } while (0)
#else
    #define FILEIO(name) do { } while(0)
#endif

#define _TOKEN_CAT2(x, y) x ## y
#define _TOKEN_CAT(x, y) _TOKEN_CAT2(x, y)
#define _MACRO_OVERL3(_1, _2, _3, _N, ...) _N
#define _RANGE1(a) int _TOKEN_CAT(_t, __LINE__)=0; _TOKEN_CAT(_t, __LINE__)<(a); (_TOKEN_CAT(_t, __LINE__))++
#define _RANGE2(i, a) int (i)=0; (i)<(a); (i)++
#define _RANGE3(i, a, b) int (i)=(a); (i)!=(b); (i)+=((b)>(a)?1:-1)
#define loop(...) for (_MACRO_OVERL3(__VA_ARGS__, _RANGE3, _RANGE2, _RANGE1)(__VA_ARGS__))

#ifdef OFFLINE
template<typename T>
void _dump(const char* s, T&& head) { 
    cerr << s << " = " << head << " <<" << endl; 
}

template<typename T, typename... Args>
void _dump(const char* s, T&& head, Args&&... tail) {
    int c = 0;
    while (*s!=',' || c!=0) {
        if (*s=='(' || *s=='[' || *s=='{' || *s=='<') c++;
        if (*s==')' || *s==']' || *s=='}' || *s=='>') c--;
        cerr << *s++;
    }
    cerr << " = " << head << ", ";
    _dump(s+1, tail...);
}

#define dump(...) do { \
    cerr << "\033[32m>> " << __LINE__ << ": " << __PRETTY_FUNCTION__ << endl; \
    cout << "   "; \
    _dump(#__VA_ARGS__, __VA_ARGS__); \
    cout << "\033[0m"; \
} while (0)
#else
#define dump(...) 
#endif

#define au auto
template<class T>
using vec = vector<T>;

template<typename Iter>
ostream& _IterOutput_(ostream &o, Iter b, Iter e, const string ss="", const string se="") {
    o << ss;
    for (auto it=b; it!=e; it++) o << (it==b ? "" : ", ") << *it;
    return o << se;
}

template<typename T1, typename T2>
ostream& operator << (ostream &o, pair<T1, T2> pair) {
    return o << "(" << pair.F << ", " << pair.S << ")";
}

template<typename T>
ostream& operator << (ostream &o, const vector<T> &vec) {
    return _IterOutput_(o, ALL(vec), "[", "]");
}

template<typename T>
ostream& operator << (ostream &o, const set<T> &st) {
    return _IterOutput_(o, ALL(st), "{", "}");
}

template<typename T, size_t N>
ostream& operator << (ostream &o, const array<T, N> &arr) {
    return _IterOutput_(o, ALL(arr), "|", "|");
}

#define y1 yyyyy1
const double EPS = 1e-8;
using pdd = pair<double, double>;
double x1, y1, r1, b1, e1;
pdd v1;
double x2, y2, r2, b2, e2;
pdd v2;
const double PI = acos(-1);

double operator "" _deg(long double x) {
    return x*PI/180;
}

double operator "" _rad(long double x) {
    return x/180*PI;
}

pdd operator + (pdd p1, pdd p2) {
    return {p1.F+p2.F, p1.S+p2.S};
}

pdd operator - (pdd p1, pdd p2) {
    return {p1.F-p2.F, p1.S-p2.S};
}

pdd operator * (double t, pdd p1) {
    return {t*p1.F, t*p1.S};
}

pdd operator * (pdd p1, double t) {
    return {t*p1.F, t*p1.S};
}

double arg(pdd p1) {
    return atan2(p1.S, p1.F);
}

double abs(pdd p1) {
    return hypot(p1.F, p1.S);
}

double intheta(double th, double l, double r) {
    if (l > r) r += PI*2;
    return (l-EPS < th and th < r+EPS) or (l-EPS < th+PI*2 and th+PI*2 < r+EPS);
}

pdd polar(pdd o, double r, double theta) {
    return o + r*pdd(cos(theta), sin(theta));
}

double operator * (pdd p1, pdd p2) {
    return p1.F*p2.F+p1.S*p2.S;
}

double dis(pdd p) {
    dump(p);
    au d = p - v2;
    au ar = arg(d);
    if (intheta(ar, b2, e2)) {
        return abs(abs(d) - r2);
    }
    
    return min(abs(polar(v2, r2, b2)-p), abs(polar(v2, r2, e2)-p));
}

#define r1 rrr111
#define r2 rrr222
vector<pdd> interCircle(pdd o1, double r1, pdd o2, double r2) {
  double d2 = (o1 - o2) * (o1 - o2);
  double d = sqrt(d2);
	if (d > r1+r2) return {};
    if (d + min(r1, r2) < max(r1, r2)) return {};
  pdd u = 0.5*(o1+o2) + ((r2*r2-r1*r1)/(2*d2))*(o1-o2);
  double A = sqrt((r1+r2+d) * (r1-r2+d) * (r1+r2-d) * (-r1+r2+d));
  pdd v = A / (2*d2) * pdd(o1.S-o2.S, -o1.F+o2.F);
  return {u+v, u-v};
}
#undef r1
#undef r2

double calc() {
    v1 = {x1, y1};
    v2 = {x2, y2};

    double d12 = abs(v2 - v1);
    double ans;
    dump(polar(v1, r1, b1));
    ans = dis(polar(v1, r1, b1));
    ans = min(ans, dis(polar(v1, r1, e1)));
    if (d12 < r1 + r2) {
        au pts = interCircle(v1, r1, v2, r2);
        dump(pts);
        if (SZ(pts)) {

            {
            double ar = arg(pts[0] - v1);
            dump(ar, b1, e1);
            if (intheta(ar, b1, e1)) {
                ans = min(ans, dis(pts[0]));
            }
            }
            {
            double ar = arg(pts[1] - v1);
            if (intheta(ar, b1, e1)) {
                ans = min(ans, dis(pts[1]));
            }
            }
        }
    }
    {
        double ar = arg(v2 - v1);
        if (intheta(ar, b1, e1)) {
            ans = min(ans, dis(polar(v1, r1, ar)));
        }
        ar += PI;
        if (intheta(ar, b1, e1)) {
            ans = min(ans, dis(polar(v1, r1, ar)));
        }
        ar -= PI;
        if (intheta(ar, b1, e1)) {
            ans = min(ans, dis(polar(v1, r1, ar)));
        }
    }

    return ans;
}

int32_t main() {
    FILEIO("circular");
    IOS;
    cout << setprecision(10) << fixed;
    cin >> x1 >> y1 >>r1>>b1>>e1;
    cin >> x2 >> y2 >>r2>>b2>>e2;
#define torad(a) a=a*PI/180
    torad(e1);
    torad(e2);
    torad(b1);
    torad(b2);

    au ans = calc();
    swap(x1, x2);
    swap(y1, y2);
    swap(r1, r2);
    swap(b1, b2);
    swap(e1, e2);
    ans = min(ans, calc());
    cout << ans << endl;
    return 0;
}
