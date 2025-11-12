#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

struct Date {
    int year;
    int month;
    int day;
};

struct Person_info {
    string last_name;
    string first_name;
    Date date_of_birth;
};

char input_data(const string& path)
{
    ofstream file;
    file.open(path);
    char char_delim = '|';
    if (file.is_open())
    {
        string delim;
        cout << "Enter delimiter:" << endl;
        getline(cin, delim);
        char_delim = *delim.data();
        string user_input;
        while (user_input != "0")
        {
            cout << "Enter last name (0 - exit):" << endl;
            getline(cin, user_input);
            if (user_input == "0")
            {
                break;
            }
            file << user_input << delim;

            cout << "Enter first name (0 - exit):" << endl;
            getline(cin, user_input);
            if (user_input == "0")
            {
                break;
            }
            file << user_input << delim;

            cout << "Enter date (Ex: 00.00.0000) (0 - exit):" << endl;
            getline(cin, user_input);
            if (user_input == "0")
            {
                break;
            }
            file << user_input << endl;
        }
        return char_delim;
    }
    else
    {
        cerr << "File could not be written" << endl;
        return char_delim;
    }
    file.close();
}

vector<string> parse_file(const string& path) {
    ifstream file;
    file.open(path);

    vector<string> result;

    if (!file.is_open()) {
        cerr << "File could not be opened" << endl;
        return result;
    }

    string line;
    while (getline(file, line)) {
        result.push_back(line);
    }

    file.close();

    return result;
}

vector<string> split_to_3(string source, char delim)
{
    vector<string> result;

    auto temp = source;
    auto delim_pos = temp.find(delim);
    string first = temp.substr(0, delim_pos);
    temp = temp.substr(delim_pos + 1);
    delim_pos = temp.find(delim);

    string second = temp.substr(0, delim_pos);
    temp = temp.substr(delim_pos + 1);
    delim_pos = temp.find(delim);

    string third = temp.substr(0, delim_pos);

    result.push_back(first);
    result.push_back(second);
    result.push_back(third);

    return result;
}

vector<Person_info> organize_data(vector<string> source, char delim) {
    vector<Person_info> result;

    for (string item : source)
    {
        vector<string> item_split = split_to_3(item, delim);
        string last_name = item_split[0];
        string first_name = item_split[1];
        string date = item_split[2];

        vector<string> date_split = split_to_3(date, '.');

        Date date_of_birth;
        date_of_birth.year = stoi(date_split[2]);
        date_of_birth.month = stoi(date_split[1]);
        date_of_birth.day = stoi(date_split[0]);

        Person_info person_info;
        person_info.last_name = last_name;
        person_info.first_name = first_name;
        person_info.date_of_birth = date_of_birth;
        
        result.push_back(person_info);
    }

    return result;
}

void write_results(const string& path, vector<Person_info> source)
{
    ofstream file;
    file.open(path);
    if (file.is_open())
    {
        file << "[" << endl;
        for (int i = 0; i < source.size(); i++)
        {
            auto item = source[i];
            file << "  {" << endl;
            file << "\t\"last_name\": " << "\"" << item.last_name << "\"," << endl;
            file << "\t\"first_name\": " << "\"" << item.first_name << "\"," << endl;
            file << "\t\"date_of_birth\": " << "{" << endl;
            file << "\t  \"year\": " << item.date_of_birth.day << "," << endl;
            file << "\t  \"month\": " << item.date_of_birth.month << "," << endl;
            file << "\t  \"day\": " << item.date_of_birth.day << endl;
            file << "\t}" << endl;
            if (i == source.size()-1)
            {
                file << "  }" << endl;
            }
            else {
                file << "  }," << endl;
            }
        }
        file << "]" << endl;
    }
    else
    {
        cerr << "File could not be written" << endl;
        return;
    }
    file.close();
}

int main()
{
    string data_path = "C:\\Programming\\urok12_11\\person_data.txt";
    string result_path = "C:\\Programming\\urok12_11\\person_result.txt";

    char delim = input_data(data_path);
    vector<string> lines = parse_file(data_path);
    vector<Person_info> full_names = organize_data(lines, delim);
    write_results(result_path, full_names);
}