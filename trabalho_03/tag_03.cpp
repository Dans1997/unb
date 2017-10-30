// // // // // // // // // // // // // // // // // // //
// TAG - Trabalho 3                                   //
// 150032552 - Claudio Segala Rodrigues Silva Filho   //
// 160071569 - Luis Felipe Braga Gebrim Silva         //
// // // // // // // // // // // // // // // // // // //

#include <bits/stdc++.h>

using namespace std;

#define MAX 100000
#define N_SCHOOLS 50
#define N_TEACHER 100

struct Teacher {
	int number;
	int skill;
	queue<int> preferences;
};

struct School {
	int number;
	int preference;
};

// Global Variables
pair<int, int> matches_of[N_SCHOOLS+1];
Teacher teachers[N_TEACHER+1];
School schools[N_SCHOOLS+1];

void show () {
	system("clear || cls");
	cout << "Results:" << endl << endl;
	for (auto i = 1; i <= N_SCHOOLS; i++) {
		cout << "School: " << setw(3) <<  i << "  Teacher: ";
		if (matches_of[i] == pair<int, int>{0, 0}) {
			cout << "-" << endl;
		} else {
			cout << setw(3) << matches_of[i].first << ", " << matches_of[i].second << endl;
		}
	}
	cout << endl;
}

void match () {
	queue<int> free_teachers; // set to determine which students have not find a match yet and have not tried all their possibilities
	queue<int> free_schools;  // set to determine which schools have not find two matches yet

	for (auto i = 1; i <= N_TEACHER; i++) { // get the first student with ac
		free_teachers.push(i);
	}

	for (auto i = 1; i <= N_SCHOOLS; i++) { // get the first student with ac
		free_schools.push(i);
	}

	for (auto i = 0; i <= N_SCHOOLS; i++) { // start all schools matches
		matches_of[i] = pair<int, int>{0, 0};
	}

	while (not free_teachers.empty()) {
		auto teacher = free_teachers.front(); // get the teacher
		free_teachers.pop(); // remove teachers

		if (teachers[teacher].preferences.empty()) { 
			continue; 
		}

		auto school = teachers[teacher].preferences.front(); teachers[teacher].preferences.pop();	
		auto school_preference = schools[school].preference;
		auto match = matches_of[school];

		if (not match.first) {                             // there is space to match with this school
			matches_of[school].first = teacher;
		} else if (not match.second) {                     // there is space to match with this school
			matches_of[school].second = teacher;
		} else if (school_preference != teachers[match.first].skill) { // if the current teacher assigned is the preference of the school (as the school have a vague preference, if the current do not match that preference, we can trade)
			free_teachers.push(match.first);                                // put the other teacher in the unmatched teacher
			matches_of[school].first = teacher;                             // match the school with the new teacher
		} else if (school_preference != teachers[match.second].skill) { // if the current teacher assigned is the preference of the school (as the school have a vague preference, if the current do not match that preference, we can trade)
			free_teachers.push(match.second);                               // put the other teacher in the unmatched teacher
			matches_of[school].second = teacher;                            // match the school with the new teacher
		} else {
			free_teachers.push(teacher); // put the teacher back if I could not match it 
		}
	}
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
	freopen("input.txt", "r", stdin);

	string aux = "";
	string line = "";

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

		aux = remove(teacher_preference, 'E');
		tmp = split(aux, ',');

		for (auto s : tmp) {
			auto school_number = stoi(s);
			t.preferences.push(school_number);
		}

		teachers[t.number] = t;
	}

	for (auto i = 0; i < N_SCHOOLS; i++) {
		getline(cin, line);

		School s;

		line = remove(line, 'E');
		line = remove(line, '(');
		line = remove(line, ')');

		auto tmp = split(line, ':');

		s.number = stoi(tmp[0]);
		s.preference = stoi(tmp[1]);

		schools[s.number] = s;
	}
}

int main () {
	read();
	match();
	show();
}