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
#define REP(i,x) for (int i=0; i<(x); i++)
#define REP1(i,a,b) for (int i=(a); i<=(b); i++)
#ifdef ONLINE_JUDGE
#define FILEIO(name) \
    freopen(name".in", "r", stdin); \
    freopen(name".out", "w", stdout);
#else
#define FILEIO(name)
#endif
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


struct Rec {
    int x,y,w,h,id;
};

using pii=pair<int,int>;
ostream& operator << (ostream& o, const Rec &r) {
    o << "[" << pii(r.x, r.y) << ' ' << pii(r.x+r.w, r.y+r.h) << "]";
    return o;
}

int X,Y;
vector<Rec> rec;

bool can(Rec r) {
    if (r.x+r.w > X or r.y+r.h > Y) return false;
    for (auto it:rec) {
        // check r, it
        int l1,r1,l2,r2;
        l1 = r.x;
        r1 = r.x+r.w;
        l2 = it.x;
        r2 = it.x+it.w;
        if (r1 <= l2 or r2 <= l1) continue;
        
        l1 = r.y;
        r1 = r.y+r.h;
        l2 = it.y;
        r2 = it.y+it.h;
        if (r1 <= l2 or r2 <= l1) continue;

        return false;
    }
    return true;
}
int find_rec(int x, int y) {
    for (auto it:rec) {
        if (it.x <= x and x < it.x+it.w and it.y <= y and y < it.y+it.h) return it.id;
    }
    return -1;
}
int find_rec(int id) {
    REP(i,SZ(rec)) {
        if (rec[i].id == id) return i;
    }
    assert(false);
}
Rec pop_rec(int id) {
    REP(i,SZ(rec)) {
        if (rec[i].id == id) {
            auto r = rec[i];
            swap(rec[i], rec.back());
            rec.pop_back();
            return r;
        }
    }
    assert(false);
}

const int MX = 266;
const int INF = 1029384756;

int isinterX(Rec a, Rec b) {
    int l1 = a.x, r1 = a.x+a.w;
    int l2 = b.x, r2 = b.x+b.w;
    return !(r1 <= l2 or r2 <= l1);
}
int isinterY(Rec a, Rec b) {
    int l1 = a.y, r1 = a.y+a.h;
    int l2 = b.y, r2 = b.y+b.h;
    return !(r1 <= l2 or r2 <= l1);
}
int f(Rec a, Rec b, int dx, int dy) {
    if (!(dx == 0 ? isinterX(a,b) : isinterY(a,b))) {
        return INF;
    }
    if (dy > 0) {
        int l = a.y + a.h, r = b.y;
        int x = r-l;
        return x >= 0 ? x : INF;
    }

    if (dy < 0) {
        int l = b.y + b.h, r = a.y;
        int x = r-l;
        return x >= 0 ? x : INF;
    }

    if (dx > 0) {
        int l = a.x + a.w, r = b.x;
        int x = r-l;
        return x >= 0 ? x : INF;
    }

    if (dx < 0) {
        int l = b.x + b.w, r = a.x;
        int x = r-l;
        return x >= 0 ? x : INF;
    }
    assert(false);
}
int bdis(Rec a, int dx, int dy) {
    if (dx > 0) return X-a.x-a.w;
    if (dx < 0) return a.x;
    if (dy > 0) return Y-a.y-a.h;
    if (dy < 0) return a.y;
    assert(false);
}
inline int sgn(int x) {
    if (x > 0) return 1;
    if (x < 0) return -1;
    return 0;
}
int cmdMove(int id, int dx, int dy) {
    int s = find_rec(id);
    static int dis[MX];
    static bool us[MX];
    int totd = max(abs(dx), abs(dy));
    int nd = 0;
    int sz = SZ(rec);
    fill(dis, dis+sz+1, INF);
    fill(us, us+sz+1, 0);
    dis[s] = 0;
    us[s] = 1;
    Rec now = rec[s];
    //cout << "Move" << endl;
    //cout << rec << endl;

    while (true) {
        int bs = -1, bv = INF;
        for (int i=0; i<sz; i++) {
            if (us[i]) continue;

            dis[i] = min(dis[i], f(now, rec[i], dx, dy)+nd);
            if (dis[i] < bv) {
                bv = dis[i];
                bs = i;
            }
        }
        //for (int i=0; i<sz; i++) cout << dis[i] << ' '; cout << endl;

        if (bs == -1) break;

        if (bv >= totd) break;
        us[bs] = 1;
        nd = bv;
        now = rec[bs];
    }

    //cout << totd << endl;
    for (int i=0; i<sz; i++) {
        if (!us[i]) continue;
        totd = min(totd, dis[i]+bdis(rec[i], dx, dy));
    }
    //cout << totd << endl;
    /*
    for (int i=0; i<sz; i++) {
        cout << dis[i] << ' ';
    } cout << endl;
    */

    for (int i=0; i<sz; i++) {
        if (!us[i]) continue;
        int d = totd - dis[i];
        if (d <= 0) continue;

        int x = sgn(dx) * d, y = sgn(dy) * d;
        rec[i].x += x;
        rec[i].y += y;
    }
    

    return totd;
}
int main() {
    IOS;
    cin >> X >> Y;
    string cmd;
    int Q = 0;
    while (cin >> cmd) {
        Q++;
        //cout << Q << " : " << rec << endl;
        int x,y,w,h;
        if (cmd == "OPEN") {
            cin >> x >> y >> w >> h;
            Rec r = Rec{x,y,w,h,Q};
            if (can(r)) {
                rec.PB(r);
            } else {
                cout << "Command " << Q << ": OPEN - window does not fit" << endl;
            }
        } else if (cmd == "CLOSE") {
            cin >> x >> y;
            int id = find_rec(x,y);
            if (id != -1) {
                pop_rec(id);
            } else {
                cout << "Command " << Q << ": CLOSE - no window at given position" << endl;
            }

        } else if (cmd == "RESIZE") {
            cin >> x >> y >> w >> h;
            int id = find_rec(x,y);
            if (id != -1) {
                Rec r = pop_rec(id);
                Rec ori = r;
                r.w = w;
                r.h = h;
                if (can(r)) {
                    rec.PB(r);
                } else {
                    cout << "Command " << Q << ": RESIZE - window does not fit" << endl;
                    rec.PB(ori);
                }

            } else {
                cout << "Command " << Q << ": RESIZE - no window at given position" << endl;
            }
        } else if (cmd == "MOVE") {
            cin >> x >> y >> w >> h;
            int id = find_rec(x,y);
            if (id != -1) {
                int d = cmdMove(id,w,h);
                if (d != abs(w+h)) cout << "Command " << Q << ": MOVE - moved " << d << " instead of " << abs(w+h) << endl;
            } else {
                cout << "Command " << Q << ": MOVE - no window at given position" << endl;
            }
        } else {
            assert(false);
        }
    }

    sort(ALL(rec),[](Rec a, Rec b) { return a.id < b.id; });
    cout << SZ(rec) << " window(s):\n";
    for (auto it:rec) cout << it.x << " " << it.y << " " << it.w << " " << it.h << endl;

    return 0;
}

