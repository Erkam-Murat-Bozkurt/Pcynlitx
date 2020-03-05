
#ifndef LOOP_INTERVALS_H
#define LOOP_INTERVALS_H

class Loop_Intervals
{
public:
  Loop_Intervals();
  virtual ~Loop_Intervals();
  void set_thread_number(int number);
  void initialize_thread_intervals();
  void set_thread_intervals(int start, int end, int thread_number);
  int * get_thread_interval(int thread_number);
  int ** interval_pointers;
  int thread_number;
  bool memory_delete_condition;
};

#endif /* LOOP_INTERVALS_H */
