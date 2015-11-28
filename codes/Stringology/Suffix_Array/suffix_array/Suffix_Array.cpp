const int MAX = 1020304;
int ct[MAX], he[MAX], rk[MAX], sa[MAX], tsa[MAX], tp[MAX][2];

void suffix_array(char *ip){

	int len = strlen(ip);
	int alp = 256;

	memset(ct, 0, sizeof(ct));
	for(int i=0;i<len;i++) ct[ip[i]+1]++;
	for(int i=1;i<alp;i++) ct[i]+=ct[i-1];
	for(int i=0;i<len;i++) rk[i]=ct[ip[i]];

	for(int i=1;i<len;i*=2){
		for(int j=0;j<len;j++){
			if(j+i>=len) tp[j][1]=0;
			else tp[j][1]=rk[j+i]+1;
			
			tp[j][0]=rk[j];
		}
		memset(ct, 0, sizeof(ct));
		for(int j=0;j<len;j++) ct[tp[j][1]+1]++;
		for(int j=1;j<len+2;j++) ct[j]+=ct[j-1];
		for(int j=0;j<len;j++) tsa[ct[tp[j][1]]++]=j;

		memset(ct, 0, sizeof(ct));
		for(int j=0;j<len;j++) ct[tp[j][0]+1]++;
		for(int j=1;j<len+1;j++) ct[j]+=ct[j-1];
		for(int j=0;j<len;j++) sa[ct[tp[tsa[j]][0]]++]=tsa[j];

		rk[sa[0]]=0;
		for(int j=1;j<len;j++){
			if( tp[sa[j]][0] == tp[sa[j-1]][0] &&
				tp[sa[j]][1] == tp[sa[j-1]][1] )
				rk[sa[j]] = rk[sa[j-1]];
			else
				rk[sa[j]] = j;
		}
	}

	for(int i=0,h=0;i<len;i++){
		if(rk[i]==0) h=0;
		else{
			int j=sa[rk[i]-1];
			h=max(0,h-1);
			for(;ip[i+h]==ip[j+h];h++);
		}
		he[rk[i]]=h;
	}
}
