#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <ctime>
#include <limits>

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

void save_db(std::string path, std::vector<std::vector<std::string>>& tasks)
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

void print_db(std::vector<std::vector<std::string>>& tasks)
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
    std::string string_date, string_time, status = "✘";
    char name[64], description[256];
    std::cout << "Write the name of your task: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.getline(name, 64);
    std::cout << "Write the description of your task:\n\t";
    std::cin.getline(description, 256);
    std::cout << "Write the deadline date or 0 if there is no deadline: ";
    std::cin >> string_date;
    std::cout << "Write the time by which you need to do the task\nor 0 if the task can be done at any time: ";
    std::cin >> string_time;
    std::vector<std::string> task{name, description, string_date, string_time, status};
    tasks.push_back(task);
}

void edit_task(std::vector<std::vector<std::string>>& tasks)
{

}

std::vector<std::vector<std::string>> deleted_tasks(std::vector<std::vector<std::string>> tasks)
{
    int task_num = 0;
    std::cout << "Write the number of the task you want to delete: ";
    std::cin >> task_num;
    std::vector<std::vector<std::string>> new_tasks;
    for (int i = 0; i < tasks.size(); ++i)
    {
        if (!(i == task_num-1))
        {
            new_tasks.push_back(tasks[i]);
        }
    }
    return new_tasks;
}

void switch_status(std::vector<std::vector<std::string>>& tasks)
{
    int task_num = 0;
    std::cout << "Write the number of the task for which you want to change the status of completion: ";
    std::cin >> task_num;
    if (tasks[task_num-1][4] == "✘")
    {
        tasks[task_num-1][4] = "✔";
    }
    else
    {
        tasks[task_num-1][4] = "✘";
    }
}

void sort_tasks(std::vector<std::vector<std::string>>& tasks)
{

}

int main()
{
    // loading data base
    std::vector<std::vector<std::string>> tasks;
    load_db("tasks.txt", tasks);
    
    //TODO switch to if-else!
    bool working = true;
    while (working)
    {
        print_db(tasks);
        std::cout << "Choose what you want to do:\n\t1. Add the task\n\t2. Edit task\n\t3. Switch the status of the task\n\t4. Delete task\n\t5. Sort tasks\nOr print 0 to exit.\n";
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
                save_db("tasks.txt", tasks);
                break;
            case '2':
                edit_task(tasks);
                save_db("tasks.txt", tasks);
                break;
            case '3':
                switch_status(tasks);
                save_db("tasks.txt", tasks);
                break;
            case '4':
                tasks = deleted_tasks(tasks);
                save_db("tasks.txt", tasks);
                break;
            case '5':
                sort_tasks(tasks);
                save_db("tasks.txt", tasks);
                break;
            default:
                std::cout << "Invalid input! Try again.\n";
                break;
        }
    }
}