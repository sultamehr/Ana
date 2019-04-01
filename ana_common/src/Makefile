CXX = g++
CXXFLAGS = -g -Wall -fPIC -I$(MY_CCQENU)
ROOTFLAGS = `root-config --cflags --glibs` -lTreePlayer
CFLAGS = -Wall -fPIC
OBJS =  CCQENuBinning.o CCQENuCuts.o CCQENuPlotUtils.o CCQENuUtils.o CCQENuEvent.o CCQENuTruth.o GlobalParameters.o
SRC = $(CCQENU_ANA)/src/*.cxx
INCLUDE += -I$(UNFOLDUTILSROOT) -I$(CCQENU_ANA)/ -I$(MY_CCQENU) -I$(PLOTUTILSROOT) -I$(MINERVAKERNELROOT) -I$(CCQENU_INCLUDE_PATH) -I$(MCREWEIGHTROOT)
LDFLAGS += -shared -Wl,-soname

TARGET = libCCQENU.so

$(TARGET): $(OBJS) $(ROOTDICTCXX)
	$(CXX) $(LDFLAGS),$(TARGET) -o $(TARGET) $(OBJS) $(ROOTFLAGS)
	if [ ! -d ${CCQENU_ANA}/lib ]; then mkdir $(CCQENU_ANA)/lib; fi
	ln -sf $(CCQENU_ANA)/src/$(TARGET) ${CCQENU_ANA}/lib/$(TARGET)

$(OBJS): %.o: %.cxx 
	$(CXX) $(INCLUDE) $(CXXFLAGS) $(ROOTFLAGS) -c $< -o $@ 

.PHONY: clean

clean:
	rm -f $(CCQENU_ANA)/lib/$(TARGET)
	rm -f $(TARGET)
	rm -f *.o
