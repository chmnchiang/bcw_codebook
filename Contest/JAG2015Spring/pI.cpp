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
#define ALL(x) x.begin(),x.end()
#define IOS ios_base::sync_with_stdio(0);cin.tie(0)
#ifdef ONLINE_JUDGE
#define FILEIO(name) \
  freopen(name".in", "r", stdin); \
  freopen(name".out", "w", stdout);
#else
#define FILEIO(name)
#endif

#define _TOKEN_CAT2(x, y) x ## y
#define _TOKEN_CAT(x, y) _TOKEN_CAT2(x, y)
#define _MACRO_OVERL3(_1, _2, _3, _N, ...) _N
#define _RANGE1(a) int _TOKEN_CAT(_t, __LINE__)=0; _TOKEN_CAT(_t, __LINE__)<(a); (_TOKEN_CAT(_t, __LINE__))++
#define _RANGE2(i, a) int (i)=0; (i)<(a); (i)++
#define _RANGE3(i, a, b) int (i)=a; (i)<(b); (i)++
#define range(...) _MACRO_OVERL3(__VA_ARGS__, _RANGE3, _RANGE2, _RANGE1)(__VA_ARGS__)

const int MX = 131072;
const double EPS = 1e-6;

typedef pair<double, double> pdd;
typedef pair<int, int> pii;
typedef long long i64;

template<typename T, typename U>
ostream& operator << (ostream &o, const pair<T, U> &p) {
    o << '(' << p.F << ", " << p.S << ")";
    return o;
}

pdd operator + (const pdd &p1, const pdd &p2) {
    return {p1.F + p2.F, p1.S + p2.S};
}

pdd operator - (const pdd &p1, const pdd &p2) {
    return {p1.F - p2.F, p1.S - p2.S};
}

pdd operator * (double f, const pdd &p) {
    return {f*p.F, f*p.S};
}

double operator * (const pdd &p1, const pdd &p2) {
    return p1.F*p2.F + p1.S*p2.S;
}

double operator / (const pdd &p1, const pdd &p2) {
    return p1.F*p2.S - p1.S*p2.F;
}

double abs(const pdd &p1) {
    return sqrt(p1*p1);
}

int N, M, L;
vector<pdd> A, B, C;
map<pii, int> mpA, mpB, mpC;

pair<pii, bool> topii(pdd p) {
    pii res = {round(p.F), round(p.S)};
    double x = p.F - res.F, y = p.S - res.S;
    bool f = (fabs(x) < EPS) and (fabs(y) < EPS);
    return {res, f};
}

 

typedef complex<double> cplx;
const double PI = acos(-1);
const cplx I(0, 1);
void fft(int n, cplx a[], double f=1.0) {
    double theta = 2 * f * PI / n;
    for (int m = n; m >= 2; m >>= 1) {
        int mh = m >> 1;
        for (int i = 0; i < mh; i++) {
            cplx w = exp(i*theta*I);
            for (int j = i; j < n; j += m) {
                int k = j + mh;
                cplx x = a[j] - a[k];
                a[j] += a[k];
                a[k] = w * x;
            }
        }
        theta *= 2;
    }
    int i = 0;
    for (int j = 1; j < n - 1; j++) {
        for (int k = n >> 1; k > (i ^= k); k >>= 1);
        if (j < i) swap(a[i], a[j]);
    }
}

