#include <print>
#include <stdint.h>
#include <vector>
#include <algorithm>
#include <filesystem>

#include "task.h"
#include "fs.h"
#include "terminal.h"
#include "colors.h"

void print_help()
{
    std::println("{}states{}: todo, doing, done", MAGENTA, RESET);

    std::println("");
    std::println("{}version{}/{}v{} - prints version number", CYAN, RESET, CYAN, RESET);

    std::println("");
    std::println("{}add{}/{}a{} - adds a task", CYAN, RESET, CYAN, RESET);
    std::println("  usage: add task-name task description");

    std::println("");
    std::println("{}remove{}/{}rm{}/{}r{} - removes a task", CYAN, RESET, CYAN, RESET, CYAN, RESET);
    std::println("  usage: remove task-name");

    std::println("");
    std::println("{}list{}/{}ls{}/{}l{} - lists all tasks", CYAN, RESET, CYAN, RESET, CYAN, RESET);

    std::println("");
    std::println("{}change{}/{}c{} - changes task state", CYAN, RESET, CYAN, RESET);
    std::println("  usage: change task-name {}state{}", MAGENTA, RESET);
}

void print_version()
{
    std::println("todo version: 1.0.0");
}

int main(int argc, char* argv[])
{
    Terminal::init_terminal();

    std::vector<Task> tasks = fs::read_tasks();
    std::sort(tasks.begin(), tasks.end());

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
    else if (command == "version" || command == "v") {
        print_version();
        return 0;
    }

    // List tasks
    else if (command == "list" || command == "ls" || command == "l") {
        for (auto& task : tasks) {
            if (task.state == State::TODO) {
                std::println("{}{}{}: description:{} state:{}{}{}", RED, task.title, RESET, task.description, RED, task.state_to_string(), RESET);
            }
            else if (task.state == State::DOING) {
                std::println("{}{}{}: description:{} state:{}{}{}", YELLOW, task.title, RESET, task.description, YELLOW, task.state_to_string(), RESET);
            }
            else {
                std::println("{}{}{}: description:{} state:{}{}{}", GREEN, task.title, RESET, task.description, GREEN, task.state_to_string(), RESET);
            }
        }
        return 0;
    }

    // Add/remove tasks
    else if (command == "add" || command == "a") {
        if (argc < 3) {
            std::println("Need to specify task title");
            return 1;
        }
        else if (argc == 3) {
            std::string_view task_title = argv[2];
            Task task;
            task.title = task_title;
            task.state = State::TODO;
            fs::save_task(task);
            tasks.push_back(task);
            return 0;
        }
        std::string_view task_title = argv[2];
        std::string task_desc;
        for (int i = 3; i < argc; ++i) {
            task_desc += argv[i];
            if (i < argc - 1) {
                task_desc += " ";
            }
        }
        Task task;
        task.title = task_title;
        task.description = task_desc;
        task.state = State::TODO;
        fs::save_task(task);
        tasks.push_back(task);
        return 0;
    }
    else if (command == "remove" || command == "rm" || command == "r") {
        if (argc < 3) {
            std::println("Need to specify task title to delete");
            return 1;
        }
        auto it = std::find_if(tasks.begin(), tasks.end(), [&](const auto& task) {
            return task.title == argv[2];
        });
        if (it != tasks.end()) {
            std::filesystem::remove(fs::tasks_directory() / (it->title + ".task"));
            tasks.erase(it);
            return 0;
        }
        std::println("Didn't find any task with that name");
        return 1;
    }

    // TODO: Change Status
    else if (command == "change" || command == "c") {
        if (argc < 3) {
            std::println("Need to specify task name and state");
            return 1;
        }
        else if (argc < 4) {
            std::println("Need to also specify the state");
            return 1;
        }
        for (auto& task : tasks) {
            if (task.title == argv[2]) {
                task.state = task.string_to_state(argv[3]);
                fs::save_task(task);
                std::println("Changed '{}{}{}' to {}", CYAN, task.title, RESET, task.state_to_string());
                return 0;
            }
        }
        std::println("No task with that title");
    }

    else {
        std::println("Unknown argument -> use help");
    }

    return 0;
}