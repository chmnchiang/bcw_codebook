const int MAXV = 101000;

int V, E;
vector<int> el[MAXV];
int dfn[MAXV], low[MAXV], did;
bool ins[MAXV];
stack<int> st;
int scc[MAXV], scn;

void tarjan(int u){
	cout << u << endl;
	dfn[u] = low[u] = ++did;
	st.push(u); ins[u] = true;

	for(int i=0; i<(int)el[u].size(); i++){
		int v = el[u][i];
		if(!dfn[v]){
			tarjan(v);
			low[u] = min(low[u], low[v]);
		}else if(ins[v]){
			low[u] = min(low[u], dfn[v]);
		}
	}

	if(dfn[u] == low[u]){
		int v;
		do{
			v = st.top();
			st.pop();
			scc[v] = scn;	
			ins[v] = false;
		}while(v != u);
		scn ++;
	}
}

void calcscc(){
	did = scn = 0;
	for(int i=0; i<V; i++){
		if(!dfn[i]) tarjan(i);
	}
}
