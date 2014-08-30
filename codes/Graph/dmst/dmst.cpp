struct Edge{
	int u,v,c;
}eg[N*N];
int n, m, nSpe, nE, bln[N], vst[N], dis[N], ismrg[N], prev[N];

int dmst(int root){
	_SZ(ismrg);
	int curW, ww;
	curW=ww=0;
	while (1){
		_SMO(prev);
		for (int i=0; i<nSpe; i++)
			dis[i] = INF;
		for (int i=0; i<nE; i++){
			if (eg[i].v!=eg[i].u && eg[i].v!=root && dis[eg[i].v] > eg[i].c){
				dis[eg[i].v] = eg[i].c;
				prev[eg[i].v] = eg[i].u;
			}
		}

		// find cycle
		int sign=1;
		curW=0;
		_SMO(bln);
		_SMO(vst);
		for (int i=0; i<nSpe; i++){
			if (ismrg[i]) continue;
			if (prev[i]==-1 && i!=root) return INF;
			if (i!=root) curW += dis[i];
			int s;
			for (s=i; s!=-1 && vst[s]==-1; s=prev[s])
				vst[s]=i;

			if (s!=-1 && vst[s]==i){
				sign=0;
				int j=s;
				while (1){
					ismrg[j]=1;
					bln[j]=s;
					ww += dis[j];
					j=prev[j];
					if (j==s) break;
				}
				ismrg[s]=0;
			}
		}

		if (sign) break;

		// merge
		for (int i=0; i<nE; i++){
			if (bln[eg[i].v]!=-1) eg[i].c -= dis[eg[i].v];
			if (bln[eg[i].u]!=-1) eg[i].u = bln[eg[i].u];
			if (bln[eg[i].v]!=-1) eg[i].v = bln[eg[i].v];
			if (eg[i].u==eg[i].v) eg[i--] = eg[--nE];
		}
		//	system("pause");
	}
	return curW+ww;
}

