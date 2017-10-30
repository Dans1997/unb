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
	cout << "Results:" << endl << endl;
	for (int i = 1; i <= N_SCHOOLS; i++) {
		cout << "School: " << setw(3) <<  i << "  Teacher: ";
		if (matches_of[i] == make_pair(0, 0)) {
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

	for (int i = 1; i <= N_TEACHER; i++) { // get the first student with ac
		free_teachers.push(i);
	}

	for (int i = 1; i <= N_SCHOOLS; i++) { // get the first student with ac
		free_schools.push(i);
	}

	for (int i = 0; i <= N_SCHOOLS; i++) { // start all schools matches
		matches_of[i] = make_pair(0, 0);
	}

	while (not free_teachers.empty()) {
		int teacher = free_teachers.front(); // get the teacher
		free_teachers.pop(); // remove teachers

		if (teachers[teacher].preferences.empty()) { 
			continue; 
		}

		int school = teachers[teacher].preferences.front(); teachers[teacher].preferences.pop();	
		int school_preference = schools[school].preference;
		pair<int,int> match = matches_of[school];

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
	for (int i = 0; i < str.size(); i++) {
		char s = str[i];
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

	for (int i = 0; i < str.size(); i++) {
		char s = str[i];
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

	for (int i = 0; i < N_TEACHER; i++) {
		Teacher t;

		getline(cin, line);

		line = remove(line, ' '); 
		line = remove(line, '(');
		line = remove(line, ')');

		vector<string> tmp = split(line, ':');
		string teacher_skills = tmp[0];
		string teacher_preference = tmp[1];

		tmp = split(teacher_skills, ',');
		aux = remove(tmp[0], 'P');
		t.number = atoi(aux.c_str());
		t.skill  = atoi(tmp[1].c_str());

		aux = remove(teacher_preference, 'E');
		tmp = split(aux, ',');

		for (int i = 0; i < tmp.size(); i++) {
			string s = tmp[i];
			int school_number = atoi(s.c_str());
			t.preferences.push(school_number);
		}

		teachers[t.number] = t;
	}

	for (int i = 0; i < N_SCHOOLS; i++) {
		getline(cin, line);

		School s;

		line = remove(line, 'E');
		line = remove(line, '(');
		line = remove(line, ')');

		vector<string> tmp = split(line, ':');

		s.number = atoi(tmp[0].c_str());
		s.preference = atoi(tmp[1].c_str());

		schools[s.number] = s;
	}

	for (int i = 1; i <= N_TEACHER; i++) {
		for (int j = 1; j <= N_SCHOOLS; j++) {
			teachers[i].preferences.push(j);
		}
		
	}
}

int main () {
	read();
	match();
	show();
}