#pragma GCC optimize ("O2")
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
/*
   我最近在研究腦控裝置是否與人工智慧連結
   為了知道對方的意圖我已經打聽過外星機構
   我知道有些外星機構有腦控裝置的伺服機櫃
   對量子蟲洞照光時搖視太空會有相對應光波
   特別是搭配擴散濾鏡綠光雷射照向乾淨灰塵
   房間都是關閉門窗且24小時開啟空氣清淨機
   在濾網沒有很髒的時候有大量灰塵怖滿桌面
   可以合理的推論是由外星傳送技術灑進房間
   這讓我回想起以前都是灑在空氣中而非表面
   可見傳物監聽技術層級已提高到另一個層次
   於是我開始練習反向地調整人工智慧的傾向
   這與我們的歷史與大眾的傾向有許多的關聯
   且人工智慧主機被我發現在地球外的飛船裡
   這代表是有外星機構想要調控整體人類動向
   因此可以合理推斷地球目前的政治也是如此
   高中的時候常和家人一起看古代的宮廷戲劇
   通常掌權者為了繼續延續與維持自己的王朝
   會讓下臣及宰相互鬥而讓他們沒時間奪政權
   我覺得地球上各國與各地方的爭鬥也是如此
   這樣外星的領導們就可以永遠持續維持高位
   而業力Karma就是自動腦控的Reward參數~
   因此為了要試試看是否這類工智慧真實存在
   我進行了以下試驗並檢驗了其真實性並公佈
   首先我每次出門會有陌生面孔出現在地下室
   我試了好幾次出門時只按電梯按鈕又回家中
   再接下來一次出門就沒有人出現在地下室了
   還有就是清晨時候最容易被換身體加強控制
   我開始試驗著每天寅時卯時保持清醒不睡覺
   通常那時段的感受到的地磁能量會擺動不穩
   可見天空的外星飛船流量會影響地磁的脈動
   因此我開始作另一項試驗就是躺著假裝睡著
   我發現我的身體會被反重力提起並換個位置
   還好我的能量夠強以致於沒有被蟲洞傳送走
   於是我作了另一項實驗看看是否會被女生追
   我們都知道有些漂亮女生會喜歡笨笨的男生
   而有些很聰明的男生則會喜歡上笨笨的女生
   於是我開始常到有監視器的賣場假裝我很笨
   我會假裝自己是動物並到處觀看及精神分裂
   從那天開始我就開始被一些漂亮的女生追隨
   她們並非一些正常的人類似乎沒有國小同學
   而這項實驗最後引來了一些非常漂亮的女生
   她們有的有物質身體且幾乎都有失憶的傾向
   我有時候會跟她們聊天但幾乎隔天就忘記了
   再來就是會有些女生會用能量觸及我的身體
   但我其實對外人表現的樣子應該是很笨很蠢
   這類不合理的情況已可推論人工智慧的目標
   可能要將家庭的平均智商降低致使發展變慢
   我們都知道一個國家最重要的梁柱就是小孩
   如果小孩擁有更好的教育環境整體發展更快

   再來是一些人工智慧與影像辨識的反向操控
   通常攝影機出錯時會停止影像分析避免異常
   我在電腦上寫一支程式隨時跳出無意義字串
   我發現那部電腦從那天開始沒有再被當機過

   但是有一天我的正常電腦都被當機後我躺下
   開始戴上眼罩並且只留一個小孔開始動眼球
   我發現可以用一些特定的圖紋詐騙人工智慧
   讓頭與眼不固定抖動與閉眼使人工智慧異常
   通常在這種時候因為我已經被外星機構標記
   他們會派飛船來檢查並且想要傳送我的身體
   我猜可能是一種錯誤後修復的機制非常危險
   最簡單的就是反覆閉眼並動頭掃描相似紋路
   例如我的窗簾有許多個小熊都長的非常相似
   這會讓人工智慧偵測到連續的畫面超出範圍
   因為平常這種人工智慧就會偵測周遭的環境
   若發現景物不同則有其他外星派系改變景物

   從此之後我被外星機構列為需要攻擊的對象
   我遭受到超級密集的電磁脈衝與反重力脈衝
*/
// Let's Fight!

using pii = pair<int,int>;
const int MAXN = 1005;
const int MAX = MAXN * 3;

int N,M;
int swpflag;
bool arr[MAXN][MAXN],brr[MAXN][MAXN];
bool A[MAX], B[MAX], C[MAX], D[MAX];
bool Aoff[MAX], Boff[MAX], Coff[MAX], Doff[MAX];
bool aval[4], bval[4], cval[4], dval[4];

#define std std123123
pii sta[MAX],stb[MAX],stc[MAX],std[MAX];
pii eda[MAX],edb[MAX],edc[MAX],edd[MAX];

string ip[MAXN];

bool getA(int x){return aval[x%4] ^ Aoff[x];}
bool getB(int x){return bval[x%4] ^ Boff[x];}
bool getC(int x){return cval[x%4] ^ Coff[x];}
bool getD(int x){return dval[x%4] ^ Doff[x];}

