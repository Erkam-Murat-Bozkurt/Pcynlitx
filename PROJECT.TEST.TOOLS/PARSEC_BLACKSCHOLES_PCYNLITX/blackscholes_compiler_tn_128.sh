g++ -I/home/erkam/PARSEC_BLACKSCHOLES_PCYNLITX/Thread_Server_Include_Directory \
    -L/home/erkam/PARSEC_BLACKSCHOLES_PCYNLITX \
    -o blackscholes_pcynlitx_tn_128 blackscholes_pcynlitx_tn_128.cpp \
    -include MT_Library_Headers.h -include TM_Client.h -include Thread_Manager.h \
    -include Thread_Server.h -include itds.h -include Thread_Locker.h \
    -lThread_Server -lm -lpthread
