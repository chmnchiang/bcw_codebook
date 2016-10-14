struct palindromic_tree{
  struct node{
    int next[26],fail,len;
    int cnt,num,st,ed;
    node(int l=0):fail(0),len(l),cnt(0),num(0){
      for(int i=0;i<26;++i)next[i]=0;
    }
  };
  vector<node >state;
  vector<char >s;
  int last,n;
  palindromic_tree():state(2),last(1),n(0){
    state[0].fail=1;
    state[1].len=-1;
    s.push_back(-1);
  }
  inline void clear(){
    state.clear();
    s.clear();
    last=1;
    n=0;
    state.push_back(0);
    state.push_back(-1);
    state[0].fail=1;
    s.push_back(-1);
  }
  inline int get_fail(int x){
    while(s[n-state[x].len-1]!=s[n])x=state[x].fail;
    return x;
  }
  inline void add(int c){
    s.push_back(c-='a');
    ++n;
    int cur=get_fail(last);
    if(!state[cur].next[c]){
      int now=state.size();
      state.push_back(state[cur].len+2);
      state[now].fail=state[get_fail(state[cur].fail)].next[c];
      state[cur].next[c]=now;
      state[now].num=state[state[now].fail].num+1;
    }
    last=state[cur].next[c];
    ++state[last].cnt;
  }
  inline void count(){
    vector<node>::reverse_iterator i=state.rbegin();
    for(;i!=state.rend();++i){
      state[i->fail].cnt+=i->cnt;
    }
  }
  inline int size(){
    return state.size()-2;
  }
};
