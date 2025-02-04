#ifndef BITBOARD_H
#define BITBOARD_H

#include <cstdint>
#include <iostream>

using namespace std;
using U64 = uint64_t;

bool get_bit(U64 bitboard, int square);
void set_bit(U64 *bitboard, int square);
void pop_bit(U64 *bitboard, int square);
void print_bitboard(U64 bitboard);

#endif
