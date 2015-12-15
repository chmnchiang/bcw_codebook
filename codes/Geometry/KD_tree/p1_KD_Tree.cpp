const INF = 1100000000;

class NODE{ public:
	int x,y,x1,x2,y1,y2;
	int i,f;
	NODE *L,*R;
};
inline long long dis(NODE& a,NODE& b){
	long long dx=a.x-b.x;
	long long dy=a.y-b.y;
	return dx*dx+dy*dy;
}
NODE node[100000];
bool cmpx(const NODE& a,const NODE& b){ return a.x<b.x; }
bool cmpy(const NODE& a,const NODE& b){ return a.y<b.y; }
NODE* KDTree(int L,int R,int dep){
	if(L>R) return 0;
	int M=(L+R)/2;
	if(dep%2==0){
		nth_element(node+L,node+M,node+R+1,cmpx);
		node[M].f=0;
	}else{
		nth_element(node+L,node+M,node+R+1,cmpy);
		node[M].f=1;
	}
	node[M].x1=node[M].x2=node[M].x;
	node[M].y1=node[M].y2=node[M].y;
	node[M].L=KDTree(L,M-1,dep+1);
	if(node[M].L){
		node[M].x1=min(node[M].x1,node[M].L->x1);
		node[M].x2=max(node[M].x2,node[M].L->x2);
		node[M].y1=min(node[M].y1,node[M].L->y1);
		node[M].y2=max(node[M].y2,node[M].L->y2);
	}
	node[M].R=KDTree(M+1,R,dep+1);
	if(node[M].R){
		node[M].x1=min(node[M].x1,node[M].R->x1);
		node[M].x2=max(node[M].x2,node[M].R->x2);
		node[M].y1=min(node[M].y1,node[M].R->y1);
		node[M].y2=max(node[M].y2,node[M].R->y2);
	}
	return node+M;
}
inline int touch(NODE* r,int x,int y,long long d){
	long long d2;
	d2 = (long long)(sqrt(d)+1);
	if(x<r->x1-d2 || x>r->x2+d2 || y<r->y1-d2 || y>r->y2+d2)
		return 0;
	return 1;
}
void nearest(NODE* r,int z,long long &md){
	if(!r || !touch(r,node[z].x,node[z].y,md)) return;
	long long d;
	if(node[z].i!=r->i){
		d=dis(*r,node[z]);
		if(d<md) md=d;
	}
	if(r->f==0){
		if(node[z].x<r->x){
			nearest(r->L,z,md);
			nearest(r->R,z,md);
		}else{
			nearest(r->R,z,md);
			nearest(r->L,z,md);
		}
	}else{
		if(node[z].y<r->y){
			nearest(r->L,z,md);
			nearest(r->R,z,md);
		}else{
			nearest(r->R,z,md);
			nearest(r->L,z,md);
		}
	}
}
int main(){
	int TT,n,i;
	long long d;
	NODE* root;
	scanf("%d",&TT);
	while(TT--){
		scanf("%d",&n);
		for(i=0;i<n;i++){
			scanf("%d %d",&node[i].x,&node[i].y);
			node[i].i=i;
		}
		root=KDTree(0,n-1,0);
		for(i=0;i<n;i++){
			d=9000000000000000000LL;
			nearest(root,i,d);
			ans[node[i].i]=d;
		}
	}
}
