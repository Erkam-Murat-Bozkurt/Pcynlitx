
#include "StringOperator.h"

int main(){

    StringOperator S_OPR;

    char File_Path [] = "TestFile";

    S_OPR.SetFilePath(File_Path);

    S_OPR.ReadFileLine(2);

    std::cout << "\n Line :" << S_OPR.GetStringBuffer();

    std::cout << "\n The end of the program..\n\n";

    return 0;
}
