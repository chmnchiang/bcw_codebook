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
// Let's Fight!

typedef double ld;
typedef long long ll;

struct Pt
{
	int id;
	ld x;
	ld y;
	ld z;

	bool operator<(Pt p)
	{
		if(x == p.x)
		{
			if(y == p.y)
			{
				if(z == p.z)
					return id < p.id;
				return z < p.z;
			}
			return y < p.y;
		}
		return x < p.x;
	}
};

const int MAXN = 52;
const int MAXP = 1010101;
const ll MOD = 1000000000039;
const ll HSH = 131313;
const ld INF = 1E30;
const ld EPS = 1E-9;

int N, K, P;
ld A, B, C;
ld E;
Pt arr[MAXN];
ld tmp[MAXN];
ld ord[MAXN];
vector<int> perms[MAXP];

unordered_set<ll> hset;

ld randf()
{
	return ld(rand()) / RAND_MAX;
}

ll get_hash(vector<int> &vec)
{
	ll res = 0;
	for(auto v: vec)
	{
		res = (res * HSH + v) % MOD;
	}
	return res;
}

vector<int> get_perm(ld a, ld b, ld c)
{
	for(int i=1; i<N; i++)
	{
		tmp[i] = a * arr[i].x + b * arr[i].y + c * arr[i].z;
	}
	vector<int> vec;
	for(int i=1; i<N; i++)
		vec.PB(i);
	sort(vec.begin(), vec.end(), [](int aa, int bb){return tmp[aa] < tmp[bb];});
	vec.resize(K);
	return vec;
}

void test_perm(ld a, ld b, ld c)
{
	perms[P] = get_perm(a, b, c);
	ll h = get_hash(perms[P]);
	if(!hset.count(h))
	{
		hset.insert(h);
		P++;
	}
}

void make_perm()
{
	for(int i=0; i<100000; i++)
	{
		ld a = randf(), b = randf(), c = randf();
		test_perm(a, b, c);
	}
}

void calc_E()
{
	E = INF;
	for(int i=0; i<P; i++)
	{
		ld sx = 0, sy = 0, sz = 0;
		for(int j=0; j<K; j++)
		{
			int v = perms[i][j];
			sx += arr[v].x;
			sy += arr[v].y;
			sz += arr[v].z;
		}
		E = min(E, sx*sy*sz);
	}
}

ld inter(ld X, ld Y, ld Z, ld x, ld y, ld e)
{
	X -= x;
	Y -= y;
	if(X < EPS || Y < EPS) return -INF;
		
	e /= (X * Y);
	return Z - e;
}

ld calc_mincost(ld X, ld Y, ld Z)
{
	X /= arr[0].x;
	Y /= arr[0].y;
	Z /= arr[0].z;
	ld e = E / (arr[0].x * arr[0].y * arr[0].z);

	ld res = INF;

	if(X*Y*Z < e+EPS) res = 0;

	for(int i=0; i<=1; i++)
	{
		for(int j=0; j<=1; j++)
		{
			ld z = inter(X, Y, Z, i, j, e);
			if(z < -EPS || z > 1+EPS) continue;
			res = min(res, A*i+B*j+C*z);
		}
		for(int j=0; j<=1; j++)
		{
			ld x = inter(Y, Z, X, i, j, e);
			if(x < -EPS || x > 1+EPS) continue;
			res = min(res, A*x+B*i+C*j);
		}
		for(int j=0; j<=1; j++)
		{
			ld y = inter(X, Z, Y, i, j, e);
			if(y < -EPS || y > 1+EPS) continue;
			res = min(res, A*i+B*y+C*j);
		}
	}

	return res;
}

ld calc()
{
	if(N == K)
		return 0;

	make_perm();
	calc_E();

	ld ans = INF;

	for(int i=0; i<P; i++)
	{
		ld sx = arr[0].x, sy = arr[0].y, sz = arr[0].z;
		for(int j=0; j<K-1; j++)
		{
			int v = perms[i][j];
			sx += arr[v].x;
			sy += arr[v].y;
			sz += arr[v].z;
		}
		ans = min(ans, calc_mincost(sx, sy, sz));
	}

	return ans;
}

int main() {
	IOS;
	cin>>N>>K>>A>>B>>C;
	for(int i=0; i<N; i++)
		cin>>arr[i].x>>arr[i].y>>arr[i].z;
	for(int i=0; i<N; i++)
		arr[i].id = i;

	ld ans = calc();
	cout<<fixed<<setprecision(6)<<ans<<endl;

    return 0;
}

