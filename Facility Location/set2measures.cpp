#include "../include/sdsl/k2_tree.hpp"
#include <iostream>
#include <fstream>
#include <queue>
#include "closest.cpp"
using namespace sdsl;
using namespace std;
typedef uint64_t idx_type;

double error(vector<double> values, double mean, int size){
  double error = 0;
  for(int i = 0; i<size; i++){
    error += pow(values[i]-mean,2);
  }
  error = sqrt(error/(size-1))/sqrt(size);
  return error;
}
int main(){
  struct timespec start, finish;
  double elapsed;
  idx_type a,b;
  int size = 1024;
  vector<tuple<idx_type,idx_type> > edges;
  ifstream file( "set1.txt" );
  vector<double> v1(10);
  vector<double> v2(10);
  vector<double> v3(10);
  vector<double> v4(10);
  double m1,m2,m3,m4,e1,e2,e3,e4;
  ofstream result1,result2,result3,result4,error1,error2,error3,error4;
  result1.open("result1.txt");
  result2.open("result2.txt");
  result3.open("result3.txt");
  result4.open("result4.txt");
  error1.open("error1.txt");
  error2.open("error2.txt");
  error3.open("error3.txt");
  error4.open("error4.txt");
  int query = 40401;
  int times = 10;
  int howmanyclosest34 = 40401;
  long long lat = 300;
  long long lon = 300;
  //long long lat = 1;
  //long long lon = 1;
  for (int i = 0; i < 40401; i++){
    file >> a;
    file >> b;
    edges.push_back(make_tuple(a,b));
  }

  k2_tree<2> tree = k2_tree<2>(edges,size);

  for(int i = 1; i <= query; i++){
    fill(v1.begin(),v1.end(),0);
    fill(v2.begin(),v2.end(),0);
    fill(v3.begin(),v3.end(),0);
    fill(v4.begin(),v4.end(),0);
    m1 = 0;
    m2 = 0;
    m3 = 0;
    m4 = 0;
    for (int j = 0; j<times; j++){
      //closest1

      clock_gettime(CLOCK_MONOTONIC, &start);

      closest1(tree, lat, lon, i);

      clock_gettime(CLOCK_MONOTONIC, &finish);

      elapsed = (finish.tv_sec - start.tv_sec);
      elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
      m1 += elapsed;
      v1[j] = elapsed;

      //closest2
      clock_gettime(CLOCK_MONOTONIC, &start);

      closest2(tree, lat, lon, i);

      clock_gettime(CLOCK_MONOTONIC, &finish);

      elapsed = (finish.tv_sec - start.tv_sec);
      elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
      m2 += elapsed;
      v2[j] = elapsed;

      if (i <= howmanyclosest34) {
        //closest3
        clock_gettime(CLOCK_MONOTONIC, &start);

        closest3(tree, lat, lon, i);

        clock_gettime(CLOCK_MONOTONIC, &finish);

        elapsed = (finish.tv_sec - start.tv_sec);
        elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
        m3 += elapsed;
        v3[j] = elapsed;

        //closest4
        clock_gettime(CLOCK_MONOTONIC, &start);

        closest4(tree, lat, lon, i);

        clock_gettime(CLOCK_MONOTONIC, &finish);

        elapsed = (finish.tv_sec - start.tv_sec);
        elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
        m4 += elapsed;
        v4[j] = elapsed;

      }
      cout << i << " " << j+1 <<endl;
    }

    m1 = m1/times;
    m2 = m2/times;
    e1 = error(v1, m1, times);
    e2 = error(v2, m2, times);

    result1 << m1;
    error1 << e1;
    result2 << m2;
    error2 << e2;

    if (i!=query){
        result1 << ",";
        error1 << ",";
        result2 << ",";
        error2 << ",";
    }

    if (i <= howmanyclosest34){
      m3 = m3/times;
      e3 = error(v3, m3, times);
      m4 = m4/times;
      e4 = error(v4, m4, times);
      result3 << m3;
      error3 << e3;
      result4 << m4;
      error4 << e4;
      if (i!=howmanyclosest34){
        result3 << ",";
        error3 << ",";
        result4 << ",";
        error4 << ",";
      }
    }
  }
  result1.close();
  result2.close();
  result3.close();
  result4.close();
  error1.close();
  error2.close();
  error3.close();
  error4.close();
}
