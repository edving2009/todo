#pragma once
#include "task.h"

#include <vector>

namespace fs {
bool save_task(Task& task);
std::vector<Task> read_tasks();
Task read_task(const std::string& task_title);
}