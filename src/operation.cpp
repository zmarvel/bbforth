
#include "operation.hpp"

template<>
SCell operator-(SCell lhs) {
  return SCell{-lhs.get()};
}

UCell operator<<(UCell lhs, const SCell& rhs) {
  return UCell{lhs.get() << rhs.get()};
}
UCell operator>>(UCell lhs, const SCell& rhs) {
  return UCell{lhs.get() >> rhs.get()};
}


/*
 * Now let's define translations from OpCodes to what the machine does
 */


void Operation<OPCODE_PLUS>::operator()(DataStack &ds) {
  UCell n1, n2;
  ds.pop(n1);
  ds.pop(n2);
  ds.push(n1 + n2);
}

void Operation<OPCODE_ONE_PLUS>::operator()(DataStack &ds) {
  UCell n1;
  ds.pop(n1);
  ds.push(n1 + static_cast<unsigned int>(1));
}

void Operation<OPCODE_MINUS>::operator()(DataStack &ds) {
  UCell n1, n2;
  ds.pop(n2);
  ds.pop(n1);
  ds.push(n1 - n2);
}

void Operation<OPCODE_ONE_MINUS>::operator()(DataStack &ds) {
  UCell n1;
  ds.pop(n1);
  ds.push(n1 - static_cast<unsigned int>(1));
}

void Operation<OPCODE_STAR>::operator()(DataStack &ds) {
  UCell n1, n2;
  ds.pop(n1);
  ds.pop(n2);
  ds.push(n1 * n2);
}

void Operation<OPCODE_SLASH>::operator()(DataStack &ds) {
  SCell n1, n2;
  ds.pop(n2);
  ds.pop(n1);
  ds.push(n1 / n2);
}

void Operation<OPCODE_MOD>::operator()(DataStack &ds) {
  SCell n1, n2;
  ds.pop(n2);
  ds.pop(n1);
  ds.push(n1 % n2);
}

void Operation<OPCODE_SLASH_MOD>::operator()(DataStack &ds) {
  SCell n1, n2;
  ds.pop(n2);
  ds.pop(n1);
  ds.push(n1 / n2);
  ds.push(n1 % n2);
}

void Operation<OPCODE_NEGATE>::operator()(DataStack &ds) {
  SCell n1;
  ds.pop(n1);
  ds.push(std::negate<SCell>{}(n1));
}

void Operation<OPCODE_ABS>::operator()(DataStack &ds) {
  SCell n1;
  ds.pop(n1);
  ds.push<SCell::type>(std::abs<SCell::type>(n1));
}

void Operation<OPCODE_MIN>::operator()(DataStack &ds) {
  SCell n1, n2;
  ds.pop(n1);
  ds.pop(n2);
  ds.push(std::min<SCell::type>(n1, n2));
}

void Operation<OPCODE_MAX>::operator()(DataStack &ds) {
  SCell n1, n2;
  ds.pop(n1);
  ds.pop(n2);
  ds.push(std::max<SCell::type>(n1, n2));
}

void Operation<OPCODE_AND>::operator()(DataStack &ds) {
  UCell n1, n2;
  ds.pop(n1);
  ds.pop(n2);
  ds.push(n1 & n2);
}

void Operation<OPCODE_OR>::operator()(DataStack &ds) {
  UCell n1, n2;
  ds.pop(n1);
  ds.pop(n2);
  ds.push(n1 | n2);
}

void Operation<OPCODE_XOR>::operator()(DataStack &ds) {
  UCell n1, n2;
  ds.pop(n1);
  ds.pop(n2);
  ds.push(n1 ^ n2);
}

void Operation<OPCODE_INVERT>::operator()(DataStack &ds) {
  UCell n1;
  ds.pop(n1);
  ds.push(~n1);
}

void Operation<OPCODE_LSHIFT>::operator()(DataStack &ds) {
  UCell u1;
  SCell n1;
  ds.pop(n1);
  ds.pop(u1);
  ds.push(u1 << n1);
}

void Operation<OPCODE_RSHIFT>::operator()(DataStack &ds) {
  UCell u1;
  SCell n1;
  ds.pop(n1);
  ds.pop(u1);
  ds.push(u1 >> n1);
}

void Operation<OPCODE_TWO_STAR>::operator()(DataStack &ds) {
  SCell n1;
  ds.pop(n1);
  ds.push(n1 * 2);
}

