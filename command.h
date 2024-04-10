#pragma once

#include "treenode.h"

class Command
{
public:
    virtual ~Command()
    {
    }
    virtual void execute() const = 0;
    virtual void undo() = 0;
    virtual void redo() = 0;
};

class SimpleCommand : public Command
{
public:
    explicit SimpleCommand(std::string pay_load);
    void execute() const override;

private:
    std::string pay_load_;
};

class ComplexCommand : public Command
{
public:
    ComplexCommand(TreeNode *receiver, std::string a, std::string b);
    void execute() const override;

private:
    TreeNode *receiver_;
    std::string a_;
    std::string b_;
};