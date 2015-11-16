string mcp(string s) {
  int n = s.length();
  s = s + s;
  int i=0, j=1, k=0;
  while (j<n && k<n) {
    if (s[i+k] == s[j+k]) k++;
    else {
      if (s[i+k] < s[j+k]) j += k+1;
      else i += k+1;
      k=0;
    }
    if (i == j) j++;
  }
  string ret;
  for (int l=0; l<n; l++) ret += s[i+l];
  return ret;
}

