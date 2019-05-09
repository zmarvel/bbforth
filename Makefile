

EXE := bbforth

MAIN_SRC := src/main.cpp

SRCS := \
	src/virtual_machine.cpp \
	src/operation.cpp \

MAIN_OBJ := $(MAIN_SRC:%.cpp=%.o)
OBJS := $(SRCS:%.cpp=%.o)

TEST_SRCS := \
	test/test_cell.cpp \
	test/test_main.cpp \

TEST_OBJS := $(TEST_SRCS:%.cpp=%.o)

DEPS := $(SRCS:%.cpp=%.d) $(TEST_SRCS:%.cpp=%.d)

CXXFLAGS += -std=c++11 -g -Wall -MD -Iinclude

TEST_CXXFLAGS = -Ilib/catch2

VPATH += ./src

$(EXE): $(MAIN_OBJ) $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^

test: CXXFLAGS += $(TEST_CXXFLAGS)
test: $(TEST_OBJS) $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm -f $(EXE) $(MAIN_OBJ) $(OBJS) $(TEST_OBJS) $(DEPS)

-include $(DEPS)
