#ifndef BITARRAY_HPP
#define BITARRAY_HPP
#include <stdint.h>
#include <string>

#include "bitset.hpp"

class BitArray : public Bitset
{
public:
  /**
   * Class constructor.
   */
  BitArray();

  /**
   * Class constructor specifying size of array.
   * @param size Size of the bit array.
   */
  BitArray(intmax_t size);

  /**
   * Class constructor which uses a string to initialize the bit array.
   * @param value String representing the bit array.
   */
  BitArray(const std::string &value);

  ~BitArray();

  BitArray(const BitArray &) = delete;            // not Copy-Constructible
  BitArray &operator=(const BitArray &) = delete; // not Copy-Assignable

  intmax_t size() const;

  bool good() const;

  void set(intmax_t index);

  void reset(intmax_t index);

  void toggle(intmax_t index);

  bool test(intmax_t index);

  std::string asString() const;

private:
  intmax_t current_size;
  uint8_t *data;
  bool valid;
};

// New method for checkoff
std::string complement(BitArray &array);

#endif