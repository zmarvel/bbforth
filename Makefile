

SRCS := \
	main.cpp \
	virtual_machine.cpp \

OBJS := $(SRCS:.cpp=.o)
DEPS := $(SRCS:.cpp=.d)

CXXFLAGS += -std=c++11 -g -Wall -MD -Iinclude

VPATH += ./src

bbforth: $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^

$(DEPS): $(OBJS)

.PHONY: clean
clean:
	rm -f $(OBJS) $(DEPS)

-include $(DEPS)
