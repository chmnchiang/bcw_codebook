/* convex hull Minkowski Sum*/
#define INF 100000000000000LL
class PT{ public:
	long long x,y;
	int POS(){
		if(y==0) return x>0?0:1;
		return y>0?0:1;
	}
};
PT pt[300000],qt[300000],rt[300000];
long long Lx,Rx;
int dn,un;
inline bool cmp(PT a,PT b){
	int pa=a.POS(),pb=b.POS();
	if(pa==pb) return (a^b)>0;
	return pa<pb;
}
int minkowskiSum(int n,int m){
	int i,j,r,p,q,fi,fj;
	for(i=1,p=0;i<n;i++){
		if(pt[i].y<pt[p].y || (pt[i].y==pt[p].y && pt[i].x<
					pt[p].x)) p=i; }
	for(i=1,q=0;i<m;i++){
		if(qt[i].y<qt[q].y || (qt[i].y==qt[q].y && qt[i].x<
					qt[q].x)) q=i; }
	rt[0]=pt[p]+qt[q];
	r=1; i=p; j=q; fi=fj=0;
	while(1){
		if((fj&&j==q) || ((!fi||i!=p) && cmp(pt[(p+1)%n]-pt[
						p],qt[(q+1)%m]-qt[q]))){
			rt[r]=rt[r-1]+pt[(p+1)%n]-pt[p];
			p=(p+1)%n;
			fi=1;
		}else{
			rt[r]=rt[r-1]+qt[(q+1)%m]-qt[q];
			q=(q+1)%m;
			fj=1;
		}
		if(r<=1 || ((rt[r]-rt[r-1])^(rt[r-1]-rt[r-2]))!=0) r
			++;
		else rt[r-1]=rt[r];
		if(i==p && j==q) break;
	}
	return r-1;
}
void initInConvex(int n){
	int i,p,q;
	long long Ly,Ry;
	Lx=INF; Rx=-INF;
	for(i=0;i<n;i++){
		if(pt[i].x<Lx) Lx=pt[i].x;
		if(pt[i].x>Rx) Rx=pt[i].x;
	}
	Ly=Ry=INF;
	for(i=0;i<n;i++){
		if(pt[i].x==Lx && pt[i].y<Ly){ Ly=pt[i].y; p=i; }
		if(pt[i].x==Rx && pt[i].y<Ry){ Ry=pt[i].y; q=i; }
	}
	for(dn=0,i=p;i!=q;i=(i+1)%n){ qt[dn++]=pt[i]; }
	qt[dn]=pt[q]; Ly=Ry=-INF;
	for(i=0;i<n;i++){
		if(pt[i].x==Lx && pt[i].y>Ly){ Ly=pt[i].y; p=i; }
		if(pt[i].x==Rx && pt[i].y>Ry){ Ry=pt[i].y; q=i; }
	}
	for(un=0,i=p;i!=q;i=(i+n-1)%n){ rt[un++]=pt[i]; }
	rt[un]=pt[q];
}
inline int inConvex(PT p){
	int L,R,M;
	if(p.x<Lx || p.x>Rx) return 0;
	L=0;R=dn;
	while(L<R-1){ M=(L+R)/2;
		if(p.x<qt[M].x) R=M; else L=M; }
		if(tri(qt[L],qt[R],p)<0) return 0;
		L=0;R=un;
		while(L<R-1){ M=(L+R)/2;
			if(p.x<rt[M].x) R=M; else L=M; }
			if(tri(rt[L],rt[R],p)>0) return 0;
			return 1;
}
int main(){
	int n,m,i;
	PT p;
	scanf("%d",&n);
	for(i=0;i<n;i++) scanf("%I64d %I64d",&pt[i].x,&pt[i].y);
	scanf("%d",&m);
	for(i=0;i<m;i++) scanf("%I64d %I64d",&qt[i].x,&qt[i].y);
	n=minkowskiSum(n,m);
	for(i=0;i<n;i++) pt[i]=rt[i];
	scanf("%d",&m);
	for(i=0;i<m;i++) scanf("%I64d %I64d",&qt[i].x,&qt[i].y);
	n=minkowskiSum(n,m);
	for(i=0;i<n;i++) pt[i]=rt[i];
	initInConvex(n);
	scanf("%d",&m);
	for(i=0;i<m;i++){
		scanf("%I64d %I64d",&p.x,&p.y);
		p.x*=3; p.y*=3;
		puts(inConvex(p)?"YES":"NO");
	}
}
