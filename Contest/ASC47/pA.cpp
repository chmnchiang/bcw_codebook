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

const double PI = acos(-1);
const double eps = 1e-6;

struct Obj {
    double x, y;
    int t;
    Obj() {}
    Obj(double _x, double _y, double _t) : 
        x(_x), y(_y), t(_t) {}
};

typedef pair<int, int> pii;
typedef pair<double, int> pdi;
typedef long long i64;
int D, F, T;
vector<pii> drones, forts, towers;

int calc(pii p) {
    vector<double> vd(D), vt(T);
    for(int i=0; i<D; i++) {
        double x = drones[i].F - p.F,
               y = drones[i].S - p.S;
        double t = atan2(y, x);
        if(t < -PI + eps) t += 2 * PI;
        vd[i] = t;
    }

    for(int i=0; i<T; i++) {
        double x = towers[i].F - p.F,
               y = towers[i].S - p.S;
        double t = atan2(y, x);
        if(t < -PI + eps) t += 2 * PI;
        vt[i] = t;
    }

    sort(vd.begin(), vd.end());
    sort(vt.begin(), vt.end());

    //for(auto x: vd) { cout << x << ' '; } cout << endl;
    //for(auto x: vt) { cout << x << ' '; } cout << endl;

    vector<int> cnt(T);
    int idl = 0, idr = 0;
    while(idl < T) {
        while(idr < T*2) {
            if(idr < T and vt[idr] - vt[idl] > PI) break;
            if(idr >= T and vt[idr-T] - vt[idl] + 2*PI > PI) break;
            idr ++;
        }
        cnt[idl] = idr - idl - 1;
        //cout << idl << ' ' << cnt[idl] << endl;
        idl ++;
    }

    deque<int> dq;

    int idd = 0, idt = 0, lCnt = 0, totCnt = 0;
    i64 ans = 0;
    while(idd < D) {
        if(idt < T and vt[idt] < vd[idd]) {
            totCnt += cnt[idt];
            lCnt ++;
            dq.PB(idt);
            idt ++;
        } else {
            //for(auto x: dq) { cout << vt[x] << ' '; } cout << endl;
            double t = vd[idd];
            //cout << "t = " << t << endl;
            while(dq.size() and t - vt[dq.front()] > PI) {
                int i = dq.front();
                lCnt --; totCnt -= cnt[i];
                dq.pop_front();
            }
            ans += totCnt - (lCnt * (lCnt - 1))/2;
            //cout << totCnt - (lCnt * (lCnt - 1))/2 << endl;;
            idd ++;
        }
    }
    return ans;
}

int main() {
    freopen("ambitious.in", "r", stdin);
    freopen("ambitious.out", "w", stdout);
    IOS;
    while(cin >> D and D) {
        for(int i=0; i<D; i++) {
            int a, b;
            cin >> a >> b;
            drones.PB(MP(a, b));
        }
        cin >> F;
        for(int i=0; i<F; i++) {
            int a, b;
            cin >> a >> b;
            forts.PB(MP(a, b));
        }

        cin >> T;
        for(int i=0; i<T; i++) {
            int a, b;
            cin >> a >> b;
            towers.PB(MP(a, b));
        }

        long long ans = 0;
        for(int i=0; i<F; i++) {
            ans += calc(forts[i]);
        }

        cout << ans << endl;
        towers.clear(); drones.clear(); forts.clear();
    }
	
	return 0;
}

