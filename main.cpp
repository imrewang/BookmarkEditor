#include "file_tree.h"

// #include <iostream>
// #include <memory>

// int main()
// {
//     auto node = std::make_shared<TreeNode>("sss");
//     std::cout << "hello" << std::endl;
//     std::weak_ptr<TreeNode> wp = node->getTreeNode();
//     std::cout << "8888" << std::endl;
//     return 0;
// }

int main()
{
    auto file = readMarkdownFile("test.md");
    auto root = buildTree(file);
    root->printTree();
    return 0;
}
