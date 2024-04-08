#pragma once
#include <vector>
#include <memory>
#include <variant>
#include <string>
#include <iostream>

class TreeNode : public std::enable_shared_from_this<TreeNode>
{

public:
    // 数据类型，可以是 字符串 或者 字符串对
    using DataType = std::variant<std::string, std::pair<std::string, std::string>>;

    explicit TreeNode(std::string data);
    explicit TreeNode(std::pair<std::string, std::string> data);

    ~TreeNode();

    void printTree(const std::string &prefix = "", bool isLastSibling = true) const;

    // set
    void setData(DataType data);

    void setParent(std::weak_ptr<TreeNode> parent);

    void addChild(std::shared_ptr<TreeNode> child);

    void addChildWithParent(std::shared_ptr<TreeNode> child);

    // get
    std::shared_ptr<TreeNode> getTreeNode();

    DataType getData() const;

    std::vector<std::shared_ptr<TreeNode>> getChildren() const;

    std::weak_ptr<TreeNode> getParent() const;

private:
    // 数据成员
    DataType m_data;
    // 子节点的向量
    std::vector<std::shared_ptr<TreeNode>> m_children;
    // 父节点的弱引用
    std::weak_ptr<TreeNode> m_parent;
};