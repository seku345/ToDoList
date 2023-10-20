#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <limits>
#include <algorithm>
#include <windows.h>

void switch_color(std::string color)
{
    int color_code = 15;
    if (color == "red") color_code = 12;
    else if (color == "yellow") color_code = 14;
    else if (color == "green") color_code = 10;
    else if (color == "blue") color_code = 9;
    else if (color == "black") color_code = 16;
    else if (color == "white") color_code = 15;
    else color_code = 15;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color_code);
}

int len_of_int(int n)
{
    int k = 0;
    while (n > 0)
    {
        n /= 10;
        k++;
    }
    return k;
}

std::string multi_str(std::string s, int n)
{
    std::string r = "";
    for (int i = 0; i < n; ++i)
    {
        r += s;
    }
    return r;
}

int max_length(std::vector<std::string> a)
{
    int max = 0;
    for (std::string s : a)
    {
        if (s.length() > max)
        {
            max = s.length();
        }
    }
    return max;
}

std::vector<std::string> line_from_column(int i, std::vector<std::vector<std::string>> m)
{
    std::vector<std::string> a;
    for (std::vector<std::string> line : m)
    {
        a.push_back(line[i]);
    }
    return a;
}

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

bool is_deadline_passed(std::string deadline_date, std::string deadline_time, bool& is_today)
{
    // getting current time
    time_t current_time;
    time(&current_time);
    struct tm* time_now = localtime(&current_time);

    // checking cases
    if ((deadline_date == "0") && (deadline_time == "0"))
    {
        return false;
    }
    else if ((deadline_date == "0") && (deadline_time != "0"))
    {
        deadline_date = std::to_string(time_now->tm_year + 1900) + "." + std::to_string(time_now->tm_mon + 1) + "." + std::to_string(time_now->tm_mday);
    }

    int year, month, day, hour, minute;
    if (sscanf(deadline_date.c_str(), "%d.%d.%d", &year, &month, &day) == 3)
    {
        if (sscanf(deadline_time.c_str(), "%d:%d", &hour, &minute) == 2)
        {
            struct tm deadline = {0};
            deadline.tm_year = year - 1900;
            deadline.tm_mon = month - 1;
            deadline.tm_mday = day;
            deadline.tm_hour = hour;
            deadline.tm_min = minute;
            deadline.tm_sec = 0;

            if (std::to_string(time_now->tm_year + 1900) + "." + std::to_string(time_now->tm_mon + 1) + "." + std::to_string(time_now->tm_mday) == deadline_date)
            {
                is_today = true;
                return false;
            }
            else if (mktime(&deadline) < mktime(time_now))
            {
                return true;
            }
        }
    }
    return false;
}

void print_db(std::vector<std::vector<std::string>> tasks)
{
    int max_num_len = len_of_int(int(tasks.size()));
    std::string num_shift = multi_str(" ", max_num_len + 2);
    std::string name_shift = multi_str(" ", std::max(4, max_length(line_from_column(0, tasks))) - 4 + 2);
    std::string description_shift = multi_str(" ", std::max(11, max_length(line_from_column(1, tasks))) - 11 + 2);
    std::string date_shift = multi_str(" ", std::max(13, max_length(line_from_column(2, tasks))) - 13 + 2);
    std::string time_shift = multi_str(" ", std::max(13, max_length(line_from_column(3, tasks))) - 13 + 2);

    std::cout << "Here are your tasks:\n";
    switch_color("yellow");
    std::cout << "N" << num_shift << "Name" << name_shift << "Description" << description_shift << "Date deadline" << date_shift << "Time deadline" << time_shift <<"Status\n";
    switch_color("white");
    for (int i = 0; i < tasks.size(); ++i)
    {
        num_shift = multi_str("0", max_num_len - len_of_int(i+1));
        switch_color("blue");
        std::cout << num_shift << i+1 << ")  ";
        switch_color("white");
        name_shift = multi_str(" ", std::max(4, max_length(line_from_column(0, tasks))) - int(tasks[i][0].length()) + 2);
        description_shift = multi_str(" ", std::max(11, max_length(line_from_column(1, tasks))) - int(tasks[i][1].length()) + 2);
        date_shift = multi_str(" ", std::max(13, max_length(line_from_column(2, tasks))) - int(tasks[i][2].length()) + 2);
        time_shift = multi_str(" ", std::max(13, max_length(line_from_column(3, tasks))) - int(tasks[i][3].length()) + 2);
        for (auto a = tasks[i].begin(); a != tasks[i].end(); ++a)
        {
            if (*a == "✔") switch_color("green");
            if (*a == "✘") switch_color("red");
            bool is_today = false;
            if (a == tasks[i].begin() + 2)
            {
                if (is_deadline_passed(tasks[i][2], tasks[i][3], is_today))
                {
                    if (!is_today) switch_color("red");
                    else if (*a != "0") switch_color("yellow");
                }
                else if (is_today && *a != "0") switch_color("yellow");
            }
            if (a == tasks[i].begin() + 3)
            {
                if (is_deadline_passed(tasks[i][2], tasks[i][3], is_today))
                {
                    switch_color("red");
                }
            }
            std::cout << *a;
            if (a == tasks[i].begin()) // name
            {
                std::cout << name_shift;
            }
            else if (a == (tasks[i].begin() + 1)) // description
            {
                std::cout << description_shift;
            }
            else if (a == (tasks[i].begin() + 2)) // date
            {
                std::cout << date_shift;
            }
            else if (a == (tasks[i].begin() + 3)) // time
            {
                std::cout << time_shift;
            }
            switch_color("white");
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
    std::pair<std::string, std::string> how_to_sort;
    std::cout << "Choose how you want to sort your tasks:\n\t1. By alpha\n\t2. By execution\n\t3. By deadline\nAlso print 1 if you want to sort in increasing order or -1 in decreasing order: ";
    std::cin >> how_to_sort.first >> how_to_sort.second;
    if (((how_to_sort.first != "1") && (how_to_sort.first != "2") && (how_to_sort.first != "3")) ||
        ((how_to_sort.second != "1") && (how_to_sort.second != "-1")))
    {
        std::cout << "Invalid input!\n";
        return;
    }
    std::sort(tasks.begin(), tasks.end(),
    [how_to_sort](std::vector<std::string> a, std::vector<std::string> b)
    {
        if ((how_to_sort.first == "1") && (how_to_sort.second == "1"))
        {
            return a[0] < b[0];
        }
        else if ((how_to_sort.first == "1") && (how_to_sort.second == "-1"))
        {
            return a[0] > b[0];
        }
        else if ((how_to_sort.first == "2") && (how_to_sort.second == "1"))
        {
            return ((a[4] == "✘") && (b[4] == "✔"));
        }
        else if ((how_to_sort.first == "2") && (how_to_sort.second == "-1"))
        {
            return ((a[4] == "✔") && (b[4] == "✘"));
        }
        else if ((how_to_sort.first == "3") && (how_to_sort.second == "1"))
        {

        }
        else if ((how_to_sort.first == "3") && (how_to_sort.second == "-1"))
        {

        }
    });
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
        switch_color("white");
        print_db(tasks);
        std::cout << "Choose what you want to do:\n\t1. Add the task\n\t2. Edit task\n\t3. Switch the status of the task\n\t4. Delete task\n\t5. Sort tasks\nOr print 0 to exit.\n";
        std::string mode;
        std::cin >> mode;
        // exit & saving
        if (mode == "0")
        {
            working = false;
            save_db("tasks.txt", tasks);
            switch_color("white");
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