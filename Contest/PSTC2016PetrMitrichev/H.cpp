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

using pdd = pair<double, double>;
using ll = long long;
const ll MAXC = 1000000000;

#define x first
#define y second

pdd operator+(pdd a, pdd b){return {a.F+b.F, a.S+b.S};}
pdd operator-(pdd a, pdd b){return {a.F-b.F, a.S-b.S};}
pdd operator*(double a, pdd b){return {a*b.F, a*b.S};}
double cross(pdd a, pdd b){return a.F*b.S-a.S*b.F;}
double cross(pdd a, pdd b, pdd o){return cross(a-o, b-o);}


ll randc() {
	ll x = rand();
	x = (x << 32) + rand();
	x %= MAXC;
	if (x < 0) x += MAXC;
	return x;
}

vector<pdd> convex_hull(vector<pdd> pt){
	sort(pt.begin(),pt.end());
	int top=0;
	vector<pdd> stk(2*pt.size());
	for (int i=0; i<(int)pt.size(); i++){
		while (top >= 2 && cross(stk[top-1],pt[i],stk[top-2]) <= 0)
			top--;
		stk[top++] = pt[i];
	}
	for (int i=pt.size()-2, t=top+1; i>=0; i--){
		while (top >= t && cross(stk[top-1],pt[i], stk[top-2]) <= 0)
			top--;
		stk[top++] = pt[i];
	}
	stk.resize(top-1);
	return stk;
}

