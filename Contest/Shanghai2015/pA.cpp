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

typedef long double ld;
typedef pair<ld, ld> pdd;

const ld EPS = 1E-9;
const ld INF = 1E20;

pdd operator+(pdd a, pdd b){return {a.F+b.F, a.S+b.S};}
pdd operator-(pdd a, pdd b){return {a.F-b.F, a.S-b.S};}
pdd operator*(pdd a, ld b){return {a.F*b, a.S*b};}
ld dot(pdd a, pdd b){return a.F*b.F+a.S*b.S;}
ld cross(pdd a, pdd b){return a.F*b.S-a.S*b.F;}
ld abs(pdd a){return sqrtl(dot(a, a));}

pdd O, A, B, V;
ld R;

bool check(pdd a, pdd v, ld t)
{
    pdd y = B - a;
    ld crs = cross(y, v);
    if(abs(crs) > EPS)
        return false;
    ld tt = dot(y, v) / dot(v, v);
    return 0 <= tt && tt <= t;
}

bool calc()
{
    A = A - O;
    B = B - O;
//  cout<<A<<" -> "<<B<<" V "<<V<<" R "<<R<<endl;

    ld pdv = dot(A, V);
    ld v2 = dot(V, V);
    ld p2 = dot(A, A);
    ld cen = pdv * pdv - v2 * (p2 - R*R);
    ld t = INF;
    if(cen >= 0)
    {
        ld tempt = (-pdv-sqrtl(cen))/v2;
        if(tempt > 0)
            t = tempt;
    }

    if(t == INF)
    {
        return check(A, V, 1e7);
    }

    if(check(A, V, t)) return true;
    pdd x = A + V * t;
    pdd v1 = x * (dot(V, x) / dot(x, x));
    pdd vz = V - v1 * 2;
    return check(x, vz, 1e7);
}

int main() {
    int T;
    cin>>T;
    for(int t=1; t<=T; t++)
    {
        cin>>O.F>>O.S>>R>>A.F>>A.S>>V.F>>V.S>>B.F>>B.S;
        bool ans = calc();
        cout<<"Case #"<<t<<": "<<(ans ? "Yes" : "No")<<endl;
    }

    return 0;
}
