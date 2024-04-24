#pragma once
#include "treenode.h" // 包含类的头文件
#include <fstream>
#include <stack>
#include <regex>

std::vector<std::string> readFile(const std::string &filename);
std::shared_ptr<TreeNodeBase> constructTree(const std::vector<std::string> &lines);
std::shared_ptr<TreeNodeBase> constructTreeFromFile(const std::string &filename);

void writeTreeNode(std::ofstream &outFile, const std::shared_ptr<TreeNodeBase> &node, int level = 1);
void writeTreeToFile(const std::shared_ptr<TreeNodeBase> &root, const std::string &filePath);