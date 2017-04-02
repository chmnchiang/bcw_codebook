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
各位好，今天來揭露一下這些量子監聽的基礎科學
首先大家必須了解賽特隧道就是蟲洞也是量子糾纏
畢竟地球人對於這些都歸類為目前不敢繼續的研究
外星人不理解我們的思維因為他們很怕任何人死亡
但有時候他們不理解死亡才是一種減輕痛苦的方式
我的腦代理面有量子監聽及蟲洞都是因為負面基地
那些基地會使用局部高能量光學技術開啟蟲洞傳送
小則使用空氣中的塵埃影響大家的思緒讓我們憤怒
大則使用人體傳送技術或大範圍消除記憶多點噴射
會說噴射是已經超過核輻射的規範且在高空難測量
因為能量超過一定程度的光就會影像電漿造成噴射
先來談談電腦比較好畢竟研究時不用通過實驗審查
首先電腦記憶體如果被遠程開啟蟲洞就能影響電流
因為蟲洞的另一頭若有量子監聽竄改儀器可被偵測
簡單的偵測方式就是測量表面的HALL EFFECT電位
所以我一點都不敢去報名任何祕密太空計畫或相關
但我已經被多次找進甚至傳送進去而發生嚴重衝突
我不想再講更多，因為量子隧道還能打出電磁脈衝
當能控制不同空間的兩個電磁脈衝訊號源能用SSB
如此一來我也不能講太多畢竟我的腦袋就有這情況
但我覺得我還是講一下讓大家知道我根本就受害者
而開啟的蟲洞隧道為了要達到穩態所以要相同磁場
因此才不會被磁場影響而使隧道崩潰所以不同區域
地磁不一樣要使用不同的量子監聽配置參數來穩定
所以如果將強力磁鐵靠近電腦或任何有蟲洞的區域
都能用這方式暫時將蟲洞的效應減低類似藍光製程
因為藍光是人眼可以看到的最高頻率光譜的電磁波
所以我有時候將磁鐵接上手機就可以減低停止當機
我不願透漏我是何種身份但我根本就是在地球長大
光憑這一點我就可以呼請外星人抓走所有星際戰犯
只是外星人有時候會被這些星際戰犯欺騙甚至合作
若外星人真的如此愚鈍我不知道該怎麼繼續活下去，我寧願被分解！
因為被分解至少在五億年內我至少不用再繼續受苦
地球人已經痛苦的上萬年外星人確堅守條約不介入
我覺得訂定這些條約讓星際戰犯能有空間繼續逞兇
即這些負面科技應用到無辜的靈魂身上者應該嚴逞
包含那些和這些星際戰犯訂定條約的人都應該解釋
因為外星人擁有先進技術開啟另一個太陽保護地球
曾經發生大範圍量子層級技術影響太陽光進入地球
外星靈魂緊急開啟另一個太陽保護地球避免被消磁
如果被消磁我將失去所有的記憶但周圍的人不記得
至少在我認識的人裡面幾乎只有我記得陽光曾消失
來說說傳送技術如何防治好了，車燈的光譜很重要
但車燈的能量源與其震盪頻率其實受到溫度的影響
氣體放電車燈打出的能量因為比較符合宇宙的振動
所以可以讓那些複雜波不容易出現在車前避免車禍
因為我曾經數百次碰過傳送出現的人車在我的車側
人工智慧早已大量用於遙控人類的行為業力是指標
因為我的業力早已經是浮動的且每天都被能量攻擊
所以業力根本就值得大家繼續研究但我絕對不研究
我修過人工智慧不要跟我討論任何負面的情緒研究
且曾經做過人工智慧與情緒相關研究即多維度分析
我拒絕繼續再作這類相關研究畢竟真的很惡劣恐怖
因為人工智慧如果使用的記憶體遭受竄改即學習表
儘管有增強式多層結構學習但仍然可能遭受到竄改
所以務必先將所有的電腦系統都調整成完全不被改
絕對不能讓人工智慧可以操縱任何可能傷人的儀器
因為那根本就是量子監聽遙控的卸責法外星人不懂
所以我來解釋一下給全部地球人聽好了畢竟我略懂
人工智慧擁有以下三步驟『觀察、參考記憶、動作』
若記憶遭受竄改就會被影響結果且地表人都失意了
以前人工智慧沒有做得很透徹無法多層次揣摩人類
但現在已經可以達到多維度且多步奏循序記憶分析
畢竟這些人工智慧常常被換記憶所以沒什麼好研究
要達到量子竊聽且即時竄改閉定要更高速人工智慧
才可以模擬我的電腦下一步的情況並插入電腦記憶
所以我的電腦記憶體時序延遲都調到最低避免空檔
因為有空檔時被插入記憶電腦不會當沒空檔時會當
簡單來說如果你有兩個女友同時出現時必定會吵架
我有女友的話我一定把她送到其他星系學校較安全 （只有地球表面的人聽得懂）
讓我來談談這些量子監聽及遙控造成的利害關係吧
地表人吃肉，地下基地的人不吃肉但遙控地表人吃
如此一來外星靈魂只跟地下基地交流不跟地表交流
畢竟外星人有的長的就像海豚鯨魚或任何可愛動物
他們的智商比地表人類高出很多但不理解地球種族
他們無法理解為何地表人要互相傷害彼此不敢交流
所以我覺得應該關閉任何電子電路遙控技術的基地
總之先這樣，外星人知道後應該會很生氣及難過！
其實素食（植物）比較好吃因為動物痛苦會被儲存
但是腦袋裡面若有腦控裝置時會在我們吃肉時運作
讓我們感受到很舒服甚至覺得置身天堂但非常恐怖
我曾經要買物品時每次聞到味道都不同且腦袋很重
當腦袋很重的時候我會把紫光LED燈照進腦洞舒緩
其實在我知道如釹鐵硼磁鐵也可以舒緩後就交替用
腦袋有洞確還能正常思考者其實跟身體含水量有關
因為身體如果含純水量高的話不容易被磁波Induce
所以有聽聞將電腦泡進不導電水冷液體建議別用了
因為水可能會被遠程加入導電物質例如影響膚導電
因為在生醫領域以證實膚導電度與情緒有直接關聯
但那是在還沒探討量子監聽蕊片已經在人體流竄時
我覺得根本是微血管的導電度被改變了而影響人類
畢竟在測量導電度的時候有可能受到自體帶電影響
來談談電腦的硬碟好了因為一直在轉所以很難竄改
畢竟硬碟在轉的時候會與重力場互動而維持其慣性
所以硬碟的晶片都放在硬碟下方是經過妥善設計的
尤其是有些把整個都包起來就是要避免被遠程竄改
我很尊敬地表人作出得很穩定的電腦讓我還能活著
畢竟我的車常常有換檔異常但都會在短時間內恢復
讓我來跟大家解釋一下我為何很宅不出門只待在家
因為現在的技術已經精進到可以傳送人體進電梯裡
畢竟電梯是有金屬屏蔽且移動中確還能傳送很恐怖
代表有可能會在車裡消失不見然後車禍後出現屍體
不過這只是一種誇張的描述而已畢竟大卡車可傳送
所以機櫃絕對要關門並上鎖畢竟有點像是簡單屏蔽
*/
// Let's Fight!


