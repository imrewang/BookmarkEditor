#pragma once
#include "treenode.h" // 包含类的头文件
#include <fstream>
#include <stack>
#include <regex>

std::vector<std::string> readMarkdownFile(const std::string &filename);
std::shared_ptr<TreeNode> buildTree(const std::vector<std::string> &lines);