#include "file.h"

std::vector<std::string> readFile(const std::string &filename)
{
    std::vector<std::string> lines;
    std::ifstream file(filename);
    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            lines.push_back(line);
        }
        file.close();
    }
    return lines;
}

std::shared_ptr<TreeNode> constructTreeFromFile(const std::vector<std::string> &lines)
{
    std::stack<std::shared_ptr<TreeNode>> stack;
    std::shared_ptr<TreeNode> rootNode;

    for (const auto &line : lines)
    {
        if (line.empty())
        {
            continue;
        }

        // 处理文件链接节点
        if (line.substr(0, 1) == "[")
        {
            std::smatch match;
            std::regex linkRegex(R"(\[(.*?)\]\((.*?)\))");
            if (std::regex_match(line, match, linkRegex))
            {
                std::string linkText = match[1];
                std::string linkUrl = match[2];
                auto linkNode = std::make_shared<TreeNode>(std::make_pair(linkText, linkUrl));
                if (!stack.empty())
                {
                    stack.top()->addChildWithParent(linkNode);
                }
            }
            continue;
        }

        int level = 0;
        while (line[level] == '#')
        {
            level++;
        }

        std::string text;
        if (level > 0 && line[level] == ' ')
        {
            text = line.substr(level + 1);
        }
        else
        {
            text = line;
        }

        auto node = std::make_shared<TreeNode>(text);
        node->getTreeNode();
        if (level == 1)
        {
            if (!rootNode)
            {
                rootNode = node;
            }
        }
        else
        {
            while (stack.size() >= level)
            {
                stack.pop();
            }
            if (!stack.empty())
            {
                stack.top()->addChildWithParent(node);
            }
        }
        stack.push(node);
    }

    return rootNode;
}

void writeTreeNode(std::ofstream &outFile, const std::shared_ptr<TreeNode> &node, int level)
{
    if (!node)
    {
        return;
    }

    // 输出节点数据
    if (std::holds_alternative<std::string>(node->getData()))
    {
        for (int i = 0; i < level; ++i)
        {
            outFile << "#";
        }
        outFile << " ";
        outFile << std::get<std::string>(node->getData()) << std::endl;
    }
    else if (std::holds_alternative<std::pair<std::string, std::string>>(node->getData()))
    {
        auto linkData = std::get<std::pair<std::string, std::string>>(node->getData());
        outFile << "[" << linkData.first << "](" << linkData.second << ")" << std::endl;
    }

    // 递归写入子节点
    for (const auto &child : node->getChildren())
    {
        writeTreeNode(outFile, child, level + 1);
    }
}

void writeTreeToFile(const std::shared_ptr<TreeNode> &root, const std::string &filePath)
{
    std::ofstream outFile(filePath);
    if (!outFile.is_open())
    {
        std::cerr << "Failed to open file: " << filePath << std::endl;
        return;
    }

    // 写入树的内容
    writeTreeNode(outFile, root);

    outFile.close();
}