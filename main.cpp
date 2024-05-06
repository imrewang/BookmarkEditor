#include "handler.h"

int main(int argc, char *argv[])
{
    std::string filePath{};
    std::shared_ptr<TreeNodeBase> receiver{};
    std::shared_ptr<TreeNodeBase> currentDir{};
    std::unique_ptr<Invoker> invoker = std::make_unique<Invoker>();

    handleOpenCommand(argc, argv, filePath, receiver, currentDir);
    handleUserInput(receiver, currentDir, filePath, invoker);

    return 0;
}
