#include "treenode.h" // 包含类的头文件

<<<<<<< HEAD
TreeNode::TreeNode(std::string data) : data_(data), children_(), parent_(), readCount_(0)
=======
TreeNode::TreeNode(std::string data)
>>>>>>> b46e899bf1d9b9eece69512035f0d950ff9c740c
{
    this->setData(data);
    std::cout << "TreeNode constructed with header data" << std::endl;
}
<<<<<<< HEAD
TreeNode::TreeNode(std::pair<std::string, std::string> data) : data_(data), children_(), parent_(), readCount_(0)
=======
TreeNode::TreeNode(std::pair<std::string, std::string> data)
>>>>>>> b46e899bf1d9b9eece69512035f0d950ff9c740c
{
    this->setData(data);
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

std::shared_ptr<TreeNodeBase> TreeNode::createNode(const DataType &data)
{
    if (std::holds_alternative<std::string>(data))
    {
        return std::make_shared<TreeNode>(std::get<std::string>(data));
    }
    else if (std::holds_alternative<std::pair<std::string, std::string>>(data))
    {
        return std::make_shared<TreeNode>(std::get<std::pair<std::string, std::string>>(data));
    }
    // 如果数据类型不匹配，返回空指针
    std::cout << "Unsupported data type for parent node." << std::endl;
    return nullptr;
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
    for (size_t i = 0; i < children_.size(); ++i)
    {
        bool isLastChild = (i == children_.size() - 1);
        children_[i]->printTree(prefix + (isLastSibling ? "    " : "│   "), isLastChild);
    }
}

std::shared_ptr<TreeNodeBase> TreeNode::findNodeByName(const std::string &name) const
{
    std::shared_ptr<TreeNodeBase> result{};

    std::function<bool(const std::shared_ptr<TreeNodeBase> &, const std::string &)> search =
        [&](const std::shared_ptr<TreeNodeBase> &node, const std::string &target) -> bool
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

    if (!search(std::const_pointer_cast<TreeNode>(shared_from_this()), name))
    {
        std::cout << "Node with name '" + name + "' not found." << std::endl;
    }
    return result;
}

<<<<<<< HEAD
void TreeNode::read()
{
    if (std::holds_alternative<std::string>(data_))
    {
        std::cout << "无法对目录节点进行 Read 操作" << std::endl;
    }
    else if (std::holds_alternative<std::pair<std::string, std::string>>(data_))
    {
        readCount_++;
    }
}

std::shared_ptr<TreeNode> TreeNode::addNodebyNode(const std::shared_ptr<TreeNode> &nodeToAdd)
=======
std::shared_ptr<TreeNodeBase> TreeNode::addNodebyNode(const std::shared_ptr<TreeNodeBase> &nodeToAdd)
>>>>>>> b46e899bf1d9b9eece69512035f0d950ff9c740c
{
    std::shared_ptr<TreeNodeBase> parentNode = nodeToAdd->getParent().lock();
    if (parentNode)
    {
        parentNode->addChild(nodeToAdd);
    }
    else
    {
        std::cout << "Parent node not found." << std::endl;
    }
    return nodeToAdd;
}

std::shared_ptr<TreeNodeBase> TreeNode::addNodebyName(const std::string &parentName, const DataType &data)
{
    auto parentNode = findNodeByName(parentName);
    if (parentNode)
    {
        std::shared_ptr<TreeNodeBase> newNode = TreeNode::createNode(data);
        parentNode->addChildWithParent(newNode);
        return newNode;
    }
    else
    {
        std::cout << "Parent node not found." << std::endl;
        return nullptr;
    }
}

std::shared_ptr<TreeNodeBase> TreeNode::deleteNodebyNode(const std::shared_ptr<TreeNodeBase> &nodeToDelete)
{
    std::shared_ptr<TreeNodeBase> deletedNode;
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

std::shared_ptr<TreeNodeBase> TreeNode::deleteNodebyName(const std::string &name)
{
    std::shared_ptr<TreeNodeBase> deletedNode;
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

void TreeNode::setParent(std::weak_ptr<TreeNodeBase> parent)
{
    parent_ = parent;
}

void TreeNode::addChild(std::shared_ptr<TreeNodeBase> child)
{
    children_.push_back(child);
}

void TreeNode::addChildWithParent(std::shared_ptr<TreeNodeBase> child)
{
    children_.push_back(child);
    child->setParent(this->shared_from_this());
}

void TreeNode::setReadCount(int readCount)
{
    readCount_ = readCount;
}

// get
std::shared_ptr<TreeNodeBase> TreeNode::getTreeNode()
{
    return shared_from_this();
}

TreeNode::DataType TreeNode::getData() const
{
    return data_;
}

std::vector<std::shared_ptr<TreeNodeBase>> &TreeNode::getChildren()
{
    return children_;
}

std::weak_ptr<TreeNodeBase> TreeNode::getParent() const
{
    return parent_;
}

int TreeNode::getReadCount() const
{
    return readCount_;
}