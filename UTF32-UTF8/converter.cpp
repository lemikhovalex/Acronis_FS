//
// Created by lemikhovalex on 20.11.2019.
//

#include "converter.hpp"


static inline uint8_t get_l_6_of_8(uint32_t x)
/*returns last 6 digits as uint8_t */
{
    return 0b10000000 + (uint8_t)(x & 0b00111111u);
}

static inline bool is_a_pieace(uint8_t x)
/* if the first and the second digit are equal to 1 and 0 returns true, else False
 * it means that this 8bits are a piece of big one letter
 * */
{
    return ((x & 128u) && !(x & 64u));
}

static void push_utf8_from_utf32(std::uint32_t utf32_ch, std::vector<uint8_t> &acceptor)
/* let's covert one single caracter and push it to the somewhere(acceptor)*/
{
    /* firstly we need to find out, how long there will be a utf8 caracter */
    if (utf32_ch <= (uint32_t)0x7f)
    /* the simplest case - just push back whole character */
    {
        acceptor.push_back((uint8_t) utf32_ch);
    }
    else if (utf32_ch <= (uint32_t)0x7ff)
    /*
     *to solve it - go to https://ru.wikipedia.org/wiki/UTF-8 and look to the second table
     * separating char to pieces of length 6
     */
    {
        acceptor.push_back((uint8_t)(0b11000000 + (uint8_t)(utf32_ch >> 6u)));
        acceptor.push_back(get_l_6_of_8(utf32_ch));
    }
    else if (utf32_ch <= (uint32_t)0xffff)
    {
        acceptor.push_back((uint8_t)(0b11100000 + (uint8_t)(utf32_ch >> 12u)));
        acceptor.push_back(get_l_6_of_8(utf32_ch >> 6u));
        acceptor.push_back(get_l_6_of_8(utf32_ch));
    }
    else if (utf32_ch <= (uint32_t)0x10ffff)
    {
        acceptor.push_back((uint8_t)(0b11110000 + (uint8_t)(utf32_ch >> 18u)));
        acceptor.push_back(get_l_6_of_8(utf32_ch >> 12u));
        acceptor.push_back(get_l_6_of_8(utf32_ch >> 6u));
        acceptor.push_back(get_l_6_of_8(utf32_ch));
    }
}


std::vector<uint8_t>to_utf8(const std::vector<uint32_t> &utf32_str)
/* now let's convert string(vector<uint32_t>) of utf32 to vector<uint8_t> */
{
    std::vector<uint8_t> out;
    for (int i = 0; i < utf32_str.size(); ++i)
    /*
     * just iterating over characters
     */
    {
        push_utf8_from_utf32(utf32_str[i], out);
    }
    return out;
}

std::vector<uint32_t>from_utf8(const std::vector<uint8_t> &utf8_string)
/* now it's time to roll back to familiar utf32 */
{
    std::vector<uint32_t> result;
    uint32_t to_push = 0;

    for (int i = 0; i < utf8_string.size();)
    /*  iterating over characters in string. for better understanding start from the bottom */
    {
        if ((utf8_string[i] >> 3u) == 0b00011110u)
        {
            to_push += ((uint32_t)utf8_string[i++] & 0b00000111u) << 18u;
            for (int j = 0u; j < 3u; ++j)
            {
                if (is_a_pieace(utf8_string[i]))
                    to_push += ((uint32_t)utf8_string[i++] & 0b00111111u)<< (2 - j)*6u;
                else{
                    throw std::runtime_error("Why not 4 bytes");
                }
            }
        }
        else if ((utf8_string[i] >> 4u) == 0b0001110u)
        /* to avoid writing lot's of strings go cycling */
        {
            to_push += ((uint32_t)utf8_string[i++] & 0b00001111u) << 12u;
            for (int j = 0; j < 2; ++j) {
                if (is_a_pieace(utf8_string[i]))
                    to_push += ((uint32_t)utf8_string[i++] & 0b00111111u)
                            << (1 - j)*6u;
                else {
                    throw std::runtime_error("Why not 3 bytes");
                }
            }
        }
        else if ((utf8_string[i] >> 5u) == 0b000110u)
        /* the next level decoding - checking if there is only 2 * 8 bytes. Then just converting */
        {
            to_push += ((uint32_t)utf8_string[i++] & 0b00011111u) << 6u;
            if (is_a_pieace(utf8_string[i]))
                to_push += ((uint32_t)utf8_string[i++] & 0b00111111u);
            else {
                throw std::runtime_error("Why not 2 bytes");
            }
        }
        else
        /* the simpliest case - just push back */
            to_push = (uint32_t)utf8_string[i++];
        result.push_back(to_push);
        to_push = 0;
    }

    return result;
}

