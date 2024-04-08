#include "file_tree.h"

int main()
{
    auto file = readMarkdownFile("test.md");
    auto root = buildTree(file);
    root->printTree();
    return 0;
}
