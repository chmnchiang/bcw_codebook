class SAM{ //SuffixAutomaton
public:
	class State{
	public:
		State *par, *go[26];
		int val;
		State (int _val) : 
				par(0), val(_val){
			MSET(go,0);
		}
	};
	State *root, *tail;
	
	void init(const string &str){
		root = tail = new State(0);
		for (int i=0; i<SZ(str); i++)
			extend(str[i]-'a');
	}
	void extend(int w){
		State *p = tail, *np = new State(p->val+1);
		for ( ; p && p->go[w]==0; p=p->par)
			p->go[w] = np;
		if (p == 0){
			np->par = root;
		} else {
			if (p->go[w]->val == p->val+1){
				np->par = p->go[w];
			} else {
				State *q = p->go[w], *r = new State(0);
				*r = *q;
				r->val = p->val+1;
				q->par = np->par = r;
				for ( ; p && p->go[w]==q; p=p->par)
					p->go[w] = r;
			}
		}
		tail = np;
	}
};
