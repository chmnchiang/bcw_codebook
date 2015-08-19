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

typedef pair<int,int> pii;

struct Answer{
    int a, b, c;
};

int N;
priority_queue<pii, vector<pii>> pq;
vector<Answer> ans;

int main() {
    FILEIO("magic");
    IOS;
    cin >> N;
    for (int i=1, v; i<=N; i++){
        cin >> v;
        pq.push(MP(-i, v));
    }
    pii remain = MP(0,0);
    while (!pq.empty()){
        pii x = pq.top();
        pq.pop();
        if (pq.empty()) {
            remain = x;
            break;
        }
        pii y = pq.top();
        pq.pop();
        int c = min(x.S, y.S);
        x.S -= c;
        y.S -= c;
        int a = -x.F;
        int b = -y.F;
        if (a > b) swap(a, b);
        ans.PB((Answer){a, b, c});
        if (x.S) pq.push(x);
        if (y.S) pq.push(y);
    }
    if (remain.S) {
        if (remain.S & 1) remain.S--;
        remain.F *= -1;
        for (int i = (int)ans.size() - 1; i>=0 && remain.S; i--) {
            if (ans[i].a != remain.F && ans[i].b != remain.F) {
                int tk = remain.S / 2;
                if (tk >= ans[i].c) {
                    tk = ans[i].c;
                }
                remain.S -= tk * 2;
                ans.PB((Answer){ans[i].a, remain.F, tk});
                ans.PB((Answer){ans[i].b, remain.F, tk});
                ans[i].c -= tk;
            }
        }
    }
    map<pii, int> mp;
    for (auto it : ans) {
        mp[MP(it.a, it.b)] += it.c;
    }
    ans.clear();
    for (auto it : mp) {
        if (it.S) {
            ans.PB((Answer){it.F.F, it.F.S, it.S});
        }
    }
    cout << ans.size() << endl;
    for (auto it : ans)
        cout << it.a << " " << it.b << " " << it.c << "\n";
  return 0;
}
