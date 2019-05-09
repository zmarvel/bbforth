
#include <limits>
#include "catch.hpp"

#include "operation.hpp"


TEST_CASE("Cell addition operations work as expected", "[addition]") {
  SECTION("Signed cells can store min and max int") {
    SCell s1{std::numeric_limits<int>::min()},
          s2{std::numeric_limits<int>::max()};
    REQUIRE(s1 == std::numeric_limits<int>::min());
    REQUIRE(s2 == std::numeric_limits<int>::max());
  }

  SECTION("Unsigned cells can store min and max unsigned int") {
    UCell u1{std::numeric_limits<unsigned int>::min()},
          u2{std::numeric_limits<unsigned int>::max()};
    REQUIRE(u1 == std::numeric_limits<unsigned int>::min());
    REQUIRE(u2 == std::numeric_limits<unsigned int>::max());
  }

  SECTION("Signed cells can be added") {
    SCell s1{std::numeric_limits<int>::min()},
          s2{std::numeric_limits<int>::max()};
    SCell result1 = s1 + s2;
    SCell result2 = s2 + s1;
    REQUIRE(result1.get() == -1);
    REQUIRE(result1.get() == result2.get());
  }
 
  SECTION("Unsigned cells can be added") {
    UCell u1{std::numeric_limits<unsigned int>::min()},
          u2{std::numeric_limits<unsigned int>::max()};
    UCell result1 = u1 + u2;
    UCell result2 = u2 + u1;
    REQUIRE(result1.get() == std::numeric_limits<unsigned int>::max());
    REQUIRE(result1.get() == result2.get());
  }

  SECTION("Signed cells can be added with unsigned cells") {
    {
      UCell u1{std::numeric_limits<unsigned int>::min()};
      SCell s1{std::numeric_limits<int>::max()};
      UCell r1 = u1 + s1;
      REQUIRE(r1.get() == std::numeric_limits<int>::max());
    }
    {
      UCell u1{std::numeric_limits<unsigned int>::min()};
      SCell s1{std::numeric_limits<int>::max()};
      SCell r1 = u1 + s1;
      REQUIRE(r1.get() == std::numeric_limits<int>::max());
    }
    {
      UCell u1{std::numeric_limits<unsigned int>::min()};
      SCell s1{std::numeric_limits<int>::max()};
      UCell r1 = s1 + u1;
      REQUIRE(r1.get() == std::numeric_limits<int>::max());
    }
    {
      UCell u1{std::numeric_limits<unsigned int>::min()};
      SCell s1{std::numeric_limits<int>::max()};
      SCell r1 = s1 + u1;
      REQUIRE(r1.get() == std::numeric_limits<int>::max());
    }
  }
}

TEST_CASE("Cell subtraction operations work as expected", "[subtraction]") {
  SECTION("Signed cells can be subtracted") {
    SCell s1{std::numeric_limits<SCell::type>::max()},
          s2{std::numeric_limits<SCell::type>::max()};
    REQUIRE((s1 - s2).get() == 0);
  }
}
