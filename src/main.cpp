#include <iostream>
#include <string>
#include "Merge.h"

int main(int argc, char *argv[])
{
    std::cout << "Merging processing" << std::endl;
    ReadFile start(argv[1], argv[2], argv[3]);
    std::cout << "Merged done" << std::endl;
    return 0;
}