#include<bits/stdc++.h>
using namespace std;
#define REP(n,i) for(int (i)=0;(i)<(n);(i)++)
#define CDREP(n,i) for(int (i)=((n)−1);(i)>=0;(i)−−)
#define CDFOR(s,e,i) for(int i=((e)−1);(i)>=(s);(i)−−)
#define _SZ(n) memset((n),0,sizeof(n))
#define _SMO(n) memset((n),−1,sizeof(n))
#define _MC(n,m) memcpy((n),(m),sizeof(n))
#define _F first
#define _S second
#define _MP(a,b) make_pair((a),(b))
#define _PB(a) push_back((a))
#define FOR(x,y) for(__typeof(y.begin())x=y.begin();x!=y.end();x++)
#define IOS ios_base::sync_with_stdio(0);
#ifdef ONLINE_JUDGE
#define FILEIO(name) \
    freopen(name".in", "r", stdin); \
    freopen(name".out", "w", stdout);
#else
#define FILEIO(name)
#endif
//Let's Fight!

const int STEP = 200000000;
const int MX = STEP*2+1;

int x = MX/2;
int mood = 0;
int ch1[2][5];
int ch2[2][5];
int ch3[2][5];
bitset<MX> arr;

int main(){
	FILEIO("beavers");
	int fail=1;
	for (int i=0; i<5; i++){
		for (int j=0; j<2; j++){
			char str[10];
			scanf("%s", str);
			ch1[j][i] = str[0] - '0';
			ch2[j][i] = str[1] == 'R' ? 1 : -1;
			ch3[j][i] = str[2] - 'A';
			if (str[2] == 'H'){
				fail = 0;
			}
		//	printf("%d %d %d\n", ch1[j][i], ch2[j][i], ch3[j][i])
		}
	}
	if (fail){
		puts("unhappy beaver");
		return 0;
	}
	int good = 0;	
	for (int i=0; i<STEP; i++){
		int t = arr[x];
		int nx = x + ch2[t][mood];
		int nmood = ch3[t][mood];
		arr[x] = ch1[t][mood];
		x = nx;
		mood = nmood;
		if (mood > 4){
			good = 1;
			break;
		}
		/*
		for (int j=MX/2-15; j<MX/2+15; j++){
			if (j == x)
				putchar('[');
			printf("%d ", arr[j]);
			if (j == x)
				putchar(']');
		}
		puts("");
		printf("%d\n",  mood);
		*/
	//	printf("%d ", x);
	}
	if (good)
		puts("happy beaver");
	else
		puts("unhappy beaver");

	return 0;
}
