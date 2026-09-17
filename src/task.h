#pragma once
#include <string>

enum class State
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
    State state;

    std::string state_to_string()
    {
        if (state == State::TODO)
            return "todo";
        else if (state == State::DOING)
            return "doing";
        else
            return "done";
    }

    State string_to_state(const std::string& string)
    {
        if (string == "todo")
            return State::TODO;
        else if (string == "doing")
            return State::DOING;
        else
            return State::DONE;
    }

    bool operator<(const Task& other) const
    {
        return state < other.state;
    }
};