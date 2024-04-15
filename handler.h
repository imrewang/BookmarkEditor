#include <string>
#include <unordered_map>
#include <iostream>

enum class CommandType
{
    Bookmark,
    Save,
    Undo,
    Redo,
    ShowTree,
    Cd,
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
    {"ls-tree", CommandType::LsTree},
    {"help", CommandType::Help},
    {"add-title", CommandType::AddTitle},
    {"add-bookmark", CommandType::AddBookmark},
    {"delete-title", CommandType::DeleteTitle},
    {"delete-bookmark", CommandType::DeleteBookmark},
    {"exit", CommandType::Exit}};

CommandType parseInput(const std::string &command);
void showHelp();