/**
 * Author: Green Siro
 * License: CC0
 * Description: Gauss-Jordan on n by (m+1) augmented matrix.
 * Returns -1=no solution, 0=unique, 1=infinitely many. Free
 * variables set to zero; EPS must suit input scale. Time:
 * O(n*m*min(n,m)). Empty input needs explicit m.
 */
#pragma once

int solveLinear(vector<vector<double>> a,int m,
                vector<double>& x,double eps=1e-9) {
  int n=(int)a.size(),row=0;vector<int> where(m,-1);
  for(int col=0;col<m && row<n;++col) {
    int sel=row;
    for(int i=row;i<n;++i)
      if(abs(a[i][col])>abs(a[sel][col])) sel=i;
    if(abs(a[sel][col])<eps) continue;
    swap(a[sel],a[row]);where[col]=row;
    double d=a[row][col];
    for(int j=col;j<=m;++j) a[row][j]/=d;
    for(int i=0;i<n;++i) if(i!=row) {
      double f=a[i][col];
      for(int j=col;j<=m;++j) a[i][j]-=f*a[row][j];
    }
    ++row;
  }
  x.assign(m,0);
  for(int j=0;j<m;++j) if(where[j]>=0) x[j]=a[where[j]][m];
  for(int i=0;i<n;++i) {
    double sum=0;for(int j=0;j<m;++j) sum+=a[i][j]*x[j];
    if(abs(sum-a[i][m])>eps) return -1;
  }
  return row==m ? 0:1;
}
