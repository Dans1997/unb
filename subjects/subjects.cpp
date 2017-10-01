#include <bits/stdc++.h>

using namespace std;

// Struct & Classes

struct Subject {
	string name;
	int key;
	int credit;
	int difficulty;
};

// Variaveis Globais

map<int, string> subjects; // dicionario de materias Key: matricula 
vector<vector<int, int>> dag;  // lista de adjacencia com (peso, proximoNo)

void readFile () {
	// O arquivo está organizado na seguinte forma:
	// #NumeroMateria Nome_Materia
	// #NumeroRequisitos #NumeroOutraMateria(x#NumeroRequisitos)

	ifstream file;
	file.open("subject.txt"); // open the file

	if(not file.is_open()) {
		cout << "Could not find file!" << endl;
		exit(0);
	}

	while(not file.eof()) {
		Subject sub;

		file >> sub.key >> sub.name >> sub.credit >> sub.difficulty;

		sub.name = replace(begin(sub.name), end(sub.name), '_', ' ');

		subjects[sub.key] = sub; // insere a matéria no dicionário de materias

		int numberOfDependencies;
		file >> numberOfDependencies;
		for(int i = 0; i < numberOfDependencies; i++) {
			int dependency;
			file >> dependency; // le uma materia que depende

			int sub_weight = sub.credit * sub.difficulty;
			dag[dependency].push(sub_weight, sub.key);
		}
	}

	file.close();
	cout << "Closing the file..." << endl;
}

void printCourse () {
	for (auto subject in subjects) {
		Subject sub = subject.second;
		cout << sub.key << " - ";
		cout << sub.name << " - ";
		cout << sub.credit << " - "; 
		cout << sub.difficulty << "\n";
	}
}

void printDAG (int u = INITIAL_SUBJECT) {
	
}

int main () {
	readFile();

	printCourse();
	printDAG();
}