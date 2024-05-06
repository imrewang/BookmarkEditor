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

<<<<<<< HEAD
    void printTree(const std::string &prefix = "", bool isLastSibling = true) const;
    std::shared_ptr<TreeNode> findNodeByName(const std::string &name) const;
    void read();
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
    void setReadCount(int readCount);
    // get
    std::shared_ptr<TreeNode> getTreeNode();
    DataType getData() const;
    std::vector<std::shared_ptr<TreeNode>> &getChildren();
    std::weak_ptr<TreeNode> getParent() const;
    int getReadCount() const;

private:
    // 数据成员
    DataType data_;
    // 子节点的向量
    std::vector<std::shared_ptr<TreeNode>> children_;
    // 父节点的弱引用
    std::weak_ptr<TreeNode> parent_;
    // 节点read次数
    int readCount_;
=======
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
>>>>>>> b46e899bf1d9b9eece69512035f0d950ff9c740c
};