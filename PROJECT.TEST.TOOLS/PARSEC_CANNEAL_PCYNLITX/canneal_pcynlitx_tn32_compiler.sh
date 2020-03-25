
g++ -I/home/erkam/PARSEC_CANNEAL_PCYNLITX/Thread_Server_Include_Directory \
    -I/home/erkam/PARSEC_CANNEAL_PCYNLITX \
    -L/home/erkam/PARSEC_CANNEAL_PCYNLITX \
    -o canneal_pcynlitx_tn32 canneal_pcynlitx_tn32.cpp data_pointer.cpp  \
     annealer_thread.cpp netlist.cpp netlist_elem.cpp rng.cpp \
    -include annealer_thread.h -include annealer_types.h \
    -include AtomicPtr.h -include netlist.h -include netlist_elem.h -include rng.h \
    -include location_t.h -include MersenneTwister.h -include MT_Library_Headers.h \
    -include data_pointer.h -include TM_Client.h -include Thread_Manager.h \
    -include Thread_Server.h -include itds.h -include Thread_Locker.h \
    -lThread_Server -lm -lpthread
