#pragma once

#include "command.h"
#include <stack>
class Invoker
{
public:
    Invoker();
    ~Invoker();

    void executeCommand(std::unique_ptr<Command> command);
    void undo();
    void redo();

private:
    std::stack<std::unique_ptr<Command>> undoStack_;
    std::stack<std::unique_ptr<Command>> redoStack_;
};