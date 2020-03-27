//-----------------------------------------------------------------------------------
//                            CS 215 - Section 007 - Project 2                           
//-----------------------------------------------------------------------------------
// Author: Noah Perry                                                                
// Date: 3/11/2020                                                          
// Description: Utilize functions, reading text files, and everything else we learned
// during this "unit".
//-----------------------------------------------------------------------------------

#include<iomanip>
#include<iostream>
#include<fstream>
#include<string>

using namespace std;

const int maxStudents = 5;
const int maxScores = 5; //per student
const int NOTFOUND = -1; //used for special cases

struct Scores {
	int made;
	int poss;
	int Num;
	double average;
	char grade;
};

struct studentInfo {
	int StudentID;
	string LastName;
	string FirstName;
	Scores studentScores[maxScores];
};

//create a display with options that can be ran
void displayMenu() {
	cout << "+-----------------------------------------+" << endl;
	cout << "|              Grade Pro Plus             |" << endl;
	cout << "|              by Noah Perry              |" << endl;
	cout << "+-----------------------------------------+" << endl;
	cout << "A - Add Student           " << "D - Drop Student" << endl;
	cout << "V - View Student          " << "P - Print Class" << endl;
	cout << "S - Sort By Avg           " << "N - Sort By Name" << endl;
	cout << "E - Enter New Scores      " << "X - Exit" << endl;
}

//given a character input which should correspond to an option, should not be specific 
//to this project and be usable in other progs (ideally)
char getOption(string validOptions) {
	string option;
	char opt;
	int found = NOTFOUND;

	cout << "Enter option: ";
	if (cin.peek() == '\n') cin.ignore(); //ignores if user accidentally inputs a newline
	getline(cin, option); //gets the entire input
	opt = toupper(option[0]); //gets the first input and makes it "case insensitive"
	found = validOptions.find(opt); //sets found value to index of char

	while (found == NOTFOUND) {
		cout << "Invalid option. Choose one of " << validOptions << endl;
		if (cin.peek() == '\n') cin.ignore(); //ignores if user accidentally inputs a newline
		getline(cin, option); //gets the entire input
		opt = toupper(option[0]); //gets the first input and makes it "case insensitive"
		found = validOptions.find(opt); //sets found value to index of char
	}

	return opt;
}

//sets partial array values for students to empty string values
void init(studentInfo studentArray[maxStudents]) {
	int i;
	int j;
	for (i = 0; i < maxStudents; ++i) {
		studentArray[i].StudentID = 0000;
		studentArray[i].LastName = "";
		studentArray[i].FirstName = "";
		for (j = 0; j < maxScores; ++j) {
			studentArray[i].studentScores[i].made = 0;
			studentArray[i].studentScores[i].poss = 0;
		}
	}
	
}

//write all current data to an output file stream "gradesout.txt" file which should be created
void write(studentInfo studentArray[maxStudents]) {
	int i;
	int j;
	ofstream f;

	f.open("gradesout.txt");
	if (!f.fail()) {
		for (i = 0; i < maxStudents; ++i) {
			f << setprecision(4) << studentArray[i].StudentID << " " << studentArray[i].LastName << ", " << studentArray[i].FirstName << " ";
			for (j = 0; j < maxScores; ++j) {
				f << studentArray[i].studentScores[i].made << " " << studentArray[i].studentScores[i].poss << " ";
			}
			f << endl;
		}
	}
	f.close();
}

//open an input filestream called "grades.txt", will modify partial array of students
void load(){
	int i;
	ifstream f;
	int StudentID; string LastName; string FirstName; int studentScores[maxScores];
	studentInfo studentArray[maxStudents];
	f.open("grades.txt");
	if (!f.fail()) {
		for (i = 0; i < maxStudents; ++i) {
			f >> StudentID >> LastName >> FirstName >> studentScores[i];
		}
	}
	else {
		cout << "No data file found... starting new class." << endl;
	}
	f.close();
}

