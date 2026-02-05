#include "bitarray.hpp"

BitArray::BitArray()
{
    valid = true;     // default to valid
    current_size = 8; // default size
    data = new uint8_t[current_size];
    for (int i = 0; i < current_size; i++)
    {
        data[i] = 0;
    }
}

BitArray::BitArray(intmax_t size)
{
    valid = true;        // default to valid
    current_size = size; // set size based on input
    if (size <= 0)
    {
        data = new uint8_t[0];
        valid = false;
    }
    else
    {
        data = new uint8_t[current_size];
        for (int i = 0; i < current_size; i++)
        {
            data[i] = 0;
        }
    }
}

BitArray::BitArray(const std::string &value)
{
    valid = true;                // default to valid
    current_size = value.size(); // set size based on string length
    data = new uint8_t[current_size];
    for (int i = 0; i < current_size; i++)
    {
        if (value.at(i) != '0' && value.at(i) != '1')
        {
            valid = false;
        }
        data[i] = value.at(i) - '0';
    }
}

// Was having memory deallocation errors, so I referenced stack exchange
// for proper destructor syntax
BitArray::~BitArray()
{
    delete[] data; // deallocate memory
}

intmax_t BitArray::size() const
{
    return current_size; // return current size
}

bool BitArray::good() const
{
    return valid; // return validity
}

void BitArray::set(intmax_t index)
{
    if (index < 0 || index >= current_size) // bounds checking
    {
        valid = false; // mark as invalid if out of bounds
    }
    else
    {
        data[index] = 1; // set bit to 1
    }
}

void BitArray::reset(intmax_t index)
{
    if (index < 0 || index >= current_size) // bounds checking
    {
        valid = false; // mark as invalid if out of bounds
    }
    else
    {
        data[index] = 0; // set bit to 0
    }
}

void BitArray::toggle(intmax_t index)
{
    if (index < 0 || index >= current_size) // bounds checking
    {
        valid = false; // mark as invalid if out of bounds
    }
    else if (data[index] == 0) // toggle bit
    {
        data[index] = 1;
    }
    else
    {
        data[index] = 0;
    }
}

bool BitArray::test(intmax_t index)
{
    if (index < 0 || index >= current_size) // bounds checking
    {
        valid = false; // mark as invalid if out of bounds
        return false;
    }
    return data[index] == 1; // compare bit to 1
}

std::string complement(BitArray &array)
{
    if (array.test(0) == 0)
    {
        return array.asString();
    }

    for (int i = 0; i < array.size(); i++) // if negative, toggle every bit
    {
        array.toggle(i);
    }

    bool carry = true;
    int count = array.size() - 1;

    while ((carry == true) && count >= 0)
    {
        if (array.test(count) == 0)
        {
            array.toggle(count);
            carry = false;
        }
        else if (array.test(count) == 1)
        {
            array.toggle(count);
            carry == true;
        }
        count--;
    }

    return array.asString();
}

std::string BitArray::asString() const
{
    std::string result = ""; // initialize empty string
    for (int i = 0; i < current_size; i++)
    {
        result += std::to_string(data[i]); // append each bit to string
    }
    return result; // return the string representation
}
