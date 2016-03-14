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


int N, theta;
typedef pair<int, int> pii;
const double PI = acos(-1.0);
const double EPS = 1e-7;

pii operator - (const pii &p1, const pii &p2) {
    return {p1.F - p2.F, p1.S - p2.S};
}

void solve() {
    vector<pii> ip(N);
    pii o = {0, 0};
    for (int i=0; i<N; i++) {
        int x, y;
        cin >> x >> y;
        pii nx = {x, y};
        ip[i] = nx - o;
        o = nx;
    }

    if (theta == 0) {
        cout << "Acceptable as proposed" << endl;
        return;
    }

    bool flag = true;
    for (auto x: ip) {
        if (x.F < 0) {
            flag = false; break;
        }
    }
    if (flag) {
        cout << "Acceptable as proposed" << endl;
        return;
    }

    typedef pair<double, int> Event;
    vector<Event> event;

    for (auto x: ip) {
        double tc = atan2(x.S, x.F);
        double t1 = tc - PI/2 - EPS, t2 = tc + PI/2 + EPS; 

        event.PB({t1, 1});
        event.PB({t2, -1});

        event.PB({t1+2*PI, 1});
        event.PB({t2+2*PI, -1});
    }
    sort(ALL(event));

    double ans = 1e9;
    bool ok = false;
    auto upd = [&](double a) {
        a = fmod(a, 2*PI);
        if (a > PI) a -= 2*PI;

        if (abs(a) < abs(ans) - 1e-6) {
            ok = true;
            ans = a;
        } else if (abs(a) < abs(ans) + 1e-6) {
            if (ans < 0 and a > 0) ans = a;
        }
    };

    int sm = 0;
    for (auto e: event) {
        double t = e.F;
        int c = e.S;
        if (c == 1) {
            sm++;
            if (sm == N)
                upd(t);
        } else {
            if (sm == N)
                upd(t);
            sm--;
        }
    }

    if (ok) {
        ans = ans / PI * 180.0;
        cout << fixed << setprecision(2);
        if (ans <= 0) {
            cout << "Acceptable after counterclockwise rotation of " << -ans << " degrees" << endl;
        } else {
            cout << "Acceptable after clockwise rotation of " << ans << " degrees" << endl;
        }
    } else {
        cout << "Unacceptable" << endl;
    }
}

int main() {
    IOS;

    int cas = 0;
    while (true) {
        cin >> N >> theta;
        if (not N and not theta) break;

        cas++;
        cout << "Case " << cas << ": ";
        solve();
        cout << endl;
    }

    return 0;
}

