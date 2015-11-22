bool DFS(int u){
  for (auto v : E[u]){
    if (!vst[v]){
      vst[v]=1;
      if (match[v] == -1 || DFS(match[v])){
        match[v] = u; match[u] = v;
        return true;
      }
    }
  }
  return false;
}
int DoMatch(int res=0){
	memset(match,-1,sizeof(match));
  for (int i=1; i<=N; i++){
    if (match[i] == -1){
      memset(vst,0,sizeof(vst));
      DFS(i);
    }
  }
  for (int i=1; i<=N; i++)
    if (match[i] != -1) res++;
  return res;
}
