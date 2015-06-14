#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<map>
#include<set>
using namespace std;
vector<int>One,Dep[100005];
set<int>st[100005];
int vis[100005];
int fa[100005];
int i,j,m,n,p,k,fox[100005],color[100005],x,y,k1;
struct Node{int ed,before;}s[1000001];
void add(int x,int y){  s[++k1].ed=y; s[k1].before=fox[x]; fox[x]=k1; }
void dfs(int x,int dep)
{ 
      int i;    Dep[dep].push_back(x);
       for (i=fox[x];i;i=s[i].before)  if (fa[x]!=s[i].ed) fa[s[i].ed]=x,dfs(s[i].ed,dep+1);
}
void Count(int x)
{ 
       int i;
     for (i=fox[x];i;i=s[i].before)
      if (fa[x]!=s[i].ed)
      { int y=s[i].ed;
         if (One.size())     color[y]=One[One.size()-1], One.pop_back();
         else { 
                   int pos=1;
                   while (pos<=m)    if (vis[pos]||st[pos].count(color[x])) ++pos; else break;
                   vis[pos]=1; color[y]=pos;
              }
                   st[color[y]].insert(color[x]);
                   st[color[x]].insert(color[y]);
               }
}
int main()
{ 
     scanf("%d",&n);
     for (i=1;i<n;i++) scanf("%d%d",&x,&y),add(x,y),add(y,x);
     m=n/2+1; 
     for (i=2;i<=m;i++) One.push_back(i);
     for (i=1;i<=m;i++) st[i].insert(i);
     color[1]=1; dfs(1,0);
     for (i=0;i<=n;i++)
       for (j=0;j<Dep[i].size();j++) Count(Dep[i][j]);
     for (i=1;i<=n;i++) printf("%d ",color[i]);
}
