/*
	This program reads in a file of course data, sorts the courses, then offers options to print
	the entire course list or a specific course and its prerequisites.

	William Kendall
	06.27.2021
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

// Structure to store course information.
struct Course {
	string courseNum; // Course number.
	string courseName; // Course name.
	string prereq1; // Course prerequisite 1.
	string prereq2; // Course prerequisite 2.
	string prereq3; // Course prerequisite 3.
	string prereq4; // Course prerequisite 4.

	Course() { // Default constructor.
		courseNum = "";
		courseName = "";
		prereq1 = "";
		prereq2 = "";
		prereq3 = "";
		prereq4 = "";
	}
};

// Reads through input file and stores information into a vector of courses to be returned.
vector<Course> readFile(string filePath) {
	ifstream inFS;
	vector<string> fileLines;
	vector<Course> courses;
	vector<Course> errorCourse;
	string tempStr;

	// Opening file.
	cout << "Opening file " << filePath << endl;
	inFS.open(filePath);

	// Outputs error if file could not open.
	if (!(inFS.is_open())) {
		cout << "Could not open " << filePath << endl;
		return errorCourse;
	}
	else {
		cout << filePath << " opened successfully." << endl;
	}

	// Stores each line into a vector.
	while (!inFS.eof()) {
		getline(inFS, tempStr);
		fileLines.push_back(tempStr);
	}

	fileLines.at(0).erase(0, 3); // Gets rid of non-alphabetical chars at beginning of first line.

	// Iterates over each line in the fileLines vector
	for (int i = 0; i < fileLines.size(); i++) {
		char currChar = 0;
		int location = 0;
		Course course; // Creates new course object.

		// Iterates over each char of current line.
		for (int j = 0; j < fileLines.at(i).size(); j++) {
			currChar = fileLines.at(i).at(j);
			if (currChar == ',') {
				location++;
				continue;
			}

			// Appends current char to correct field of course based on the location (determined by commas).
			switch (location) {
			case 0:
				course.courseNum = course.courseNum + currChar;
				break;
			case 1:
				course.courseName = course.courseName + currChar;
				break;
			case 2:
				course.prereq1 = course.prereq1 + currChar;
				break;
			case 3:
				course.prereq2 = course.prereq2 + currChar;
				break;
			case 4:
				course.prereq3 = course.prereq3 + currChar;
				break;
			case 5:
				course.prereq4 = course.prereq4 + currChar;
				break;
			}
		}
		courses.push_back(course); // Appends course to vector of courses.
	}
	return courses; // Returns vector of courses.
}

// Sorts courses into alphabetical order.
void sortCourses(vector<Course> &courses) {
	int min = 0; // Index of current "minimum" course
	int size = courses.size(); // Size of courses vector

	// Iterates over all items, swapping when a courseNum is less than the current minimum courseNum.
	for (int pos = 0; pos < size; pos++) {
		min = pos;

		for (int i = pos; i < size; i++) {
			if (courses.at(i).courseNum < courses.at(min).courseNum) {
				min = i;
			}
		}

		swap(courses.at(pos), courses.at(min));
	}
}

int main() {
	string filePath = "ABCU_Advising_Program_Input.txt";

	vector<Course> courses;
	int menuChoice = 0;

	// Iterates until user asks to exit by entering 9.
	while (menuChoice != 9) {

		// Outputting the menu and receiving user input.
		cout << "Menu:" << endl;
		cout << "  1. Load Course Data" << endl;
		cout << "  2. Print All Courses" << endl;
		cout << "  3. Print A Specific Course" << endl;
		cout << "  9. Exit" << endl;
		cout << "Enter choice: ";
		cin >> menuChoice;

		switch (menuChoice) {
		case 1: // Opens and reads file before sorting the vector of courses.
			courses = readFile(filePath);
			if (courses.at(0).courseNum == "") {
				return -1;
			}
			sortCourses(courses);
			break;
		case 2: // Outputs all courses.
			for (int i = 0; i < courses.size(); i++) {
				cout << "Course Number: " << courses.at(i).courseNum << endl;
				cout << "Course Name: " << courses.at(i).courseName << endl;
				cout << "Prerequisite 1: " << courses.at(i).prereq1 << endl;
				cout << "Prerequisite 2: " << courses.at(i).prereq2 << endl;
				cout << "Prerequisite 3: " << courses.at(i).prereq3 << endl;
				cout << "Prerequisite 4: " << courses.at(i).prereq4 << endl;
			}
			break;
		case 3: // Asks user for a specific course, then outputs that course's info if it exists.
			string userCourse;
			int i = 0;
			bool found = false;
			cout << "Please enter the course number: " << endl;
			cout << "Use format \"DEPT###\"" << endl;
			cin >> userCourse;

			for (i; i < courses.size(); i++) {
				if (userCourse.compare(courses.at(i).courseNum) == 0) {
					cout << "Course Number: " << courses.at(i).courseNum << endl;
					cout << "Course Name: " << courses.at(i).courseName << endl;
					cout << "Prerequisite 1: " << courses.at(i).prereq1 << endl;
					cout << "Prerequisite 2: " << courses.at(i).prereq2 << endl;
					cout << "Prerequisite 3: " << courses.at(i).prereq3 << endl;
					cout << "Prerequisite 4: " << courses.at(i).prereq4 << endl;
					found = true;
					break;
				}
			}
			if (found == false) {
				cout << userCourse << " could not be found." << endl;
			}
			break;
		}
	}

	cout << endl << "Goodbye." << endl;
	
	return 0;
}