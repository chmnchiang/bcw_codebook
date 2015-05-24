//bcw0x1bd2 {{{
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
#define IOS ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef ONLINE_JUDGE
#define FILEIO(name) \
  freopen(name".in", "r", stdin); \
  freopen(name".out", "w", stdout);
#else
#define FILEIO(name)
#endif

void RI() {}

template<typename... T>
void RI( int& head, T&... tail ) {
	    scanf("%d",&head);
			    RI(tail...);
}

mt19937 rng(0x5EED);
int randint(int lb, int ub) {
    return uniform_int_distribution<int>(lb, ub)(rng);
}
// Let's Fight! }}}

string ans[50];
int main(){
ans[1] = "$3 -> kill 10 with .........G\n";
ans[2] = "$6 -> kill 10 with ........GG\n";
ans[3] = "$9 -> kill 10 with .......GGG\n";
ans[4] = "$10 -> kill 4 with ........R.\n$12 -> kill 10 with ......GGGG\n";
ans[5] = "$13 -> kill 4 with ........RG\n$15 -> kill 10 with .....GGGGG\n";
ans[6] = "$14 -> kill 1 with ......SGGG\n$16 -> kill 4 with .......GRG\n$18 -> kill 10 with ....GGGGGG\n";
ans[7] = "$17 -> kill 1 with .....GSGGG\n$19 -> kill 4 with ......GGRG\n$21 -> kill 10 with ...GGGGGGG\n";
ans[8] = "$17 -> kill 1 with .....SGGGG\n$20 -> kill 4 with .....R..R.\n$24 -> kill 10 with ..GGGGGGGG\n";
ans[9] = "$19 -> kill 1 with .....SSGGG\n$23 -> kill 4 with .....R..RG\n$27 -> kill 10 with .GGGGGGGGG\n";
ans[10] = "$22 -> kill 1 with ....GSSGGG\n$26 -> kill 4 with .....R.GRG\n$30 -> kill 10 with GGGGGGGGGG\n";
ans[11] = "$22 -> kill 1 with ....SSGGGG\n$29 -> kill 4 with .....RGGRG\n$34 -> kill 7 with ....GSRGGR\n$38 -> kill 10 with ....SSSRRG\n";
ans[12] = "$25 -> kill 1 with ...GSSGGGG\n$30 -> kill 4 with ..R..R..R.\n$35 -> kill 7 with .....SSSRR\n$40 -> kill 10 with .....SSRRR\n";
ans[13] = "$27 -> kill 1 with ...SSSGGGG\n$33 -> kill 4 with ..R..R..RG\n$38 -> kill 7 with ....GSSSRR\n$41 -> kill 8 with ..SSSRRGG.\n$43 -> kill 10 with ....GSSRRR\n";
ans[14] = "$30 -> kill 1 with ..GSSSGGGG\n$36 -> kill 4 with ..R..R.GRG\n$41 -> kill 7 with ...GGSSSRR\n$44 -> kill 8 with .GSSSRRGG.\n$46 -> kill 10 with ...GGSSRRR\n";
ans[15] = "$31 -> kill 1 with ....SSSGRG\n$39 -> kill 4 with ..R..RGGRG\n$44 -> kill 7 with ..GGGSSSRR\n$47 -> kill 8 with GGSSSRRGG.\n$49 -> kill 10 with ..GGGSSRRR\n";
ans[16] = "$34 -> kill 1 with ...GSSSGRG\n$40 -> kill 4 with ..SSSRSR..\n$45 -> kill 7 with ....SSSRRR\n$50 -> kill 10 with ...SSSSRRR\n";
ans[17] = "$34 -> kill 1 with ..SSSRGGG.\n$43 -> kill 4 with ..SSSRSR.G\n$48 -> kill 7 with ...GSSSRRR\n$53 -> kill 10 with ..GSSSSRRR\n";
ans[18] = "$37 -> kill 1 with ..SSGSRGGG\n$46 -> kill 4 with ..SSSRSRGG\n$51 -> kill 7 with ..GGSSSRRR\n$56 -> kill 10 with .GGSSSSRRR\n";
ans[19] = "$40 -> kill 1 with .GSSGSRGGG\n$49 -> kill 4 with .GSSSRSRGG\n$54 -> kill 7 with .GGGSSSRRR\n$59 -> kill 10 with GGGSSSSRRR\n";
ans[20] = "$43 -> kill 1 with GGSSGSRGGG\n$50 -> kill 4 with ..SSSRSRR.\n$57 -> kill 7 with GGGGSSSRRR\n$70 -> kill 10 with .SRSSSRRRR\n";
ans[21] = "$44 -> kill 1 with .SSSGRGGR.\n$53 -> kill 4 with ..SSSRSRRG\n$63 -> kill 7 with .GSSSRRSRR\n$73 -> kill 10 with GSRSSSRRRR\n";
ans[22] = "$47 -> kill 1 with .SSSGRGGRG\n$56 -> kill 4 with .GSSSRSRRG\n$66 -> kill 7 with GGSSSRRSRR\n$80 -> kill 10 with SSRRRSSRRR\n";
ans[23] = "$50 -> kill 1 with GSSSGRGGRG\n$59 -> kill 4 with GGSSSRSRRG\n$75 -> kill 7 with SRSRSSRSRR\n$80 -> kill 10 with SSRRRSSRRR\n";
ans[24] = "$54 -> kill 1 with SRSSRGGGR.\n$60 -> kill 3 with .SSSRSRR.R\n$65 -> kill 4 with ..RSRSSRRR\n$75 -> kill 7 with SRSRSSRSRR\n$80 -> kill 10 with SSRRRSSRRR\n";
ans[25] = "$57 -> kill 1 with SRSSRGGGRG\n$63 -> kill 3 with .SSSRSRRGR\n$68 -> kill 4 with .GRSRSSRRR\n";
ans[26] = "$64 -> kill 1 with SRSSRGRGRG\n$66 -> kill 3 with GSSSRSRRGR\n$71 -> kill 4 with GGRSRSSRRR\n";
ans[27] = "$66 -> kill 1 with SRRSSSRGGR\n$70 -> kill 3 with SSSRSRSSRR\n$75 -> kill 4 with SRRSSSRSRR\n";
ans[28] = "$70 -> kill 3 with SSSRSRSSRR\n$75 -> kill 4 with SRRSSSRSRR\n";
ans[29] = "$78 -> kill 3 with RSRSSRRRGR\n";
ans[30] = "";	FILEIO("defend");
	int h;
	cin >> h;
	cout << ans[h];
	return 0;
}

