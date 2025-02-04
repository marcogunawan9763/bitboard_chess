/*
 * File: attacks.cpp
 * Description: This program generates the precalculated attack tables of every piece for lookup.
 * Date: 2025-01-31
 */


#include "lookup.h"
#include "attacks.h"
#include "bitboard.h"

using U64 = uint64_t;

//Lookup Tables
U64 pawn_attacks[2][64];
U64 knight_attacks[64];
U64 bishop_attacks[64];
U64 rook_attacks[64];
U64 queen_attacks[64];
U64 king_attacks[64];

/*
PAWN ATTACK TABLE INITIALISER

*/

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

    //return possible attacks for a pawn at a given square
    return attacks;
}

//initialise pawn attacks table
void init_pawn_attacks(){
    for (int square = 0; square < 64; square++){
        pawn_attacks[white][square] = mask_pawn_attacks(white, square);
        pawn_attacks[black][square] = mask_pawn_attacks(black, square);
    }
}

/*
KNIGHT ATTACK TABLE INITIALISER

*/

U64 mask_knight_attacks(int square){

    //result attacks bitboard
    U64 attacks = 0ULL;

    //piece bitboard
    U64 bitboard = 0ULL;

    set_bit(&bitboard, square);

    //can U
    if(not_1_rank){
        //can RR
        if ((bitboard >> 6) & not_ab_file){
            attacks |= (bitboard >> 6);
        }
        
        //can LL
        if ((bitboard >> 10) & not_hg_file){
            attacks |= (bitboard >> 10);
        }

    }

    //can UU
    if (not_12_rank){
        //can R
        if ((bitboard >> 15) & not_a_file){
            attacks |= (bitboard >> 15);
        }
        
        //can L
        if ((bitboard >> 17) & not_h_file){
            attacks |= (bitboard >> 17);
        }

    }

    //can D
    if(not_8_rank){
        //can RR
        if ((bitboard << 10) & not_ab_file){
            attacks |= (bitboard << 10);
        }
        
        //can LL
        if ((bitboard << 6) & not_hg_file){
            attacks |= (bitboard << 6); 
        }

    }
    
    //can DD
    if (not_78_rank){
        //can L
        if ((bitboard << 15) & not_h_file){
            attacks |= (bitboard << 15);
        }
        
        //can R
        if ((bitboard << 17) & not_a_file){
            cout << "yay";
            attacks |= (bitboard << 17);
        }

    }

    //return possible attacks for a knight at a given square
    return attacks;
}

//initialise knight attacks table
void init_knight_attacks(){
    for (int square = 0; square < 64; square++){
        knight_attacks[square] = mask_knight_attacks(square);
    }
}


/*
ROOK ATTACK TABLE INITIALISER

*/