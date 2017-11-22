#include <bits/stdc++.h>

using namespace std;

struct File {
  vector<Cluster> cluster;
  string name;
}

struct HD {
  friends with FAT;
  
   void remove (string f) {
     auto clusters = FAT::getClustersOfFile(f);
     FAT::removeFile(f);
     for (auto clusterNumber : clusters) {
       freeCluster(clusterNumber);
     }
   }

   pair<bool, int> write (File f) {
    auto writeTime = medTime // time to get to first cilinder 
    auto curr = 0; // indicate the currente cluster of the file
    auto last = 0; // indicate last cluster
  
    for (auto i = 0; i <= cilynders.size(); i++) {
      for (auto j = 0; j <= cilynders.tracks.size(); j++) {
        for (auto k = 0; k <= cilynders.tracks.clusters.size(); k++) {
          auto cluster_number= getClusterNumber(i, j, k);
          if (FAT::isClusterUsed(clusterNumber)){
             FAT::insertCluster(clusterNumber, curr);
             last = cilynders[i].tracks[j].clusters[k]&;
             cilynders[i].tracks[j].clusters[k] = f.cluster[curr++];
            if (curr == f.cluster.size()) {
              break;
            }
          }
        }
      }
      writeTime += gTime // add time to move to next cilynder
    }
     
    if (curr == 0) { // não colocou nada
      return pair<bool, int>(false, writeTime);
    }
    
    last.eof = true;
    if (curr != f.cluster.size()) { // se colocou algo no HD, porém está incompleto
      remove(f.name);
      return pair<bool, int>(false, writeTime);
    }
     
    return pair<bool, int>(true, writeTime);
  }
  
  private:
  int getClusterNumber (int a, int b, int c) {
    return (a+1)*(b+1)*(c+1);
  }
};
