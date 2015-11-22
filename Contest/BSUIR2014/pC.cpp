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
#define IOS ios_base::sync_with_stdio(0); cin.tie(0)
// Let's Fight!
const int MAX = 102030;
int ct[MAX], he[MAX], rk[MAX], sa[MAX], tsa[MAX], tp[MAX][2];

int rmq[18][MAX];

void buildRMQ() {
	for (int i=0; i<MAX; i++) {
		rmq[0][i] = he[i];
	}
	for (int i=1; i<18; i++) {
		for (int j=0; j+(1<<i)<MAX; j++) {
			rmq[i][j] = min(rmq[i-1][j], rmq[i-1][j+(1<<(i-1))]);
		}
	}
}

int query(int l, int r) {
	if (l > r) return 1e9;
	
	int lv = 0;
	for (int i=0; ; i++) {
		if ((r-l+1) < (1<<i)) break;
		lv = i;
	}
	return min(rmq[lv][l], rmq[lv][r-(1<<lv)+1]);
}

void suffix_array(char *ip){
	int len = strlen(ip);
	int alp = 256;
	memset(ct, 0, sizeof(ct));
	for(int i=0;i<len;i++) ct[ip[i]+1]++;
	for(int i=1;i<alp;i++) ct[i]+=ct[i-1];
	for(int i=0;i<len;i++) rk[i]=ct[ip[i]];
	for(int i=1;i<len;i*=2){
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
	for(int i=0,h=0;i<len;i++){
		if(rk[i]==0) h=0;
		else{
			int j=sa[rk[i]-1];
			h=max(0,h-1);
			for(;ip[i+h]==ip[j+h];h++);
		}
		he[rk[i]]=h;
	}
}
const int MX = 101010;
typedef long long i64;
typedef pair<int, int> pii;
char ip[MX];
i64 sm[MX];
i64 sm2[MX];
priority_queue<pii> pq;
int len;

int findMin(int prk, int plen) {
	int l = 0, r = prk+1;

	while (l < r) {
		int md = (l+r)/2;
		//cout << md << ' ' << prk << ' ' << query(md, prk) << endl;
		if (query(md, prk) >= plen) r = md;
		else l = md + 1;
	}
	//cout << l << endl;
	return l - 1;
}

int findMax(int prk, int plen) {
	int l = prk, r = len;
	while (l < r) {
		int md = (l+r+1)/2;
		//cout << prk+1 << ' '<<md << ' ' << query(prk+1, md) << endl;
		if (query(prk+1, md) >= plen) l = md;
		else r = md - 1;
	}
	//cout << "L = " << l << endl;
	return l;
}

int main() {
	cin >> ip;
	len = strlen(ip);
	suffix_array(ip);

	
/*	for (int i=0; i<len; i++) {
		cout << ip+sa[i] << ' ' << he[i] << endl;
	}*/

	for (int i=1; i<=len; i++) {
		sm[i] = sm[i-1] + len - sa[i-1];
	}

	i64 a = 0;
	for (int i=len-1; i>=0; i--) {
		int h = he[i];
		int c = 0;
		while (pq.size() and pq.top().F >= h) {
			a -= 1LL * pq.top().F * pq.top().S;
			c += pq.top().S;
			pq.pop();
		}
		a += 1LL * h * (c+1);
		pq.push(MP(h, c+1));
		sm2[i] = a;
//		cout << i << ' ' << sm2[i] << endl;
	}

	buildRMQ();
	int Q; cin >> Q;
	for (int i=0; i<Q; i++) {
		int l, r; cin >> l >> r; l--; r--;
		//cout << rk[l] << endl;
		int z = findMin(rk[l], r-l+1);
		//cout << "Z = " << z << endl;
		//cout << sm[z] << ' ' << r-l << endl;
		i64 ans = sm[z] + 1LL * (r - l) * (rk[l] - z + 1);
		if (r-l) {
			int zz = findMax(rk[l], r-l);
			//cout << zz << endl;
			ans += 1LL * (r-l) * (zz - rk[l]);
			ans += sm2[zz+1];
		}
		cout << ans << endl;
	}

	return 0;
}

