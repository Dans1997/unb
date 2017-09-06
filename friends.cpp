// // //
// Trabalho 1 de TAG 
// 150032552 - Claudio Segala Rodrigues Silva Filho
// 000000000 - Luiz Gebrim
// // //

// Includes
#include <bits/stdc++.h>

// Usings
using namespace std;

// Defines
#define MAX_SIZE 100
#define pb push_back
#define vi vector<int>
#define ii pair<int, int>
#define ff first
#define ss second

// Global Variables
vector<string> names;
vi graph[MAX_SIZE + 1];
vector<pair<int, int>> order;
vector<vi> cliques;

void clear_screen() {
  system("clear || cls");
} 

void read_file() {
  // Make file the standart input 
  freopen("input.txt", "r", stdin);

  int id;
  while(cin >> id) {
    int v;
    string name;

    cin >> name;
    names.pb(name);

    while(true){
      cin >> v;
      if(not v) break;
      graph[id].pb(v);
      graph[v].pb(id);
    }
  }
}

void bk(vi r, vi p, vi e){
  if(p.empty() && e.empty()) cliques.pb(r);
  
  bool mark[50], mark2[50];
  memset(mark,0,sizeof mark);
  memset(mark2,0,sizeof mark2);
  for(int i = 0; i < p.size(); i++)
    mark[p[i]] = 1;
  for(int i = 0; i < e.size(); i++)
    mark2[e[i]] = 1;
  
  for(int i = 0; i < p.size(); i++){
    r.pb(p[i]);
    vector<int> p2, e2;
    for(int j = 0; j < graph[p[i]].size(); j++){
      if(mark[graph[p[i]][j]])
        p2.pb(graph[p[i]][j]);
      if(mark2[graph[p[i]][j]])
        e2.pb(graph[p[i]][j]);
    }
    bk(r,p2,e2);
    r.pop_back();
    mark[p[i]] = 0;
    mark2[p[i]] = 1;
  }
}

bool comp(vi a, vi b){
  return b.size() < a.size();
}

void print_graph_by_order() {
  clear_screen();
  printf(" Friends Order By Degree:\n\n");

  for(int i = 1; i < 50; i++){
    order.pb(make_pair(graph[i].size(),i));
  }
  sort(order.begin(), order.end());

  for(int i = order.size()-1; i >= 0; i--)
    cout << " Degree: " << order[i].ff << "\nNumber: " << order[i].ss << "\nName: " << names[order[i].ss - 1] << endl;

  cout << "Press [enter] to go back!" << endl;
  getchar(); getchar();
}

void bron_kerbosch() {
  vector<int> r,p,e;
  for(int i = 1; i < 50; i++)
    p.push_back(i);
  bk(r,p,e);

  sort(cliques.begin(), cliques.end(), comp);

  cout << "Clique maximum" << endl;
  cout << "Size: " << cliques[0].size() << endl;
  cout << "Friends:" << endl;
  for(int i = 0; i < cliques[0].size(); i++){
    cout << cliques[0][i] << " " << names[cliques[0][i] - 1] << endl;
  }

  cout << "---------------------------" << endl << endl;
  cout << "Clique maximal" << endl;
  cout << "Size: " << cliques[1].size() << endl;
  cout << "Friends:" << endl;
  for(int i = 0; i < cliques[1].size(); i++){
    cout << cliques[1][i] << " " << names[cliques[1][i] - 1] << endl;
  }
}
  
int main() {
  clear_screen();

  cout << "Preparing graph..." << endl;
  read_file();
  // TODO: throw error if something is wrong
  
  enum options {
    findClick,
    printGraph,
    leave
  };
  
  int op;
  
  do {
    cout << "Welcome" << endl;
    cout << findClick << " Find Click in Friends Graph" << endl;
    cout << printGraph << " Print Friends Graph Ordered By Degree" << endl;
    cout << leave << " Leave" << endl;
    cout << " > ";
    cin >> op;
    
    clear_screen();
    
    switch(op) {
      case findClick:
        cout << "Iniciating Bron-Kerbosch Algorithm..." << endl;
        bron_kerbosch();
        break;
      case printGraph:
        cout << "Printing graph..." << endl;
        print_graph_by_order();
        break;
      case leave: 
        break;
      default:
        cout << "Please enter a valid number!";
    }
  } while(not (op == leave));

  return 0;
}
