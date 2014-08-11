#include<bits/stdc++.h>

using namespace std;

const int MAXV = 1000;

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

int main(){

	cin >> V >> E;
	for(int i=0; i<E; i++){
		int u, v;
		cin >> u >> v;
		el[u].push_back(v);
	}


	calcscc();

	cout << "vertex" << '\t' << "dfn" << '\t' << "low" << '\t' << "sccid" << endl;
	for(int i=0; i<V; i++){
		cout << i << ":\t" << dfn[i] << '\t' << low[i] << '\t' << scc[i] << endl;
	}

	return 0;
}

