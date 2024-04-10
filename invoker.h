#pragma once

#include "command.h"
#include <stack>
class Invoker
{
public:
    Invoker();
    ~Invoker();

    void executeCommand(Command *command);
    void undo();
    void redo();

private:
    std::stack<Command *> undoStack;
    std::stack<Command *> redoStack;
};