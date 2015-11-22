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

typedef long double ld;
typedef pair<ld, ld> pdd;

const int MAXN = 9;
const int MAXP = 514;
const ld INF = 1E20;
const ld EPS = 1E-9;
const ld PI = acosl(-1);
const ld R = 100;

int N, P;
pdd goal;
pdd pole[MAXN];
pdd pt[MAXP];
ld theta[MAXP];
ld pdis[MAXP];
ld edge[MAXP][MAXP];
vector<int> cirpt[MAXN];

pdd operator+(pdd a, pdd b) {return {a.F+b.F, a.S+b.S};}
pdd operator-(pdd a, pdd b) {return {a.F-b.F, a.S-b.S};}
pdd operator*(pdd a, ld b) {return {a.F*b, a.S*b};}
ld dot(pdd a, pdd b) {return a.F*b.F+a.S*b.S;}
ld cross(pdd a, pdd b) {return a.F*b.S-a.S*b.F;}
ld abs(pdd a) {return sqrtl(dot(a, a));}
ld dis(pdd a, pdd b) {return abs(a-b);}
ld arg(pdd a) {return atan2l(a.S, a.F);}

int newpt(pdd p)
{
	pt[P] = p;
	return P++;
}

pdd point_angle(pdd p, ld th)
{
	return p + pdd(cosl(th), sinl(th)) * R;
}

ld rec(ld x)
{
	while(x >= PI) x -= 2*PI;
	while(x < -PI) x += 2*PI;
	return x;
}

vector<pdd> cir_cir_int(pdd o1, pdd o2)
{
	vector<pdd> ret;
	ld d = abs(o1 - o2);
	if (d > R*2) return {};
	ld d2 = dot(o1-o2, o1-o2);

	pdd u = (o1 + o2) * 0.5;
	pdd v = MP(o1.S - o2.S, -o1.F + o2.F) * (sqrtl((R*2+d) * d * (R*2-d) * d) / (2 * d2));
	ret.PB(u + v);
	ret.PB(u - v);

	return ret;
}

vector<pdd> cir_cir_tan(pdd p1, pdd p2)
{
	vector<pdd> ret;
	pdd d = p2 - p1;
	ld th = arg(d);
	ld da = abs(d);

	ret.PB(point_angle(p1, th + PI/2));
	ret.PB(point_angle(p1, th - PI/2));

	if(da > 2*R)
	{
		ld phi = acosl(2*R/da);
		ret.PB(point_angle(p1, th + phi));
		ret.PB(point_angle(p1, th - phi));
	}

	return ret;
}

vector<pdd> point_cir_tan(pdd p, pdd c)
{
	vector<pdd> ret;
	pdd d = p - c;
	ld th = arg(d);
	ld da = abs(d);
	ld phi = acosl(R/da);
	ret.PB(point_angle(c, th + phi));
	ret.PB(point_angle(c, th - phi));
	return ret;
}

bool seg_cir_int(pdd p, pdd q, pdd c)
{
	if(dis(p, c) < R-EPS || dis(q, c) < R-EPS) return true;

	pdd d = q - p;
	ld da = abs(d);
	if(da > EPS)
	{
		ld t = dot(c-p, d) / dot(d, d);
		if(0 < t && t < 1)
		{
			pdd s = p + d * t;
			if(dis(s, c) < R-EPS) return true;
		}
	}
	return false;
}

void make()
{
	newpt({0, 0});
	newpt(goal);

	for(int i=0; i<N; i++)
	{
		for(int j=0; j<N; j++)
		{
			if(i == j) continue;
			vector<pdd> vec = cir_cir_tan(pole[i], pole[j]);
			for(auto p: vec)
			{
				int x = newpt(p);
				cirpt[i].PB(x);
			}
		}

		vector<pdd> vec = point_cir_tan(pt[0], pole[i]);
		vector<pdd> v2 = point_cir_tan(pt[1], pole[i]);
		vec.insert(vec.end(), v2.begin(), v2.end());
		for(auto p: vec)
		{
			int x = newpt(p);
			cirpt[i].PB(x);
		}
	}

	for(int i=0; i<N; i++)
	{
		for(int j=i+1; j<N; j++)
		{
			vector<pdd> vec = cir_cir_int(pole[i], pole[j]);
			for(auto p: vec)
			{
				int x = newpt(p);
				cirpt[i].PB(x);
				cirpt[j].PB(x);
			}
		}
	}

	for(int i=0; i<P; i++)
		for(int j=0; j<P; j++)
			edge[i][j] = INF;
	for(int i=0; i<P; i++)
		pdis[i] = INF;

	for(int i=0; i<N; i++)
	{
		int sz = cirpt[i].size();
		for(auto v: cirpt[i])
		{
			theta[v] = arg(pt[v] - pole[i]);
		}
		sort(cirpt[i].begin(), cirpt[i].end(), [](int a, int b){return theta[a] < theta[b];});

		for(int j=0; j<sz; j++)
		{
			int v1 = cirpt[i][j];
			ld th1 = theta[v1];
			int k = (j+1)%sz;
			int v2 = cirpt[i][k];
			ld th2 = theta[v2];
			if(k == 0)
			{
				th2 += 2 * PI;
			}

			ld thmid = (th1 + th2) / 2;
			pdd pmid = point_angle(pole[i], thmid);

			bool ok = true;
			for(int x=0; x<N; x++)
			{
				ld d = dis(pmid, pole[x]);
				if(d < R - EPS)
					ok = false;
			}

			if(ok)
			{
				ld len = (th2 - th1) * R;
				edge[v1][v2] = min(edge[v1][v2], len);
				edge[v2][v1] = min(edge[v2][v1], len);
			}
		}
	}

	for(int i=0; i<P; i++)
	{
		for(int j=0; j<P; j++)
		{
			if(i == j) continue;
			pdd pi = pt[i], pj = pt[j];
			bool ok = true;
			for(int x=0; x<N; x++)
			{
				if(seg_cir_int(pi, pj, pole[x]))
					ok = false;
			}

			if(ok)
			{
				ld len = dis(pi, pj);
				edge[i][j] = min(edge[i][j], len);
				edge[j][i] = min(edge[j][i], len);
			}
		}
	}

	//for(int i=0; i<P; i++) {for(int j=0; j<P; j++) cout<<edge[i][j]<<" ";cout<<endl;}
}

ld calc()
{
	queue<int> Q;
	pdis[0] = 0;
	Q.push(0);

	while(!Q.empty())
	{
		int v = Q.front();
		Q.pop();

		ld d = pdis[v];
		for(int i=0; i<P; i++)
		{
			ld newdis = d + edge[v][i];
			if(newdis < pdis[i])
			{
				pdis[i] = newdis;
				Q.push(i);
			}
		}
	}

	/*
	for(int i=0; i<P; i++)
		cout<<i<<" : "<<pt[i].F<<","<<pt[i].S<<endl;

	for(int i=0; i<P; i++) cout<<pdis[i]<<" ";cout<<endl;
	*/

	return pdis[1];
}

int main() {
	IOS;
	cin>>N>>goal.F>>goal.S;
	for(int i=0; i<N; i++)
		cin>>pole[i].F>>pole[i].S;

	make();
	ld res = calc();

	if(res == INF)
		cout<<"0.0"<<endl;
	else
		cout<<fixed<<setprecision(10)<<res<<endl;

    return 0;
}

