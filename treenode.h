#pragma once
#include "treenodebase.h"

class TreeNode : public TreeNodeBase, public std::enable_shared_from_this<TreeNode>
{
public:
    explicit TreeNode(std::string data);
    explicit TreeNode(std::pair<std::string, std::string> data);
    ~TreeNode() override;

    // 工厂方法用于创建 TreeNodeBase 对象
    static std::shared_ptr<TreeNodeBase> createNode(const DataType &data);

    void printTree(const std::string &prefix = "", bool isLastSibling = true) const override;
    std::shared_ptr<TreeNodeBase> findNodeByName(const std::string &name) const override;
    std::shared_ptr<TreeNodeBase> addNodebyNode(const std::shared_ptr<TreeNodeBase> &nodeToAdd) override;
    std::shared_ptr<TreeNodeBase> addNodebyName(const std::string &parentName, const DataType &data) override;
    std::shared_ptr<TreeNodeBase> deleteNodebyNode(const std::shared_ptr<TreeNodeBase> &nodeToDelete) override;
    std::shared_ptr<TreeNodeBase> deleteNodebyName(const std::string &name) override;

    // set
    void setData(DataType data) override;
    void setParent(std::weak_ptr<TreeNodeBase> parent) override;
    void addChild(std::shared_ptr<TreeNodeBase> child) override;
    void addChildWithParent(std::shared_ptr<TreeNodeBase> child) override;
    // get
    std::shared_ptr<TreeNodeBase> getTreeNode() override;
    DataType getData() const override;
    std::vector<std::shared_ptr<TreeNodeBase>> &getChildren() override;
    std::weak_ptr<TreeNodeBase> getParent() const override;
};