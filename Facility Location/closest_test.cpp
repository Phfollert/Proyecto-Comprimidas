#include "../include/sdsl/k2_tree.hpp"
#include <iostream>
#include <queue>
#include "closest.cpp"
using namespace sdsl;
using namespace std;
typedef uint64_t idx_type;

void check(string closest, string test, vector<vector<int> > mat, vector<pair<int, int> > result, vector<pair<int, int> > expected, int x, int y){
  cout << "Starting test" << endl;
  int len = result.size();
  int len2 = expected.size();
  if (len != len2){
    cout << closest << " failed " << test << " test because different size " << len << " , "<< len2 << endl;
    exit(1);
  };
  int dist1;
  int dist2;
  for (int i = 0;i < len; i++){
    dist1=abs(result[i].first - x)+abs(result[i].second - y);
    dist2=abs(expected[i].first - x)+abs(expected[i].second - y);
    //cout << result[i].first << "," << result[i].second << " vs " << expected[i].first << "," << expected[i].second << endl;
    if(dist1 != dist2 || mat[result[i].second-1][result[i].first-1] == 0){
      cout << closest << " failed " << test << " test" << endl;
      exit(1);
    }
    mat[result[i].second-1][result[i].first-1] = 0;
  }
  cout << closest << " passed " << test << " Test" << endl;
}

/*This function doesn't check if the point exist and if it is not being counted more than one.
it only checks if the sequence of distance is the same
*/
void check2(string closest, string test, vector<pair<int, int> > result, vector<pair<int, int> > expected, int x, int y){
  int len = result.size();
  int len2 = expected.size();
  if (len != len2){
    cout << closest << " failed " << test << " test" << endl;
    exit(1);
  };
  int dist1;
  int dist2;
  for (int i = 0;i < len; i++){
    dist1=abs(result[i].first - x)+abs(result[i].second - y);
    dist2=abs(expected[i].first - x)+abs(expected[i].second - y);
    if(dist1 != dist2){
      cout << closest << " failed " << test << " test" << endl;
      exit(1);
    }
  }
  cout << closest << " passed " << test << " Test" << endl;
}

void test1(){
  string test = "First";
  cout << test << ":Book example" << endl;
  vector<vector <int>> mat({{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
  });
  k2_tree<2> tree = k2_tree<2>(mat);
  vector<pair<int, int> > expected({make_pair(11,8), make_pair(6,10)});
  check("closest1", test, mat, closest1(tree, 8, 8, 2), expected, 8, 8);
  check("closest2", test, mat, closest2(tree, 8, 8, 2), expected, 8, 8);
  check("closest3", test, mat, closest3(tree, 8, 8, 2), expected, 8, 8);
}

void test2(){
  string test = "Second";
  cout << test << ":Empty grid" << endl;
  vector<vector <int>> mat({{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  });
  k2_tree<2> tree = k2_tree<2>(mat);
  vector<pair<int, int> > expected({});
  check("closest1", test, mat, closest1(tree, 11, 8, 20), expected, 11, 8);
  check("closest2", test, mat, closest2(tree, 11, 8, 20), expected, 11, 8);
  check("closest3", test, mat, closest3(tree, 11, 8, 20), expected, 11, 8);
}

void test3(){
  string test = "Third";
  cout << test << ":Empty search" << endl;
  vector<vector <int>> mat({{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
  });
  k2_tree<2> tree = k2_tree<2>(mat);
  vector<pair<int, int> > expected({});
  check("closest1", test, mat, closest1(tree, 11, 8, 0), expected, 11, 8);
  check("closest2", test, mat, closest2(tree, 11, 8, 0), expected, 11, 8);
  check("closest3", test, mat, closest3(tree, 11, 8, 0), expected, 11, 8);
}

void test4(){
  string test = "Fourth";
  cout << test << ":Dense grid" << endl;
  vector<vector <int>> mat({{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
  });
  k2_tree<2> tree = k2_tree<2>(mat);
  vector<pair<int, int> > expected;
  int a,b;
  for(int d = 0; d <= 30; d++){
    for(int r = 0; r <= d; r++){
      if (d-r>15 || r > 15) continue;
      expected.push_back(make_pair(1+d-r,r+1));
    }
  }
  check("closest1", test, mat, closest1(tree, 1, 1, 500), expected, 1, 1);
  check("closest2", test, mat, closest2(tree, 1, 1, 500), expected, 1, 1);
  check("closest3", test, mat, closest3(tree, 1, 1, 500), expected, 1, 1);
}

void test5(){
  string test = "Fifth";
  cout << test << ":Big grid and big m" << endl;
  int size = 1048576;
  vector<tuple<idx_type,idx_type> > edges;
  vector<pair<int, int> > expected;
  for(int d = 0; d <= 200; d++){
    for(int r = 0; r <= d; r++){
      if (d-r>size || r > size) continue;
      expected.push_back(make_pair(1+d-r,r+1));
      edges.push_back(make_tuple(d-r,r));
    }
  }
  k2_tree<2> tree = k2_tree<2>(edges,size);
  check2("closest1", test, closest1(tree, 1, 1, 20301), expected, 1, 1);
  check2("closest2", test, closest2(tree, 1, 1, 20301), expected, 1, 1);
  check2("closest3", test, closest3(tree, 1, 1, 20301), expected, 1, 1);
}

int main(){
  cout << "Running tests" << endl;
  test1();
  cout << endl;
  test2();
  cout << endl;
  test3();
  cout << endl;
  test4();
  cout << endl;
  test5();
  cout << endl;
  cout << "All test passed" << endl;
}
