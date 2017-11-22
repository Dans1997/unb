#include <bits/stdc++.h>

using namespace std;

struct File {n 
  vector<Cluster> cluster;
  string name;
}

struct HD {
  friends with FAT;

  void write (File f) {
    auto curr = 0; // indicate the currente cluster of the file
    auto last = 0; // indicate last cluster
  
    for (auto i = 0; i <= cilynders.size(); i++) {
      for (auto j = 0; j <= cilynders.tracks.size(); j++) {
        for (auto k = 0; k <= cilynders.tracks.clusters.size(); k++) {
          auto cluster_number= getClusterNumber(i, j, k);
          if (FAT::isClusterUsed(clusterNumber)){
             FAT::insertCluster(clusterNumber, curr);
             cilynders[i].tracks[j].clusters[k] = f.cluster[curr++];
          }
        }
      }
    }
  }
  
  private:
  int getClusterNumber (int a, int b, int c) {
    return (a+1)*(b+1)*(c+1);
  }
};
