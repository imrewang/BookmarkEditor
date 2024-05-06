#include "handler.h"

CommandType parseInput(const std::string &command)
{
    auto it = command_map.find(command);
    if (it != command_map.end())
    {
        return it->second;
    }
    else
    {
        return CommandType::Invalid;
    }
}

void showHelp()
{
    std::cout << "可用命令及其用法:\n"
              << "bookmark <文件路径> - 将文件路径作为书签文件\n"
              << "save    - 保存当前书签状态\n"
              << "undo    - 撤销上一次操作\n"
              << "redo    - 重做上一次操作\n"
              << "show-tree   - 显示当前书签树结构\n"
              << "cd at \"<名称>\"  - 将当前位置切换到指定标题下的指定书签\n"
              << "read-bookmark \"<名称>\" - 访问指定节点\n"
              << "ls-tree - 列出当前标题下的所有子节点\n"
              << "add-title \"<名称>\"  - 在当前位置添加一个标题节点\n"
              << "add-title \"<名称1>\" at \"<名称2>\"    - 在指定标题下添加一个标题节点\n"
              << "add-bookmark \"<名称1>@<名称2>\" at \"<名称3>\"   - 在指定标题下添加一个书签节点\n"
              << "delete-title \"<名称>\"   - 删除指定标题及其子节点\n"
              << "delete-bookmark \"<名称>\"    - 删除指定书签\n"
              << "exit    - 退出程序\n";
}

<<<<<<< HEAD
// 从输入中提取目标名称
std::string extractTargetName(const std::string &input)
=======
// 执行 cd 命令的函数
void executeCdCommand(std::shared_ptr<TreeNodeBase> &receiver, std::shared_ptr<TreeNodeBase> &currentDir, const std::string &input)
>>>>>>> b46e899bf1d9b9eece69512035f0d950ff9c740c
{
    size_t quoteStart = input.find('"');
    if (quoteStart == std::string::npos)
    {
        std::cout << "输入格式不正确，缺少引号。" << std::endl;
        return "";
    }
    size_t quoteEnd = input.find('"', quoteStart + 1);
    if (quoteEnd == std::string::npos)
    {
        std::cout << "输入格式不正确，缺少闭合的引号。" << std::endl;
        return "";
    }

<<<<<<< HEAD
    return input.substr(quoteStart + 1, quoteEnd - quoteStart - 1);
}

// 执行 cd 命令的函数
void executeCdCommand(std::shared_ptr<TreeNode> &receiver, std::shared_ptr<TreeNode> &currentDir, const std::string &input)
{
    std::string targetName = extractTargetName(input);
    if (!targetName.empty())
=======
    // 提取引号内的名称作为目标名称
    std::string targetName = input.substr(quoteStart + 1, quoteEnd - quoteStart - 1);
    std::shared_ptr<TreeNodeBase> newDir = receiver->findNodeByName(targetName);
    if (newDir)
>>>>>>> b46e899bf1d9b9eece69512035f0d950ff9c740c
    {
        std::shared_ptr<TreeNode> newDir = receiver->findNodeByName(targetName);
        if (newDir)
        {
            currentDir = newDir;
            std::cout << "当前目录为：" << targetName << std::endl;
        }
        else
        {
            std::cout << "找不到指定 Cd 节点：" << targetName << std::endl;
        }
    }
}

// 执行 cd 命令的函数
void executeReadBookmark(std::shared_ptr<TreeNode> &receiver, const std::string &input)
{
    std::string targetName = extractTargetName(input);
    if (!targetName.empty())
    {
        std::shared_ptr<TreeNode> readNode = receiver->findNodeByName(targetName);
        if (readNode)
        {
            readNode->read();
        }
        else
        {
            std::cout << "找不到指定 Read 节点：" << targetName << std::endl;
        }
    }
}

void handleOpenCommand(int argc, char *argv[], std::string &filePath, std::shared_ptr<TreeNodeBase> &receiver, std::shared_ptr<TreeNodeBase> &currentDir)
{
    if (argc == 3 && std::string(argv[1]) == "open")
    {
        filePath = argv[2];
        std::cout << "打开文件：" << filePath << std::endl;
        receiver = constructTreeFromFile(filePath);
        currentDir = receiver;
    }
}

void handleUserInput(std::shared_ptr<TreeNodeBase> &receiver, std::shared_ptr<TreeNodeBase> &currentDir,
                     std::string &filePath, std::unique_ptr<Invoker> &invoker)
{
    // 读取终端命令并执行相应操作
    std::string input{};
    while (true)
    {
        std::cout << "请输入命令: ";
        std::getline(std::cin >> std::ws, input); // 忽略前导空白符
        // 查找空格的位置
        size_t spacePos = input.find(' ');
        std::string commandHead;
        if (spacePos != std::string::npos)
        {
            // 如果找到了空格，则获取空格前的部分作为命令
            commandHead = input.substr(0, spacePos);
        }
        else
        {
            // 如果没有找到空格，则整个字符串都是命令
            commandHead = input;
        }

        CommandType commandType = parseInput(commandHead);

        if (commandType != CommandType::Bookmark && !receiver)
        {
            std::cout << "文件未打开，无法执行其他操作。" << std::endl;
            continue;
        }
        std::unique_ptr<Command> command{};
        switch (commandType)
        {
        case CommandType::Bookmark:
            // 假设有一个处理Bookmark的函数command.substr(spacePos + 1)
            filePath = input.substr(spacePos + 1);
            receiver = constructTreeFromFile(filePath);
            currentDir = receiver;
            invoker.reset(new Invoker()); // 重置Invoker实例
            break;
        case CommandType::Save:
            writeTreeToFile(receiver, filePath);
            std::cout << "文件已保存" << std::endl;
            break;
        case CommandType::Undo:
            invoker->undo();
            break;
        case CommandType::Redo:
            invoker->redo();
            break;
        case CommandType::ShowTree:
            receiver->printTree();
            break;
        case CommandType::Cd:
            executeCdCommand(receiver, currentDir, input);
            break;
        case CommandType::ReadBookmark:
            executeReadBookmark(receiver, input);
            break;
        case CommandType::LsTree:
            if (currentDir)
            {
                currentDir->printTree();
            }
            break;
        case CommandType::Help:
            showHelp();
            break;
        case CommandType::AddTitle:
        case CommandType::AddBookmark:
            command = std::make_unique<AddCommand>(receiver, input);
            break;
        case CommandType::DeleteTitle:
        case CommandType::DeleteBookmark:
            command = std::make_unique<DeleteCommand>(receiver, input);
            break;
        case CommandType::Exit:
            std::cout << "退出程序" << std::endl;
            return; // 使用 return 来退出程序
        case CommandType::Invalid:
            std::cout << "无效命令，请重新输入。" << std::endl;
            break;
        default:
            std::cout << "未知命令，请尝试 'help' 获取帮助。" << std::endl;
            break;
        }

        if (command)
        {
            invoker->executeCommand(std::move(command));
        }
    }
}