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

const int STEP = 100000;
const double PI = acos(-1);
const double EPS = 1e-9;

typedef pair<double, double> pdd;
typedef pair<pdd, pdd> Line;

pdd operator+(pdd a, pdd b){return {a.F+b.F, a.S+b.S};}
pdd operator-(pdd a, pdd b){return {a.F-b.F, a.S-b.S};}
pdd operator*(double a, pdd b){return {a*b.F, a*b.S};}
double cross(pdd a, pdd b){return a.F*b.S-a.S*b.F;}
double cross(pdd a, pdd b, pdd o){return cross(a-o, b-o);}

int N;

pdd P0;

bool inr(pdd p)
{
	return p.F>=0 and p.F<=1 and p.S>=0 and p.S<=1;
}

pdd interPnt(Line l1, Line l2, bool &res){
    pdd p1, p2, q1, q2;
    tie(p1, p2) = l1;
    tie(q1, q2) = l2;
	double f1 = cross(p2, q1, p1);
    double f2 = -cross(p2, q2, p1);
	double f = (f1 + f2);

    if(fabs(f) < EPS) {
        res = false;
        return {0, 0};
    }

    res = true;
	return (f2 / f) * q1 + (f1 / f) * q2;
}

bool isin(Line l0, Line l1, Line l2) {
    // Check inter(l1, l2) in l0
    bool res;
    pdd p = interPnt(l1, l2, res);
    return cross(l0.S, p, l0.F) > EPS;
}

/* If no solution, check: 1. ret.size() < 3
 * Or more precisely, 2. interPnt(ret[0], ret[1])
 * in all the lines. (use (l.S - l.F).cross(p - l.F) > 0
 */
vector<Line> halfPlaneInter(vector<Line> lines) {
    int sz = lines.size();
    vector<double> ata(sz), ord(sz);
    for (int i=0; i<sz; i++) {
        ord[i] = i;
        pdd d = lines[i].S - lines[i].F;
        ata[i] = atan2(d.S, d.F);
    }
    sort(ALL(ord), [&](int i, int j) {
        if (abs(ata[i] - ata[j]) < EPS) {
            return cross(lines[i].S, lines[j].S, lines[i].F) < 0;
        }
        return ata[i] < ata[j];
    });
    vector<Line> fin;
    for (int i=0; i<sz; i++) {
        if (!i or fabs(ata[ord[i]] - ata[ord[i-1]]) > EPS) {
            fin.PB(lines[ord[i]]);
        }
    }
    
    deque<Line> dq;
    for (int i=0; i<SZ(fin); i++) {
        while(SZ(dq) >= 2 and 
              not isin(fin[i], dq[SZ(dq)-2], dq[SZ(dq)-1])) {
            dq.pop_back();
        }
        while(SZ(dq) >= 2 and 
              not isin(fin[i], dq[0], dq[1])) {
            dq.pop_front();
        }
        dq.push_back(fin[i]);
    }

    while (SZ(dq) >= 3 and
           not isin(dq[0], dq[SZ(dq)-2], dq[SZ(dq)-1])) {
        dq.pop_back();
    }

    while (SZ(dq) >= 3 and
           not isin(dq[SZ(dq)-1], dq[0], dq[1])) {
        dq.pop_front();
    }
    vector<Line> res(ALL(dq));
    return res;
}

double halfPlaneArea(vector<Line> vec)
{
	if(SZ(vec) < 3) return 0;
	int sz = SZ(vec);
	vector<pdd> vpt;
	bool trash;
	for(int i=0; i<sz; i++)
		vpt.PB(interPnt(vec[i], vec[(i+1)%sz], trash));

	double ans = 0;
	for(int i=0; i<sz; i++)
		ans += cross(vpt[i], vpt[(i+1)%sz]) / 2;
	return abs(ans);
}

double dirArea(pdd dir)
{
	vector<Line> vec;
	vec.PB({{0, 0}, {1, 0}});
	vec.PB({{1, 0}, {1, 1}});
	vec.PB({{1, 1}, {0, 1}});
	vec.PB({{0, 1}, {0, 0}});
	vec.PB({P0, P0+dir});
	vec = halfPlaneInter(vec);
	return halfPlaneArea(vec);
}

double eval(double th)
{
	double dx = cos(th), dy = sin(th);
	pdd dir = {dx, dy};
	double lb = 0, rb = 2;
	for(int i=0; i<50; i++)
	{
		double mb = (lb + rb) / 2;
		if(inr(P0 + mb * dir))
			lb = mb;
		else
			rb = mb;
	}
	double len = lb;
	double A = dirArea(dir);

	double ans = (len * len / 2) * N * pow(A, N-1);
//	cout<<"TH "<<th<<" DIR "<<dir<<" LEN "<<len<<" A "<<A<<" ANS "<<ans<<endl;
	return ans;
}

double calc()
{
	double ans = 0;
	for(int i=0; i<STEP; i++)
	{
		double lth = 2 * PI * i / STEP;
		double rth = 2 * PI * (i+1) / STEP;
		double mth = (lth + rth) / 2;

		double lv = eval(lth);
		double mv = eval(mth);
		double rv = eval(rth);

		ans += (lv + 4 * mv + rv) / 6 * (rth - lth);
	}
	return ans;
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

bool inConvex(pdd p, vector<pdd> &vec)
{
	int sz = SZ(vec);
	for(int i=0; i<sz; i++)
	{
		pdd p1 = vec[i], p2 = vec[(i+1)%sz];
		if(cross(p2-p1, p-p1) < 0) return false;
	}
	return true;
}

double frand()
{
	return (double)rand() / RAND_MAX;
}

double sim(int k)
{
	double cnt = 0;

	for(int x=0; x<k; x++)
	{
		vector<pdd> vec;
		for(int i=0; i<N; i++)
			vec.PB({frand(), frand()});
		vec = convex_hull(vec);
		if(inConvex(P0, vec))
			cnt += 1;
	}
	return cnt / k;
}

int main() {
	IOS;
	srand(time(0));

	cin>>N>>P0.F>>P0.S;

	double ans = 1 - calc();
	cout<<fixed<<setprecision(10)<<ans<<endl;
//	cout<<sim(1000000)<<endl;

	return 0;
}

