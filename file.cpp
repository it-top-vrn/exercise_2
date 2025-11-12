#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Date {
    string year;
    string month;
    string day;
};
struct Person {
    string last_name;
    string first_name;
    Date date_of_birth;
};

Person parsing(string str) {
    char delim = '|';
    int delim_pos_1 = str.find(delim);
    int delim_pos_2 = str.find(delim, delim_pos_1 + 1);
    Person person;
    person.last_name = str.substr(0, delim_pos_1);
    person.first_name = str.substr(delim_pos_1 + 1, delim_pos_2 - delim_pos_1 - 1);

    string date_str = str.substr(delim_pos_2 + 1);
    char delim2 = '.';
    int delim2_pos_1 = date_str.find(delim2);
    int delim2_pos_2 = date_str.find(delim2, delim2_pos_1 + 1);
    person.date_of_birth.day = date_str.substr(0, delim2_pos_1);
    person.date_of_birth.month = date_str.substr(delim2_pos_1 + 1, delim2_pos_2 - delim2_pos_1 - 1);
    person.date_of_birth.year = date_str.substr(delim2_pos_2 + 1);
    return person;
}


int main() {
    string source_path = "C:\\programming\\text2.txt";

    ifstream file;
    file.open(source_path);
    if (!file.is_open()) {
        cout << "File does not exist" << endl;
        return 0;
    }
    string line;
    vector<Person> persons;
    while (getline(file, line)) {
        persons.push_back(parsing(line));
    }
    file.close();

    ofstream file2;
    string result_file_path = "C:\\programming\\result_file.txt";
    file2.open(result_file_path);
    if (!file2.is_open()) {
        cout << "File does not exists" << endl;
        return 0;
    }
    for (auto person:persons) {
        file2 << "[\n" << "\t{\n" << "\t\tlast_name: " << person.last_name << "," << endl;
        file2 << "\t\tfirst_name: " << person.first_name << "," << endl;
        file2 << "\t\tdate_of_birth: " << "{" << endl;
        file2 << "\t\t\tyear: " << person.date_of_birth.year << "," << endl;
        file2 << "\t\t\tmonth: " << person.date_of_birth.month << "," << endl;
        file2 << "\t\t\tday: " << person.date_of_birth.day << "," << endl;
        file2 << "\t\t}" << endl << "\t}" << "\n]" << endl;
    }
}