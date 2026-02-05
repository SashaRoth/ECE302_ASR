#ifndef BITSET_HPP
#define BITSET_HPP
#include <stdint.h> // support for intmax_t
#include <string>

class Bitset
{
public:
  virtual ~Bitset() {}; // virtual destructor, no need to comment

  /**
   * Checks the size of the array.
   * @return Size of the array.
   */
  virtual intmax_t size() const = 0;

  /**
   * Checks the validity of the array.
   * @return True if the array is valid, false otherwise.
   */
  virtual bool good() const = 0;

  /**
   * Sets the n-th index of the array to 1.
   * @param index Index to set.
   */
  virtual void set(intmax_t index) = 0;

  /**
   * Sets the n-th index of the array to 0.
   * @param index Index to reset.
   */
  virtual void reset(intmax_t index) = 0;

  /**
   * Toggles the n-th index of the array.
   * @param index Index to toggle.
   */
  virtual void toggle(intmax_t index) = 0;

  /**
   * Checks if the n-th index of the array equals 1.
   * @param index Index to test.
   * @return True if the n-th index equals 1, false otherwise.
   */
  virtual bool test(intmax_t index) = 0;

  /**
   * Gets the array as a string.
   * @return String representation of the array.
   */
  virtual std::string asString() const = 0;
};

#endif