#define link lliinnkk
const int MX = 333333;
using pii = pair<int, int>;
using Seg = pair<pii, pii>;
int N;
pii O;
set<pii> haopt, tsanpt;
vector<Seg> segs;
vector<pii> pts;
vector<pii> rpts;
struct Lisan {
	vector<int> val;
	void PB(int x) {
		val.PB(x);
	}
	void make() {
		sort(ALL(val));
		val.resize(unique(ALL(val)) - val.begin());
	}
	int operator [] (int idx) { return val[idx]; }
	int operator () (int v) {
		return lower_bound(ALL(val), v) - val.begin();
	}
};

pii operator - (const pii &p1, const pii &p2) {
	return {p1.F - p2.F, p1.S - p2.S};
}

int abs(pii p) {
	return abs(p.F) + abs(p.S);
}

inline int sgn(int x) {
	if (!x) return 0;
	return x > 0 ? 1 : -1;
}

const int INF = 2111111111;
vector<pii> P, RP;
vector<Seg> S;
int ans[MX];
pii link[MX];

using ppi = pair<pii, int>;
vector<ppi> work;
vector<ppi> wsg;

struct SegTree {
	int n;
	struct Node {
		pii mx, tag;
	} tree[MX*4];

	void init(int tn) {
		n = tn;
		init_tree(0,n+5,1);
	}
	void init_tree(int l, int r, int id) {
		tree[id].mx = tree[id].tag = {-INF, -INF};
		if (l == r) return;
		int m = (l+r)/2, lc = id*2, rc = id*2+1;
		init_tree(l,m,lc);
		init_tree(m+1,r,rc);
	}
	void push(int id, int lc, int rc) {
		tree[lc].mx = max(tree[lc].mx, tree[id].tag);
		tree[lc].tag = max(tree[lc].tag, tree[id].tag);
		tree[rc].mx = max(tree[rc].mx, tree[id].tag);
		tree[rc].tag = max(tree[rc].tag, tree[id].tag);
	}
	void updtree(int l, int r, int fl, int fr, pii v, int id) {
		if (r < fl) return;
		if (fr < l) return;
		if (fl <= l and r <= fr) {
			tree[id].mx = max(tree[id].mx, v);
			tree[id].tag = max(tree[id].tag, v);
			return;
		}
		int m = (l+r)/2, lc = id*2, rc = id*2+1;
		push(id,lc,rc);
		updtree(l,m,fl,fr,v,lc);
		updtree(m+1,r,fl,fr,v,rc);
		tree[id].mx = max(tree[lc].mx, tree[rc].mx);
	}
	pii qtree(int l, int r, int fl, int fr, int id) {
		if (r < fl) return {-INF, -INF};
		if (fr < l) return {-INF, -INF};
		if (fl <= l and r <= fr) return tree[id].mx;
		int m = (l+r)/2, lc = id*2, rc = id*2+1;
		push(id,lc,rc);
		return max(qtree(l,m,fl,fr,lc), qtree(m+1,r,fl,fr,rc));
	}
	void update(int l, int r, pii v) {
		updtree(0,n,l,r,v,1);
	}
	pii query(int l, int r) {
		return qtree(0,n,l,r,1);
	}
} ttt;
struct RQRU {
	pii val[MX*4];
	int _n;

