#ifndef ATTACKS_H
#define ATTACKS_H

#include <cstdint>
#include <iostream>

using namespace std;
using U64 = uint64_t;

U64 mask_pawn_attacks(int side, int square);
U64 mask_knight_attacks(int square);
U64 mask_king_attacks(int square);
void init_leaper_attacks();

U64 mask_rook_attacks(int square);
U64 mask_bishop_attacks(int square);
U64 rook_attack_on_the_fly(int square, U64 blockers);
U64 bishop_attack_on_the_fly(int square, U64 blockers);

U64 set_occupancies(int index, int bits_in_mask, U64 attack_mask);
U64 random_U64();
U64 random_U64_fewbits();
int transform(U64 bitboard, U64 magic, int bits);
U64 find_magic(int sq, int m, int bishop);

void init_slider_attacks(int bishop);
U64 get_bishop_attacks(int square, U64 occupancy);
U64 get_rook_attacks(int square, U64 occupancy);

void init_all();

// Lookup tables
extern U64 pawn_attacks[2][64];
extern U64 knight_attacks[64];
extern U64 king_attacks[64];

extern U64 bishop_attacks[64][512];
extern U64 rook_attacks[64][4096];
extern U64 queen_attacks[64];

#endif