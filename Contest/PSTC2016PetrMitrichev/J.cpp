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

int cnt;
struct Bigint{
//	static const int LEN = 1135/8+6;
	static const long long BIGMOD = 100000000;

	int s;
	int vl;
	//long long v[LEN];
	vector<long long> v;
	Bigint() : s(1) { vl = 0; }
	Bigint(long long a) {
		s = 1; vl = 0;
		if (a < 0) { s = -1; a = -a; }
		while (a) {
			push_back(a % BIGMOD);
			a /= BIGMOD;
		}
	}
	Bigint(string str) {
		s = 1; vl = 0;
		int stPos = 0, num = 0;
		if (!str.empty() && str[0] == '-') {
			stPos = 1;
			s = -1;
		}
		for (int i=SZ(str)-1, q=1; i>=stPos; i--) {
			num += (str[i] - '0') * q;
			if ((q *= 10) >= BIGMOD) {
				push_back(num);
				num = 0; q = 1;
			}
		}
		if (num) push_back(num);
		n();
	}

	int len() const {
		//return vl;
		    return SZ(v);
	}
	bool empty() const { return len() == 0; }
	void push_back(int x) {
		//v[vl++] = x;
		    v.PB(x);
	}
	void pop_back() {
		//vl--;
		    v.pop_back();
	}
	long long back() const {
		//return v[vl-1];
		    return v.back();
	}
	void n() {
		while (!empty() && !back()) pop_back();
	}
	void resize(int nl) {
		vl = nl;
		//fill(v, v+vl, 0);
		    v.resize(nl);
		    fill(ALL(v), 0);
	}

	void print() const {
		if (empty()) { putchar('0'); return; }
		if (s == -1) putchar('-');
		printf("%lld", back());
		for (int i=len()-2; i>=0; i--) printf("%.8lld",v[i]);
	}
	friend std::ostream& operator << (std::ostream& out, const Bigint &a) {
		if (a.empty()) { out << "0"; return out; } 
		if (a.s == -1) out << "-";
		out << a.back();
		for (int i=a.len()-2; i>=0; i--) {
			char str[10];
			snprintf(str, 5, "%.8lld", a.v[i]);
			out << str;
		}
		return out;
	}

	int cp3(const Bigint &b)const {
		if (s != b.s) return s - b.s;
		if (s == -1) return -(-*this).cp3(-b);
		if (len() != b.len()) return len()-b.len();//int
		for (int i=len()-1; i>=0; i--)
			if (v[i]!=b.v[i]) return v[i]-b.v[i];
		return 0;
	}

	bool operator < (const Bigint &b)const{ return cp3(b)<0; }
	bool operator <= (const Bigint &b)const{ return cp3(b)<=0; }
	bool operator == (const Bigint &b)const{ return cp3(b)==0; }
	bool operator != (const Bigint &b)const{ return cp3(b)!=0; }
	bool operator > (const Bigint &b)const{ return cp3(b)>0; }
	bool operator >= (const Bigint &b)const{ return cp3(b)>=0; }

	Bigint operator - () const {
		Bigint r = (*this);
		r.s = -r.s;
		return r;
	}
	Bigint operator + (const Bigint &b) const {
		if (s == -1) return -(-(*this)+(-b));
		if (b.s == -1) return (*this)-(-b);
		Bigint r;
		int nl = max(len(), b.len());
		r.resize(nl + 1);
		for (int i=0; i<nl; i++) {
			if (i < len()) r.v[i] += v[i];
			if (i < b.len()) r.v[i] += b.v[i];
			if(r.v[i] >= BIGMOD) {
				r.v[i+1] += r.v[i] / BIGMOD;
				r.v[i] %= BIGMOD;
			}
		}
		r.n();
		return r;
	}
	Bigint operator - (const Bigint &b) const {
		if (s == -1) return -(-(*this)-(-b));
		if (b.s == -1) return (*this)+(-b);
		if ((*this) < b) return -(b-(*this));
		Bigint r;
		r.resize(len());
		for (int i=0; i<len(); i++) {
			r.v[i] += v[i];
			if (i < b.len()) r.v[i] -= b.v[i];
			if (r.v[i] < 0) {
				r.v[i] += BIGMOD;
				r.v[i+1]--;
			}
			cnt++;
		}
		r.n();
		return r;
	}
	Bigint operator * (const Bigint &b) {
		Bigint r;
		r.resize(len() + b.len() + 1);
		r.s = s * b.s;
		for (int i=0; i<len(); i++) {
			for (int j=0; j<b.len(); j++) {
				r.v[i+j] += v[i] * b.v[j];
				if(r.v[i+j] >= BIGMOD) {
					r.v[i+j+1] += r.v[i+j] / BIGMOD;
					r.v[i+j] %= BIGMOD;
				}
				cnt++;
			}
		}
		r.n();
		return r;
	}
	Bigint operator / (const Bigint &b) {
		Bigint r;
		r.resize(max(1, len()-b.len()+1));
		int oriS = s;
		Bigint b2 = b; // b2 = abs(b)
		s = b2.s = r.s = 1;
		for (int i=r.len()-1; i>=0; i--) {
			int d=0, u=BIGMOD-1;
			while(d<u) {
				int m = (d+u+1)>>1;
				r.v[i] = m;
				if((r*b2) > (*this)) u = m-1;
				else d = m;
			}
			r.v[i] = d;
		}
		s = oriS;
		r.s = s * b.s;
		r.n();
		return r;
	}
	Bigint operator % (const Bigint &b) {
		return (*this)-(*this)/b*b;
	}
};

