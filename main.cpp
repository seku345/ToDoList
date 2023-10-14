#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <ctime>

void load_db(std::string path, std::vector<std::array<std::string, 3>>& tasks)
{
    std::fstream file;
    file.open(path);
    file << "123\n";
    file.close();
    
}

int main()
{
    // loading data base
    std::vector<std::array<std::string, 3>> tasks;
    load_db("tasks.txt", tasks);
    for (std::array<std::string, 3> x : tasks)
    {
        for (std::string a : x)
        {
            std::cout << a << ' ';
        }
        std::cout << '\n';
    }
}