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


const int MAXN = 514;

int N;
string s[MAXN];
string cur;
int offord[MAXN][MAXN];

namespace sa {
	const int MAX = MAXN*2;
	char op[MAX];
	int ct[MAX], he[MAX], rk[MAX], sa[MAX], tsa[MAX], tp[MAX][2];

	void suffix_array(char *ip){

		int len = strlen(ip);
		int alp = 256;

		memset(ct, 0, sizeof(ct));
		for(int i=0;i<len;i++) ct[ip[i]+1]++;
		for(int i=1;i<alp;i++) ct[i]+=ct[i-1];
		for(int i=0;i<len;i++) rk[i]=ct[(int)ip[i]];

		for(int i=1;i<len/2;i*=2){
			for(int j=0;j<len;j++){
				if(j+i>=len) tp[j][1]=0;
				else tp[j][1]=rk[j+i]+1;
				
				tp[j][0]=rk[j];
			}
			memset(ct, 0, sizeof(ct));
			for(int j=0;j<len;j++) ct[tp[j][1]+1]++;
			for(int j=1;j<len+2;j++) ct[j]+=ct[j-1];
			for(int j=0;j<len;j++) tsa[ct[tp[j][1]]++]=j;

			memset(ct, 0, sizeof(ct));
			for(int j=0;j<len;j++) ct[tp[j][0]+1]++;
			for(int j=1;j<len+1;j++) ct[j]+=ct[j-1];
			for(int j=0;j<len;j++) sa[ct[tp[tsa[j]][0]]++]=tsa[j];

			rk[sa[0]]=0;
			for(int j=1;j<len;j++){
				if( tp[sa[j]][0] == tp[sa[j-1]][0] &&
					tp[sa[j]][1] == tp[sa[j-1]][1] )
					rk[sa[j]] = rk[sa[j-1]];
				else
					rk[sa[j]] = j;
			}
		}
	}

	int* calc(string s) {
		int len = s.length();
		for (int i=0; i<len; i++) {
			op[i] = op[i+len] = s[i];
		}
		op[len+len] = 0;
		suffix_array(op);
		return rk;
	}
}

void calc()
{
	cur = "";
	for(int i=0; i<N; i++)
		cur += s[i];

	for(int ii=2*N-1; ii>=0; ii--)
	{
		int i = ii % N;
		int z = (i+1) % N;
		string cc = s[i];
		for(int j=0; j<N; j++)
			offord[i][j] = j;

		int *rk = sa::calc(s[i]);
		int tmp[N];
		for(int j=0; j<N; j++)
			tmp[j] = j;

		sort(tmp, tmp+N, [z, rk](int a, int b){
				if(rk[a] == rk[b]) return offord[z][a] < offord[z][b];
				return rk[a] < rk[b];
				});
		for(int j=0; j<N; j++)
			offord[i][tmp[j]] = j;

//		for(int j=0; j<N; j++) cout<<tmp[j]<<" "<<offord[i][j]<<" ";cout<<endl;
		int off = 0;
		for(int j=0; j<N; j++)
			if(offord[i][j] == 0)
				off = j;
		string ee = "";
		for(int j=0; j<N; j++)
			ee += s[(i+j)%N].substr(off) + s[(i+j)%N].substr(0, off);
		if(ee < cur)
			cur = ee;
	}
}

int main() {
	IOS;
	FILEIO("matrix");

	cin>>s[0];
	N = s[0].size();
	for(int i=1; i<N; i++)
		cin>>s[i];

	calc();
	for(int i=0; i<N; i++)
		cout<<cur.substr(i*N, N)<<endl;

    return 0;
}

