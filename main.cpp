#include <iostream>
#include "treenode.h"

void testTreeNode()
{
    // 构造一个 TreeNode 节点，并设置数据为 "imre"
    TreeNode node("imre");

    // 获取节点的数据并打印
    TreeNode::DataType data = node.getData();
    if (std::holds_alternative<std::string>(data))
    {
        std::cout << "Data: " << std::get<std::string>(data) << std::endl;
    }
    else if (std::holds_alternative<std::pair<std::string, std::string>>(data))
    {
        auto pairData = std::get<std::pair<std::string, std::string>>(data);
        std::cout << "Data: " << pairData.first << ", Link: " << pairData.second << std::endl;
    }

    // 输出节点的子节点数量
    std::cout << "Number of children: " << node.getChildren().size() << std::endl;

    // 输出节点的父节点是否为空
    std::cout << "Parent exists: " << !node.getParent().expired() << std::endl;
}

int main()
{
    testTreeNode();
    return 0;
}
