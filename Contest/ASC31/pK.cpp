/* bcw0x1bd2 */
#include <bits/stdc++.h>
//
using namespace std;
//
#define REP(n,i) for(int (i)=0;(i)<(n);(i)++)
#define CDREP(n,i) for(int (i)=((n)-1);(i)>=0;(i)--)
#define CDFOR(s,e,i) for(int i=((e)-1);(i)>=(s);(i)--)
#define _SZ(n) memset((n),0,sizeof(n))
#define _SMO(n) memset((n),-1,sizeof(n))
#define _MC(n,m) memcpy((n),(m),sizeof(n))
#define _F first
#define _S second
#define _MP make_pair
#define _PB push_back
#define FOR(x,y) for(__typeof(y.begin())x=y.begin();x!=y.end();x++)
#define IOS ios_base::sync_with_stdio(0);
// Let's Fight!

int pri[256];
int N;
char str[5514],str2[5514];
int match[5514];
int top,stk[5514];
int opSum[5514], numSum[5514];
char ans[1000][4000];
vector<string> vec;

int find_space(int id){
	if (id == 0)
		return 0;
	id--;
//	printf("count %d %d\n", opSum[id],numSum[id]);
	return opSum[id]*5+numSum[id];
}
void f(int l, int r, int lv){
	if (l > r)
		return ;
	while (str[l] == '(' && match[l] == r){
		l++;
		r--;
	}
//	printf("%d %d %d\n", l, r, lv);
	if (l == r){
		int id = find_space(l);
//		printf("%d\n", id);
		if (lv)
			ans[lv-1][id] = '|';
		ans[lv][id] = str[l];
		return ;
	}
	
	int pos=-1;
	char op='+';
	for (int i=l; i<=r; i++){
		if (str[i] == '('){
			i = match[i];
			continue;
		} else if (pri[str[i]]){
			if (pri[str[i]] >= pri[op]){
				op = str[i];
				pos = i;
			}
		}
	}
	f(pos+1,r,lv+2);
	int at = find_space(pos)+2;
//	printf("%d\n", at);
	ans[lv][at] = str[pos];
	if (lv){
		ans[lv-1][at] = '|';
	}
	ans[lv][at+1] = ']';
	ans[lv][at-1] = '[';
	f(l,pos-1,lv+2);
}
int main(int argc, char** argv)
{
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
	_SZ(pri);
	pri['+'] = pri['-'] = 1;
	pri['*'] = pri['/'] = 2;
	pri['^'] = 3;
	gets(str);
	_SMO(match);
	_SZ(opSum);
	_SZ(numSum);
	top = 0;
	N = strlen(str);
	vec.clear();
	for (int i=0; i<N; i++){
		if (str[i] == '('){
			stk[top++] = '(';
		} else if (str[i] == ')'){
			while (top>0 && stk[top-1] != '('){
				string ch = "";
				ch += (char)stk[top-1];
				vec._PB(ch);
				top--;
			}
			top--;
		} else if (pri[str[i]]){
			while (top>0 && stk[top-1] != '(' && 
				   pri[stk[top-1]]>=pri[str[i]] && str[i] != '^'){
				string ch = "";
				ch += (char)stk[top-1];
				vec._PB(ch);
				top--;
			}
			stk[top++] = str[i];
		} else if ('a' <= str[i] && str[i] <= 'z'){
			string ch="";
			ch += (char)str[i];
			vec._PB(ch);
		}
	}
	while (top>0){
		string ch = "";
		ch += (char)stk[top-1];
		vec._PB(ch);
		top--;
	}
	top=0;
	string strStk[1024];
	for (int i=0; i<(int)vec.size(); i++){
		if (pri[vec[i][0]]){
			strStk[top-2] = "("+strStk[top-2]+vec[i][0]+strStk[top-1]+")";
			top--;
		} else {
			strStk[top++] = vec[i];
		}
//		cout << vec[i];
	}
//	cout << endl;
//	cout << strStk[0] << endl;
	strcpy(str,strStk[0].c_str());
	N = strlen(str);
//	printf("%s\n%d\n", str, N);
	top = 0;
	for (int i=0; i<N; i++){
		if (i != 0){
			opSum[i] = opSum[i-1];
			numSum[i] = numSum[i-1];
		}
		if (str[i] == '('){
			stk[top++] = i;
		} else if (str[i] == ')'){
			top--;
			match[stk[top]] = i;
			match[i] = stk[top];
		} else if ('a' <= str[i] && str[i] <= 'z'){
			numSum[i]++;
		} else if (pri[(int)str[i]]){
			opSum[i]++;
		}
	}
	_SZ(ans);
	f(0,N-1,0);
	for (int i=0; i<1000; i++){
		int ed=-1;
		for (int j=4000-1; j>=0; j--){
			if (ans[i][j]){
				ed = j;
				break;
			}
		}
		if (ed == -1)
			break;
		int ed2=ed;
		for (int k=ed; k>=0; k--){
			if (ans[i][k] == ']'){
				for (int j=k+1; j<4000; j++){
					ans[i][j] = '-';
					if (ans[i+1][j] != 0){
						ans[i][j] = '.';
						ed2 = max(ed2,j);
						break;
					}
				}

				for (int j=k-3; j>=0; j--){
					ans[i][j] = '-';
					if (ans[i+1][j] != 0){
						ans[i][j] = '.';
						break;
					}
				}

			}
		}
		for (int j=0; j<=ed2; j++){
			if (ans[i][j]){
				putchar(ans[i][j]);
			} else {
				putchar(' ');
			}
		}
		putchar('\n');
	}

	return 0;
}
