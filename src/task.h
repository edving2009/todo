#include <string>

enum class Status
{
    TODO,
    DOING,
    DONE
};

class Task
{
  public:
    std::string title;
    std::string description;
    Status status;
};