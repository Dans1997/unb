#include <bits/stdc++.h>

using namespace std;

#define MAX 100000
#define N_SCHOOLS 50
#define N_TEACHER 100

struct Teacher {
	int number;
	int skill;
	int matching_school;
	queue<int> preferences;
};

struct School {
	int number;
	int matching_teacher;
	int preference;
};

// Global Variables
int matches[N_SCHOOLS+1];
Teacher teachers[N_TEACHER+1];
School schools[N_SCHOOLS+1];

void show () {
	system("clear || cls");
	cout << "Results:" << endl << endl;
	for (auto i = 1; i <= N_SCHOOLS; i++) {
		cout << "School: " << setw(3) <<  i << "  Teacher: ";
		if (matches[i] == 0) {
			cout << "-" << endl;
		} else {
			cout << setw(3) << matches[i] << endl;
		}
	}
}

// TODO: each teacher can only go to this 5 schools?
void match () {
	cout << "iniciating algorithm... ";
	set<int> free_teachers; // set to determine which students have not find a match yet and have not tried all their possibilities
	for (auto i = 1; i <= N_TEACHER; i++) { // get the first student with ac
		if (teachers[i].preferences.size()) {
			free_teachers.insert(i);
		}
	}

	for (auto i = 0; i <= N_SCHOOLS; i++) {
		matches[i] = 0;
	}
	cout << "[OK]" << endl;

	cout << "matching teachers with schools... ";
	while (free_teachers.size()) {

		auto t = *free_teachers.begin(); // get the teacher number
		free_teachers.erase(free_teachers.begin()); // remove teacher from the set of umatched teachers

		if (teachers[t].preferences.empty()) { // there is not preferences anymore
			free_teachers.erase(free_teachers.begin()); // remove from the unmatched teachers, because we cannot match him with any school
			continue;
		}

		auto s = teachers[t].preferences.front(); // get best option of school for the current teacher
				 teachers[t].preferences.pop();   // remove the teacher preference
			
		auto other_t = matches[s];

		if (other_t == 0) { // there is no match with this school
			matches[s] = t;
		} else if (schools[s].preference != teachers[other_t].skill) { // if the current teacher assigned is the preference of the school (as the school have a vague preference, if the current do not match that preference, we can trade)
			free_teachers.insert(other_t); // put the other teacher in the unmatched teacher
			matches[s] = t; // match the school with the new teacher
		} else {
			free_teachers.insert(t); // put the teacher back if I could not match it 
		}
	}
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

		aux = remove(teacher_preference, 'E');
		tmp = split(aux, ',');

		for (auto s : tmp) {
			// cout << s << " ";
			auto school_number = stoi(s);
			t.preferences.push(school_number);
		}
		// cout << endl;

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
		s.preference = stoi(tmp[1]);

		schools[s.number] = s;
	}
	cout << "[OK]" << endl;
}

int main () {
	read();
	match();
	show();
}