void Z_value(char *s, int *z, int len) {
	int i,j,left,right;
	left=right=0; z[0]=len;
	for(i=1;i<len;i++) {
		j=max(min(z[i-left],right-i),0);
		for(;i+j<len&&s[i+j]==s[j];j++);
		z[i]=j;
		if(i+z[i]>right) {
			right=i+z[i];
			left=i;
		}
	}
}
