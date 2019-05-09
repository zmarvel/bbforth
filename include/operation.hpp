

#ifndef OPERATION_H
#define OPERATION_H

#include <cstdint>
#include <cmath>
#include <algorithm>
#include <functional>

#include "virtual_machine.hpp"

/* Types */

enum OpCode {
  /* -- ARITHMETIC -------------------------------------------------------- */
  /* - single-Cell                                                          */
  OPCODE_PLUS = 0,
  OPCODE_ONE_PLUS,
  OPCODE_MINUS,
  OPCODE_ONE_MINUS,
  OPCODE_STAR,
  OPCODE_SLASH,
  OPCODE_MOD,
  OPCODE_SLASH_MOD,
  OPCODE_NEGATE,
  OPCODE_ABS,
  OPCODE_MIN,
  OPCODE_MAX,

  /* - single-Cell bitwise                                                  */
  OPCODE_AND,
  OPCODE_OR,
  OPCODE_XOR,
  OPCODE_INVERT,
  OPCODE_LSHIFT,
  OPCODE_RSHIFT,
  OPCODE_TWO_STAR,
  OPCODE_TWO_SLASH,

  /* - single-Cell comparison                                               */
  OPCODE_LESS_THAN,
  OPCODE_EQUALS,
  OPCODE_GREATER_THAN,
  OPCODE_ZERO_LESS_THAN,
  OPCODE_ZERO_EQUALS,
  OPCODE_U_LESS_THAN,

  /* - single-Cell arithmetic                                               */
  OPCODE_STAR_SLASH, // (n1*n2)/n3
  OPCODE_STAR_SLASH_MOD, // n1*n2 = n3*n5 + n4


  /* -- STACK MANIPULATION ------------------------------------------------ */
  OPCODE_DROP,
  OPCODE_DUP,
  OPCODE_OVER,
  OPCODE_SWAP,
  OPCODE_ROT,
  OPCODE_QUESTION_DUP,
  OPCODE_TWO_DROP,
  OPCODE_TWO_DUP,
  OPCODE_TWO_OVER,
  OPCODE_TWO_SWAP,



  OPCODE_LAST,
};


template<unsigned int opcode>
class Operation {
  public:
    Operation(const Operation &) = delete;

    constexpr unsigned int getOpcode() {
      return opcode;
    }

    // abstract method
    void operator()(DataStack &ds);
};



/*
 * Declarations and definitions
 */


/*
 * First override a bunch of operators to simplify operations on Cell<T>
 */

/* - Arithmetic ------------------------------------------------------------ */
template<class T>
Cell<T> operator+(Cell<T> lhs, const Cell<T>& rhs) {
  return Cell<T>{lhs.get() + rhs.get()};
}
template<class T>
Cell<T> operator-(Cell<T> lhs, const Cell<T>& rhs) {
  return Cell<T>{lhs.get() - rhs.get()};
}
template<class T>
Cell<T> operator*(Cell<T> lhs, const Cell<T>& rhs) {
  return Cell<T>{lhs.get() * rhs.get()};
}
template<class T>
Cell<T> operator/(Cell<T> lhs, const Cell<T>& rhs) {
  return Cell<T>{lhs.get() / rhs.get()};
}
template<class T>
Cell<T> operator%(Cell<T> lhs, const Cell<T>& rhs) {
  return Cell<T>{lhs.get() % rhs.get()};
}
template<class T>
Cell<T> operator-(Cell<T> lhs); // TODO
namespace std {
  template<class T>
  const Cell<T> abs(Cell<T>& lhs) {
    return std::abs(lhs.get());
  }
  template<class T>
  const Cell<T> min(const Cell<T>& lhs, const Cell<T>& rhs) {
    return std::min<T>(lhs.get(), rhs.get());
  }
  template<class T>
  const Cell<T> max(const Cell<T>& lhs, const Cell<T>& rhs) {
    return std::max<T>(lhs.get(), rhs.get());
  }
}

/* - Arithmetic ------------------------------------------------------------ */
template<class T>
Cell<T> operator+(Cell<T> lhs, const T& rhs) {
  return lhs + Cell<T>{rhs};
}
template<class T>
Cell<T> operator-(Cell<T> lhs, const T& rhs) {
  return lhs - Cell<T>{rhs};
}
template<class T>
Cell<T> operator*(Cell<T> lhs, const T& rhs) {
  return lhs * Cell<T>{rhs};
}
template<class T>
Cell<T> operator/(Cell<T> lhs, const T& rhs) {
  return lhs / Cell<T>{rhs};
}
template<class T>
Cell<T> operator%(Cell<T> lhs, const T& rhs) {
  return lhs % Cell<T>{rhs};
}



/* - Bitwise --------------------------------------------------------------- */
template<class T>
Cell<T> operator&(Cell<T> lhs, const Cell<T>& rhs) {
  return Cell<T>{lhs.get() & rhs.get()};
}
template<class T>
Cell<T> operator|(Cell<T> lhs, const Cell<T>& rhs) {
  return Cell<T>{lhs.get() | rhs.get()};
}
template<class T>
Cell<T> operator^(Cell<T> lhs, const Cell<T>& rhs) {
  return Cell<T>{lhs.get() ^ rhs.get()};
}
template<class T>
Cell<T> operator~(Cell<T> lhs) {
  return Cell<T>{~lhs.get()};
}

