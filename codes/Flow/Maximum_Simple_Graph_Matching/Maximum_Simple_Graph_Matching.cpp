const int MAX = 300;

int V, E;
int el[MAX][MAX];
int mtp[MAX];
int djs[MAX];
int bk[MAX], pr[MAX], vt[MAX];
queue<int> qu;

int ffa(int a){
	return (djs[a] == -1) ? a : djs[a] = ffa(djs[a]);
}

void djo(int a, int b){
	int fa = ffa(a), fb = ffa(b);
	if (fa != fb) djs[fb] = fa;
}

int lca(int u, int v){
	static int ts = 0;
	ts ++;
	while(1){
		if( u != -1 ){
			u = ffa(u);
			if(vt[u] == ts) return u;
			vt[u] = ts;
			if(pr[u] != -1) u = bk[pr[u]];
			else u = -1;
		}
		swap(u, v);
	}
	return u;
}

void flower(int u, int w){
	while(u != w){
		int v1 = pr[u], v2 = bk[v1];
		if(ffa(v2) != w) bk[v2] = v1;
		if(mtp[v1] == 1){
			qu.push(v1);
			mtp[v1] = 0;
		}
		if(mtp[v2] == 1){
			qu.push(v2);
			mtp[v2] = 0;
		}
		djo(v1, w);
		djo(v2, w);
		djo(u, w);
		u = v2;
	}
}
bool flow(int s){
	memset(mtp, -1, sizeof(mtp));
	while(qu.size()) qu.pop();
	qu.push(s);
	mtp[s] = 0; bk[s] = pr[s] = -1;

	while(qu.size() && pr[s] == -1){
		int u = qu.front(); qu.pop();
		for(int v=0; v<V; v++){
			
			if (el[u][v] == 0) continue;
			if (ffa(v) == ffa(u)) continue;

			if(pr[v] == -1){
				do{
					int t = pr[u];
					pr[v] = u; pr[u] = v;
					v = t; u = t==-1?-1:bk[t];
				}while( v != -1 );
				break;
			}else if(mtp[v] == 0){
				int w = lca(u, v);	
				if(ffa(w) != ffa(u)) bk[u] = v;
				if(ffa(w) != ffa(v)) bk[v] = u;
				flower(u, w);
				flower(v, w);
			}else if(mtp[v] != 1){
				bk[v] = u;
				mtp[v] = 1;
				mtp[pr[v]] = 0;
				qu.push(pr[v]);
			}
		}
	}
	return pr[s] != -1;
}


int match(){

	memset(pr, -1, sizeof(pr));
	int a = 0;
	for (int i=0; i<V; i++){
		if (pr[i] == -1){
			if(flow(i)) a++;
			else mtp[i] = i;
		}
	}
	return a;
}
