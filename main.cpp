#include "file.h"
#include "handler.h"
#include "invoker.h"

int main(int argc, char *argv[])
{
    std::string filePath;
    std::shared_ptr<TreeNode> receiver;
    std::shared_ptr<TreeNode> currentDir;
    std::unique_ptr<Invoker> invoker = std::make_unique<Invoker>();
    if (argc == 3 && std::string(argv[1]) == "open")
    {
        filePath = argv[2];
        std::cout << "打开文件：" << filePath << std::endl;
        auto file = readFile(filePath);
        receiver = constructTreeFromFile(file);
        currentDir = receiver;
    }

    // 读取终端命令并执行相应操作
    std::string input;
    while (true)
    {
        std::cout << "请输入命令: ";
        std::getline(std::cin, input);
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
        std::unique_ptr<Command> command;
        switch (commandType)
        {
        case CommandType::Bookmark:
            // 假设有一个处理Bookmark的函数command.substr(spacePos + 1)
            filePath = input.substr(spacePos + 1);
            receiver = constructTreeFromFile(readFile(filePath));
            currentDir = receiver;
            invoker.reset(new Invoker()); // 重置Invoker实例
            break;
        case CommandType::Save:
            writeTreeToFile(receiver, filePath);
            std::cout << "文件已保存" << std::endl;
            break;
        case CommandType::Undo:
            invoker->undo();
            std::cout << "撤销上一步操作" << std::endl;
            break;
        case CommandType::Redo:
            invoker->redo();
            std::cout << "重做上一步操作" << std::endl;
            break;
        case CommandType::ShowTree:
            receiver->printTree();
            break;
        case CommandType::Cd:
            currentDir = receiver->findNodeByName(input.substr(spacePos + 1));
            break;
        case CommandType::LsTree:
            currentDir->printTree();
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
            return 0; // 使用 return 0 来退出程序
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
