#pragma once
#include "treenode.h" // 包含类的头文件
#include <fstream>
#include <stack>
#include <regex>

std::vector<std::string> readFile(const std::string &filename);
std::shared_ptr<TreeNode> constructTree(const std::vector<std::string> &lines);
std::shared_ptr<TreeNode> constructTreeFromFile(const std::string &filename);

void writeTreeNode(std::ofstream &outFile, const std::shared_ptr<TreeNode> &node, int level = 1);
void writeTreeToFile(const std::shared_ptr<TreeNode> &root, const std::string &filePath);