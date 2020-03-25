g++ -o canneal_std_thread canneal_std_thread.cpp annealer_thread.cpp netlist.cpp rng.cpp netlist_elem.cpp annealer_thread.h \
       annealer_types.h netlist.h rng.h netlist_elem.h location_t.h -lm -lpthread
