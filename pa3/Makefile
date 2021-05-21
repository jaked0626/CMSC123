ifeq ($(DEBUG),yes)
  OPTIMIZE_FLAG = -O0 -g -DDEBUG
else
  OPTIMIZE_FLAG = -O3
endif


OBJS = USAGovClickFileReader.o \
       ThreadPool.o WorkerThread.o \
       USAGovClick.o USAGovClickData.o USAGovClickTask.o \
       jsoncpp.o main.o 
DEPS = $(OBJS:.o=.d)
CXX = clang++
CXXFLAGS = -std=c++0x -Wall -MMD -MP -I. $(OPTIMIZE_FLAG)
LDLIBS = -lpthread
BIN = usagov-clicks 

all: usagov-clicks

$(BIN): $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) -o $(BIN) $(LDLIBS)
		
%.d: %.cpp

clean:
	-rm -f $(OBJS) $(BIN) *.d
	
-include $(DEPS)
