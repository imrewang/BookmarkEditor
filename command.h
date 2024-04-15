#pragma once
#include <sstream>
#include <iomanip>
#include "treenode.h"

class Command
{
public:
    virtual ~Command()
    {
    }
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual void redo() = 0;
};

class AddCommand : public Command
{
private:
    std::shared_ptr<TreeNode> receiver_; // 示例中用的是树节点
    std::shared_ptr<TreeNode> addNode_;
    std::string input_;

public:
    AddCommand(std::shared_ptr<TreeNode> receiver, std::string input) : receiver_(receiver), input_(input), addNode_(nullptr) {}
    void execute() override;
    void undo() override;
    void redo() override;
};

class DeleteCommand : public Command
{
private:
    std::shared_ptr<TreeNode> receiver_;
    std::shared_ptr<TreeNode> deleteNode_;
    std::string input_;

public:
    DeleteCommand(std::shared_ptr<TreeNode> receiver, std::string input) : receiver_(receiver), input_(input), deleteNode_(nullptr) {}
    void execute() override;
    void undo() override;
    void redo() override;
};
