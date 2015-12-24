#include<bits/stdc++.h>
using namespace std;
#define REP(n,i) for(int (i)=0;(i)<(n);(i)++)
#define CDREP(n,i) for(int (i)=((n)−1);(i)>=0;(i)−−)
#define CDFOR(s,e,i) for(int i=((e)−1);(i)>=(s);(i)−−)
#define _SZ(n) memset((n),0,sizeof(n))
#define _SMO(n) memset((n),−1,sizeof(n))
#define _MC(n,m) memcpy((n),(m),sizeof(n))
#define _F first
#define _S second
#define _MP(a,b) make_pair((a),(b))
#define _PB(a) push_back((a))
#define FOR(x,y) for(__typeof(y.begin())x=y.begin();x!=y.end();x++)
#define IOS ios_base::sync_with_stdio(0);
#ifdef ONLINE_JUDGE
#define FILEIO(name) \
    freopen(name".in", "r", stdin); \
    freopen(name".out", "w", stdout);
#else
#define FILEIO(name)
#endif
//Let's Fight!
//

const double EPS = 1e-8;
const double PI = acos(-1);

struct point_t{
	double x,y;
	point_t operator - (const point_t& arg) const {
		point_t rt;
		rt.x = x - arg.x;
		rt.y = y - arg.y;
		return rt;
	}
}ip[150],ans;

int N;

bool ptcmp(point_t p1, point_t p2){

	double a1 = atan2(p1.y, p1.x);
	double a2 = atan2(p2.y, p2.x);
	a1 += PI;
	a2 += PI;

	if( a1 > PI - EPS ) a1 -= PI ;
	if( a2 > PI - EPS ) a2 -= PI ;

	return a1 < a2;
}

double atan3(double y, double x){
	double t = atan2(y, x);
	t += PI;
	if( t > PI - EPS ) t -= PI;
	return t;
}

bool check(int i1, int i2, int i3, int i4){

	point_t  p1 = ip[i1],p2 = ip[i2],p3 = ip[i3],p4 = ip[i4];
	
	double del = ( - (p2.y - p1.y) * (p4.x - p3.x) +
					(p2.x - p1.x) * (p4.y - p3.y) ) ;
	if(fabs(del) < EPS) return false;

	double n1 = p1.x * (p2.y - p1.y) - p1.y * (p2.x - p1.x);
	double n2 = p3.x * (p4.y - p3.y) - p3.y * (p4.x - p3.x);

	double px = - ( n1 * (p4.x - p3.x) ) + (n2 * (p2.x - p1.x) );
	double py = - ( n1 * (p4.y - p3.y) ) + (n2 * (p2.y - p1.y) );

	vector<pair<double, int> > temp;

	point_t cent = point_t{px/del, py/del};

	for(int i=0; i<N; i++){
		point_t qq = ip[i] - cent;
		temp.push_back( make_pair( atan3(qq.y, qq.x) , i));
		if( fabs( ip[i].x - cent.x) < EPS && 
				fabs( ip[i].y - cent.y) < EPS ) return false;
	}	

	sort(temp.begin(), temp.end());

	for(int i=0; i<(int)temp.size(); i+=2){
		
		double a1 = temp[i]._F;
		double a2 = temp[i+1]._F;
		if( fabs(a1 - a2) > EPS ) {
			return false;
		}
			
		if( i ){ 
			double a3 = temp[i-1]._F;
			if( fabs(a3 - a2) < EPS ) return false;
		}
	}


	ans =point_t{px / del, py / del};
	return true;

}
int main(){
	FILEIO("center");
	scanf("%d", &N);
	N *= 2;
	for (int i=0; i<N; i++){
		scanf("%lf %lf", &ip[i].x, &ip[i].y);
	}
	int p1=0;
	int p2=-1;
	int cc=0;

	for (int i=1; i<N; i++){
		if (i == 1)
			p2 = 2;
		else
			p2 = 1;
		for (int j=1; j<N; j++){
			if (j == p1 || j == p2 || j == i)
				continue;
			if (check(p1,i,p2,j)){
				cc++;
			}
		}
	}
	if (cc == 0){
		puts("Impossible");
	} else if (cc == 1){
		printf("Center of the universe found at (%.9f, %.9f)\n", ans.x, ans.y);
	} else {
		puts("Ambiguity");
	}

	return 0;
}