const int MX = 511;
int N, K;
Bigint D;
bool used[MX];
vector<int> A;

using A34 = array<int, 3>;
map<A34, Bigint> mp;


Bigint fac[MX];
Bigint C[MX][MX/2+10];
Bigint wrong[MX];

inline Bigint _C(int n, int m) {
	if (m > n-m) return C[n][n-m];
	return C[n][m];
}

static void pre() {
	fac[0] = 1;
	for (int i=1; i<MX; i++) {
		fac[i] = fac[i-1] * i;
	}

	/*
	for (int i=0; i<MX; i++) {
		faclr[i][i] = 1;
		for (int j=i+1; j<MX; j++) {
			faclr[i][j] = faclr[i][j-1] * j;
		}
	}*/

	for (int i=0; i<MX; i++) {
		C[i][0] = 1;
		for (int j=1; j<i; j++) {
			if (j > i-j) break;
			C[i][j] = _C(i-1, j-1) + _C(i-1, j);
		}
	}

	wrong[0] = 1;
	for (int i=1; i<MX; i++) {
		Bigint t = 1, ans = 0;
		for (int j=i; j>=0; j--) {
			if (j%2) {
				ans = ans - t;
			} else {
				ans = ans + t;
			}
			t = t * j;
		}
		wrong[i] = ans;
	}
}


using pii = pair<int, int>;
map<pii, Bigint> mp2;

int zzz;
Bigint dp2(int n, int m) {
	if (n < m) return 0;
	if (n == m) {
		return fac[m];
	}

	if (mp2.count(pii(n, m))) return mp2[pii(n, m)];
	//cout << n << ' ' << m << endl;
	zzz++;

	Bigint ans = Bigint(n-1) * dp2(n-1, m) + Bigint(n-m-1) * dp2(n-2, m);
	mp2[pii(n, m)] = ans;
	return ans;
}

Bigint dp(int n, int m, int k) {
	if (k < 0) return 0;
	if (k > n-m) return 0;
	if (m > n) return 0;

	A34 jwj = {n, m, k};
	{
		auto it = mp.find(jwj);
		if (it != end(mp)) return it->S;
	}

	Bigint ans = 0;
	/*
	for (int i=0; i<=min(n-m, m); i++) {
		if (n-m-i-k < 0) break;
		ans = ans + C[n-m][i] * C[n-m-i][k] * wrong[n-m-i-k] * faclr[m-i][m] * fac[m];
		cout << ans << endl;
	}*/
	ans = _C(n-m, k) * dp2(n-k, m);
	mp[jwj] = ans;
	zzz++;
	return ans;
}

A34 LYH() {
	int n = N - SZ(A) - 1;
	int m = 0, k = K;
	for (int i=0; i<SZ(A); i++) {
		int x = A[i];
		if (x > SZ(A)+1) m++;
		if (x == i+1) k--;
	}
	return A34{n, m, k};
}

void solve() {
	string S;
	cin >> N >> K >> S;
	D = Bigint(S);
	D = D - Bigint(1);

	for (int i=1; i<=N; i++) used[i] = 0;
	A.clear();

	for (int i=0; i<N; i++) {
		int t = N-i;
		int id = 1;
		A34 lyh = LYH();
		int n, m, k;
		vector<int> vec;
		for (int j=0; j<t; j++) {
			while (used[id]) {
				id++;
			}
			vec.PB(id);
			id++;
		}

		int l = 0, r = t-1;
		n = lyh[0], m = lyh[1], k = lyh[2];
		while (l < r) {
			int md = (l+r)/2;

			int dd, ddd, dddd;
			dd = ddd = dddd = 0;
			for (int j=0; j<=md; j++) {
				int x = vec[j];
				if (i+1 == x) ddd++;
				else if (i+1 < x) dddd++;
				else dd++;
			}

			Bigint d = Bigint(dd) * dp(n, m, k) + Bigint(ddd) * dp(n, m, k-1) + Bigint(dddd) * dp(n, m+1, k);
			//cout << A << ' ' << vec[md] << ' ' << D << ' '  << d << endl;

			if (D < d) {
				r = md;
			} else {
				l = md+1;
			}
		}
		A.PB(vec[l]);
		used[vec[l]] = 1;

		if (l) {
			int md = l-1;
			int dd, ddd, dddd;
			dd = ddd = dddd = 0;
			for (int j=0; j<=md; j++) {
				int x = vec[j];
				if (i+1 == x) ddd++;
				else if (i+1 < x) dddd++;
				else dd++;
			}

			Bigint d = Bigint(dd) * dp(n, m, k) + Bigint(ddd) * dp(n, m, k-1) + Bigint(dddd) * dp(n, m+1, k);
			D = D - d;
		}

/*
			int x = id;
			A.PB(x);
			n = lyh[0], m = lyh[1], k = lyh[2];
			if (i+1 == x) {
				k--;
			} else if (x > i+1) {
				m++;
			}
			//cout << A << ' ' << n << ' ' << m << ' ' << k << endl;
			Bigint d = dp(n, m, k);
			//cout << A << ": " << d << endl;
			if (D < d) {
				used[x] = 1;
				break;
			} else {
				D = D - d;
				A.pop_back();
				id++;
				//assert(j != t-1);
			}
			*/
	}

	for (int i=0; i<N; i++) cout << A[i] << " \n"[i == N-1];
}

int main() {
	IOS;

	pre();
	int Q;
	cin >> Q;
	while (Q--) {
		solve();
	}

	cerr << cnt << endl;
	cerr << zzz << endl;
	return 0;
}
