#include "command.h"

void AddCommand::execute()
{
    // Parsing the input command
    std::istringstream iss(input_);
    std::string cmd, title, parentName, at, link;

    iss >> cmd >> std::quoted(title);
    if (cmd == "add-title")
    {
        iss >> at >> std::quoted(parentName);
        if (parentName.empty())
        {
            addNode_ = receiver_->addNodebyName(std::get<std::string>(receiver_->getData()), title);
        }
        else
        {
            addNode_ = receiver_->addNodebyName(parentName, title);
        }
    }
    else if (cmd == "add-bookmark")
    {
        // 分割名称1和名称2
        size_t pos = title.find('@');
        std::string quotedName1 = title.substr(0, pos);
        std::string quotedName2 = title.substr(pos + 1);
        // 移除引号
        std::string name1 = quotedName1.substr(1, quotedName1.length() - 2);
        std::string name2 = quotedName2.substr(1, quotedName2.length() - 2);
        iss >> at >> std::quoted(parentName);
        addNode_ = receiver_->addNodebyName(parentName, std::make_pair(name1, name2));
    }
}

void AddCommand::undo()
{
    if (addNode_)
    {
        receiver_->deleteNodebyNode(addNode_);
    }
}

void AddCommand::redo()
{
    if (addNode_)
    {
        receiver_->addNodebyNode(addNode_);
    }
}

void DeleteCommand::execute()
{
    std::istringstream iss(input_);
    std::string cmd, title;
    iss >> cmd >> std::quoted(title);

    deleteNode_ = receiver_->deleteNodebyName(title);
}

void DeleteCommand::undo()
{
    if (deleteNode_)
    {
        receiver_->addNodebyNode(deleteNode_);
    }
}

void DeleteCommand::redo()
{
    if (deleteNode_)
    {
        receiver_->deleteNodebyNode(deleteNode_);
    }
}