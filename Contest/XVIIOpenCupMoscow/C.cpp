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

#define int long long

const int MXN = 333333;
const int MX = MXN;
using pii = pair<int, int>;

struct BccVertex {
	int n,nBcc,step,root,dfn[MXN],low[MXN];
	vector<int> E[MXN], ap;
	vector<pii> bcc[MXN];
	int top;
	pii stk[MXN];
	void init(int _n) {
		n = _n;
		nBcc = step = 0;
		for (int i=0; i<n; i++) E[i].clear();
	}
	void add_edge(int u, int v) {
		E[u].PB(v);
		E[v].PB(u);
	}
	void DFS(int u, int f) {
		dfn[u] = low[u] = step++;
		int son = 0;
		for (auto v:E[u]) {
			if (v == f) continue;
			if (dfn[v] == -1) {
				son++;
				stk[top++] = {u,v};
				DFS(v,u);
				if (low[v] >= dfn[u]) {
					if(v != root) ap.PB(v);
					do {
						assert(top > 0);
						bcc[nBcc].PB(stk[--top]);
					} while (stk[top] != pii(u,v));
					nBcc++;
				}
				low[u] = min(low[u], low[v]);
			} else {
				if (dfn[v] < dfn[u]) stk[top++] = pii(u,v);
				low[u] = min(low[u],dfn[v]);
			}
		}
		if (u == root && son > 1) ap.PB(u);
	}
	// return the edges of each bcc;
	vector<vector<pii>> solve() {
		vector<vector<pii>> res;
		for (int i=0; i<n; i++) {
			dfn[i] = low[i] = -1;
		}
		ap.clear();
		for (int i=0; i<n; i++) {
			if (dfn[i] == -1) {
				top = 0;
				root = i;
				DFS(i,i);
			}
		}
		REP(i,nBcc) res.PB(bcc[i]);
		return res;
	}
} graph;
int V, M;
int B;
vector<vector<pii> > bcce;
vector<int> vtb[MX];
vector<int> bccv[MX];
bool isp[MX];

vector<int> E[MX];
int vt[MX];
int color[MX];

bool colo(int u, int c) {
	if (vt[u]) {
		return (c == color[u]);
	}

	vt[u] = 1;
	color[u] = c;

	for (auto v: E[u]) {
		bool res = colo(v, !c);
		if (!res) return 0;
	}

	return 1;
}

using LL = long long;
LL ans[2];
LL res[MX][2];

LL C2(int x) {
	LL y = x;
	return y * (y-1) / 2;
}

void dfs(int u, int sv) {
	const auto &vts = bccv[u];
	
	vector<pii> chr;
	for (auto s: vts) if (isp[s] && s != sv) {
		for (auto v: vtb[s]) {
			if (v == u) continue;
			dfs(v, s);
			chr.PB({v, s});
		}
	}

	for (auto v: vts) {
		E[v].clear();
		vt[v] = 0;
	}
	for (auto p: bcce[u]) {
		E[p.F].PB(p.S);
		E[p.S].PB(p.F);
	}
	bool flag = colo(vts[0], 0);


	int cl[2] = {0, 0};

	if (!flag) {
		res[u][0] = 1;
		res[u][1] = 0;

		for (auto &p: chr) {
			swap(p.F, p.S);
		}
		sort(ALL(chr));

		int i = 0;
		int n = SZ(chr);
		while (i < n) {
			int j = i;
			while (j < n && chr[j].F == chr[i].F) {
				j++;
			}
			LL c[2] = {0, 0};

			for (int k=i; k<j; k++) {
				int v = chr[k].S;
				ans[0] += c[0] * (res[v][0]-1);
				ans[0] += c[1] * res[v][1];

				ans[1] += c[1] * (res[v][0]-1);
				ans[1] += c[0] * res[v][1];

				c[0] += res[v][0] - 1;
				c[1] += res[v][1];
			}
			i = j;
		}


		
		return;
	}

	if (sv == -1) sv = vts[0];

	int ccc = color[sv];
	for (auto v: vts) {
		color[v] ^= ccc;
	}

	LL a0 = -ans[0], a1 = -ans[1];


	for (auto v: vts) {
		cl[color[v]] ++;
	}

	ans[0] += C2(cl[0]);
	ans[0] += C2(cl[1]);
	ans[1] += 1LL * cl[0] * cl[1];


	res[u][0] = cl[0];
	res[u][1] = cl[1];

	for (auto p: chr) {
		int v = p.F, s = p.S;

		LL cc[2] = {res[u][0], res[u][1]};
		cc[color[s]] --;

		LL dd[2] = {res[v][0]-1, res[v][1]};

		ans[0] += 1LL * dd[0] * cc[color[s]]; 
		ans[0] += 1LL * dd[1] * cc[!color[s]]; 

		ans[1] += 1LL * dd[0] * cc[!color[s]];
		ans[1] += 1LL * dd[1] * cc[color[s]];

		//cout << ans[0] + a0 << " ! " << ans[1] + a1 << endl;

		res[u][0] += res[v][color[s]^0];
		res[u][1] += res[v][color[s]^1];
		res[u][color[s]] --;
	}

	a0 += ans[0]; a1 += ans[1];
	//cout << u << ": " << res[u][0] << ' ' << res[u][1] << endl;
	//cout << cl[0] << ' ' << cl[1] << endl;
	//cout << a0 << ' ' << a1 << endl;
}

int32_t main() {
	IOS;

	cin >> V >> M;
	if (V == 1) {
		cout << 0 << ' ' << 0 << endl;
		return 0;
	}
	graph.init(V);
	for (int i=0; i<M; i++) {
		int u, v; cin >> u >> v;
		u--; v--;
		graph.add_edge(u, v);
	}

	bcce = graph.solve();
	B = SZ(bcce);

	for (int i=0; i<B; i++) {
		const auto &vec = bcce[i];
		vector<int> vv;
		for (auto p: vec) {
			vv.PB(p.F); vv.PB(p.S);
		}
		sort(ALL(vv));
		vv.resize(unique(ALL(vv)) - vv.begin());

		for (auto v: vv) {
			vtb[v].PB(i);
			bccv[i].PB(v);
		}
	}

	//for (int i=0; i<B; i++) cout << bccv[i] << endl;

	for (int i=0; i<V; i++) {
		isp[i] = (SZ(vtb[i]) >= 2);
	}

	dfs(0, -1);

	cout << ans[0] << ' ' << ans[1] << endl;


	return 0;
}

/* 
[ 0 1 ]
[ 0 2 ]
[ 0 3 ]
1: 2 0
1 0
2: 1 1
0 1
0: 3 2
3 5
4 6


[ 3 4 5 6 ]
[ 3 7 8 ]
[ 2 9 ]
[ 0 1 2 3 ]
1: 3 0
3 0
2: 1 1
0 1
3: 3 2
4 5
7 6


   */

