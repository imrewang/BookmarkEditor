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
        receiver->printTree("1");
        std::cout << "------------------" << std::endl;
        auto dn = receiver->deleteNodebyName("参考资料");
        receiver->printTree("2");
        receiver->addNodebyNode(dn);
        receiver->printTree("3");
        auto an = receiver->addNodebyName("课程", "test");
        receiver->printTree("44");
        receiver->deleteNodebyNode(an);
        receiver->printTree("55");
        writeTreeToFile(receiver, "test2.md");
        std::cout << "+++++++++" << std::endl;
    }
    std::cout << "^^^^^^^^^" << std::endl;
    return 0;
}
