
#include "operation.h"



//template<class T>
//Cell<T>::Cell(T data)
//   : value{data}
//{
//}

template<>
Cell<int>::Cell(unsigned int data)
   : value{static_cast<int>(data)}
{
}

template<>
Cell<unsigned int>::Cell(int data)
   : value{static_cast<unsigned int>(data)}
{
}

template<>
Cell<int>::Cell(int data)
   : value{data}
{
}

template<>
Cell<unsigned int>::Cell(unsigned int data)
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


DataStack::DataStack(size_t size)
   : myStackSize{size},
   mypStack{new UCell[size]},
   myStackEmpty{false},
   myiTop{0}
{
}

DataStack::~DataStack() {
}


template<class T>
bool DataStack::peek(Cell<T> &c) {
   if (myStackEmpty) {
      return false;
   }

   c = mypStack.get()[myiTop];

   return true;
}

template<class T>
bool DataStack::pop(Cell<T> &c) {
   if (myStackEmpty) {
      return false;
   }

   if (myiTop == 0) {
      myStackEmpty = true;
   }

   c = mypStack.get()[myiTop--];

   return true;
}

bool DataStack::push(UCell c) {
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
   : myDataStack{}
{
}

VirtualMachine::~VirtualMachine() {
}
