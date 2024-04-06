#include "treenode.h" // 包含类的头文件

// 构造函数
TreeNode::TreeNode(std::string data) : m_data(data), m_children(), m_parent() {}
TreeNode::TreeNode(std::pair<std::string, std::string> data) : m_data(data), m_children(), m_parent() {}

// 析构函数
TreeNode::~TreeNode() {}

// 设置节点的数据
void TreeNode::setData(DataType data)
{
    m_data = data;
}

// 设置父节点
void TreeNode::setParent(std::weak_ptr<TreeNode> parent)
{
    m_parent = parent;
}

// 添加子节点
void TreeNode::addChild(std::shared_ptr<TreeNode> child)
{
    m_children.push_back(child);
}

// 获取节点的数据
TreeNode::DataType TreeNode::getData() const
{
    return m_data;
}

// 获取子节点的向量
std::vector<std::shared_ptr<TreeNode>> TreeNode::getChildren() const
{
    return m_children;
}

// 获取父节点
std::weak_ptr<TreeNode> TreeNode::getParent() const
{
    return m_parent;
}
