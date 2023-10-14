#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <ctime>

std::vector<std::string> split(std::string string, char delimiter)
{
    std::vector<std::string> list_of_strings;
    std::string temp = "";
    for (char c : string)
    {
        if (c != delimiter)
        {
            temp += c;
        }
        else
        {
            list_of_strings.push_back(temp);
            temp = "";
        }
    }
    if (temp != "") list_of_strings.push_back(temp);
    return list_of_strings;
}

void load_db(std::string path, std::vector<std::vector<std::string>>& tasks)
{
    std::fstream file(path);
    std::string line;
    while (getline(file, line))
    {
        std::vector<std::string> separated_line = split(line, '\t');
        tasks.push_back(separated_line);
    }
    file.close();
    
}

void print_db(std::vector<std::vector<std::string>> tasks)
{
    for (int i = 0; i < tasks.size(); ++i)
    {
        std::cout << i+1 << ") ";
        for (std::string a : tasks[i])
        {
            std::cout << a << ' ';
        }
        std::cout << '\n';
    }
}

void save_db(std::string path, std::vector<std::vector<std::string>> tasks)
{

}

int main()
{
    // loading data base
    std::vector<std::vector<std::string>> tasks;
    load_db("tasks.txt", tasks);

    bool working = true;
    while (working)
    {
        std::cout << "Choose what you want to do:\n\t1. Add task\n\t2. Edit task\n\t3. View tasks\nOr print 0 to exit.\n";
        char mode;
        std::cin >> mode;
        switch (mode)
        {
            case '0':
                working = false;
                save_db("tasks.txt", tasks);
                break;
            case '1':
                
                break;
            case '2':

                break;
            case '3':
                print_db(tasks);
                break;
            default:
                std::cout << "Invalid input! Try again.\n";
                break;
        }
    }
}