int ans[111];
double mean[333];
void pre() {
	ans[3] = 11;
	ans[4] = 13.139;
	ans[5] = 15.7957;
	ans[6] = 19.9292;
	ans[7] = 27.8856;
	ans[8] = 38.4445;
	ans[9] = 49.0037;
	ans[10] = 58.5097;
	ans[11] = 65.4194;
	ans[12] = 71.5746;
	ans[13] = 76.2381;
	ans[14] = 79.6728;
	ans[15] = 82.3131;
	ans[16] = 84.6225;
	ans[17] = 85.1967;
	ans[18] = 86.6304;
	ans[19] = 87.7143;
	ans[20] = 94;
	ans[3] = 10;
	ans[4] = 11;
	ans[5] = 13;
	ans[6] = 16;
	ans[7] = 22;
	ans[8] = 33;
	ans[9] = 45;
	ans[10] = 58;
	ans[11] = 66;
	ans[12] = 73;
	ans[13] = 79;
	ans[14] = 82;
	ans[15] = 85;
	ans[16] = 88;
	ans[17] = 87;
	ans[18] = 90;
	ans[19] = 90;
	ans[20] = 98;

	mean[10] = 9222.6725506200;
	mean[11] = 9586.0353376400;
	mean[12] = 9817.0753630400;
	mean[13] = 10019.3469379300;
	mean[14] = 10289.7315135200;
	mean[15] = 10483.3290637400;
	mean[16] = 10642.4113066900;
	mean[17] = 10774.9059605700;
	mean[18] = 10881.3122763200;
	mean[19] = 11066.5391652600;
	mean[20] = 11132.8856965800;
	mean[21] = 11198.9049376500;
	mean[22] = 11340.2919712100;
	mean[23] = 11441.7087237000;
	mean[24] = 11543.4687841800;
	mean[25] = 11618.0272890800;
	mean[26] = 11661.1645595100;
	mean[27] = 11753.3100017300;
	mean[28] = 11802.1495718500;
	mean[29] = 11836.3987515800;
	mean[30] = 11899.7260219200;
	mean[31] = 11985.4487417300;
	mean[32] = 12001.6902762000;
	mean[33] = 12053.2879413000;
	mean[34] = 12111.1384412700;
	mean[35] = 12166.0719327600;
	mean[36] = 12179.3762104400;
	mean[37] = 12241.8969903100;
	mean[38] = 12311.2745107800;
	mean[39] = 12320.7185313800;
	mean[40] = 12344.6814196600;
	mean[41] = 12391.8049033200;
	mean[42] = 12432.2421199300;
	mean[43] = 12465.6638356600;
	mean[44] = 12470.4727674400;
	mean[45] = 12524.6318184200;
	mean[46] = 12551.0622080800;
	mean[47] = 12581.8385932700;
	mean[48] = 12567.5928712000;
	mean[49] = 12602.1575508300;
	mean[50] = 12646.0936719700;
	mean[51] = 12656.4168884400;
	mean[52] = 12711.4763965500;
	mean[53] = 12715.8506058900;
	mean[54] = 12718.3499728700;
	mean[55] = 12731.1594632200;
	mean[56] = 12771.7354728100;
	mean[57] = 12779.3889500000;
	mean[58] = 12796.0845541900;
	mean[59] = 12811.8100078700;
	mean[60] = 12853.7103029200;
	mean[61] = 12853.6644994100;
	mean[62] = 12901.0891108500;
	mean[63] = 12883.0699876900;
	mean[64] = 12899.9899707600;
	mean[65] = 12929.1450060500;
	mean[66] = 12939.6725563200;
	mean[67] = 12956.4341512200;
	mean[68] = 12977.4697453700;
	mean[69] = 12989.2632402200;
	mean[70] = 13008.3048964500;
	mean[71] = 12986.9249728700;
	mean[72] = 13010.4235310000;
	mean[73] = 13027.1054532000;
	mean[74] = 13049.2548466100;
	mean[75] = 13055.7455752700;
	mean[76] = 13042.6225187700;
	mean[77] = 13078.6771021300;
	mean[78] = 13090.1224676200;
	mean[79] = 13098.5290268200;
	mean[80] = 13114.0400119400;
	mean[81] = 13118.5941692500;
	mean[82] = 13112.4710761600;
	mean[83] = 13142.7145258500;
	mean[84] = 13136.6014334000;
	mean[85] = 13137.2474049800;
	mean[86] = 13145.9205741600;
	mean[87] = 13172.7281644200;
	mean[88] = 13178.1502229600;
	mean[89] = 13183.9264370100;
	mean[90] = 13195.1036520800;
	mean[91] = 13194.5087669800;
	mean[92] = 13216.9174356700;
	mean[93] = 13209.4785733200;
	mean[94] = 13211.5155433100;
	mean[95] = 13233.1307256800;
	mean[96] = 13229.6359100400;
	mean[97] = 13249.3187403400;
	mean[98] = 13261.4003544200;
	mean[99] = 13272.8440300500;
	mean[100] = 13271.8684610200;
}
int main() {
	IOS;
	pre();
	int N;
	cin>>N;

//	double tot = 0;
	REP(_,N) {
//		int ra;
		int M,x,y;
//		cin>>ra;

//		double xp = 2e9;
//		double yp = 2e9;

		vector<pdd> vec;
		cin>>M;
		REP(__,M) {
			cin>>x>>y;
			vec.PB({x,y});
//			xp = min(xp, 1.*x);
//			yp = min(yp, 1.*y);
		}


		double area = 0;
		REP(i,M) {
			area += vec[i].F * vec[(i+1)%M].S;
			area -= vec[i].S * vec[(i+1)%M].F;
		}

		area = sqrt(abs(area)) / 1e5;

		int res = 10;
		double dif = abs(area - mean[10]);
		REP1(i,10,100) {
			if (dif > abs(mean[i]-area)) {
				dif = abs(mean[i]-area);
				res = i;
			}
		}

		int ni;
		if (M < 3) ni = 10;
		else if (M > 20) ni = 100;
		else ni = ans[M];

		/*
		xp /= 1e9;
		yp /= 1e9;

		int ni2 = sqrt((1 / xp - 1) * (1 / yp - 1));

		if (ni2 < 10) ni2 = 10;
		if (ni2 > 100) ni2 = 100;

		*/

		double a = 1.5;
		double b = 3.5;
		res = (a * ni + b * res) / (a+b);
		cout<<res<<endl;

//		cout<<ra<<" "<<res<<endl;
//		tot += abs(log((double)res/ra));
	}
//	cout<<fixed<<setprecision(10)<<(tot/N)<<endl;

	return 0;
}

