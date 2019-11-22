//
// Created by lemikhovalex on 20.11.2019.
//

#ifndef UNTITLED_CONVERTER_HPP
#define UNTITLED_CONVERTER_HPP

#endif //UNTITLED_CONVERTER_HPP

#include <cstdint>
#include <bitset>
#include <iostream>
#include <vector>
#include <stdexcept>
/*
https://ru.wikipedia.org/wiki/UTF-8
*/

std::vector<uint8_t>to_utf8(const std::vector<uint32_t> &x);
std::vector<uint32_t>from_utf8(const std::vector<uint8_t> &x);

