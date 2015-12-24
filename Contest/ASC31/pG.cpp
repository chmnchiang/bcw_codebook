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

typedef long long i64;
typedef pair<int, int> pii;

const i64 P = 51400000033ll;
const i64 Q = 107;

string ip;
int len;

int trn[30];

vector<pair<i64, int> > vt[5000];

int main(int argc, char** argv)
{
	//cout << P << endl;
	freopen("pattern.in", "r", stdin);
	freopen("pattern.out", "w", stdout);

	cin >> ip;

	for(int i = 0; i < (int)ip.length(); i++){

		int usal = 0;

		i64 hs = 0;
		memset( trn, 0, sizeof(trn) );

		for(int j = i; j < (int)ip.length(); j++){

			int x = ip[j] - 'a';

			if( trn[x] == 0 ){
				trn[x] = ++usal;
			}

			hs *= Q;
			hs += trn[x];
			hs %= P;


			vt[j-i].push_back(make_pair(hs, i));

		}

	}

	i64 bkey;
	int bl = 0, bb = 0;
	int bs = 0;


	for(int i = 0 ; i < ip.length(); i++){

		sort(vt[i].begin(), vt[i].end());
		
		for(int j = 0, k = 0; j < (int)vt[i].size(); j = k){
			for( ; ( k < vt[i].size() ) && ( vt[i][k].first == vt[i][j].first ) ; k++ );
			
			if( bs < ( k - j ) * (i+1) ){
				bs = ( k - j ) * (i+1);
				bkey = vt[i][j].first ; 
				bl = i + 1;
				bb  = vt[i][j].second;
			}

		}
	}


	for(int i = bb; i < bb + bl ; i ++){
		cout << ip[i] ;
	}

	cout << endl;

	return 0;
}
