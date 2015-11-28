// {{{ StoerWagner
const int inf=1000000000;
// should be larger than max.possible mincut
class StoerWagner {
	public:
		int n,mc; // node id in [0,n-1]
		vector<int> adj[MAXN];
		int cost[MAXN][MAXN];
		int cs[MAXN];
		bool merged[MAXN],sel[MAXN];
		// --8<-- include only if cut is explicitly needed
			DisjointSet djs;
		vector<int> cut;
		//--8<--------------------------------------------
			StoerWagner(int _n):n(_n),mc(inf),djs(_n) {
				for(int i=0;i<n;i++)
					merged[i]=0;
				for(int i=0;i<n;i++)
					for(int j=0;j<n;j++)
						cost[i][j]=cost[j][i]=0;
			}
		void append(int v,int u,int c) {
			if(v==u) return;
			if(!cost[v][u]&&c) {
				adj[v].PB(u);
				adj[u].PB(v);
			}
			cost[v][u]+=c;
			cost[u][v]+=c;
		}
		void merge(int v,int u) {
			merged[u]=1;
			for(int i=0;i<n;i++)
				append(v,i,cost[u][i]);
			// --8<-- include only if cut is explicitly needed
				djs.merge(v,u);
			//--8<--------------------------------------------
		}
		void phase() {
			priority_queue<pii> pq;
			for(int v=0;v<n;v++) {
				if(merged[v]) continue;
				cs[v]=0;
				sel[v]=0;
				pq.push({0,v});
			}
			int v,s,pv;
			while(pq.size()) {
				if(cs[pq.top().S]>pq.top().F) {
					pq.pop();
					continue;
				}
				pv=v;
				v=pq.top().S;
				s=pq.top().F;
				pq.pop();
				sel[v]=1;
				for(int i=0;i<adj[v].size();i++) {
					int u=adj[v][i];
					if(merged[u]||sel[u]) continue;
					cs[u]+=cost[v][u];
					pq.push({cs[u],u});
				}
			}
			if(s<mc) {
				mc=s;
				// --8<-- include only if cut is explicitly
				needed ------
					cut.clear();
				for(int i=0;i<n;i++)
					if(djs.getrep(i)==djs.getrep(v)) cut.PB(i);
				//--8<----------------------------------------
			}
			merge(v,pv);
		}
		int mincut() {
			if(mc==inf) {
				for(int t=0;t<n-1;t++)
					phase();
			
			return mc;
		}
		// --8<-- include only if cut is explicitly needed
		------
			vector<int> getcut() { // return one side of the cut
				mincut();
				return cut;
			}
		//--8<--------------------------------------------
};
// }}}
