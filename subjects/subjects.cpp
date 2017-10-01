// // // // // // // // // // // // // // // // // // //
// TAG - Trabalho 2                                   //
// 150032552 - Claudio Segala Rodrigues Silva Filho   //
// 160071569 - Luis Felipe Braga Gebrim Silva         //
// // // // // // // // // // // // // // // // // // //

// Arquivo 
// Organizado na seguinte forma:
// #NumeroMateria Nome_Materia #NumeroCreditos #NumeroDificuldade // #NumeroRequisitos #NumeroOutraMateria(x#NumeroRequisitos)

#include <bits/stdc++.h>
using namespace std;

#define l_l  << " " <<

// Struct & Classes
struct Subject {
	string name;
	int key, credit, difficulty, weight;
};

// Variaveis Globais
map<int, Subject> subjects; // dicionario de materias Key: matricula 
vector<vector<int>> dag;  // lista de adjacencia com (peso, proximoNo)

void buildDAG () {
	dag.resize(100);

	ifstream file;
	file.open("subjects.txt"); // open the file

	if(not file.is_open()) {
		cout << "Could not find file!" << endl;
		exit(0);
	}

	while(not file.eof()) {
		Subject sub;
		file >> sub.key >> sub.name >> sub.credit >> sub.difficulty;
		cout << sub.key l_l sub.name l_l sub.credit l_l sub.difficulty << endl;
		sub.weight = sub.credit * sub.difficulty;

		subjects[sub.key] = sub; // insere a matéria no dicionário de materias

		int numberOfDependencies;
		file >> numberOfDependencies;
		cout << numberOfDependencies << endl;
		for(int i = 0; i < numberOfDependencies; i++) {
			int dependency;
			file >> dependency; // le uma materia que depende
			dag[dependency].push_back(sub.key);
		}
	}

	file.close();
}

void printCourse () {
	cout << "Computer Science\n\n";
	for (auto sub : subjects) {
		cout << sub.second.key << " - " << sub.second.name << " - " << sub.second.credit << " - " << sub.second.difficulty << "\n";
	}
	cout << "\n\n\n";
}

void printDAG () {

}

int main () {
	buildDAG();
	printCourse();

	printDAG();
}