#include "../include/sdsl/k2_tree.hpp"
#include <iostream>
#include <queue>
#include "closest_helper_inf.cpp"
using namespace sdsl;
using namespace std;

//Priority search by distance
vector<pair<int, int> > closest1(k2_tree<2>& G, int x, int y, int m){
  vector<pair<int, int> > ans;
  priority_queue<vector<long long>, vector<vector<long long> >, compare1 > Q;
  Q.push(vector<long long>({1,1,0,0,0,G.get_size(), 0, 0}));
  int v, l, x0, y0, s, len, new_v, new_x0, new_y0;
  long long d, xdist, ydist, new_xdist, new_ydist;
  int k = G.get_k();
  int r1 = 1;
  int c1 = 1;
  int r2 = k;
  int c2 = k;
  while (m>0 && !Q.empty()){
    vector<long long> element = Q.top();
    Q.pop();
    v = element[0];
    l = element[1];
    d = element[2];
    x0 = element[3];
    y0 = element[4];
    s = element[5];
    xdist = element[6];
    ydist = element[7];

    if (s==1){
      //cout << "found " << m << endl;
      ans.push_back(make_pair(x0+1,y0+1));
      m = m-1;
    }
    else if (s!=1){
      len = s/k;
      //cout << len << endl;
      for (int r = r1; r<=r2; r++){
        for (int c = c1; c<=c2; c++){
          //cout << v << " " << (r-1)*k+c << endl;
          if (childrenlabeled(G, v, (r-1)*k+c)){
            //cout << "not fun" << endl;
            new_v = labeledchild(G, v, (r-1)*k+c);
            //cout << "labelie" << endl;
            new_x0 = x0 + (c-1)*len;
            new_y0 = y0 + (r-1)*len;
            new_xdist = 0;
            new_ydist = 0;
            if (x <= new_x0) new_xdist += new_x0 + 1 - x;
            else if (x > new_x0 + len) new_xdist += x - new_x0 - len;
            if (y <= new_y0) new_ydist += new_y0 + 1 - y;
            else if (y > new_y0 + len) new_ydist += y - new_y0 - len;
            //cout << "pusheare" << endl;
            Q.push(vector<long long>({new_v, l+1, max(new_xdist, new_ydist), new_x0, new_y0, len, new_xdist, new_ydist}));
            //cout << "pushie" << endl;
          }
        }
      }
    }
  }
  return ans;
}

//Recursive Search
vector<pair<int, int> > closest2(k2_tree<2>& G, int x, int y, int m){
  vector<pair<int, int> > ans;
  priority_queue<vector<long long>, vector<vector<long long> >, compare2 > R;
  int s = G.get_size();
  top(0, 0, 1, 1, 0, 0, x, y, s, G, R, m);
  while(!R.empty()){
    vector<long long> r = R.top();
    ans.push_back(make_pair(r[0], r[1]));
    R.pop();
  }
  reverse(ans.begin(),ans.end());
  return ans;
}

//Centric Search
vector<pair<int, int> > closest3(k2_tree<2>& G, int x, int y, int m){
  int range = max(ceil((ceil(sqrt(m))-1)/2),1.0);
  int s = G.get_size();
  vector<vector<long long> > ret = rangeQuery(G, x, y, range);
  int maxR = max(max(s-x,s-y),max(x,y));
  while(ret.size() < m && range<maxR){
    range = 2*range;
    ret = rangeQuery(G, x, y, range);
  }
  return getM(ret, m);
}

vector<pair<int, int> > closest4(k2_tree<2>& G, int x, int y, int m){
  int range = max(ceil((ceil(sqrt(m))-1)/2),1.0);
  int s = G.get_size();
  int desv = sqrt(s);
  vector<vector<long long> > ret = rangeQuery(G, x, y, range);
  int maxR = max(max(s-x,s-y),max(x,y));
  while(ret.size() < m && range<maxR){
    range += desv/2;
    ret = rangeQuery(G, x, y, range);
  }
  return getM(ret, m);
}
