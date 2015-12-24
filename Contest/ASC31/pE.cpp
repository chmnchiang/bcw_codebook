/* bcw0x1bd2 */
#include <bits/stdc++.h>
//
using namespace std;
//
#define REP(n,i) for(int (i)=0;(i)<(n);(i)++)
#define CDREP(n,i) for(int (i)=((n)-1);(i)>=0;(i)--)
#define CDFOR(s,e,i) for(int i=((e)-1);(i)>=(s);(i)--)
#define _SZ(n) memset((n),0,sizeof(n))
#define _SMO(n) memset((n),-1,sizeof(n))
#define _MC(n,m) memcpy((n),(m),sizeof(n))
#define _F first
#define _S second
#define _MP make_pair
#define _PB push_back
#define FOR(x,y) for(__typeof(y.begin())x=y.begin();x!=y.end();x++)
#define IOS ios_base::sync_with_stdio(0);
// Let's Fight!

const int MX = 250005;
int N,nid;
char str[205][55];
int bound[MX];
unordered_map<string,int> idx;
vector<int> E[MX];
int dp[MX];

int f(int u){
	if (bound[u])
		return 1;
	if (dp[u] != -1)
		return dp[u];
	dp[u] = 0;
	for (auto v : E[u]){
		if (f(v) == 0){
			dp[u] = 1;
			break;
		}
	}
	return dp[u];
}
int main()
{
	freopen("game.in", "r", stdin);
	freopen("game.out","w", stdout);
	nid = 0;
	scanf("%d", &N);
	for (int i=0; i<N; i++){
		scanf("%s", str[i]);
		int len = strlen(str[i]);
		for (int j=0; j<len; j++){
			for (int k=j; k<len; k++){
				string s;
				s = string(str[i]+j,k-j+1);
				if (!idx.count(s)){
					idx[s] = nid++;
				}
			}
		}
	}
	_SZ(bound);
	_SMO(dp);
	for (int i=0; i<N; i++){
		bound[idx[str[i]]] = 1;
		int len=strlen(str[i]);
		for (int j=0; j<len; j++){
			for (int k=j; k<len; k++){
				string s = string(str[i]+j,k-j+1);
				int id = idx[s];
				if (j > 0){
					string s2 = string(str[i]+j-1,k-(j-1)+1);
					E[id]._PB(idx[s2]);
				}
				if (k+1<len){
					string s2 = string(str[i]+j,k+1-j+1);
					E[id]._PB(idx[s2]);
				}
			}
		}
	}
	vector<char> ans;
	for (int i=33; i<=126; i++){
		string s = "";
		s += (char)i;
		if (idx.count(s)){
			int id = idx[s];
			if (!bound[id] && !f(id)){
				ans._PB(i);
			}
		}
	}
	if (ans.size()){
		puts("First");
		for (auto i : ans)
			putchar(i);
		puts("");
	} else {
		puts("Second");
	}
	

	return 0;
}
