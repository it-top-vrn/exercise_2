#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;
struct Data {
    int year;
    int month;
    int day;
};
struct Person
{
    string last_name;
    string first_name;
    Data date_of_birth;
};
void split_name(const string& source, char delim, string& last_name, string& first_name) {
    auto pos = source.find(delim);
    last_name = source.substr(0, pos);
    first_name = source.substr(pos + 1);
}

void split_data(const string& source, char delim, int& year, int& month, int& day) {
    auto pos = source.find(delim);
    auto pos_rw = source.find_last_of(delim);
    day = stoi(source.substr(0, pos));
    month = stoi(source.substr(pos + 1, pos));
    year = stoi(source.substr(pos_rw + 1));
}
void split(string& lest, string& name, string& data, char delim){

    auto pos_rw = lest.find_last_of(delim);
    name = lest.substr(0, pos_rw);
    data = lest.substr(pos_rw + 1);
}
vector<Person>read_file(Person& person, const string& path, char delim_name, char delim_data) {
    ifstream file;
    string name;
    string data;
    file.open(path);
    vector<Person>result;
    string line;
    while (getline(file, line)) {
        split(line, name, data, delim_name);
        split_name(name, delim_name, person.last_name, person.first_name);
        split_data(data, delim_data, person.date_of_birth.year, person.date_of_birth.month, person.date_of_birth.day);
        result.push_back(person);
    }
    file.close();
    return result;
}
void give_info(vector<Person>& info) {
    for (Person person : info) {
        cout << "last_name:" << person.last_name << endl;
        cout << "first_name:" << person.first_name << endl;
        cout << "date_of_birth:\n{\n" <<"year:"<< person.date_of_birth.year << endl;
        cout << "month:" << person.date_of_birth.month << endl;
        cout << "day:" << person.date_of_birth.day << "\n}\n" <<endl;   
    }
}
int main()
{
    Person person;
    string request;
    char delim_data;
    char delim_name;
    string path;
    vector<Person>info;
    while (request != "0") {
        cout << "Would you like to read the file? |1-yes|0-not|"<< endl;
        cin >> request;
        if (request == "1")
        {
            cout<<"Provide a link to the file" << endl;
            cin >> path;
            cout << "Keep a name separation sign." << endl;
            cin >> delim_name;
            cout << "Keep a date separation sign." << endl;
            cin >> delim_data;
            vector<Person>info = read_file(person, path, delim_name, delim_data);
            give_info(info);
        }
    }
}