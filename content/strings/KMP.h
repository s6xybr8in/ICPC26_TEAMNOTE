/**
 * Author: Green Siro
 * License: CC0
 * Description: Prefix function and all match starts; empty
 * pattern matches at every boundary. Time: O(text +
 * pattern).
 */
#pragma once

vector<int> prefixFunction(const string& s) {
  vector<int> p(s.size());
  for(int i=1;i<(int)s.size();++i) {
    int j=p[i-1];
    while(j && s[i]!=s[j]) j=p[j-1];
    if(s[i]==s[j]) ++j;
    p[i]=j;
  }
  return p;
}
vector<int> kmp(const string& text,const string& pat) {
  vector<int> ans;
  if(pat.empty()) {
    ans.resize(text.size()+1);iota(ans.begin(),ans.end(),0);
    return ans;
  }
  auto p=prefixFunction(pat);int j=0;
  for(int i=0;i<(int)text.size();++i) {
    while(j && text[i]!=pat[j]) j=p[j-1];
    if(text[i]==pat[j]) ++j;
    if(j==(int)pat.size()) ans.push_back(i-j+1),j=p[j-1];
  }
  return ans;
}
