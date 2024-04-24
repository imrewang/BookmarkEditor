#pragma once
#include <vector>
#include <memory>
#include <variant>
#include <string>
#include <iostream>
#include <functional>

class TreeNodeBase
{
public:
    // 数据类型，可以是 字符串 或者 字符串对
    using DataType = std::variant<std::string, std::pair<std::string, std::string>>;

    TreeNodeBase() = default; // 默认构造函数

    virtual ~TreeNodeBase() = default;

    virtual void printTree(const std::string &prefix = "", bool isLastSibling = true) const = 0;
    virtual std::shared_ptr<TreeNodeBase> findNodeByName(const std::string &name) const = 0;
    virtual std::shared_ptr<TreeNodeBase> addNodebyNode(const std::shared_ptr<TreeNodeBase> &nodeToAdd) = 0;
    virtual std::shared_ptr<TreeNodeBase> addNodebyName(const std::string &parentName, const DataType &data) = 0;
    virtual std::shared_ptr<TreeNodeBase> deleteNodebyNode(const std::shared_ptr<TreeNodeBase> &nodeToDelete) = 0;
    virtual std::shared_ptr<TreeNodeBase> deleteNodebyName(const std::string &name) = 0;

    // set
    virtual void setData(DataType data) = 0;
    virtual void setParent(std::weak_ptr<TreeNodeBase> parent) = 0;
    virtual void addChild(std::shared_ptr<TreeNodeBase> child) = 0;
    virtual void addChildWithParent(std::shared_ptr<TreeNodeBase> child) = 0;
    // get
    virtual std::shared_ptr<TreeNodeBase> getTreeNode() = 0;
    virtual DataType getData() const = 0;
    virtual std::vector<std::shared_ptr<TreeNodeBase>> &getChildren() = 0;
    virtual std::weak_ptr<TreeNodeBase> getParent() const = 0;

protected:
    // 数据成员
    DataType data_{};
    // 子节点的向量
    std::vector<std::shared_ptr<TreeNodeBase>> children_{};
    // 父节点的弱引用
    std::weak_ptr<TreeNodeBase> parent_{};
};
