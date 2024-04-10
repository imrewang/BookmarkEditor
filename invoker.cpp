#include "invoker.h"

Invoker::Invoker() {}

Invoker::~Invoker()
{
    while (!undoStack.empty())
    {
        delete undoStack.top();
        undoStack.pop();
    }
    while (!redoStack.empty())
    {
        delete redoStack.top();
        redoStack.pop();
    }
}

void Invoker::executeCommand(Command *command)
{
    // TODO 1.只加入adddelete 2.clear redo stack
    command->execute();
    undoStack.push(command);
}

void Invoker::undo()
{
    if (!undoStack.empty())
    {
        Command *command = undoStack.top();
        undoStack.pop();
        command->undo();
        redoStack.push(command);
    }
    else
    {
        std::cout << "Nothing to undo." << std::endl;
    }
}

void Invoker::redo()
{
    if (!redoStack.empty())
    {
        Command *command = redoStack.top();
        redoStack.pop();
        command->redo();
        undoStack.push(command);
    }
    else
    {
        std::cout << "Nothing to redo." << std::endl;
    }
}