//print a neat report (example on specifications doc)
void printReport(studentInfo studentArray[maxStudents]) {
	int i;

	cout << " ID   Name                   Avg   Grd  Scores" << endl;
	cout << "----  --------------------  -----  ---  -----------------------------------------" << endl;
	for (i = 0; i < maxStudents; ++i) {
		cout << setw(4) << studentArray[i].StudentID << left << setw(20) << studentArray[i].LastName << ", " << studentArray[i].FirstName;
		cout << right << setw(5) << fixed << setprecision(1) << studentArray[i].studentScores[i].average;
		cout << setw(6) << " " << studentArray[i].studentScores[i].grade << " ";
		for (i = 0; i < studentArray[i].studentScores[i].Num; ++i) {
			cout << setw(3) << fixed << setprecision(0) << right << studentArray[i].studentScores[i].made << "/" << studentArray[i].studentScores[i].poss;
		}
	}
}

//add a new student to the partial array that should be established already
void addStudent(studentInfo studentArray[maxStudents]) {
	int i;
	int j;
	int seat = 0;

	if (seat > maxStudents) {
		cout << "No more students may be added." << endl;
	}
	else {
		cout << "Enter Student ID Number: ";
		cin >> studentArray[seat].StudentID;
		cout << "\nEnter First and Last Name: ";
		cin >> studentArray[seat].FirstName >> studentArray[seat].LastName;
		cout << "\nEnter Number of Scores: ";
		cin >> studentArray[seat].studentScores[seat].Num;
		while (studentArray[seat].studentScores[seat].Num < 0 && studentArray[seat].studentScores[seat].Num > 5) {
			cout << "Invalid Number of Scores";
			cout << "\nEnter Number of Scores: ";
			cin >> studentArray[seat].studentScores[seat].Num;
		}
		for (j = 0; j < studentArray[seat].studentScores[seat].Num; ++j) {
			cout << "Enter Score " << j + 1 << ": ";
			cin >> studentArray[seat].studentScores[j].made >> studentArray[seat].studentScores[j].poss;
			cout << endl;
		}
		++seat;
		cout << "New Student Added." << endl;
	}
}

//given a student ID and a partial array of students, find the matching student in the array
int search(studentInfo studentArray[maxStudents], int studentID) {
	int i;
	for (i = 0; i < maxStudents; ++i) {
		if (studentArray[i].StudentID == studentID) {
			return i;
		}
		else {
			i = NOTFOUND;
			return i;
		}
	}
}

//given the index of the array and remove the student from said index
studentInfo removeStudent(char index){
	remove(index);
}

int findStudent(studentInfo studentArray[maxStudents]) {
	int studentID;
	int result;
	cout << "Enter Student ID Number: ";
	cin >> studentID;
	cout << endl;
	result = search(studentArray, studentID);
	if (result = NOTFOUND) {
		cout << "Student ID " << studentID << " not found!" << endl;
	}
	else {
		return result;
	}
}

//use find student and remove student to find the student in the array and remove them
void dropStudent(studentInfo studentArray[maxStudents]) {
	int result;
	result = findStudent(studentArray);
	if (result >= 0) {
		removeStudent(result);
		cout << studentArray[result].FirstName << " " << studentArray[result].LastName << " dropped." << endl;
	}
}

//given an array of scores, will calculate an average percentage
 double getAvg(Scores studentScores[maxScores]) {
	int i;
	int scoresArray[maxScores];
	int total = 0;
	double TotalAverage = 0;
	
	for (i = 0; i < studentScores[i].Num; ++i) {
		scoresArray[i] = studentScores[i].made / studentScores[i].poss;
	}

	for (i = 0; i < studentScores[i].Num; ++i) {
		total = total + scoresArray[i];
	}

	TotalAverage = total / studentScores[i].Num * 100.0;
	
	return TotalAverage;
}

