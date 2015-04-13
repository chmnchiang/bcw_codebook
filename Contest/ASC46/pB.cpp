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

int Ans[123];

void pre() {
	Ans[1] = 1;
	Ans[2] = 3;
	Ans[3] = 19;
	Ans[4] = 249;
	Ans[5] = 5881;
	Ans[6] = 246603;
	Ans[7] = 17583259;
	Ans[8] = 45888717;
	Ans[9] = 163310;
	Ans[10] = 19515357;
	Ans[11] = 120600562;
	Ans[12] = 94532668;
	Ans[13] = 170068731;
	Ans[14] = 113380982;
	Ans[15] = 116314918;
	Ans[16] = 135722253;
	Ans[17] = 92496699;
	Ans[18] = 168632607;
	Ans[19] = 52943590;
	Ans[20] = 139540378;
	Ans[21] = 149403433;
	Ans[22] = 20634661;
	Ans[23] = 154635245;
	Ans[24] = 44748413;
	Ans[25] = 84449088;
	Ans[26] = 76425331;
	Ans[27] = 149271011;
	Ans[28] = 110788855;
	Ans[29] = 81817469;
	Ans[30] = 2743628;
	Ans[31] = 110868665;
	Ans[32] = 168766695;
	Ans[33] = 140536132;
	Ans[34] = 32089451;
	Ans[35] = 119863612;
	Ans[36] = 76960464;
	Ans[37] = 14335986;
	Ans[38] = 149457208;
	Ans[39] = 119159917;
	Ans[40] = 175375275;
	Ans[41] = 99675999;
	Ans[42] = 78268439;
	Ans[43] = 111791244;
	Ans[44] = 49829108;
	Ans[45] = 132662391;
	Ans[46] = 167561368;
	Ans[47] = 140745695;
	Ans[48] = 16427738;
	Ans[49] = 71378034;
	Ans[50] = 157505566;
	Ans[51] = 145934042;
	Ans[52] = 67970766;
	Ans[53] = 82925837;
	Ans[54] = 20732309;
	Ans[55] = 93432484;
	Ans[56] = 120931438;
	Ans[57] = 58274270;
	Ans[58] = 59850134;
	Ans[59] = 109772495;
	Ans[60] = 161179483;
	Ans[61] = 163330949;
	Ans[62] = 18585968;
	Ans[63] = 169254656;
	Ans[64] = 140518812;
	Ans[65] = 6438206;
	Ans[66] = 95467049;
	Ans[67] = 18316107;
	Ans[68] = 81469154;
	Ans[69] = 31504149;
	Ans[70] = 57468720;
	Ans[71] = 89860784;
	Ans[72] = 31868343;
	Ans[73] = 6359733;
	Ans[74] = 62866159;
	Ans[75] = 63021931;
	Ans[76] = 61701285;
	Ans[77] = 121439335;
	Ans[78] = 9844799;
	Ans[79] = 66966541;
	Ans[80] = 2087735;
	Ans[81] = 75221537;
	Ans[82] = 98353329;
	Ans[83] = 155592893;
	Ans[84] = 6627787;
	Ans[85] = 92242499;
	Ans[86] = 126867400;
	Ans[87] = 61127277;
	Ans[88] = 79596297;
	Ans[89] = 109879421;
	Ans[90] = 52188793;
	Ans[91] = 161169615;
	Ans[92] = 109178107;
	Ans[93] = 74250061;
	Ans[94] = 11154070;
	Ans[95] = 175542153;
	Ans[96] = 19488904;
	Ans[97] = 11217798;
	Ans[98] = 102077943;
	Ans[99] = 163957726;
	Ans[100] = 150441759;
}
int main(){
	FILEIO("bipartite");
	int N;
	pre();
	while(cin >> N && N) {
		cout << Ans[N] << endl;
	}
	return 0;
}

