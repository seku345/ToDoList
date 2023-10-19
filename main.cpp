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

void save_db(std::string path, std::vector<std::vector<std::string>> tasks)
{
    std::fstream file(path, std::ios_base::out | std::ios_base::trunc);
    std::string export_line = "";
    for (std::vector<std::string> line : tasks)
    {
        for (std::string part : line)
        {
            export_line += part + "\t";
        }
        export_line += '\n';
    }
    file << export_line;
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
    std::cout << "Write the number of the task you want to edit: ";
    int task_num = 0; //TODO VALIDATION
    std::cin >> task_num;
    std::cout << "Select what you want to edit:\n\t1. Name\n\t2. Description\n\t3. Date deadline\n\t4. Time deadline\n";
    std::string choice;
    std::cin >> choice;
    if (choice == "1")
    {
        std::cout << "Enter a new name for the " << task_num << " task: ";
        char name[64];
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.getline(name, 64);
        tasks[task_num-1][0] = name;
    }
    else if (choice == "2")
    {
        std::cout << "Enter a new description for the " << task_num << " task:\n\t";
        char description[256];
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.getline(description, 256);
        tasks[task_num-1][1] = description;
    }
    else if (choice == "3")
    {
        std::cout << "Enter a new date deadline for the " << task_num << " task: ";
        std::string date;
        std::cin >> date;
        tasks[task_num-1][2] = date;
    }
    else if (choice == "4")
    {
        std::cout << "Enter a new time deadline for the " << task_num << " task: ";
        std::string time;
        std::cin >> time;
        tasks[task_num-1][3] = time;
    }
    else
    {
        std::cout << "Invalid input!";
    }
}

void delete_task(std::vector<std::vector<std::string>>& tasks)
{
    int task_num = 0;
    std::cout << "Write the number of the task you want to delete: ";
    std::cin >> task_num;
    tasks.erase(tasks.begin() + task_num - 1, tasks.begin() + task_num);
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
    
    bool working = true;
    while (working)
    {
        // main menu
        print_db(tasks);
        std::cout << "Choose what you want to do:\n\t1. Add the task\n\t2. Edit task\n\t3. Switch the status of the task\n\t4. Delete task\n\t5. Sort tasks\nOr print 0 to exit.\n";
        std::string mode;
        std::cin >> mode;
        // exit & saving
        if (mode == "0")
        {
            working = false;
            save_db("tasks.txt", tasks);
            break;
        }
        // adding task
        else if (mode == "1")
        {
            add_task(tasks);
            save_db("tasks.txt", tasks);
        }
        // editing task
        else if (mode == "2")
        {
            edit_task(tasks);
            save_db("tasks.txt", tasks);
        }
        // completing task
        else if (mode == "3")
        {
            switch_status(tasks);
            save_db("tasks.txt", tasks);
        }
        // deleting task
        else if (mode == "4")
        {
            delete_task(tasks);
            save_db("tasks.txt", tasks);
        }
        // sorting tasks
        else if (mode == "5")
        {
            sort_tasks(tasks);
            save_db("tasks.txt", tasks);
        }
        // validation
        else
        {
            std::cout << "Invalid input! Try again.\n";
        }
    }
}