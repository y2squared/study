#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
const size_t MAX_N = 50000;
int main(int argc, char** argv) {
  size_t N, R, test_num;
  cin >> test_num;
  for(size_t test_id = 0 ; test_id < test_num ; test_id++) {
    cin >> N >> R;
  
    vector<vector<long> > adjacent(N+1);
    for(size_t i = 1; i <= N ; ++i) {
      adjacent[i].resize(N+1,LONG_MAX);
    }

    for(size_t i = 0; i < R ; ++i) {
      size_t start,end;
      long cost;
      cin >> start >> end >> cost;
      adjacent[start][end] = cost;
    }

    long prev[MAX_N+1] = {0};
    long d[MAX_N+1] ;
    d[1] = 0; // d(v) = 0
    for(size_t i = 2 ; i <= N ; ++i) d[i] = LONG_MAX;
    vector<long> Q(N);
    for(size_t i = 1 ; i <= N ; ++i) {
      Q[i-1] = i;
    }
    //
    while(!Q.empty()) {
      size_t min_dv = 0;
      for(size_t i = 0 ; i < Q.size() ; ++i) {
        if(d[Q[i]] < d[Q[min_dv]]) {
          min_dv = i;
        }
      }
      min_dv = Q[min_dv];
      Q.erase(remove(Q.begin(),Q.end(),min_dv),Q.end());
      size_t qsize = Q.size();
      for(size_t i = 0 ; i < qsize; ++i) {
        if( adjacent[min_dv][Q[i]] != LONG_MAX && d[Q[i]] > d[min_dv] + adjacent[min_dv][Q[i]] ) {
          d[Q[i]] = d[min_dv] + adjacent[min_dv][Q[i]];
          prev[Q[i]] = min_dv;
        }
      }
    }
    cout << d[N] << endl;
  }
  return 0;
}
