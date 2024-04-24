#include "treenodebase.h"
class TreeDecorator : public TreeNodeBase
{
public:
    explicit TreeDecorator(std::shared_ptr<TreeNodeBase> component);

    virtual ~TreeDecorator() = default; // 虚析构函数

    virtual void printTree(const std::string &prefix = "", bool isLastSibling = true) const override;

    virtual std::shared_ptr<TreeNodeBase> findNodeByName(const std::string &name) const override;
    // add
    virtual std::shared_ptr<TreeNodeBase> addNodebyNode(const std::shared_ptr<TreeNodeBase> &nodeToAdd) override;
    virtual std::shared_ptr<TreeNodeBase> addNodebyName(const std::string &parentName, const DataType &data) override;
    // delete
    virtual std::shared_ptr<TreeNodeBase> deleteNodebyNode(const std::shared_ptr<TreeNodeBase> &nodeToDelete) override;
    virtual std::shared_ptr<TreeNodeBase> deleteNodebyName(const std::string &name) override;
    // set
    virtual void setData(DataType data) override;
    virtual void setParent(std::weak_ptr<TreeNodeBase> parent) override;
    virtual void addChild(std::shared_ptr<TreeNodeBase> child) override;
    virtual void addChildWithParent(std::shared_ptr<TreeNodeBase> child) override;
    // get
    virtual std::shared_ptr<TreeNodeBase> getTreeNode() override;
    virtual DataType getData() const override;
    virtual std::vector<std::shared_ptr<TreeNodeBase>> &getChildren() override;
    virtual std::weak_ptr<TreeNodeBase> getParent() const override;

protected:
    std::shared_ptr<TreeNodeBase> component_;
};