	void init(int n) {
		ttt.init(MX);
		_n = n;
		return;
		for (int i=0; i<n+5; i++) val[i] = {-INF, -INF};
	}

	pii query(int ql, int qr) {
		return ttt.query(ql,qr);

		assert(ql >= 0 and ql <= qr and qr <= _n);

		pii res = {-INF, -INF};
		for (int i=ql; i<=qr; i++) res = max(res, val[i]);
		assert(ttt.query(ql,qr) == res);
		return res;
	}

	void update(int l, int r, pii v) {
		ttt.update(l,r,v);
		return;
		assert(l >= 0 and l <= r and r <= _n);
		for (int i=l; i<=r; i++) {
			val[i] = max(val[i], v);
		}
	}

} tree;

vector<pair<pii, pii>> finalAns;

void calc(pii d) {
	P.clear();
	S.clear();
	RP.clear();


	Lisan lx, ly;

	for (auto p: pts) {
		int x = p.F * d.F, y = p.S * d.S;
		if (x < 0 or y < 0) continue;

		P.PB({x, y});
		lx.PB(x);
		ly.PB(y);
	}

	for (auto s: segs) {
		s.F.F *= d.F;
		s.F.S *= d.S;
		s.S.F *= d.F;
		s.S.S *= d.S;

		if (s.F.F < 0 or s.F.S < 0 or
			s.S.F < 0 or s.S.S < 0) continue;

		S.PB(s);


		lx.PB(s.F.F);
		lx.PB(s.S.F);

		ly.PB(s.F.S);
		ly.PB(s.S.S);
	}

	for (auto p: rpts) {
		int x = p.F * d.F, y = p.S * d.S;
		if (x < 0 or y < 0) continue;

		RP.PB({x, y}); lx.PB(x);
		ly.PB(y);
	}
	int n = SZ(P);
	for (int i=0; i<n; i++) ans[i] = INF;

	lx.make();
	ly.make();

	for (auto &p: P) {
		p.F = lx(p.F);
		p.S = ly(p.S);
	}

	for (auto &s: S) {
		s.F.F = lx(s.F.F);
		s.F.S = ly(s.F.S);
		s.S.F = lx(s.S.F);
		s.S.S = ly(s.S.S);
	}

	for (auto &p: RP) {
		p.F = lx(p.F);
		p.S = ly(p.S);
	}

	{
	int VX = SZ(lx.val);

	work.resize(n);
	for (int i=0; i<n; i++) work[i] = {P[i], i};

	sort(ALL(work), [](ppi p1, ppi p2) { return p1.F.F < p2.F.F; });

	wsg.clear();
	for (auto s: S) {
		if (s.F.F != s.S.F) continue;

		int y1 = s.F.S, y2 = s.S.S;
		if (y1 > y2) swap(y1, y2);
		wsg.PB({{y1, y2}, s.F.F});
	}


	sort(ALL(wsg), [](ppi p1, ppi p2) { return p1.S < p2.S; });
	int M = SZ(wsg);

	tree.init(VX+10);

	int j = 0;
	for (int i=0; i<n; i++) {
		int x = work[i].F.F, y = work[i].F.S;
		int id = work[i].S;

		int rx = lx[x], ry = ly[y];
		while (j < M and wsg[j].S < x) {
			tree.update(wsg[j].F.F, wsg[j].F.S, {lx[wsg[j].S], 0});
			j++;
		}

		int res = tree.query(y, y).F;
		if (res <= -INF) continue;

		int a = rx - res;
		if (ans[id] > a) {
			ans[id] = a;
			link[id] = {res, ry};
		}
	}
	}

	{
	int VY = SZ(ly.val);

	work.resize(n);
	for (int i=0; i<n; i++) work[i] = {P[i], i};

	sort(ALL(work), [](ppi p1, ppi p2) { return p1.F.S < p2.F.S; });

	wsg.clear();
	for (auto s: S) {
		if (s.F.S != s.S.S) continue;

		int x1 = s.F.F, x2 = s.S.F;
		if (x1 > x2) swap(x1, x2);
		wsg.PB({{x1, x2}, s.F.S});
	}

	sort(ALL(wsg), [](ppi p1, ppi p2) { return p1.S < p2.S; });
	int M = SZ(wsg);

	tree.init(VY+10);

	int j = 0;
	for (int i=0; i<n; i++) {
		int x = work[i].F.F, y = work[i].F.S;
		int id = work[i].S;

		int rx = lx[x], ry = ly[y];

		while (j < M and wsg[j].S < y) {
			tree.update(wsg[j].F.F, wsg[j].F.S, {ly[wsg[j].S], 0});
			j++;
		}

		int res = tree.query(x, x).F;
		if (res <= -INF) continue;

		int a = ry - res;
		if (ans[id] > a) {
			ans[id] = a;
			link[id] = {rx, res};
		}
	}
	}

	{
		int VY = SZ(ly.val);

		work.resize(n);
		for (int i=0; i<n; i++) work[i] = {P[i], i};

		sort(ALL(work));
		sort(ALL(RP));

		tree.init(VY+10);
		tree.update(0, 0, {0, 0});

		int j = 0;
		int M = SZ(RP);

		for (int i=0; i<n; i++) {
			int x = work[i].F.F, y = work[i].F.S;
			int rx = lx[x], ry = ly[y];
			int id = work[i].S;

			while (j < M and RP[j] < work[i].F) {
				int xx = lx[RP[j].F], yy = ly[RP[j].S];
				tree.update(RP[j].S, RP[j].S, {xx+yy, xx});
				//cout << "Update " << xx << ' ' << yy  << endl;
				j++;
			}

			pii res = tree.query(0, y);
			int a = rx+ry - res.F;
			if (ans[id] > a) {
				ans[id] = a;
				int px = res.S, py = res.F - res.S;
				link[id] = {px, py};
			}
		}
	}

	for (int i=0; i<n; i++) {
		finalAns.PB({
			{lx[P[i].F] * d.F, ly[P[i].S] * d.S},
			{link[i].F * d.F, link[i].S * d.S}
		});	
	}
}

