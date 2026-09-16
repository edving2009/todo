#include <print>
#include <stdint.h>
#include <vector>
#include <algorithm>
#include <filesystem>

#include "task.h"
#include "fs.h"

void print_help()
{
    std::println("Helping");
}

void print_version()
{
    std::println("todo version: 1.0.0");
}

int main(int argc, char* argv[])
{
    std::vector<Task> tasks;

    std::println("Argument count: {}\n", argc);
    for (int i = 0; i < argc; ++i) {
        std::println("argc[{}]", argv[i]);
    }
    std::println("");

    tasks = fs::read_tasks();

    // If there is no arguments print help
    if (argc < 2) {
        print_help();
        return 1;
    }

    std::string command = std::string(argv[1]);

    // Help
    if (command == "help") {
        print_help();
        return 0;
    }

    // Version
    else if (command == "version") {
        print_version();
        return 0;
    }

    // List tasks
    // TODO: Display them using colors & sort them -> 1st todo, 2nd doing, 3rd done
    else if (command == "list") {
        for (const auto& task : tasks) {
            std::println("{}", task.title);
        }
        return 0;
    }

    // Add/remove tasks
    else if (command == "add") {
        if (argc == 3) {
            std::string_view task_title = argv[2];
            Task task;
            task.title = task_title;
            task.status = Status::TODO;
            fs::save_task(task);
            tasks.push_back(task);
            return 0;
        }
        else if (argc == 4) {
            std::string_view task_title = argv[2];
            std::string_view task_desc = argv[3];
            Task task;
            task.title = task_title;
            task.description = task_desc;
            task.status = Status::TODO;
            fs::save_task(task);
            tasks.push_back(task);
            return 0;
        }
        else {
            std::println("Need to specify task title");
            return 1;
        }
    }
    else if (command == "remove" || command == "rm") {
        if (argc < 3) {
            std::println("Need to specify task title to delete");
            return 1;
        }
        auto it = std::find_if(tasks.begin(), tasks.end(), [&](const auto& task) {
            return task.title == argv[2];
        });
        if (it != tasks.end()) {
            std::filesystem::remove(it->title + ".task");
            tasks.erase(it);
            return 0;
        }
        std::println("Didn't find any task with that name");
        return 1;
    }

    // TODO: Display Status

    // TODO: Change Status

    else {
        std::println("Unknown argument ->  use help");
    }

    return 0;
}