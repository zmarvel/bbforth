
#include "operation.h"



template<class T>
Cell<T>::Cell(T data)
   : value{data}
{
}

template<class T>
Cell<T>::~Cell()
{
}

template<class T>
Cell<T> operator+(Cell<T> lhs, const Cell<T> &rhs) {
   return lhs.value + rhs.value;
}

Stack::Stack(size_t size)
   : myStackSize{size},
   mypStack{new UCell[size]},
   myStackEmpty{false},
   myiTop{0}
{
}

template<class T>
bool Stack::peek(Cell<T> &c) {
   if (myStackEmpty) {
      return false;
   }

   c = mypStack.get()[myiTop];

   return true;
}

template<class T>
bool Stack::pop(Cell<T> &c) {
   if (myStackEmpty) {
      return false;
   }

   if (myiTop == 0) {
      myStackEmpty = true;
   }

   c = mypStack.get()[myiTop--];

   return true;
}

template<class T>
bool Stack::push(Cell<T> c) {
   if (myiTop == myStackSize) {
      return false;
   }

   if (myStackEmpty) {
      myStackEmpty = false;
   }

   mypStack[++myiTop] = c;

   return true;
}


VirtualMachine::VirtualMachine()
   : myDataStack{},
   myInstructionStack{}
{
}

VirtualMachine::~VirtualMachine() {
}
