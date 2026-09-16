#pragma once
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

    std::string status_to_string()
    {
        if (status == Status::TODO)
            return "TODO";
        else if (status == Status::DOING)
            return "DOING";
        else if (status == Status::DONE)
            return "DONE";
        
        return "UNKNOWN";
    }

    Status string_to_status(const std::string& string)
    {
        if (string == "TODO")
            return Status::TODO;
        else if (string == "DOING")
            return Status::DOING;
        else if (string == "DONE")
            return Status::DONE;

        return Status::TODO;
    }
};