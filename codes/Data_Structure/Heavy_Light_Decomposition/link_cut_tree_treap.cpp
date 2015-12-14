const int MXN = 100005;
const int MEM = 100005;
struct Treap {
  static Treap nil, mem[MEM], *pmem;
  Treap *l, *r, *p, *lctp;
  int val;
  int rev, size;
  Treap () :
    l(&nil), r(&nil), p(&nil), lctp(&nil), val(-1), rev(0), size(0) {}
  Treap (int _val) :
    l(&nil), r(&nil), p(&nil), lctp(&nil), val(_val), rev(0), size(1) {}
} Treap::nil,Treap::mem[MEM],*Treap::pmem=Treap::mem;

int size(const Treap *t) { return t->size; }
void push(Treap *t) {
  if (!size(t)) return;
  if (t->rev) {
    swap(t->l, t->r);
    if (size(t->l)) t->l->rev^=1;
    if (size(t->r)) t->r->rev^=1;
  }
  t->rev=0;
}
void pull(Treap *t) {
  if (!size(t)) return;
  t->size = size(t->l)+size(t->r)+1;
  if (size(t->l)) t->l->p=t;
  if (size(t->r)) t->r->p=t;
}
Treap* merge(Treap *a, Treap *b) {
  if (!size(a)) return b;
  if (!size(b)) return a;
  push(a); push(b);
  if (rand() % (size(a) + size(b)) < size(a)) {
    a->r = merge(a->r, b);
    pull(a);
    return a;
  } else {
    b->l = merge(a, b->l);
    pull(b);
    return b;
  }
}
void split(Treap *t, int k, Treap *&a, Treap *&b) {
  push(t);
  if (!size(t)) a=b=&Treap::nil;
  else if (size(t->l) + 1 <= k) {
    a=t;
    split(t->r, k - size(t->l) - 1, a->r, b);
    pull(a);
  } else {
    b=t;
    split(t->l, k, a, b->l);
    pull(b);
  }
}
Treap* getRoot(Treap *t) {
  while (size(t->p)) t=t->p;
  return t;
}
Treap* head(Treap *t) {
  push( t=getRoot(t) );
  while (size(t->l)) push( t=t->l );
  return t;
}
Treap* tail(Treap *t) {
  push( t=getRoot(t) );
  while (size(t->r)) push( t=t->r );
  return t;
}
int get_rank(Treap *t) {
  vector<Treap*> path;
  for (; size(t); t=t->p) path.push_back(t);
  reverse(begin(path), end(path));
  for (auto it:path) push(it);
  int k=0;
  t=path.back();
  Treap *last=t->r;
  while (size(t)) {
    if (last == t->r) k+=size(t->l)+1;
    last=t; t=t->p;
  }
  return k;
}
void lct_split(Treap *t, Treap *&a, Treap *&b, int flg) {
  // if flg==1, Treap a should include node t;
  int k=get_rank(t);
  if (!flg) k--;
  split(getRoot(t), k, a, b);
  a->p=b->p=&Treap::nil;
  if (size(b)) head(b)->lctp=tail(a);
}
Treap* expose(Treap *t) {
  Treap *tr;
  vector<Treap*> vec;
  while (size(t)) {
    lct_split(t, t, tr, 1);
    vec.push_back(t);
    t=head(t)->lctp;
  }
  for (auto v:vec) t=merge(v, t);
  t->p=head(t)->lctp=&Treap::nil;
  return t;
}
Treap* evert(Treap *t) {
  t=expose(t);
  t->rev^=1;
  t->p=head(t)->lctp=&Treap::nil;
  return t;
}
void cut(Treap *x, Treap *y) {
  //  cut node y when root is x.
  x=evert(x);
  if (head(y) != y) lct_split(y, x, y, 0);
  head(y)->lctp=&Treap::nil;
}
void link(Treap *x, Treap *y) {
//  head(y)->lctp = x;
//  return;
  y=evert(y);
  y=expose(y);
  head(y)->lctp=x;
}

int N, Q, jmp[MXN];
Treap *vt[MXN];
int flg;

int getNxt(int v) {
  v+=jmp[v];
  if (v>N) v=0;
  return v;
}
int main(int argc, char** argv) {
  vt[0] = new (Treap::pmem++) Treap(0);
  scanf("%d%d", &N, &Q);
  for (int i=1; i<=N; i++) {
    RI(jmp[i]);
    vt[i] = new (Treap::pmem++) Treap(i);
  }
  for (int i=N; i>=1; i--) link(vt[getNxt(i)],vt[i]);
  int cmd, a, b;
  while (Q--) {
    scanf("%d", &cmd);
    if (cmd == 0) {
      scanf("%d%d", &a, &b);
      cut(vt[0], vt[a]);
      jmp[a]=b;
      link(vt[getNxt(a)], vt[a]);
    } else {
      scanf("%d", &a);
      evert(vt[0]);
      Treap *rt=expose(vt[a]);
      int v=head(rt)->p->val, sz = size(rt)-1;
      rt=head(rt);
      if (size(rt->r)) {
        rt=rt->r;
        while (size(rt->l)) rt=rt->l;
        v=rt->val;
      }
      printf("%d %d\n", v, sz);
    }
  }
  return 0;
}
