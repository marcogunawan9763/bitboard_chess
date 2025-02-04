#ifndef ATTACKS_H
#define ATTACKS_H

#include <cstdint>
#include <iostream>

using namespace std;
using U64 = uint64_t;

U64 mask_pawn_attacks(int side, int square);
void init_pawn_attacks();

U64 mask_knight_attacks(int square);
void init_knight_attacks();

U64 mask_rook_attacks(int square);
void init_rook_attacks();

// Lookup tables
extern U64 pawn_attacks[2][64];
extern U64 knight_attacks[64];
extern U64 bishop_attacks[64];
extern U64 rook_attacks[64];
extern U64 queen_attacks[64];
extern U64 king_attacks[64];

#endif