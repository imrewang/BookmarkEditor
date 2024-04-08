#include "treenode.h" // 包含类的头文件

TreeNode::TreeNode(std::string data) : m_data(data), m_children(), m_parent()
{
    std::cout << "TreeNode constructed with header data" << std::endl;
}
TreeNode::TreeNode(std::pair<std::string, std::string> data) : m_data(data), m_children(), m_parent()
{
    std::cout << "TreeNode constructed with bookmark data" << std::endl;
}

TreeNode::~TreeNode()
{
    std::cout << "TreeNode destructed :";
    if (std::holds_alternative<std::string>(m_data))
    {
        std::cout << std::get<std::string>(m_data) << std::endl;
    }
    else if (std::holds_alternative<std::pair<std::string, std::string>>(m_data))
    {
        auto linkData = std::get<std::pair<std::string, std::string>>(m_data);
        std::cout << "[" << linkData.first << "]" << std::endl;
    }
}

void TreeNode::printTree(const std::string &prefix, bool isLastSibling) const
{
    std::cout << prefix;
    std::cout << (isLastSibling ? "└── " : "├── ");

    // 输出节点的数据
    if (std::holds_alternative<std::string>(m_data))
    {
        std::cout << std::get<std::string>(m_data) << std::endl;
    }
    else if (std::holds_alternative<std::pair<std::string, std::string>>(m_data))
    {
        auto linkData = std::get<std::pair<std::string, std::string>>(m_data);
        std::cout << "[" << linkData.first << "]" << std::endl;
    }

    // 递归打印子节点
    for (size_t i = 0; i < m_children.size(); ++i)
    {
        bool isLastChild = (i == m_children.size() - 1);
        m_children[i]->printTree(prefix + (isLastSibling ? "    " : "│   "), isLastChild);
    }
}

// set
void TreeNode::setData(DataType data)
{
    m_data = data;
}

void TreeNode::setParent(std::weak_ptr<TreeNode> parent)
{
    m_parent = parent;
}

void TreeNode::addChild(std::shared_ptr<TreeNode> child)
{
    m_children.push_back(child);
}

void TreeNode::addChildWithParent(std::shared_ptr<TreeNode> child)
{
    m_children.push_back(child);
    child->m_parent = this->shared_from_this(); // 设置子节点的父节点为当前节点
}

// get
std::shared_ptr<TreeNode> TreeNode::getTreeNode()
{
    return shared_from_this();
}

TreeNode::DataType TreeNode::getData() const
{
    return m_data;
}

std::vector<std::shared_ptr<TreeNode>> TreeNode::getChildren() const
{
    return m_children;
}

std::weak_ptr<TreeNode> TreeNode::getParent() const
{
    return m_parent;
}