#include "readcountdecorator.h"

ReadCountDecorator::ReadCountDecorator(std::shared_ptr<TreeNodeBase> component) : TreeDecorator(std::move(component)) {}

void ReadCountDecorator::printTree(const std::string &prefix, bool isLastSibling) const
{
    std::cout << prefix;
    std::cout << (isLastSibling ? "└── " : "├── ");

    // 输出节点的数据
    if (std::holds_alternative<std::string>(component_->getData()))
    {
        std::string nodeData = std::get<std::string>(component_->getData());
        if (readCount_ > 0)
        {
            std::cout << "[*" << nodeData << "(" << readCount_ << ")]" << std::endl;
        }
        else
        {
            std::cout << nodeData << std::endl;
        }
    }
    else if (std::holds_alternative<std::pair<std::string, std::string>>(component_->getData()))
    {
        auto linkData = std::get<std::pair<std::string, std::string>>(component_->getData());
        if (readCount_ > 0)
        {
            std::cout << "[*" << linkData.first << "(" << readCount_ << ")]" << std::endl;
        }
        else
        {
            std::cout << "[" << linkData.first << "]" << std::endl;
        }
    }

    // 递归打印子节点
    for (size_t i = 0; i < component_->getChildren().size(); ++i)
    {
        bool isLastChild = (i == component_->getChildren().size() - 1);
        std::string newPrefix = prefix + (isLastSibling ? "    " : "│   ");
        std::shared_ptr<TreeNodeBase> child = component_->getChildren()[i];
        child->printTree(newPrefix, isLastChild);
    }
}

void ReadCountDecorator::read()
{
    readCount_++;
}

void ReadCountDecorator::setReadCount(const int readCount)
{
    readCount_ = readCount;
}

int ReadCountDecorator::getReadCount() const
{
    return readCount_;
}