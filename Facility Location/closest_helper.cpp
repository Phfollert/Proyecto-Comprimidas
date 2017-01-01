#include "../include/sdsl/k2_tree.hpp"
#include <iostream>
#include <queue>
#include <algorithm>

using namespace sdsl;
using namespace std;

struct compare1
{
  bool operator()(const vector<long long> l, const vector<long long> r)
  {
    if (l[2]==r[2]) return l[5]>r[5];
    return l[2] > r[2];
  }
};

struct compare2
{
  bool operator()(const vector<long long> l, const vector<long long> r)
  {
    return l[2] < r[2];
  }
};

void printv(vector<pair<int,int> > points) {
  int size = points.size();
  for(int i = 0; i<size; i++){
    cout << points[i].first << "," << points[i].second << endl;
  }
}

bool childrenlabeled(k2_tree<2>& G, int father, int son){
  //It isn't located in last level
  bit_vector t = G.get_t();
  int k = G.get_k();
  int size = t.size();
  int nodes = size/(k*k);
   // It's located in last level
  if (father > nodes) {
    bit_vector l = G.get_l();
    father = father - nodes;
    return l[k*k*(father-1)+son-1];
  }
  return t[k*k*(father-1)+son-1];
}

int labeledchild(k2_tree<2>& G, int father, int son){
  bit_vector::rank_1_type rank = G.get_rank();
  int k = G.get_k();
  bit_vector t = G.get_t();
  int size = t.size();
  int nodes = size/(k*k);
  if (father > nodes) {
    return 1; // any value
  }
  return rank(k*k*(father-1)+son)+1;
}

void recursiveRangeQuery(k2_tree<2>& G, int v, int x, int y, int x0, int y0, int s, int range, vector<vector<long long> > &R){
  if(s == 1) {
    R.push_back(vector<long long>({x0+1,y0+1,abs(x-x0-1)+abs(y-y0-1)}));
  }
  else{
    int new_v, new_x0, new_y0, new_d;
    int k = G.get_k();
    int len = s/k;
    int c1 = ceil(1.0*max(x-range-x0,1)/len);
    int r1 = ceil(1.0*max(y-range-y0,1)/len);
    int c2 = ceil(1.0*min(x+range-x0,s)/len);
    int r2 = ceil(1.0*min(y+range-y0,s)/len);
    for (int r = r1; r<=r2; r++){
      for (int c = c1; c<=c2; c++){
        if (childrenlabeled(G, v, (r-1)*k+c)){
          new_v = labeledchild(G, v, (r-1)*k+c);
          new_x0 = x0 + (c-1)*len;
          new_y0 = y0 + (r-1)*len;
          recursiveRangeQuery(G, new_v, x, y, new_x0, new_y0, len, range, R);
        }
      }
    }
  }
}

vector<vector<long long> > rangeQuery(k2_tree<2>& G, int x, int y, int r){
  vector<vector<long long> > R;
  recursiveRangeQuery(G, 1, x, y, 0, 0, G.get_size(), r, R);
  return R;
}

vector<pair<int, int> > getM (vector<vector<long long> >& R, int m){
  vector<pair<int, int> > ans;
  m = min(m, (int)R.size());
  partial_sort(R.begin(), R.begin()+m, R.end(), compare2());
  for(int i = 0; i < m; i++){
    vector<long long> r = R[i];
    ans.push_back(make_pair(r[0], r[1]));
  }
  return ans;
}

long long Mdistance (vector<vector<long long> >& R, long long m){
  if (m==0) return 0;
  nth_element(R.begin(), R.begin()+m-1, R.end(), compare2());
  vector<long long> point = R[m-1];
  long long d = point[2];
  return d;

}
void top(long long d, int v, int l, int x0, int y0, int x, int y, int s, k2_tree<2>& G, priority_queue<vector<long long>, vector<vector<long long> >, compare2> &R, long long m){
  if (R.size() >= m && (m==0 || d >= R.top()[2])){
    return;
  }
  if (s==1){
    if (R.size() == m){
      R.pop();
    }
    R.push(vector<long long>({x0+1,y0+1,d}));
  }
  else if (s!=1){
    int new_v, new_x0, new_y0;
    long long new_d;
    int k = G.get_k();
    int len = s/k;
    int r1 = 1;
    int c1 = 1;
    int r2 = k;
    int c2 = k;
    for (int r = r1; r<=r2; r++){
      for (int c = c1; c<=c2; c++){
        if (childrenlabeled(G, v, (r-1)*k+c)){
          new_v = labeledchild(G, v, (r-1)*k+c);
          new_x0 = x0 + (c-1)*len;
          new_y0 = y0 + (r-1)*len;
          new_d = 0;
          if (x <= new_x0) new_d += new_x0 + 1 - x;
          else if (x > new_x0 + len) new_d += x - new_x0 - len;
          if (y <= new_y0) new_d += new_y0 + 1 - y;
          else if (y > new_y0 + len) new_d += y - new_y0 - len;
          top(new_d, new_v, l+1, new_x0, new_y0, x, y, len, G, R, m);
        }
      }
    }
  }
}
