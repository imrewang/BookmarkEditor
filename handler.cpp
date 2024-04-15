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
              << "ls-tree - 列出当前标题下的所有子节点\n"
              << "add-title \"<名称>\"  - 在当前位置添加一个标题节点\n"
              << "add-title \"<名称1>\" at \"<名称2>\"    - 在指定标题下添加一个标题节点\n"
              << "add-bookmark \"<名称1>@<名称2>\" at \"<名称3>\"   - 在指定标题下添加一个书签节点\n"
              << "delete-title \"<名称>\"   - 删除指定标题及其子节点\n"
              << "delete-bookmark \"<名称>\"    - 删除指定书签\n"
              << "exit    - 退出程序\n";
}