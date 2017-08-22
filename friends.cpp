// // //
// Trabalho 1 de TAG 
// 150032552 - Claudio Segala Rodrigues Silva Filho
// 000000000 - Luiz Gebrim
// // //

#include <vector.h>
#include <string.h>
#include <iostream.h>
#include <stdlib.h>

using namespace std;

void clear_screen() {
  system("clear || cls");
} 
  
int main() {
  clear_screen();
  
  enum options {ap
    findClick,
    printGraph,
    leave
  };
  
  auto op = leave;
  
  do {
    cout << "Welcome" << endl;
    cout << findClick << " Find Click in Friends Graph" << endl;
    cout << printGraph << " Print Friends Graph" << endl;
    cout << leave << " Leave" << endl;
    cout << " > ";
    cin >> op;
    
    clear_screen();
    
    switch(op) {
      case findClick:
        cout << "Preparing graph..." << endl;
        auto g = read_file();
        cout << "Iniciating Bron-Kerbosch Algorithm..." << endl;
        auto ans = bron_kerbosch(&g);
        cout << "Printing answers..." << endl;
        for(auto a : ans) {
          plot(a); // use dracula Graph js or sigma Js to draw graph
        }
        break;
      case printGraph:
        cout << "Preparing graph..." << endl;
        auto g = read_file();
        cout << "Printing graph..." << endl;
        plot(g);
        break;
      case leave: 
        break;
      default:
        cout << "Please enter a valid number!";
    }
  } while(not (op == leave));

  return 0;
}
