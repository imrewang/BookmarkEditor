#include "treedecorator.h"

class ReadCountDecorator : public TreeDecorator
{

public:
    explicit ReadCountDecorator(std::shared_ptr<TreeNodeBase> component);

    void printTree(const std::string &prefix = "", bool isLastSibling = true) const override;

    void read();

    void setReadCount(const int readCount);
    int getReadCount() const;

private:
    int readCount_ = 0; // 添加额外的成员变量记录阅读次数
};