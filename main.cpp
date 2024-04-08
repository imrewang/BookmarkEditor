#include "file_tree.h"

int main(int argc, char *argv[])
{
    std::string filePath;
    if (argc == 3 && std::string(argv[1]) == "open")
    {
        filePath = argv[2];
        std::cout << "打开文件：" << filePath << std::endl;
    }

    {
        auto file = readFile("test.md");
        auto receiver = constructTreeFromFile(file);
        receiver->printTree();
        writeTreeToFile(receiver, "test2.md");
    }
    std::cout << "^^^^^^^^^" << std::endl;
    return 0;
}