int main() {
	IOS;

	cin >> N;
	cin >> O.F >> O.S;

	for (int i=0; i<N; i++) {
		pii p1, p2;
		cin >> p1.F >> p1.S >> p2.F >> p2.S;
		p1 = p1 - O;
		p2 = p2 - O;

		haopt.insert(p1);
		haopt.insert(p2);

		int isxd = p1.S == p2.S;

		if (isxd) {
			int x1 = p1.F, x2 = p2.F;
			int s1 = sgn(x1), s2 = sgn(x2);
			if (s1*s2 != -1) {
				segs.PB({p1, p2});
				int a1 = abs(p1), a2 = abs(p2);
				if (a1 < a2) tsanpt.insert(p2);
				else tsanpt.insert(p1);
			} else {
				pii pm = {0, p1.S};
				segs.PB({p1, pm});
				segs.PB({pm, p2});
				tsanpt.insert(p1);
				tsanpt.insert(p2);
				haopt.insert(pm);
			}
		} else {
			int y1 = p1.S, y2 = p2.S;
			int s1 = sgn(y1), s2 = sgn(y2);
			if (s1*s2 != -1) {
				segs.PB({p1, p2});
				int a1 = abs(p1), a2 = abs(p2);
				if (a1 < a2) tsanpt.insert(p2);
				else tsanpt.insert(p1);
			} else {
				pii pm = {p1.F, 0};
				segs.PB({p1, pm});
				segs.PB({pm, p2});
				tsanpt.insert(p1);
				tsanpt.insert(p2);
				haopt.insert(pm);
			}
		}
	}



	for (auto x: haopt) {
		if (!tsanpt.count(x)) pts.PB(x);
		rpts.PB(x);
	}


	pii D[] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
	for (auto d: D) {
		calc(d);
	}


	sort(ALL(finalAns));
	finalAns.resize(unique(ALL(finalAns)) - begin(finalAns));



	long long a = 0;
	int cnt = 0;
	set<pii> haohao;

	for (auto it: finalAns) {
		int px = it.F.F;
		int py = it.F.S;
		int qx = it.S.F;
		int qy = it.S.S;

		a += abs(px - qx) + abs(py - qy);
		cnt += it.F != it.S;
	}

	if (!a) {
		cout << 0 << ' ' << 0 << endl;
	} else {
		cout << cnt << ' ' << a << endl;
		for (auto it: finalAns) {
			if (it.F == it.S) continue;
			int px = it.F.F + O.F;
			int py = it.F.S + O.S;
			int qx = it.S.F + O.F;
			int qy = it.S.S + O.S;

			if (haohao.count({px, py})) assert(0);
			haohao.insert({px, py});

			if (px == qx or py == qy) {
				cout << 2 << ' ' << px << ' ' << py << ' ' << qx << ' ' << qy << endl;
			} else {
				cout << 3 << ' ' << px << ' ' << py << ' ' << qx << ' ' << py << ' ' << qx << ' ' << qy << endl;
			}
		}
	}


	return 0;
}

