// par : fail link
// val : a topological order ( useful for DP )
// go[x] : automata edge ( x is integer in [0,26) )

struct SAM{
	struct State{
		int par, go[26], val;
		State () : par(0), val(0){ FZ(go); }
		State (int _val) : par(0), val(_val){	FZ(go);	}
	};
	vector<State> vec;
	int root, tail;
	
	void init(int arr[], int len){
		vec.resize(2);
		vec[0] = vec[1] = State(0);
		root = tail = 1;
		for (int i=0; i<len; i++)
			extend(arr[i]);
	}
	void extend(int w){
		int p = tail, np = vec.size();
		vec.PB(State(vec[p].val+1));
		for ( ; p && vec[p].go[w]==0; p=vec[p].par)
			vec[p].go[w] = np;
		if (p == 0){
			vec[np].par = root;
		} else {
			if (vec[vec[p].go[w]].val == vec[p].val+1){
				vec[np].par = vec[p].go[w];
			} else {
				int q = vec[p].go[w], r = vec.size();
				vec.PB(vec[q]);
				vec[r].val = vec[p].val+1;
				vec[q].par = vec[np].par = r;
				for ( ; p && vec[p].go[w] == q; p=vec[p].par)
					vec[p].go[w] = r;
			}
		}
		tail = np;
	}
};

