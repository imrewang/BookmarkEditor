#include "treedecorator.h"

TreeDecorator::TreeDecorator(std::shared_ptr<TreeNodeBase> component) : component_(std::move(component)) {}

void TreeDecorator::printTree(const std::string &prefix, bool isLastSibling) const
{
    component_->printTree(prefix, isLastSibling);
}

std::shared_ptr<TreeNodeBase> TreeDecorator::findNodeByName(const std::string &name) const
{
    return component_->findNodeByName(name);
}

std::shared_ptr<TreeNodeBase> TreeDecorator::addNodebyNode(const std::shared_ptr<TreeNodeBase> &nodeToAdd)
{
    return component_->addNodebyNode(nodeToAdd);
}

std::shared_ptr<TreeNodeBase> TreeDecorator::addNodebyName(const std::string &parentName, const DataType &data)
{
    return component_->addNodebyName(parentName, data);
}

std::shared_ptr<TreeNodeBase> TreeDecorator::deleteNodebyNode(const std::shared_ptr<TreeNodeBase> &nodeToDelete)
{
    return component_->deleteNodebyNode(nodeToDelete);
}

std::shared_ptr<TreeNodeBase> TreeDecorator::deleteNodebyName(const std::string &name)
{
    return component_->deleteNodebyName(name);
}

void TreeDecorator::setData(DataType data)
{
    component_->setData(data);
}

void TreeDecorator::setParent(std::weak_ptr<TreeNodeBase> parent)
{
    component_->setParent(parent);
}

void TreeDecorator::addChild(std::shared_ptr<TreeNodeBase> child)
{
    component_->addChild(child);
}

void TreeDecorator::addChildWithParent(std::shared_ptr<TreeNodeBase> child)
{
    component_->addChildWithParent(child);
}

std::shared_ptr<TreeNodeBase> TreeDecorator::getTreeNode()
{
    return component_->getTreeNode();
}

TreeDecorator::DataType TreeDecorator::getData() const
{
    return component_->getData();
}

std::vector<std::shared_ptr<TreeNodeBase>> &TreeDecorator::getChildren()
{
    return component_->getChildren();
}

std::weak_ptr<TreeNodeBase> TreeDecorator::getParent() const
{
    return component_->getParent();
}