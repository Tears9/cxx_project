TARGET = first_thread
LIBS = -lpthread
OBJS = first_thread.o
CXXFLAGS = -std=c++11

all : $(TARGET)

$(TARGET) : $(OBJS)
	$(CXX) $^ -o $@ $(LIBS)

clean :
	-@$(RM) $(OBJS) $(TARGET)

.PHONY : all clean
