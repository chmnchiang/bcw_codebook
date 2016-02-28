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
#define REP(i,x) for(int i=0;i<(x);i++)
#define REP1(i,a,b) for (int i=(a);i<=(b);i++)
// Let's Fight!

const int MAXN = 101010;

int M;
char ty[MAXN];
int n[MAXN];
bool res[MAXN];
int ntotal[MAXN], ntrue[MAXN];

bool calc()
{
	int dollar = 0;
	for(int i=0; i<M; i++)
		if(ty[i] == '$')
			dollar++;

	if(!dollar)
	{
		res[0] = 0;
		for(int i=1; i<=M; i++)
			res[i] = res[i-1] ^ (ty[i-1] == '-');
		return res[0] == res[M];
	}

	for(int i=0; i<M; i++)
	{
		if(ty[i] != '$') continue;
		int nn = n[i];
		int total = 0, gnum = 0;
		int cur = i;
		res[cur] = 0;
		total++;
		gnum++;
		while(1)
		{
			int nxt = cur-1;
			if(nxt < 0) nxt += M;
			if(ty[nxt] == '$') break;
			res[nxt] = res[cur] ^ (ty[nxt] == '-');
			total++;
			if(!res[nxt]) gnum++;
			cur = nxt;
		}
		ntotal[nn] += total;
		ntrue[nn] += gnum;
	}

	int curnum = 0;
	for(int i=0; i<MAXN; i++)
		curnum += ntotal[i] - ntrue[i];

	for(int i=0; i<MAXN; i++)
	{
		int thisnum = curnum - ntotal[i] + 2 * ntrue[i];
		if(thisnum == i)
		{
			for(int j=0; j<M; j++)
			{
				if(ty[j] != '$') continue;
				int nn = n[j];
				if(i == nn) continue;
				int cur = j;
				while(1)
				{
					res[cur] = !res[cur];
					int nxt = cur - 1;
					if(nxt < 0) nxt += M;
					if(ty[nxt] == '$') break;
					cur = nxt;
				}
			}
			return true;
		}
	}

	return false;
}

int main() {
	IOS;
	FILEIO("truth");

	cin>>M;
	for(int i=0; i<M; i++)
	{
		cin>>ty[i];
		if(ty[i] == '$')
			cin>>n[i];
	}

	bool r = calc();
	if(r)
	{
		cout<<"consistent"<<endl;
		for(int i=0; i<M; i++)
			cout<<(res[i] ? 'f' : 't');
		cout<<endl;
	}
	else
	{
		cout<<"inconsistent"<<endl;
	}

	return 0;
}
