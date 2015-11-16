string mcp(string s){
  int n = s.length();
  s += s;
  int i=0, j=1, k=0;
  while (j<n && k<n){
    if (s[i+k] == s[j+k]) k++;
    else {
      if (s[i+k] < s[j+k]) {
        j += k + 1;
      } else {
        i = j;
        j = max(j+1, j+k);
      }
      k = 0;
    }
  }
  return s.substr(i, n);
}

