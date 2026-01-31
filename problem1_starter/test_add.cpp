#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "add.hpp"

double THRESHOLD = 0.0001;

TEST_CASE("Test add", "[Add]")
{
  Add<int> a;
  REQUIRE(a.call(1, 2) == 3); // passes

  Add<long> b;
  REQUIRE(b.call(50000000L, 60000000L) == 110000000L); // passes

  Add<double> c;
  REQUIRE(c.call(3 - sqrt(2), 4 + sqrt(2)) - 7.0 < THRESHOLD); // passes

  Add<char> d;
  /*
  REQUIRE(d.call('2', '3') == '5'); <-- FAILS

  Chars are converted to their ASCII values when adding them with the basic + operand, which
  returns an unexpected result. In this case: '2' is 50 and '3' is 51 in ASCII, so the result
  is 101, which corresponds to 'e' --> it fails

  The correct test would be:
  */
  REQUIRE(d.call('2', '3') == 'e');

  Add<std::string> e;
  /*
  REQUIRE(e.call("2", "3") == "5"); <-- FAILS

  Strings are concatenated when using the + operator, so this test will also fail

  The correct test would be:
  */
  REQUIRE(e.call("2", "3") == "23");

  Add<bool> f;
  /*
  REQUIRE(f.call(true, true) == 2);

  This class implementation (Add<bool>) converts the arguments to integers (true = 1, false = 0)
  and then returns that value as a bool. Bools can only be true or false, so any non-zero
  value is converted to true. Therefore, it cannot return 2, and it will fail.

  The correct test would be:
  */
  REQUIRE(f.call(true, true) == true);
}

/* Answers to questions:

1. Test cases should test all methods of a class. In this case, we have developed several
test cases to test call() with different data types. However, we still need to test the constructor
and destructor, to verify that the class instantiates correctly and that there are no memory leaks
or other issues when an object of the class is destroyed.

2. Yes, if we want call() to behave as question 5 expected for all data types, we need to overload
the + operator for chars and strings. In this case, we wants chars to be added by their numerical value
instead of their ASCII value, and we want strings to be added numerically instead of concatenated. The
call() function also failed for the bool type, but this was caused by a mismatch in return type; it
would not be addressed by overloading the + operator.

*/
