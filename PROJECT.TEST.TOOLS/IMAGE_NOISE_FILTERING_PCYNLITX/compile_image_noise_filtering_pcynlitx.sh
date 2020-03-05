
g++ -I/home/erkam/IMAGE_NOISE_FILTERING_PCYNLITX/Thread_Server_Include_Directory \
    -I/home/erkam/IMAGE_NOISE_FILTERING_PCYNLITX \
    -L//home/erkam/IMAGE_NOISE_FILTERING_PCYNLITX \
    -o image_noise_filtering_pcynlitx main.cpp Loop_Intervals.cpp \
    -include Loop_Intervals_Client.h -include Loop_Intervals.h -include MT_Library_Headers.h \
    -include TM_Client.h -include Thread_Manager.h -include Thread_Server.h -include itds.h \
    -include Thread_Locker.h -lThread_Server `pkg-config --cflags --libs opencv` -lpthread
