#pragma once
#include "task.h"

#include <vector>
#include <filesystem>

namespace fs {
bool save_task(Task& task);
std::vector<Task> read_tasks();
Task read_task(const std::string& task_title);
std::filesystem::path find_root_directory();
std::filesystem::path tasks_directory();
}