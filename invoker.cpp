#include "invoker.h"

Invoker::Invoker() {}

Invoker::~Invoker()
{
}

void Invoker::executeCommand(std::unique_ptr<Command> command)
{
    command->execute();
    undoStack_.push(std::move(command)); // 保存命令以便可以撤销
    while (!redoStack_.empty())
    {
        redoStack_.pop();
    }
}

void Invoker::undo()
{
    if (!undoStack_.empty())
    {
        std::unique_ptr<Command> command = std::move(undoStack_.top());
        undoStack_.pop();
        command->undo();
        redoStack_.push(std::move(command)); // 将命令移至重做栈
        std::cout << "撤销上一步操作" << std::endl;
    }
    else
    {
        std::cout << "undoStack 为空。 无法执行 undo 操作。" << std::endl;
    }
}

void Invoker::redo()
{
    if (!redoStack_.empty())
    {
        std::unique_ptr<Command> command = std::move(redoStack_.top());
        redoStack_.pop();
        command->redo();
        undoStack_.push(std::move(command)); // 重做后重新放回撤销栈
        std::cout << "重做上一步操作" << std::endl;
    }
    else
    {
        std::cout << "redoStack 为空。 无法执行 redo 操作。" << std::endl;
    }
}