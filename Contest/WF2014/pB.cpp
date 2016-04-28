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

typedef long long ll;
#define double long double

const int MAXN = 256;
const int MAXW = 10101;
const ll INF = 1LL<<60;

struct Car {
    ll x,v;
    ll at(ll t) { return x + v * t; }
};

int N, W, C, D;
ll ct[MAXN], cdt[MAXN];
ll dw[MAXN], dt[MAXN], ddt[MAXN];

ll dp[MAXW], tmp[MAXW];
Car car[MAXW];
int fr,bk,deq[MAXW];

inline bool better(const Car &a, const Car &b, const Car &c) {
    __int128_t x = (a.x-b.x);
    x = x * (c.v-b.v);
    __int128_t y = (b.x-c.x);
    y = y * (b.v-a.v);
    return x >= y;
    return (a.x-b.x)*(c.v-b.v) >= (b.x-c.x)*(b.v-a.v);
}
void solve_dp(vector<ll> &a, vector<ll> &b, ll A, ll B)
{
    int n = a.size();
    if(n == 0) return;
    fr = bk = 0;
    deq[bk++] = 0;
    REP(i,n) {
        car[i] = {a[i]-A*i-B*i*i,i};
    }
    for(int i=1; i<n; i++)
    {
        ll t = 2*i*B;
        while (bk-fr >= 2 and car[deq[fr]].at(t) <= car[deq[fr+1]].at(t)) fr++;
        b[i] = car[deq[fr]].at(t);
        b[i] += A * i - B * i * i;
        while (bk - fr >= 2 and better(car[deq[bk-2]],car[deq[bk-1]],car[i])) bk--;
        deq[bk++] = i;

        continue;
        
        for(int j=0; j<i; j++)
        {
            b[i] = max(b[i], a[j] + A * (i-j) - B * (i-j) * (i-j));
        }
        
    }
}

double solve2(double total)
{
    double lb = -1E12, rb = 1E12;
    double tot = 0, cost = 0;
    for(int i=0; i<100; i++)
    {
        if(rb - lb < 1E-14) break;
        double mb = (lb + rb) / 2;
        tot = cost = 0;
        for(int j=0; j<C; j++)
        {
            if(ct[j] < mb) continue;
            if(cdt[j] == 0)
            {
                tot += (total + 1);
                cost += (total + 1) * ct[j];
                continue;
            }
            double h = (ct[j] - mb) / cdt[j];
            tot += h;
            cost += h * (mb + ct[j]) / 2;
        }
        if(tot > total)
            lb = mb;
        else
            rb = mb;
    }
    assert(lb > -2.2E8);
    cost += (total - tot) * lb;
//  cout<<total<<" "<<tot<<" "<<cost<<endl;
    return cost;
}

double calc()
{
    for(int i=0; i<=W; i++)
        dp[i] = -INF;
    dp[0] = 0;

    for(int i=0; i<D; i++)
    {
        int w = dw[i];
        for(int j=0; j<w; j++)
        {
            vector<ll> v1, v2;
            for(int k=j; k<=W; k+=w)
            {
                v1.PB(dp[k]);
                v2.PB(-INF);
            }
            solve_dp(v1, v2, dt[i] + ddt[i] / 2, ddt[i] / 2);
            for(int k=0; k<(int)v2.size(); k++)
            {
                int x = j + k * w;
                dp[x] = max(dp[x], v2[k]);
            }
        }
    }

    double res = -INF;

    for(int i=0; i<=W; i++)
    {
        if(dp[i] < -INF/2) continue;
        if(C == 0)
        {
            if(i < W) continue;
            res = max(res, dp[i] / (double)2);
            continue;
        }
        double val = dp[i] + solve2(W-i);
        res = max(res, val / 2);
//      cout<<i<<" : "<<dp[i]<<" + "<<solve2(W-i)<<" = "<<val<<endl;
    }

    return res;
}

int main() {
    IOS;
    cin>>N>>W;
    for(int i=0; i<N; i++)
    {
        char c;
        cin>>c;
        if(c == 'D')
        {
            cin>>dw[D]>>dt[D]>>ddt[D];
            dt[D] *= 2;
            ddt[D] *= 2;
            D++;
        }
        else
        {
            cin>>ct[C]>>cdt[C];
            ct[C] *= 2;
            cdt[C] *= 2;
            C++;
        }
    }

    double res = calc();
    if(res < -INF/2)
        cout<<"impossible"<<endl;
    else
        cout<<fixed<<setprecision(12)<<res<<endl;

    return 0;
}
