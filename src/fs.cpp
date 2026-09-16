#include "fs.h"
#include <fstream>
#include <print>
#include <filesystem>

namespace fs {
bool save_task(Task& task)
{
    std::ofstream output(task.title + ".task");

    if (!output.is_open()) {
        std::println("Error when saving task to file");
        return false;
    }

    output << task.title << "\n";
    output << task.description << "\n";
    output << task.status_to_string();

    output.close();

    return true;
}

std::vector<Task> read_tasks()
{
    std::vector<Task> tasks;
    for (auto const& dir_entry : std::filesystem::directory_iterator{std::filesystem::current_path()})
        if (dir_entry.path().extension() == ".task") {
            Task task = read_task(dir_entry.path().stem());
            tasks.push_back(task);
        }
    return tasks;
}

Task read_task(const std::string& task_title)
{
    std::ifstream input(task_title + ".task");
    Task task;
    if (!input.is_open()) {
        std::println("Error when read task from file");
    }
    std::string task_status;
    if (input >> task.title >> task.description >> task_status) {
        task.status = task.string_to_status(task_status);
    }
    return task;
}
}