//given an average, assign the average with its corresponding letter grade
char getGrade(int average) {
	if (average >= 90) {
		return 'A';
	}
	else if (average >= 80 && average < 90) {
		return 'B';
	}
	else if (average >= 70 && average < 80) {
		return 'C';
	}
	else if (average >= 60 && average < 70) {
		return 'D';
	}
	else if (average < 60) {
		return 'E';
	}
}

//given the partial array, invoke functions to view student name, average grades, etc.
void viewStudent(studentInfo studentArray[maxStudents]) {
	int i;
	int result;
	result = findStudent(studentArray);
	int avg;
	char grade;
	studentInfo scores;

	if (result = NOTFOUND) {

	}
	else {
		Scores studentScores[maxScores];
		studentScores[maxScores] = studentArray[result].studentScores[result];
		avg = getAvg(studentScores);
		grade = getGrade(avg);
		cout << "ID:   " << studentArray[result].StudentID << "  Name:  " << studentArray[result].LastName << ", " << studentArray[result].FirstName << endl;
		cout << "Avg:  " << avg << "  Grade: " << grade << endl;
		cout << "Number of Scores:  " << studentScores[result].Num << endl;
		cout << "Scores:            ";
		for (i = 0; i < studentScores[result].Num; ++i) {
			cout << studentScores[result].made << "\\" << studentScores[result].poss;
		}
		cout << endl;
	}
}

//given two indices, swap all the data between them
void swap(studentInfo studentArray[maxStudents], int x, int y) {
	studentInfo temp;
	temp = studentArray[x];
	studentArray[x] = studentArray[y];
	studentArray[y] = temp;
}

//reorders all students in partial array by grade average (highest to lowest)
void sortByAvg(studentInfo studentArray[maxStudents]) {
	int i;
	int k;
	int avg[maxStudents];
	for (i = 0; i < studentArray[i].studentScores[i].Num; ++i) {
		avg[i] = getAvg(studentArray[i].studentScores);
	}

	for (int i = 0; i < maxStudents; ++i) {
		for (int k = i + 1; k < maxStudents; ++k) {
			if (avg[i] > avg[k]) {
				studentInfo temp;
				temp = studentArray[i];
				studentArray[i] = studentArray[k];
				studentArray[k] = temp;
			}

		}
	}
	cout << "Class sorted by Average." << endl;
}

//reorders all students in partial array by last name, first name from A to Z
void sortByName(studentInfo studentArray[maxStudents]) {
	int i;
	int k;
	for (int i = 0; i < maxStudents; ++i) {
		for (int k = i + 1; k < maxStudents; ++k) {
			if (studentArray[i].LastName > studentArray[k].LastName) {
				studentInfo temp;
				temp = studentArray[i];
				studentArray[i] = studentArray[k];
				studentArray[k] = temp;
			}
		}
	}
	cout << "Class sorted by Name." << endl;
}

//sort students by name and allow for grades to be entered for all students in the class for a single assignment
void enterScores() {

}

//enable all functions to be called accordingly
int main() {
	string validOptions = "ADVPSNEX";
	char option;
	studentInfo studentArray[maxStudents];
	int swap1;
	int swap2;

	init(studentArray);
	load();
	while (option != 'x') {
		displayMenu();
		option = getOption(validOptions);

		switch (option) {
		case 'A':
			addStudent(studentArray);
			break;
		case 'D':
			dropStudent();
			break;
		case 'V':
			viewStudent(studentArray);
			break;
		case 'P':
			printReport(studentArray);
			displayMenu();
			getOption(validOptions);
			break;
		case 'S':
			cin >> swap1;
			cin >> swap2;
			swap(swap1, swap2);
			break;
		case 'N':
			sortByName(studentArray);
			break;
		case 'E':
			enterScores();
			break;
		case 'X':
			write(studentArray);
			cout << "Class data written to file." << endl;
			cout << "Thanks for using Grade Pro Plus!" << endl;
			break;
		}
		system("pause");
	}
	system("pause");
	return 0;
}
