#ifndef ATTACKS_H
#define ATTACKS_H

#include <cstdint>
#include <iostream>

using namespace std;
using U64 = uint64_t;

U64 mask_pawn_attacks(int side, int square);
void init_pawn_attacks();
extern U64 pawn_attacks[2][64];

#endif