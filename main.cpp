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
    std::cout << "Here are your tasks:\n";
    for (int i = 0; i < tasks.size(); ++i)
    {
        std::cout << i+1 << ") ";
        for (std::string a : tasks[i])
        {
            std::cout << a << ' ';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

void add_task(std::vector<std::vector<std::string>>& tasks)
{
    std::string name, description, string_date, string_time, status = "✘";
    std::cout << "Write the name of your task: ";
    std::cin >> name;
    std::cout << "Write the description of your task:\n\t";
    std::cin >> description;
    std::cout << "Write the deadline date or 0 if there is no deadline: ";
    std::cin >> string_date;
    std::cout << "Write the time by which you need to do the task\nor 0 if the task can be done at any time: ";
    std::cin >> string_time;
    std::vector<std::string> task{name, description, string_date, string_time, status};
    tasks.push_back(task);
}

void save_db(std::string path, std::vector<std::vector<std::string>> tasks)
{
    std::fstream file(path);
    for (std::vector<std::string> line : tasks)
    {
        std::string export_line = "";
        for (std::string part : line)
        {
            export_line += part + "\t";
        }
        export_line += '\n';
        file << export_line;
    }
    file.close();
}

int main()
{
    // loading data base
    std::vector<std::vector<std::string>> tasks;
    load_db("tasks.txt", tasks);

    bool working = true;
    while (working)
    {
        print_db(tasks);
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
                add_task(tasks);
                break;
            case '2':

                break;
            case '3':
                break;
            default:
                std::cout << "Invalid input! Try again.\n";
                break;
        }
    }
}