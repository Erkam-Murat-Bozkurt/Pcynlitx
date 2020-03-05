
#include "Loop_Intervals.h"

Loop_Intervals::Loop_Intervals()
{
   this->interval_pointers = nullptr;

   this->memory_delete_condition = false;
};

Loop_Intervals::~Loop_Intervals()
{
   if(!this->memory_delete_condition)
   {
       this->memory_delete_condition = true;

       for(int i=0;i<this->thread_number;i++)
       {
            if(this->interval_pointers[i] != nullptr){

               delete this->interval_pointers[i];
            }
       }

       if(this->interval_pointers != nullptr)
       {
          delete this->interval_pointers;
       }
   }
};

void Loop_Intervals::set_thread_number(int number)
{
     this->thread_number = number;
}

void Loop_Intervals::initialize_thread_intervals()
{
     this->interval_pointers = new int * [2*this->thread_number];

     for(int i=0;i<this->thread_number;i++)
     {
         this->interval_pointers[i] = new int [10];
     }
}

void Loop_Intervals::set_thread_intervals(int start, int end, int thread_number)
{
    this->interval_pointers[thread_number][0] = start;

    this->interval_pointers[thread_number][1] = end;
}

int * Loop_Intervals::get_thread_interval(int thread_number)
{
      return this->interval_pointers[thread_number];
}
