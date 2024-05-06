#pragma once

#include <string>
#include <unordered_map>
#include <iostream>
#include "treenode.h"
#include "file.h"
#include "invoker.h"

enum class CommandType
{
    Bookmark,
    Save,
    Undo,
    Redo,
    ShowTree,
    Cd,
    ReadBookmark,
    LsTree,
    Help,
    AddTitle,
    AddBookmark,
    DeleteTitle,
    DeleteBookmark,
    Exit,
    Invalid
};

static std::unordered_map<std::string, CommandType> command_map = {
    {"bookmark", CommandType::Bookmark},
    {"save", CommandType::Save},
    {"undo", CommandType::Undo},
    {"redo", CommandType::Redo},
    {"show-tree", CommandType::ShowTree},
    {"cd", CommandType::Cd},
    {"read-bookmark", CommandType::ReadBookmark},
    {"ls-tree", CommandType::LsTree},
    {"help", CommandType::Help},
    {"add-title", CommandType::AddTitle},
    {"add-bookmark", CommandType::AddBookmark},
    {"delete-title", CommandType::DeleteTitle},
    {"delete-bookmark", CommandType::DeleteBookmark},
    {"exit", CommandType::Exit}};

CommandType parseInput(const std::string &command);

void handleOpenCommand(int argc, char *argv[],
                       std::string &filePath, std::shared_ptr<TreeNode> &receiver, std::shared_ptr<TreeNode> &currentDir);
void handleUserInput(std::shared_ptr<TreeNode> &receiver, std::shared_ptr<TreeNode> &currentDir,
                     std::string &filePath, std::unique_ptr<Invoker> &invoker);

void showHelp();
void executeCdCommand(std::shared_ptr<TreeNode> &receiver, std::shared_ptr<TreeNode> &currentDir,
                      const std::string &input);
