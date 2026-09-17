#include "fs.h"
#include <filesystem>
#include <fstream>
#include <print>

namespace fs {
bool save_task(Task& task)
{
    std::ofstream output(tasks_directory() / (task.title + ".task"));

    if (!output.is_open()) {
        std::println("Error when saving task to file");
        return false;
    }

    output << task.title << "\n";
    output << task.description << "\n";
    output << task.state_to_string();

    output.close();

    return true;
}

std::vector<Task> read_tasks()
{
    std::vector<Task> tasks;
    for (auto const& dir_entry : std::filesystem::directory_iterator{tasks_directory()})
        if (dir_entry.path().extension() == ".task") {
            Task task = read_task(dir_entry.path().stem().string());
            tasks.push_back(task);
        }
    return tasks;
}

Task read_task(const std::string& task_title)
{
    std::ifstream input(tasks_directory() / (task_title + ".task"));
    Task task;

    if (!input.is_open()) {
        std::println("Error when reading task from file");
        return task;
    }

    std::string task_state;

    std::getline(input, task.title);
    std::getline(input, task.description);
    std::getline(input, task_state);

    task.state = task.string_to_state(task_state);

    return task;
}

std::filesystem::path find_root_directory()
{
    auto current = std::filesystem::current_path();

    while (true) {
        if (std::filesystem::is_directory(current / ".tasks")) {
            return current;
        }

        auto parent = current.parent_path();

        if (parent == current) {
            return {};
        }

        current = parent;
    }
}

std::filesystem::path tasks_directory()
{
    auto root = find_root_directory();

    if (!root.empty()) {
        return root / ".tasks";
    }

    auto tasks_dir = std::filesystem::current_path() / ".tasks";

    std::filesystem::create_directories(tasks_dir);

    return tasks_dir;
}
}