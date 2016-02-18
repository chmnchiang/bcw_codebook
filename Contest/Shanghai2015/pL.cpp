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

int X, Y;

int calc()
{
    int g = __gcd(X, Y);
    X /= g;
    Y /= g;
    int ans = 1;
    while(1)
    {
        if(X>Y) swap(X, Y);
        if(Y%(X+1) == 0)
        {
            Y /= X+1;
            ans++;
        }
        else
            break;
    }
    return ans;
}

int main() {
    IOS;
    int T;
    cin>>T;
    for(int t=1; t<=T; t++)
    {
        cin>>X>>Y;
        int ans = calc();
        cout<<"Case #"<<t<<": "<<ans<<"\n";
    }

    return 0;
}