/* - Comparison ------------------------------------------------------------ */
template<class T>
Cell<T> operator<(Cell<T> lhs, const Cell<T>& rhs) {
  return Cell<T>{lhs.get() < rhs.get()};
}
template<class T>
Cell<T> operator>(Cell<T> lhs, const Cell<T>& rhs) {
  return Cell<T>{lhs.get() > rhs.get()};
}
template<class T>
Cell<T> operator<=(Cell<T> lhs, const Cell<T>& rhs) {
  return Cell<T>{lhs.get() <= rhs.get()};
}
template<class T>
Cell<T> operator>=(Cell<T> lhs, const Cell<T>& rhs) {
  return Cell<T>{lhs.get() >= rhs.get()};
}
template<class T>
Cell<T> operator==(Cell<T> lhs, const Cell<T>& rhs) {
  return Cell<T>{lhs.get() == rhs.get()};
}

template<class T>
Cell<T> operator<(Cell<T> lhs, const T& rhs) {
  return Cell<T>{lhs.get() < rhs};
}
template<class T>
Cell<T> operator>(Cell<T> lhs, const T& rhs) {
  return Cell<T>{lhs.get() > rhs};
}
template<class T>
Cell<T> operator<=(Cell<T> lhs, const T& rhs) {
  return Cell<T>{lhs.get() <= rhs};
}
template<class T>
Cell<T> operator>=(Cell<T> lhs, const T& rhs) {
  return Cell<T>{lhs.get() >= rhs};
}
template<class T>
Cell<T> operator==(Cell<T> lhs, const T& rhs) {
  return Cell<T>{lhs.get() == rhs};
}

template<>
class Operation<OPCODE_PLUS> {
  public:
    void operator()(DataStack &ds);
};
template<>
class Operation<OPCODE_ONE_PLUS> {
  public:
    void operator()(DataStack &ds);
};
template<>
class Operation<OPCODE_MINUS> {
  public:
    void operator()(DataStack &ds);
};
template<>
class Operation<OPCODE_ONE_MINUS> {
  public:
    void operator()(DataStack &ds);
};
template<>
class Operation<OPCODE_STAR> {
  public:
    void operator()(DataStack &ds);
};
template<>
class Operation<OPCODE_SLASH> {
  public:
    void operator()(DataStack &ds);
};
template<>
class Operation<OPCODE_MOD> {
  public:
    void operator()(DataStack &ds);
};
template<>
class Operation<OPCODE_SLASH_MOD> {
  public:
    void operator()(DataStack &ds);
};
template<>
class Operation<OPCODE_NEGATE> {
  public:
    void operator()(DataStack &ds);
};
template<>
class Operation<OPCODE_ABS> {
  public:
    void operator()(DataStack &ds);
};
template<>
class Operation<OPCODE_MIN> {
  public:
    void operator()(DataStack &ds);
};
template<>
class Operation<OPCODE_MAX> {
  public:
    void operator()(DataStack &ds);
};
template<>
class Operation<OPCODE_AND> {
  public:
    void operator()(DataStack &ds);
};
template<>
class Operation<OPCODE_OR> {
  public:
    void operator()(DataStack &ds);
};
template<>
class Operation<OPCODE_XOR> {
  public:
    void operator()(DataStack &ds);
};
template<>
class Operation<OPCODE_INVERT> {
  public:
    void operator()(DataStack &ds);
};
template<>
class Operation<OPCODE_LSHIFT> {
  public:
    void operator()(DataStack &ds);
};
template<>
class Operation<OPCODE_RSHIFT> {
  public:
    void operator()(DataStack &ds);
};
template<>
class Operation<OPCODE_TWO_STAR> {
  public:
    void operator()(DataStack &ds);
};
template<>
class Operation<OPCODE_TWO_SLASH> {
  public:
    void operator()(DataStack &ds);
};
template<>
class Operation<OPCODE_LESS_THAN> {
  public:
    void operator()(DataStack &ds);
};
template<>
class Operation<OPCODE_EQUALS> {
  public:
    void operator()(DataStack &ds);
};
template<>
class Operation<OPCODE_GREATER_THAN> {
  public:
    void operator()(DataStack &ds);
};
template<>
class Operation<OPCODE_ZERO_LESS_THAN> {
  public:
    void operator()(DataStack &ds);
};
template<>
class Operation<OPCODE_ZERO_EQUALS> {
  public:
    void operator()(DataStack &ds);
};
template<>
class Operation<OPCODE_U_LESS_THAN> {
  public:
    void operator()(DataStack &ds);
};
template<>
class Operation<OPCODE_STAR_SLASH> {
  public:
    void operator()(DataStack &ds);
};
template<>
class Operation<OPCODE_STAR_SLASH_MOD> {
  public:
    void operator()(DataStack &ds);
};
template<>
class Operation<OPCODE_DROP> {
  public:
    void operator()(DataStack &ds);
};
template<>
class Operation<OPCODE_DUP> {
  public:
    void operator()(DataStack &ds);
};
template<>
class Operation<OPCODE_OVER> {
  public:
    void operator()(DataStack &ds);
};
template<>
class Operation<OPCODE_SWAP> {
  public:
    void operator()(DataStack &ds);
};
template<>
class Operation<OPCODE_ROT> {
  public:
    void operator()(DataStack &ds);
};
template<>
class Operation<OPCODE_QUESTION_DUP> {
  public:
    void operator()(DataStack &ds);
}; // TODO
template<>
class Operation<OPCODE_TWO_DROP> {
  public:
    void operator()(DataStack &ds);
};
template<>
class Operation<OPCODE_TWO_DUP> {
  public:
    void operator()(DataStack &ds);
};
template<>
class Operation<OPCODE_TWO_OVER> {
  public:
    void operator()(DataStack &ds);
};
template<>
class Operation<OPCODE_TWO_SWAP> {
  public:
    void operator()(DataStack &ds);
};




#endif // OPERATION_H
