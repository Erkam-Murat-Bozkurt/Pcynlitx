
#include "Cpp_FileOperations.h"
#include "StringOperator.h"
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <thread>
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <chrono>

void Readers_Function(int start_point, int end_point, int thread_number);
void Writers_Function(int thread_number);
int  File_Length_Determine();
void Check_Read_Start_Condition();
bool Is_Word_Included(int thread_number, int line_number);

std::thread thread_1;

std::thread thread_2;

std::thread thread_3;

std::thread thread_4;

char Target_File [] = "Target_File";

char Record_File [] = "Record_File";

char search_word [] = "File";

StringOperator Searcher[2];

Cpp_FileOperations Reader;

Cpp_FileOperations Writer[2];

int reader_thread_wait_at_start = 0;

int writer_thread_wait_at_start = 0;

char * Buffer = nullptr;

bool include_condition = false;

bool write_condition = false;

bool read_start_condition = true;

int read_operation_counter = 0;

int end_of_file_position = 0; // The number of line from the start of the file to the enf of file

int read_block_number = 0;

int write_block_number = 0;

int Elapsed_Time = 0;

std::mutex mtx_1;
std::mutex mtx_2;

std::condition_variable cv_1;
std::condition_variable cv_2;
