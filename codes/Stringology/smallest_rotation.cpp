string solve(string str){
	int N = str.length();
	str += str;
	int i=0, j=1, k=0;
	while (j<N && k<N){
		if (str[i+k] == str[j+k]) k++;
		else {
			if (k == 0 && str[i] > str[j]){
				i++; j++;
			} else if (str[i+k] < str[j+k]){
				j += k+1;
			} else {
				i += k+1;
				j = i + 1;
			}
			k=0;
		}
	}
	string ret = "";
	for (int l=0; l<N; l++)
		ret += str[i+l];
	return ret;
}
