
g++ -std=c++14 -o fluidanimate_std_thread cellpool.cpp cellpool.hpp fluid.hpp \
       fluidview.hpp parsec_barrier.cpp parsec_barrier.hpp fluidanimate_std_thread.cpp -lpthread -lglut
