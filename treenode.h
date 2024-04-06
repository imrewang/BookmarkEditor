#pragma once
#include <vector>
#include <memory>
#include <variant>
#include <string>

class TreeNode
{
public:
    // 数据类型，可以是 字符串 或者 字符串对
    using DataType = std::variant<std::string, std::pair<std::string, std::string>>;

    // 构造函数，接受数据作为参数
    TreeNode(std::string data);
    TreeNode(std::pair<std::string, std::string> data);

    // 析构函数
    ~TreeNode();

    // 设置节点的数据
    void setData(DataType data);

    // 设置父节点
    void setParent(std::weak_ptr<TreeNode> parent);

    // 添加子节点
    void addChild(std::shared_ptr<TreeNode> child);

    // 获取节点的数据
    DataType getData() const;

    // 获取子节点的向量
    std::vector<std::shared_ptr<TreeNode>> getChildren() const;

    // 获取父节点
    std::weak_ptr<TreeNode> getParent() const;

private:
    // 数据成员
    DataType m_data;
    // 子节点的向量
    std::vector<std::shared_ptr<TreeNode>> m_children;
    // 父节点的弱引用
    std::weak_ptr<TreeNode> m_parent;
};