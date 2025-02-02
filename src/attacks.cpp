#include "lookup.h"
#include "attacks.h"
#include "bitboard.h"

using U64 = uint64_t;

U64 pawn_attacks[2][64];

//generate pawn attacks
U64 mask_pawn_attacks(int side, int square){

    //result attacks bitboard
    U64 attacks = 0ULL;

    //piece bitboard
    U64 bitboard = 0ULL;

    set_bit(&bitboard, square);

    //white pawns
    if (!side){
        if((bitboard >> 7) & not_a_file){
            attacks |= (bitboard >> 7);
        } 
        if((bitboard >> 9) & not_h_file){
            attacks |= (bitboard >> 9);
        } 
    }

    else{
        if((bitboard << 7) & not_h_file){
            attacks |= (bitboard << 7);
        } 
        if((bitboard << 9) & not_a_file){
            attacks |= (bitboard << 9);
        } 
    }

    return attacks;
}

void init_pawn_attacks(){
    for (int square = 0; square < 64; square++){
        pawn_attacks[white][square] = mask_pawn_attacks(white, square);
        pawn_attacks[black][square] = mask_pawn_attacks(black, square);
    }
}

