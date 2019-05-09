
#include "operation.hpp"



template<class T>
Cell<T>::Cell(T data)
  : value{data}
{
}

template<class T>
Cell<T>::~Cell()
{
}

template<>
SCell operator-(SCell lhs) {
  return SCell{-lhs.get()};
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

bool VirtualMachine::runOnce() {
  UCell op;
  myInstructionStack.pop(op);

  switch (static_cast<enum OpCode>(op.get())) {
    /* -- ARITHMETIC -------------------------------------------------------- */
    /* - single-Cell                                                          */
    case OPCODE_PLUS:
      Operation<OPCODE_PLUS>{}(myDataStack);
      break;
    case OPCODE_ONE_PLUS:
      Operation<OPCODE_ONE_PLUS>{}(myDataStack);
      break;
    case OPCODE_MINUS:
      Operation<OPCODE_MINUS>{}(myDataStack);
      break;
    case OPCODE_ONE_MINUS:
      Operation<OPCODE_ONE_MINUS>{}(myDataStack);
      break;
    case OPCODE_STAR:
      Operation<OPCODE_STAR>{}(myDataStack);
      break;
    case OPCODE_SLASH:
      Operation<OPCODE_SLASH>{}(myDataStack);
      break;
    case OPCODE_MOD:
      Operation<OPCODE_MOD>{}(myDataStack);
      break;
    case OPCODE_SLASH_MOD:
      Operation<OPCODE_SLASH_MOD>{}(myDataStack);
      break;
    case OPCODE_NEGATE:
      Operation<OPCODE_NEGATE>{}(myDataStack);
      break;
    case OPCODE_ABS:
      Operation<OPCODE_ABS>{}(myDataStack);
      break;
    case OPCODE_MIN:
      Operation<OPCODE_MIN>{}(myDataStack);
      break;
    case OPCODE_MAX:
      Operation<OPCODE_MAX>{}(myDataStack);
      break;

      /* - single-Cell bitwise                                                  */
    case OPCODE_AND:
      Operation<OPCODE_AND>{}(myDataStack);
      break;
    case OPCODE_OR:
      Operation<OPCODE_OR>{}(myDataStack);
      break;
    case OPCODE_XOR:
      Operation<OPCODE_XOR>{}(myDataStack);
      break;
    case OPCODE_INVERT:
      Operation<OPCODE_INVERT>{}(myDataStack);
      break;
    case OPCODE_LSHIFT:
      Operation<OPCODE_LSHIFT>{}(myDataStack);
      break;
    case OPCODE_RSHIFT:
      Operation<OPCODE_RSHIFT>{}(myDataStack);
      break;
    case OPCODE_TWO_STAR:
      Operation<OPCODE_TWO_STAR>{}(myDataStack);
      break;
    case OPCODE_TWO_SLASH:
      Operation<OPCODE_TWO_SLASH>{}(myDataStack);
      break;

      /* - single-Cell comparison                                               */
    case OPCODE_LESS_THAN:
      Operation<OPCODE_LESS_THAN>{}(myDataStack);
      break;
    case OPCODE_EQUALS:
      Operation<OPCODE_EQUALS>{}(myDataStack);
      break;
    case OPCODE_GREATER_THAN:
      Operation<OPCODE_GREATER_THAN>{}(myDataStack);
      break;
    case OPCODE_ZERO_LESS_THAN:
      Operation<OPCODE_ZERO_LESS_THAN>{}(myDataStack);
      break;
    case OPCODE_ZERO_EQUALS:
      Operation<OPCODE_ZERO_EQUALS>{}(myDataStack);
      break;
    case OPCODE_U_LESS_THAN:
      Operation<OPCODE_U_LESS_THAN>{}(myDataStack);
      break;

      /* - single-Cell arithmetic                                               */
    case OPCODE_STAR_SLASH: // (n1*n2)/n3
      Operation<OPCODE_STAR_SLASH>{}(myDataStack);
      break;
    case OPCODE_STAR_SLASH_MOD: // n1*n2 = n3*n5 + n4
      Operation<OPCODE_STAR_SLASH_MOD>{}(myDataStack);
      break;


      /* -- STACK MANIPULATION ------------------------------------------------ */
    case OPCODE_DROP:
      Operation<OPCODE_DROP>{}(myDataStack);
      break;
    case OPCODE_DUP:
      Operation<OPCODE_DUP>{}(myDataStack);
      break;
    case OPCODE_OVER:
      Operation<OPCODE_OVER>{}(myDataStack);
      break;
    case OPCODE_SWAP:
      Operation<OPCODE_SWAP>{}(myDataStack);
      break;
    case OPCODE_ROT:
      Operation<OPCODE_ROT>{}(myDataStack);
      break;
    case OPCODE_QUESTION_DUP:
      Operation<OPCODE_QUESTION_DUP>{}(myDataStack);
      break;
    case OPCODE_TWO_DROP:
      Operation<OPCODE_TWO_DROP>{}(myDataStack);
      break;
    case OPCODE_TWO_DUP:
      Operation<OPCODE_TWO_DUP>{}(myDataStack);
      break;
    case OPCODE_TWO_OVER:
      Operation<OPCODE_TWO_OVER>{}(myDataStack);
      break;
    case OPCODE_TWO_SWAP:
      Operation<OPCODE_TWO_SWAP>{}(myDataStack);
      break;



    case OPCODE_LAST:
      break;
  }

  return true;
}
