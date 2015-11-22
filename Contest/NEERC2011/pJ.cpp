#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
#define FZ(n) memset((n),0,sizeof(n))
#define FMO(n) memset((n),-1,sizeof(n))
#define MC(n,m) memcpy((n),(m),sizeof(n))
#define F first
#define S second
#define MP make_pair
#define PB push_back
#define ALL(x) begin(x),end(x)
#define SZ(x) ((int)(x).size())
#define IOS ios_base::sync_with_stdio(0); cin.tie(0)
#ifdef ONLINE_JUDGE
#define FILEIO(name) \
  freopen(name".in", "r", stdin); \
  freopen(name".out", "w", stdout);
#else
#define FILEIO(name)
#endif
// Let's Fight!

struct Bigint {
	static const int bL = 60;
	static const int bM = 10000;
	int v[bL], l, s;
	Bigint() : l(0), s(1) {
		FZ(v);
	}
	Bigint (long long a) {
		*this = Bigint();
		s = 1;
		if (a<0) {
			s = -1;
			a = -a;
		}
		for (l=0; a; v[l++]=a%bM, a/=bM);
	}
	void n() {
		for (; l; l--) if (v[l-1]) return;
	}
    void print() const {
        if(l==0){ putchar('0');return; }
        if(s==-1) putchar('-');
        printf("%d",v[l-1]);
        for(int i=l-2;i>=0;i--) printf("%.4d",v[i]);
    }

	int cp3(const Bigint &b)const {
		if (s != b.s) return s > b.s;
		if (s == -1) return -(-*this).cp3(-b);
        if(l!=b.l) return l>b.l?1:-1;
        for(int i=l-1;i>=0;i--)
            if(v[i]!=b.v[i])
                return v[i]>b.v[i]?1:-1;
        return 0;
    }
	bool operator < (const Bigint &b)const{ return cp3(b)==-1; }
    bool operator == (const Bigint &b)const{ return cp3(b)==0; }
    bool operator != (const Bigint &b)const{ return cp3(b)!=0; }
    bool operator > (const Bigint &b)const{ return cp3(b)==1; }
	Bigint operator - () const {
		Bigint r = (*this);
		r.s = -r.s;
		return r;
	}
    Bigint operator + (const Bigint &b) const {
        if(s == -1) return -(-(*this)+(-b));
        if(b.s == -1) return (*this)-(-b);
        Bigint r;
        r.l=max(l,b.l);
        for(int i=0;i<r.l;i++) {
            r.v[i]+=v[i]+b.v[i];
            if(r.v[i]>=bM) {
                r.v[i+1]+=r.v[i]/bM;
                r.v[i]%=bM;
            }
        }
        if(r.v[r.l]) r.l++;
        return r;
    }

    Bigint operator - (const Bigint &b) const {
        if(s == -1) return -(-(*this)-(-b));
        if(b.s == -1) return (*this)+(-b);
        if((*this)<b) return -(b-(*this));
        Bigint r;
        r.l=l;
        for(int i=0;i<l;i++) {
            r.v[i]+=v[i];
            if(i<b.l) r.v[i]-=b.v[i];
            if(r.v[i]<0) {
                r.v[i]+=bM;
                r.v[i+1]--;
            }
        }
        r.n();
        return r;
    }
	Bigint sign(int s2) {
		Bigint r = *this;
		r.s *= s2;
		return r;
	}
};

typedef pair<Bigint, Bigint> pii;

struct Instruction {
	vector<string> ins;
}f[105];

struct dp_t{
	Bigint v[5];
	dp_t () {
		for (int i=0; i<5; i++) {
			v[i] = Bigint();
		}
	}
}dp[105];

int N, onstack[105][4];
pii location[105][4];
int done[105][4];
int movD[105];
pii mov[105][4];
Bigint ans;

const int dirMove[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
const int sign[4][2] = {{1, 1}, {-1, 1}, {-1, -1}, {1, -1}};

Bigint absBigint(Bigint a) {
	a.s = 1;
	return a;
}
void rotateR(dp_t &a) {
	a.v[4] = a.v[0];
	for (int i=0; i<4; i++)
		a.v[i] = a.v[i+1];
}
void back0(dp_t &a, int dir) {
	for (int i=0; i<dir; i++) {
		rotateR(a);
	}
}
void go(int id, Bigint x, Bigint y, int dir) {
	if (onstack[id][dir]) {
		if (x != location[id][dir].F || y != location[id][dir].S) {
			puts("Infinity");
		} else {
			for (int i=1; i<=N; i++) {
				for (int j=0; j<4; j++) {
					ans = max(ans, dp[i].v[j]);
				}
			}
			ans.print();
			puts("");
		}
		exit(0);
	}
	if (done[id][dir]) return;
	onstack[id][dir] = 1;
	Bigint oriX = x;
	Bigint oriY = y;
	location[id][dir] = {x, y};
	dp_t best;
	int oriD = dir;
	for (auto it : f[id].ins) {
		if ('0' <= it[0] && it[0] <= '9') {
			int j = atoi(it.c_str());
			go(j, x, y, dir);

			dp_t tmp = dp[j];

			for (int i=0; i<4-dir; i++) {
				rotateR(tmp);
			}
			Bigint tx = x - oriX;
			Bigint ty = y - oriY;
			for (int i=0; i<4; i++) {
				ans = max(ans, tmp.v[i] + x.sign(sign[i][0]) + y.sign(sign[i][1]));
				best.v[i] = max(best.v[i], tmp.v[i] + tx.sign(sign[i][0]) + ty.sign(sign[i][1]));
			}

			x = x + mov[j][dir].F;
			y = y + mov[j][dir].S;
			dir = (dir + movD[j]) % 4;
		} else {
			if (it == "LEFT") {
				dir++;
			} else if (it == "RIGHT") {
				dir--;
			} else {
				x = x + dirMove[dir][0];
				y = y + dirMove[dir][1];
			}
			
			Bigint tx = x - oriX;
			Bigint ty = y - oriY;
			for (int i=0; i<4; i++) {
				best.v[i] = max(best.v[i], tx.sign(sign[i][0]) + ty.sign(sign[i][1]));
			}

			dir = (dir + 4) % 4;
		}
		ans = max(ans, absBigint(x) + absBigint(y));
	}
	mov[id][oriD] = {x - oriX, y - oriY};
	movD[id] = (4 + dir - oriD) % 4;
	back0(best, oriD);
	dp[id] = best;

	done[id][oriD] = 1;
	onstack[id][oriD] = 0;
}

int main() {
	FILEIO("journey");
	cin >> N;
	for (int i=1, M; i<=N; i++) {
		cin >> M;
		for (int j=0; j<M; j++) {
			string str;
			cin >> str;
			if (str[0] == 'F') {
				str = str.substr(1, string::npos);
			}
			f[i].ins.PB(str);
		}
	}
	FZ(done);
	FZ(onstack);
	go(1, 0, 0, 0);
	ans.print();
	puts("");

	return 0;
}