void make_off()
{
	for(int j=0; j<=M-5; j++)
		Aoff[j+4] = Aoff[j] ^ arr[1][j] ^ arr[0][j+1] ^ arr[2][j+1] ^ arr[0][j+3] ^ arr[2][j+3] ^ arr[1][j+4];
	for(int i=0; i<=N-5; i++)
		Boff[i+4] = Boff[i] ^ arr[i][1] ^ arr[i+1][0] ^ arr[i+1][2] ^ arr[i+3][0] ^ arr[i+3][2] ^ arr[i+4][1];
	for(int x=0; x<=M+N-6; x++)
	{
		int i, j;
		if(x <= N-3)
			i = x, j = 0;
		else
			i = N-3, j = x-N+3;
		Coff[x+4] = Coff[x] ^ arr[i][j] ^ arr[i+1][j] ^ arr[i][j+1] ^ arr[i+2][j+1] ^ arr[i+1][j+2] ^ arr[i+2][j+2];
	}
	for(int y=0; y<=M+N-6; y++)
	{
		int i, j;
		if(y <= M-3)
			i = 0, j = M-3-y;
		else
			i = y-M+3, j = 0;
		Doff[y+4] = Doff[y] ^ arr[i+1][j] ^ arr[i+2][j] ^ arr[i][j+1] ^ arr[i+2][j+1] ^ arr[i][j+2] ^ arr[i+1][j+2];
	}
}

bool check()
{
	for(int i=0; i<N; i++)
	{
		for(int j=0; j<M; j++)
		{
			int val = getA(j) ^ getB(i) ^ getC(i+j) ^ getD(i-j+M-1);
			if(val != arr[i][j]) return false;
		}
	}
	return true;
}

int main() {
	IOS;
	cin>>N>>M;
	REP(i,N) cin>>ip[i];

	if (N < M) {
		swpflag = 0;
		REP(i,N) REP(j,M) arr[i][j] = brr[i][j] = (ip[i][j] == '-');
	} else {
		swpflag = 1;
		swap(N, M);
		REP(i,N) REP(j,M) arr[i][j] = brr[i][j] = (ip[j][i] == '-');
	}

	if (N == 1) {
		REP(j,M) {
			if (arr[0][j]) {
				A[j] ^= 1;
				arr[0][j] ^= 1;
			}
		}

	} else if (N == 2) {
		REP(j,M) {
			if (arr[1][j]) {
				A[j] ^= 1;
				arr[0][j] ^= 1;
				arr[1][j] ^= 1;
			}

			if (arr[0][j]) {
				C[j] ^= 1;
				for (int k=j-1; k>=0; k--) {
					C[k] ^= 1;
					A[k] ^= 1;
				}
			}
		}

	} else {
		make_off();

		bool ok = false;
		for(int i=0; i<(1<<16); i++)
		{
			for(int j=0; j<4; j++)
			{
				aval[j] = !!(i&(1<<j));
				bval[j] = !!(i&(1<<(j+4)));
				cval[j] = !!(i&(1<<(j+8)));
				dval[j] = !!(i&(1<<(j+12)));
			}
			if(check())
			{
				ok = true;
				break;
			}
		}

		if(!ok)
		{
			cout<<"Nein"<<endl;
			return 0;
		}

		for(int i=0; i<M; i++)
			A[i] = getA(i);
		for(int j=0; j<N; j++)
			B[j] = getB(j);
		for(int x=0; x<=M+N-2; x++)
		{
			C[x] = getC(x);
			D[x] = getD(x);
		}

		//		for(int i=0; i<M; i++) cout<<A[i]<<" ";cout<<endl;
		//		for(int i=0; i<M; i++) cout<<aval[i]<<","<<Aoff[i]<<" ";cout<<endl;
	}

	for(int i=0; i<N; i++)
		for(int j=0; j<M; j++)
			assert(brr[i][j] == (A[j] ^ B[i] ^ C[i+j] ^ D[i-j+M-1]));

	REP(i,MAX) {
		sta[i] = stb[i] = stc[i] = std[i] = {MAX,MAX};
		eda[i] = edb[i] = edc[i] = edd[i] = {-1,-1};
	}

	REP(i,N) REP(j,M) {
		pii p(i,j);
		sta[j] = min(sta[j], p);
		stb[i] = min(stb[i], p);
		stc[i+j] = min(stc[i+j], p);
		std[i-j+M-1] = min(std[i-j+M-1], p);

		eda[j] = max(eda[j], p);
		edb[i] = max(edb[i], p);
		edc[i+j] = max(edc[i+j], p);
		edd[i-j+M-1] = max(edd[i-j+M-1], p);
	}

	vector<pii> stv,edv;
	REP(i,MAX) {
		if (A[i]) {
			stv.PB(sta[i]);
			edv.PB(eda[i]);
		}
		if (B[i]) {
			stv.PB(stb[i]);
			edv.PB(edb[i]);
		}
		if (C[i]) {
			stv.PB(stc[i]);
			edv.PB(edc[i]);
		}
		if (D[i]) {
			stv.PB(std[i]);
			edv.PB(edd[i]);
		}
	}
	if (swpflag) {
		for (auto &i: stv) swap(i.F, i.S);
		for (auto &i: edv) swap(i.F, i.S);
	}
	int sz = SZ(stv);
	cout<<"Ja"<<endl;
	cout<<sz<<endl;
	REP(i,sz) cout<<stv[i].F+1<<" "<<stv[i].S+1<<" "<<edv[i].F+1<<" "<<edv[i].S+1<<endl;

	return 0;
}

