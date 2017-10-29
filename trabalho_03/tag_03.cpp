#include <bits/stdc++.h>

using namespace std;

#define MAX 100000
#define N_SCHOOLS 50
#define N_TEACHER 100

struct Teacher {
	int number;
	int skill;
	vector<int> preferences;
};

struct School {
	int number;
	int preference;
};

// Variaveis Globais
int table[MAX][MAX];
Teacher teachers[N_TEACHER];
School schools[N_SCHOOLS];

vector<string> split (string str, char c) {
	vector<string> ans;
	string tmp = "";
	for (auto s : str) {
		if (s == c) {
			ans.push_back(tmp);
			tmp = "";
		} else {
			tmp += s;
		}
	}

	if (ans.size() == 0) {
		ans.push_back(tmp);
	}

	return ans;
}

string remove (string str, char c) {
	string ans = "";

	for (auto s : str) {
		if (s != c) {
			ans += s;
		}
	}

	return ans;
}

void read_input () {
	freopen("input.txt", "r", stdin);

	auto aux = "";
	auto line = "";

	for (auto i = 0; i < N_TEACHER; i++) {
		Teacher t;

		getline(cin, line);

		line = remove(line, ' '); 
		line = remove(line, '(');
		line = remove(line, ')');

		auto tmp = split(line, ':');
		auto teacher_skills = tmp[0];
		auto teacher_preference = tmp[1];

		tmp = split(teacher_skills, ',');
		aux = remove(tmp[0], 'P');
		t.number = stoi(aux);
		t.skill  = stoi(tmp[1]);

		aux = remove(tmp[1], 'E');
		tmp = split(aux, ',');

		for (auto s : tmp) {
			auto school_number = stoi(s);
			t.preferences.push_back(school_number);
		}

		teachers[t.number] = t;
	}

	for (auto i = 0; i < N_SCHOOLS; i++) {
		getline(cin, line);

		School school;

		line = remove(line, 'E');
		line = remove(line, '(');
		line = remove(line, ')');

		auto tmp = split(line, ':');

		s.number = stoi(tmp[0]);
		s.preference = stoi(tmp[1]);

		schools[s.number] = s;
	}
}

void iniciate () {
	system("clear || cls");
	printf("Emparelhamento de Professores com Escolas:\n");	
}

int main () {
	iniciate();
	read_input();
}