
#include "Data_Receiver.h"
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <thread>
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include "acess_sequence_data_types.h"

void Readers_Function(Data_Receiver * Receiver, int thread_number);
void Writers_Function(Data_Receiver * Receiver, int thread_number);
void Check_Read_Start_Condition();

std::thread thread_1;

std::thread thread_2;

std::thread thread_3;

std::thread thread_4;

int reader_thread_wait_at_start = 0;

int writer_thread_wait_at_start = 0;

bool read_start_condition = true;

int read_operation_counter = 0;

bool Data_Checking(char ** data_pointer_1, char ** data_pointer_2);

bool thread_0_exit_condition = false;

bool thread_1_exit_condition = false;

bool thread_2_wait_condition = false;

bool thread_3_wait_condition = false;


int Data_Size = 0;

bool data_mismatch = false;

int Elapsed_Time = 0;

std::mutex mtx_rd;
std::mutex mtx_wr;
std::mutex mtx_02;
std::mutex mtx_13;

std::condition_variable cv_rd;
std::condition_variable cv_wr;
std::condition_variable cv_02;
std::condition_variable cv_13;
