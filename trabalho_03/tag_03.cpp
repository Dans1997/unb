#include <bits/stdc++.h>

using namespace std;

#define MAX 100000
#define N_SCHOOLS 50
#define N_TEACHER 100

struct Teacher {
	int number;
	int skill;
	int matching_school;
	vector<int> preferences;
};

struct School {
	int number;
	int matching_teacher;
	vector<int> preferences;
};

// Global Variables
pair<int, int> matches[N_SCHOOLS+1];
Teacher teachers[N_TEACHER+1];
School schools[N_SCHOOLS+1];

void show () {
	system("clear || cls");
	cout << "Results:" << endl << endl;
	for (auto i = 1; i <= N_SCHOOLS; i++) {
		cout << "  Teacher: " << matches[i].first << " School: ";
		if (matches[i].second == 0) {
			cout << "-" << endl;
		} else {
			cout << matches[i].second << endl;
		}
	}
}

void match () {
	cout << "iniciating algorithm... ";
	for (auto i = 1; i <= N_SCHOOLS; i++) {
		matches[i] = {0, 0};
	}
	cout << "[OK]" << endl;

	cout << "matching teachers with schools... ";
	// while () {
	// 	for ()
	// }
	cout << "[OK]" << endl;
}

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

	if (tmp.size()) {
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

void read () {
	cout << "opening file... ";
	freopen("input.txt", "r", stdin);
	cout << "[OK]" << endl;

	string aux = "";
	string line = "";


	cout << "getting teachers preferences... ";
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
	cout << "[OK]" << endl;

	cout << "getting schools preferences... ";
	for (auto i = 0; i < N_SCHOOLS; i++) {
		getline(cin, line);

		School s;

		line = remove(line, 'E');
		line = remove(line, '(');
		line = remove(line, ')');

		auto tmp = split(line, ':');

		s.number = stoi(tmp[0]);
		auto p = stoi(tmp[1]);

		for (auto j = 1; j <= N_TEACHER; j++) {
			if (teachers[j].skill == p) {
				s.preferences.push_back(teachers[j].number);
			}
		}

		schools[s.number] = s;
	}
	cout << "[OK]" << endl;
}

int main () {
	read();
	match();
	show();
}