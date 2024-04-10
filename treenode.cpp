#include "treenode.h" // 包含类的头文件

TreeNode::TreeNode(std::string data) : data_(data), children_(), parent_()
{
    std::cout << "TreeNode constructed with header data" << std::endl;
}
TreeNode::TreeNode(std::pair<std::string, std::string> data) : data_(data), children_(), parent_()
{
    std::cout << "TreeNode constructed with bookmark data" << std::endl;
}

TreeNode::~TreeNode()
{
    std::cout << "TreeNode destructed :";
    if (std::holds_alternative<std::string>(data_))
    {
        std::cout << std::get<std::string>(data_) << std::endl;
    }
    else if (std::holds_alternative<std::pair<std::string, std::string>>(data_))
    {
        auto linkData = std::get<std::pair<std::string, std::string>>(data_);
        std::cout << "[" << linkData.first << "]" << std::endl;
    }
}

void TreeNode::printTree(const std::string &prefix, bool isLastSibling) const
{
    std::cout << prefix;
    std::cout << (isLastSibling ? "└── " : "├── ");

    // 输出节点的数据
    if (std::holds_alternative<std::string>(data_))
    {
        std::cout << std::get<std::string>(data_) << std::endl;
    }
    else if (std::holds_alternative<std::pair<std::string, std::string>>(data_))
    {
        auto linkData = std::get<std::pair<std::string, std::string>>(data_);
        std::cout << "[" << linkData.first << "]" << std::endl;
    }

    // 递归打印子节点
    for (size_t i = 0; i < children_.size(); ++i)
    {
        bool isLastChild = (i == children_.size() - 1);
        children_[i]->printTree(prefix + (isLastSibling ? "    " : "│   "), isLastChild);
    }
}

std::shared_ptr<TreeNode> TreeNode::findNodeByName(const std::string &name) const
{
    std::shared_ptr<TreeNode> result;

    std::function<bool(const std::shared_ptr<TreeNode> &, const std::string &)> search =
        [&](const std::shared_ptr<TreeNode> &node, const std::string &target) -> bool
    {
        std::visit([&](const auto &data)
                   {
                       if constexpr (std::is_same_v<std::decay_t<decltype(data)>, std::string>)
                       {
                           if (data == target)
                           {
                               result = node;
                               return true; // 返回true表示找到结果
                           }
                       }
                       else if constexpr (std::is_same_v<std::decay_t<decltype(data)>, std::pair<std::string, std::string>>)
                       {
                           auto linkData = data;
                           if (linkData.first == target)
                           {
                               result = node;
                               return true; // 返回true表示找到结果
                           }
                       }
                       return false; // 默认情况下返回false
                   },
                   node->getData());

        if (result)
        { // 如果已经找到结果，则直接退出
            return true;
        }

        for (const auto &child : node->getChildren())
        {
            if (search(child, target))
            {
                return true; // 如果在子节点中找到结果，则直接退出
            }
        }

        return false; // 如果没有找到结果，则返回false
    };

    search(std::const_pointer_cast<TreeNode>(shared_from_this()), name);
    return result;
}

std::shared_ptr<TreeNode> TreeNode::deleteNodebyNode(const std::shared_ptr<TreeNode> &nodeToDelete)
{
    std::shared_ptr<TreeNode> deletedNode;
    if (nodeToDelete)
    {
        auto parentNode = nodeToDelete->getParent().lock();
        if (parentNode)
        {
            auto &children = parentNode->getChildren();
            auto it = std::find(children.begin(), children.end(), nodeToDelete);
            if (it != children.end())
            {
                deletedNode = *it;
                children.erase(it);
            }
        }
    }
    else
    {
        std::cout << "Node to delete not found." << std::endl;
    }
    return deletedNode;
}

std::shared_ptr<TreeNode> TreeNode::deleteNodebyName(const std::string &name)
{
    std::shared_ptr<TreeNode> deletedNode;
    auto nodeToDelete = findNodeByName(name);
    if (nodeToDelete)
    {
        deletedNode = deleteNodebyNode(nodeToDelete);
    }
    else
    {
        std::cout << "Node to delete not found by name." << std::endl;
    }
    return deletedNode;
}

// set
void TreeNode::setData(DataType data)
{
    data_ = data;
}

void TreeNode::setParent(std::weak_ptr<TreeNode> parent)
{
    parent_ = parent;
}

void TreeNode::addChild(std::shared_ptr<TreeNode> child)
{
    children_.push_back(child);
}

void TreeNode::addChildWithParent(std::shared_ptr<TreeNode> child)
{
    children_.push_back(child);
    child->parent_ = this->shared_from_this(); // 设置子节点的父节点为当前节点
}

// get
std::shared_ptr<TreeNode> TreeNode::getTreeNode()
{
    return shared_from_this();
}

TreeNode::DataType TreeNode::getData() const
{
    return data_;
}

std::vector<std::shared_ptr<TreeNode>> &TreeNode::getChildren()
{
    return children_;
}

std::weak_ptr<TreeNode> TreeNode::getParent() const
{
    return parent_;
}