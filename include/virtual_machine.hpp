
#ifndef VIRTUAL_MACHINE_H
#define VIRTUAL_MACHINE_H

#include <cstddef>
#include <memory>
#include <cmath>



template<class T>
class Cell {
  public:
    using type = T;

    Cell(T data = 0)
      : value{data}
    {
    }

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wnarrowing"
    Cell(const Cell<unsigned int>& other)
      : value{other.value} { }

    Cell(const Cell<int>& other)
      : value{other.value} { }

    operator Cell<int>() const {
      return Cell{static_cast<int>(value)};
    }

    operator Cell<unsigned int>() const {
      return Cell{static_cast<unsigned int>(value)};
    }

    operator bool() const {
      return static_cast<bool>(value);
    }
#pragma GCC diagnostic pop

    ~Cell()
    {
    }

    T get() const {
      return value;
    }
    T value;
};




using SCell = Cell<int>;
using UCell = Cell<unsigned int>;


const size_t DATA_STACK_DEFAULT_SIZE = 256;
const size_t INSTRUCTION_STACK_DEFAULT_SIZE = 1024;

class Stack {
  public:
    Stack(size_t size);

    Stack(const Stack&) = delete;

    template<class T>
    bool peek(Cell<T> &c) {
      if (myStackEmpty) {
        return false;
      }

      c = mypStack.get()[myiTop];

      return true;
    }

    template<class T>
    bool push(Cell<T> c) {
      if (myiTop == myStackSize) {
        return false;
      }

      if (myStackEmpty) {
        myStackEmpty = false;
      }

      mypStack[++myiTop] = c;

      return true;
    };

    template<class T>
    bool pop(Cell<T> &c) {
      if (myStackEmpty) {
        return false;
      }

      if (myiTop == 0) {
        myStackEmpty = true;
      }

      c = mypStack.get()[myiTop--];

      return true;
    }

  private:
    size_t myStackSize;
    std::unique_ptr<UCell[]> mypStack;
    bool myStackEmpty;
    size_t myiTop;
};

class DataStack : public Stack {
  public:
    DataStack(size_t size = DATA_STACK_DEFAULT_SIZE)
      : Stack{size} {}
};

class InstructionStack : public Stack {
  public:
    InstructionStack(size_t size = INSTRUCTION_STACK_DEFAULT_SIZE)
      : Stack{size} {}
};


class VirtualMachine {
  public:
    explicit VirtualMachine();
    ~VirtualMachine();

    bool runOnce();

  private:
    DataStack myDataStack;
    InstructionStack myInstructionStack;
};


#endif // VIRTUAL_MACHINE_H