i64 solve() {
    i64 ans = 0;
    if (A.size() == 1 or B.size() == 1) {
        int sza = A.size(), szb = B.size();
        for (range(i, sza)) {
            for (range(j, szb)) {
                pdd p = 0.5 * (A[i] + B[j]);
                pii res; bool fg;
                tie(res, fg) = topii(p);
                if (fg) {
                    ans += 1LL * mpA[A[i]] * mpB[B[j]] * mpC[res];
                }
            }
        }
        return ans;
    }

    pdd pA = A[1] - A[0];
    pdd pB = B[1] - B[0];
    auto intersect = [](pdd p1, pdd p2, pdd q1, pdd q2) -> pdd {
        double a1 = (q1 - p1) / (q2 - p1);
        double a2 = -1.0 * ((q1 - p2) / (q2 - p2));
        double a = a1 + a2;
        return (a2/a)*p1 + (a1/a)*p2;
    };
    if (fabs(pA / pB) > EPS) {
        // not parall
        pdd o = intersect(A[1], A[0], B[1], B[0]);
        for (auto p: C) {
            auto fun = [&](pdd p1, pdd p2, pdd q1, pdd q2) {
                pdd pp = p + p1 - p2;
                pdd q = intersect(p, pp, q1, q2);
                q = q + q - o;
                return topii(q);
            };
            auto r1 = fun(B[0], B[1], A[0], A[1]);
            auto r2 = fun(A[0], A[1], B[0], B[1]);
            if (r1.S and r2.S) {
                //cout << r1.F << ", " << r2.F << endl;
                //cout << mpA[r1.F] << ' ' << mpB[r2.F] << ' ' << mpC[p] << endl;
                /*if (mpA[r1.F] and mpB[r2.F]) {
                    cout << "o = " << o << endl;
                    cout << fun(B[0], B[1], A[0], A[1]) << ' ' << fun(A[0], A[1], B[0], B[1]) << endl;
                    cout << r1.F << ' ' << r2.F << ' ' <<  p << endl;
                    cout << mpA[r1.F] << ' ' << mpB[r2.F] << endl;
                    while(1);
                }*/
                ans += 1LL * mpA[r1.F] * mpB[r2.F] * mpC[p];
            }
        }
        return ans;
    }

    if ( [&]() -> bool {
            if (C.size() == 1) return true;
            pdd pC = C[1] - C[0];
            return fabs(pC / pA) > EPS;
        }() ) {
        pdd m = 0.5 * (A[0] + B[0]) - 3.14159 * pA;
        for (auto p: C) {
            pdd d = p - m;
            if (fabs(d/pA) < EPS) {
                for (auto q: A) {
                    pdd r = p + p - q;
                    auto res = topii(r);
                    if (res.S) {
                        ans += 1LL * mpA[q] * mpB[res.F] * mpC[p];
                    }
                }
            }
        }
        return ans;
    }

    
    pdd m = 0.5 * (A[0] + B[0]) - 3.14159 * pA;
    if ( fabs((m-C[0])/pA) > EPS ) return 0; 

    const int M4 = MX * 4;
    static cplx cA[M4], cB[M4];
    bool fg = (fabs(A[1].F - A[0].F) > EPS);

    for (auto a: A) {
        //int x = fg ? (a.F+0.5) : (a.S+0.5);
        int x = fg ? (a.F) : (a.S);
        x += MX;
        int t = mpA[a];
        cA[x] = cplx(t, 0);
    }

    for (auto b: B) {
        //int x = fg ? (b.F+0.5) : (b.S+0.5);
        int x = fg ? (b.F) : (b.S);
        x += MX;
        int t = mpB[b];
        cB[x] = cplx(t, 0);
    }

    fft(M4, cA);
    fft(M4, cB);
    for (int i=0; i<M4; i++) {
        cA[i] *= cB[i];
    }
    fft(M4, cA, -1.0);
    for (int i=0; i<M4; i++) {
        cA[i] /= M4;
        //if (abs(cA[i]) > EPS) cout << cA[i].real() << ' ';
    } //cout << endl;

    for (auto c: C) {
        //int x = fg ? (c.F+0.5) : (c.S+0.5);
        int x = fg ? (c.F) : (c.S);
        x += MX;
        x *= 2;
        int q = cA[x].real() + 0.5;
        ans += 1LL * q * mpC[c];
    }
    return ans;
}

int main() {
    IOS;
    cin >> L >> M >> N;
#define _MAGIC(a, b) \
    for (range(a)) { \
        int x, y; cin >> x >> y; \
        b.PB({x, y}); mp##b[{x, y}] ++; \
    } sort(ALL(b)); b.resize(unique(ALL(b))-b.begin());
    _MAGIC(L, A);
    _MAGIC(M, B);
    _MAGIC(N, C);

    cout << solve() << endl;
    return 0;
}
