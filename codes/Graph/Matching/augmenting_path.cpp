bool DFS(int u){
  FOR(it,E[u]){
    if (!vst[*it]){
      vst[*it]=1;
      if (match[*it] == -1 || DFS(match[*it])){
        match[*it] = u;
        match[u] = *it;
        return true;
      }
    }
  }
  return false;
}
int DoMatch(int res=0){
  MSET(match,-1);
  for (int i=1; i<=m; i++){
    if (match[i] == -1){
      memset(vst,0,sizeof(vst));
      DFS(i);
    }
  }
  for (int i=1; i<=m; i++)
    if (match[i] != -1) res++;
  return res;
}