void Operation<OPCODE_TWO_SLASH>::operator()(DataStack &ds) {
  SCell n1;
  ds.pop(n1);
  ds.push(n1 / 2);
}

void Operation<OPCODE_LESS_THAN>::operator()(DataStack &ds) {
  SCell n1, n2;
  ds.pop(n2);
  ds.pop(n1);
  ds.push(n1 < n2);
}

void Operation<OPCODE_EQUALS>::operator()(DataStack &ds) {
  UCell n1, n2;
  ds.pop(n2);
  ds.pop(n1);
  ds.push(n1 == n2);
}

void Operation<OPCODE_GREATER_THAN>::operator()(DataStack &ds) {
  SCell n1, n2;
  ds.pop(n2);
  ds.pop(n1);
  ds.push(n1 > n2);
}

void Operation<OPCODE_ZERO_LESS_THAN>::operator()(DataStack &ds) {
  SCell n1;
  ds.pop(n1);
  ds.push(n1 < 0);
}

void Operation<OPCODE_ZERO_EQUALS>::operator()(DataStack &ds) {
  UCell n1;
  ds.pop(n1);
  ds.push(n1 == static_cast<unsigned int>(0));
}

void Operation<OPCODE_U_LESS_THAN>::operator()(DataStack &ds) {
  UCell n1, n2;
  ds.pop(n2);
  ds.pop(n1);
  ds.push(n1 < n2);
}

void Operation<OPCODE_STAR_SLASH>::operator()(DataStack &ds) {
  UCell n1, n2, n3;
  ds.pop(n3);
  ds.pop(n2);
  ds.pop(n1);
  ds.push((n1*n2)/n3);
}

void Operation<OPCODE_STAR_SLASH_MOD>::operator()(DataStack &ds) {
  SCell n1, n2, n3, n4, n5;
  ds.pop(n3);
  ds.pop(n2);
  ds.pop(n1);
  n4 = (n1*n2) % n3;
  n5 = (n1*n2) / n3;
  ds.push(n4);
  ds.push(n5);
}

void Operation<OPCODE_DROP>::operator()(DataStack &ds) {
  UCell n1;
  ds.pop(n1);
}

void Operation<OPCODE_DUP>::operator()(DataStack &ds) {
  UCell n1;
  ds.pop(n1);
  ds.push(n1);
}

void Operation<OPCODE_OVER>::operator()(DataStack &ds) {
  UCell n1, n2;
  ds.pop(n2);
  ds.pop(n1);
  ds.push(n1);
  ds.push(n2);
  ds.push(n1);
}

void Operation<OPCODE_SWAP>::operator()(DataStack &ds) {
  UCell n1, n2;
  ds.pop(n2);
  ds.pop(n1);
  ds.push(n2);
  ds.push(n1);
}

void Operation<OPCODE_ROT>::operator()(DataStack &ds) {
  UCell n1, n2, n3;
  ds.pop(n3);
  ds.pop(n2);
  ds.pop(n1);
  ds.push(n2);
  ds.push(n3);
  ds.push(n1);
}

void Operation<OPCODE_QUESTION_DUP>::operator()(DataStack &ds) {
  UCell n1;
  ds.peek(n1);
  if (n1) {
    ds.push(n1);
  }
}

void Operation<OPCODE_TWO_DROP>::operator()(DataStack &ds) {
  UCell n1, n2;
  ds.pop(n2);
  ds.pop(n1);
}

void Operation<OPCODE_TWO_DUP>::operator()(DataStack &ds) {
  UCell n1, n2;
  ds.pop(n2);
  ds.peek(n1);
  ds.push(n2);
  ds.push(n1);
  ds.push(n2);
}

void Operation<OPCODE_TWO_OVER>::operator()(DataStack &ds) {
  UCell n1, n2, n3, n4;
  ds.pop(n4);
  ds.pop(n3);
  ds.pop(n2);
  ds.pop(n1);
  ds.push(n1);
  ds.push(n2);
  ds.push(n3);
  ds.push(n4);
  ds.push(n1);
  ds.push(n2);
}

void Operation<OPCODE_TWO_SWAP>::operator()(DataStack &ds) {
  UCell n1, n2, n3, n4;
  ds.pop(n4);
  ds.pop(n3);
  ds.pop(n2);
  ds.pop(n1);
  ds.push(n3);
  ds.push(n4);
  ds.push(n1);
  ds.push(n2);
}


