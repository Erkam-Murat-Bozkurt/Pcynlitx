
PROJECT_HEADER_FILES=~/PCYNLITX.PROJECT.LIBRARY/PROJECT.HEADER.FILES
PROJECT_LIBRARY_DIRECTORY=~/PCYNLITX.PROJECT.LIBRARY/PROJECT.LIBRARY


g++ -std=c++14 -o pcynlitx_data_clustering_test  -I$PROJECT_HEADER_FILES \
    -L$PROJECT_LIBRARY_DIRECTORY Pcynlitx_Data_Clustering_Test.cpp -include Cpp_FileOperations.h -lmptools
