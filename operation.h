

#ifndef OPERATION_H
#define OPERATION_H

#include <cstdint>
#include <cmath>
#include <algorithm>
#include <functional>

#include "virtual_machine.h"

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
   explicit Operation();
   ~Operation();

   Operation(const Operation &) = delete;

   constexpr unsigned int getOpcode() {
      return opcode;
   }

   // abstract method
   void operator()(DataStack &ds) = 0;
};

template<>
class Operation<OPCODE_PLUS> {
   void operator()(DataStack &ds) {
      UCell n1, n2;
      ds.pop(n1);
      ds.pop(n2);
      ds.push(n1 + n2);
   }
};
template<>
class Operation<OPCODE_ONE_PLUS> {
   void operator()(DataStack &ds) {
      UCell n1;
      ds.pop(n1);
      ds.push(n1 + static_cast<unsigned int>(1));
   }
};
template<>
class Operation<OPCODE_MINUS> {
   void operator()(DataStack &ds) {
      UCell n1, n2;
      ds.pop(n2);
      ds.pop(n1);
      ds.push(n1 - n2);
   }
};
template<>
class Operation<OPCODE_ONE_MINUS> {
   void operator()(DataStack &ds) {
      UCell n1;
      ds.pop(n1);
      ds.push(n1 - static_cast<unsigned int>(1));
   }
};
template<>
class Operation<OPCODE_STAR> {
   void operator()(DataStack &ds) {
      UCell n1, n2;
      ds.pop(n1);
      ds.pop(n2);
      ds.push(n1 * n2);
   }
};
template<>
class Operation<OPCODE_SLASH> {
   void operator()(DataStack &ds) {
      SCell n1, n2;
      ds.pop(n2);
      ds.pop(n1);
      ds.push(n1 / n2);
   }
};
template<>
class Operation<OPCODE_MOD> {
   void operator()(DataStack &ds) {
      SCell n1, n2;
      ds.pop(n2);
      ds.pop(n1);
      ds.push(n1 % n2);
   }
};
template<>
class Operation<OPCODE_SLASH_MOD> {
   void operator()(DataStack &ds) {
      SCell n1, n2;
      ds.pop(n2);
      ds.pop(n1);
      ds.push(n1 / n2);
      ds.push(n1 % n2);
   }
};
template<>
class Operation<OPCODE_NEGATE> {
   void operator()(DataStack &ds) {
      SCell n1;
      ds.pop(n1);
      ds.push(std::negate<SCell>{}(n1));
   }
};
template<>
class Operation<OPCODE_ABS> {
   void operator()(DataStack &ds) {
      SCell n1;
      ds.pop(n1);
      ds.push<SCell::type>(std::abs<SCell::type>(n1));
   }
};
template<>
class Operation<OPCODE_MIN> {
   void operator()(DataStack &ds) {
      SCell n1, n2;
      ds.pop(n1);
      ds.pop(n2);
      ds.push(std::min<SCell::type>(n1, n2));
   }
};
template<>
class Operation<OPCODE_MAX> {
   void operator()(DataStack &ds) {
      SCell n1, n2;
      ds.pop(n1);
      ds.pop(n2);
      ds.push(std::max<SCell::type>(n1, n2));
   }
};
template<>
class Operation<OPCODE_AND> {
   void operator()(DataStack &ds) {
      UCell n1, n2;
      ds.pop(n1);
      ds.pop(n2);
      ds.push(n1 & n2);
   }
};
template<>
class Operation<OPCODE_OR> {
   void operator()(DataStack &ds) {
      UCell n1, n2;
      ds.pop(n1);
      ds.pop(n2);
      ds.push(n1 | n2);
   }
};
template<>
class Operation<OPCODE_XOR> {
   void operator()(DataStack &ds) {
      UCell n1, n2;
      ds.pop(n1);
      ds.pop(n2);
      ds.push(n1 ^ n2);
   }
};
template<>
class Operation<OPCODE_INVERT> {
   void operator()(DataStack &ds) {
      UCell n1;
      ds.pop(n1);
      ds.push(~n1);
   }
};
template<>
class Operation<OPCODE_LSHIFT> {
   void operator()(DataStack &ds) {
      UCell u1;
      SCell n1;
      ds.pop(n1);
      ds.pop(u1);
      ds.push(u1 << n1);
   }
};
template<>
class Operation<OPCODE_RSHIFT> {
   void operator()(DataStack &ds) {
      UCell u1;
      SCell n1;
      ds.pop(n1);
      ds.pop(u1);
      ds.push(u1 >> n1);
   }
};
template<>
class Operation<OPCODE_TWO_STAR> {
   void operator()(DataStack &ds) {
      SCell n1;
      ds.pop(n1);
      ds.push(n1 * 2);
   }
};
template<>
class Operation<OPCODE_TWO_SLASH> {
   void operator()(DataStack &ds) {
      SCell n1;
      ds.pop(n1);
      ds.push(n1 / 2);
   }
};
template<>
class Operation<OPCODE_LESS_THAN> {
   void operator()(DataStack &ds) {
      SCell n1, n2;
      ds.pop(n2);
      ds.pop(n1);
      ds.push(n1 < n2);
   }
};
template<>
class Operation<OPCODE_EQUALS> {
   void operator()(DataStack &ds) {
      UCell n1, n2;
      ds.pop(n2);
      ds.pop(n1);
      ds.push(n1 == n2);
   }
};
template<>
class Operation<OPCODE_GREATER_THAN> {
   void operator()(DataStack &ds) {
      SCell n1, n2;
      ds.pop(n2);
      ds.pop(n1);
      ds.push(n1 > n2);
   }
};
template<>
class Operation<OPCODE_ZERO_LESS_THAN> {
   void operator()(DataStack &ds) {
      SCell n1;
      ds.pop(n1);
      ds.push(n1 < 0);
   }
};
template<>
class Operation<OPCODE_ZERO_EQUALS> {
   void operator()(DataStack &ds) {
      UCell n1;
      ds.pop(n1);
      ds.push(n1 == static_cast<unsigned int>(0));
   }
};
template<>
class Operation<OPCODE_U_LESS_THAN> {
   void operator()(DataStack &ds) {
      UCell n1, n2;
      ds.pop(n2);
      ds.pop(n1);
      ds.push(n1 < n2);
   }
};
template<>
class Operation<OPCODE_STAR_SLASH> {
   void operator()(DataStack &ds) {
      UCell n1, n2, n3;
      ds.pop(n3);
      ds.pop(n2);
      ds.pop(n1);
      ds.push((n1*n2)/n3);
   }
};
template<>
class Operation<OPCODE_STAR_SLASH_MOD>; // TODO
template<>
class Operation<OPCODE_DROP> {
   void operator()(DataStack &ds) {
      UCell n1;
      ds.pop(n1);
   }
};
template<>
class Operation<OPCODE_DUP> {
   void operator()(DataStack &ds) {
      UCell n1;
      ds.pop(n1);
      ds.push(n1);
   }
};
template<>
class Operation<OPCODE_OVER> {
   void operator()(DataStack &ds) {
      UCell n1, n2;
      ds.pop(n2);
      ds.pop(n1);
      ds.push(n1);
      ds.push(n2);
      ds.push(n1);
   }
};
template<>
class Operation<OPCODE_SWAP> {
   void operator()(DataStack &ds) {
      UCell n1, n2;
      ds.pop(n2);
      ds.pop(n1);
      ds.push(n2);
      ds.push(n1);
   }
};
template<>
class Operation<OPCODE_ROT> {
   void operator()(DataStack &ds) {
      UCell n1, n2, n3;
      ds.pop(n3);
      ds.pop(n2);
      ds.pop(n1);
      ds.push(n2);
      ds.push(n3);
      ds.push(n1);
   }
};
template<>
class Operation<OPCODE_QUESTION_DUP>; // TODO
template<>
class Operation<OPCODE_TWO_DROP> {
   void operator()(DataStack &ds) {
      UCell n1, n2;
      ds.pop(n2);
      ds.pop(n1);
   }
};
template<>
class Operation<OPCODE_TWO_DUP> {
   void operator()(DataStack &ds) {
      UCell n1, n2;
      ds.pop(n2);
      ds.peek(n1);
      ds.push(n2);
      ds.push(n1);
      ds.push(n2);
   }
};
template<>
class Operation<OPCODE_TWO_OVER>;
template<>
class Operation<OPCODE_TWO_SWAP>;



#endif // OPERATION_H
