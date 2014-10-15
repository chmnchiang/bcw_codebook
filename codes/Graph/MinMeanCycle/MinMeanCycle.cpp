/* minimum mean cycle */
class Edge { public:
	int v,u;
	double c;
};
int n,m;
Edge e[MAXEDGE];
double d[MAXNUM][MAXNUM];
inline void relax(double &x,double val) { if(val<x) x=val; }
inline void bellman_ford() {
	int i,j;
	for(j=0;j<n;j++) d[0][j]=0.0;
	for(i=0;i<n;i++) {
		for(j=0;j<n;j++) d[i+1][j]=inf;
		for(j=0;j<m;j++)
			if(d[i][e[j].v]<inf-eps) relax(d[i+1][e[j].u],d[i][
					e[j].v]+e[j].c);
	}
}
inline double karp_mmc() {
	// returns inf if no cycle, mmc otherwise
	int i,k; double mmc=inf,avg;
	bellman_ford();
	for(i=0;i<n;i++) {
		avg=0.0;
		for(k=0;k<n;k++) {
			if(d[n][i]<inf-eps) avg=max(avg,(d[n][i]-d[k][i])/(
						n-k));
			else avg=max(avg,inf);
		}
		mmc=min(mmc,avg);
	}
	return mmc;
}
