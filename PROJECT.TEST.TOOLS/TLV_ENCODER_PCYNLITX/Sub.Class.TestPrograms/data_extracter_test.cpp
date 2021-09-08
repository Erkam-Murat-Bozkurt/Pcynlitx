
#include "data_extracter.h"

int main(int argc, char** argv){

    char json_data [] = "{StudentName:\"alex\",StudentNumber:1,PassStatus:true}";

    data_extracter extracter;

    extracter.extract_json_line_data(json_data);

    std::cout << "\n extracted string: " << extracter.getExtractedString();

    std::cout << "\n extracted integer: " << extracter.getExtractedInteger();

    std::cout << "\n extracted integer: " << extracter.getExtractedBolean();

    std::cout << "\n\n";

    return 0;
}
