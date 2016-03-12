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
    freopen(name".in", "r", stdin);
//    freopen(name".out", "w", stdout);
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

typedef pair<int, int> pii;

const int MAXN = 202020;

int N;
int arr[MAXN];

void calc()
{
    int s = 0, t = 0;
    vector<int> vs, vt;
	for(int i=0; i<N; i++)
	{
		if(i>0)
        {
            if(arr[i] < arr[i-1]) break;
            if(arr[i] - arr[i-1] == 1 && arr[i] != i+1) break;
            if(i>1 && (arr[i]-arr[i-1]) < (arr[i-1]-arr[i-2])) break;
        }
        vs.PB(arr[i]);
	}
	for(int i=N-1; i>=0; i--)
	{
		if(i<N-1)
        {
            if(arr[i] > arr[i+1]) break;
            if(arr[i+1] - arr[i] == 1 && arr[i] != i+1) break;
            if(i<N-2 && (arr[i+1]-arr[i]) < (arr[i+2]-arr[i+1])) break;
        }
        vt.PB(arr[i]);
	}

    vector<pii> vp;
    for(auto v: vs)
        vp.PB({v, 1});
    for(auto v: vt)
        vp.PB({v, 2});
    sort(ALL(vp));

    int K = -1;
    for(int i=0; i<(int)vp.size()-1; i++)
    {
        if(vp[i].S == 1 && vp[i+1].S == 2)
        {
            int ss = vp[i].F, tt = vp[i+1].F;
            int kk = tt - ss + 1;
            if(kk > K)
            {
                K = kk;
                s = ss;
                t = tt;
            }
        }
    }


//    cout<<s<<" "<<t<<endl;

	cout<<K<<endl;
	for(int i=0; i<K; i++)
		cout<<(s+i)<<(i==K-1 ? "\n" : " ");
}

int main() {
	IOS;
	FILEIO("crossword");
	
	cin>>N;
	for(int i=0; i<N; i++)
		cin>>arr[i];

	calc();

	return 0;
}

