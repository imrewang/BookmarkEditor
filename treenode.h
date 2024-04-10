#pragma once
#include <vector>
#include <memory>
#include <variant>
#include <string>
#include <iostream>
#include <functional>

class TreeNode : public std::enable_shared_from_this<TreeNode>
{

public:
    // 数据类型，可以是 字符串 或者 字符串对
    using DataType = std::variant<std::string, std::pair<std::string, std::string>>;

    explicit TreeNode(std::string data);
    explicit TreeNode(std::pair<std::string, std::string> data);

    ~TreeNode();

    void printTree(const std::string &prefix = "", bool isLastSibling = true) const;
    std::shared_ptr<TreeNode> findNodeByName(const std::string &name) const;
    // add delete
    std::shared_ptr<TreeNode> addNodebyNode(const std::shared_ptr<TreeNode> &nodeToAdd);
    std::shared_ptr<TreeNode> addNodebyName(const std::string &parentName, const DataType &data);
    std::shared_ptr<TreeNode> deleteNodebyNode(const std::shared_ptr<TreeNode> &nodeToDelete);
    std::shared_ptr<TreeNode> deleteNodebyName(const std::string &name);

    // set
    void setData(DataType data);
    void setParent(std::weak_ptr<TreeNode> parent);
    void addChild(std::shared_ptr<TreeNode> child);
    void addChildWithParent(std::shared_ptr<TreeNode> child);
    // get
    std::shared_ptr<TreeNode> getTreeNode();
    DataType getData() const;
    std::vector<std::shared_ptr<TreeNode>> &getChildren();
    std::weak_ptr<TreeNode> getParent() const;

private:
    // 数据成员
    DataType data_;
    // 子节点的向量
    std::vector<std::shared_ptr<TreeNode>> children_;
    // 父节点的弱引用
    std::weak_ptr<TreeNode> parent_;
};