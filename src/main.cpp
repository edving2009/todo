#include <print>
#include <stdint.h>
#include <vector>
#include <cstring>

#include "task.h"

void print_help()
{
    std::println("Helping");
}

int main(int argc, char* argv[])
{
    std::vector<Task> tasks;

    std::println("Argument count: {}\n", argc);
    for (int i = 0; i < argc; ++i) {
        std::println("argc[{}]", argv[i]);
    }
    std::println("");

    // If there is no arguments print task titles
    if (argc == 1) {
        if (tasks.size() == 0) {
            std::println("There is no tasks, add task using add task-name");
        }
        for (const auto& task : tasks) {
            std::println("{}", task.title);
        }
    }

    // Help
    if (argc == 2 && strcmp(argv[1], "help") == 0) {
        print_help();
    }

    // List tasks
    else if (argc == 2 && strcmp(argv[1], "list")) {
        for (const auto& task : tasks) {
            std::println("{}", task.title);
        }
    }
    else if (argc == 2 && strcmp(argv[1], "ls")) {
        for (const auto& task : tasks) {
            std::println("{}", task.title);
        }
    }
    else if (argc == 2 && strcmp(argv[1], "show")) {
        for (const auto& task : tasks) {
            std::println("{}", task.title);
        }
    }

    // Add/remove tasks
    else if (argc == 3 && strcmp(argv[1], "add") == 0) {
        std::string_view task_title = argv[2];
        Task task;
        task.title = task_title;
        tasks.push_back(task);
    }

    /*else {
        std::println("Unknown argument ->  use help");
    }*/

    return 0;
}