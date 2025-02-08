/*
 * File: attacks.cpp
 * Description: This program generates the precalculated attack tables of every piece for lookup.
 * Last updated: 2025-02-05
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

/*
KNIGHT ATTACK TABLE INITIALISER

*/

U64 mask_knight_attacks(int square){

    //result attacks bitboard
    U64 attacks = 0ULL;

    //piece bitboard
    U64 bitboard = 0ULL;

    set_bit(&bitboard, square);

    if (((bitboard >> 6) & not_ab_file) && not_1_rank) attacks |= (bitboard >> 6);
    if (((bitboard >> 10) & not_hg_file) && not_1_rank) attacks |= (bitboard >> 10);
    if (((bitboard >> 15) & not_a_file) && not_12_rank) attacks |= (bitboard >> 15);
    if (((bitboard >> 17) & not_h_file) && not_12_rank) attacks |= (bitboard >> 17);

    if (((bitboard << 10) & not_ab_file) && not_8_rank) attacks |= (bitboard << 10);
    if (((bitboard << 6) & not_hg_file) && not_8_rank) attacks |= (bitboard << 6); 
    if (((bitboard << 15) & not_h_file) && not_78_rank) attacks |= (bitboard << 15);
    if (((bitboard << 17) & not_a_file) && not_78_rank) attacks |= (bitboard << 17);

    //return possible attacks for a knight at a given square
    return attacks;
}

/*
KING ATTACK TABLE INITIALISER
*/

U64 mask_king_attacks(int square){
    //result attacks bitboard
    U64 attacks = 0ULL;

    //piece bitboard
    U64 bitboard = 0ULL;

    set_bit(&bitboard, square);

    if (bitboard >> 8) attacks |= (bitboard >> 8);
    if ((bitboard >> 9) & not_h_file) attacks |= (bitboard >> 9);
    if ((bitboard >> 7) & not_a_file) attacks |= (bitboard >> 7);
    if ((bitboard >> 1) & not_h_file) attacks |= (bitboard >> 1);

    if (bitboard << 8) attacks |= (bitboard << 8);
    if ((bitboard << 9) & not_h_file) attacks |= (bitboard << 9);
    if ((bitboard << 7) & not_a_file) attacks |= (bitboard << 7);
    if ((bitboard << 1) & not_h_file) attacks |= (bitboard << 1);

    return attacks;
}

/*
ROOK ATTACK TABLE INITIALISER
*/


U64 mask_rook_attacks(int square){
    //result attacks bitboard
    U64 attacks = 0ULL;

    //piece bitboard
    U64 bitboard = 0ULL;

    set_bit(&bitboard, square);

    //variable to move the rook square
    int step = 8;
 
    //vertical up (have to check for step < 64, else from the 1st rank and going up )
    while (((bitboard >> step) & not_8_rank) && (step < 64)){
        attacks |= (bitboard >> step);
        step += 8;
    }

    //vertical down
    step = 8;
    while (((bitboard << step) & not_1_rank) && step < 64){
        attacks |= (bitboard << step);
        step += 8;
    }

    //horizontal left
    step = 1;
    while (((bitboard >> step) & (not_a_file)) && step < 64){
        attacks |= (bitboard >> step);
        step += 1;
    }

     //horizontal right
    step = 1;
    while (((bitboard << step) & (not_h_file)) && step < 64){
        attacks |= (bitboard << step);
        step += 1;
    }

    return attacks;
}

/*
BISHOP ATTACK INITIALISER
*/

U64 mask_bishop_attacks(int square){
    //result attacks bitboard
    U64 attacks = 0ULL;

    //piece bitboard
    U64 bitboard = 0ULL;

    set_bit(&bitboard, square);

    //up right
    int step = 7;

    while (((bitboard >> step) & (not_h_file) & (not_8_rank )) && step < 64){
        attacks |= (bitboard >> step);
        step += 7;
    }

    //up left
    step = 9;

    while (((bitboard >> step) & (not_a_file) & (not_8_rank )) && step < 64){
        attacks |= (bitboard >> step);
        step += 9;
    }

    //down right
    step = 9;

    while (((bitboard << step) & (not_h_file) & (not_1_rank )) && step < 64){
        attacks |= (bitboard << step);
        step += 9;
    }

    //down left
    step = 7;

    while (((bitboard << step) & (not_a_file) & (not_1_rank )) && step < 64){
        attacks |= (bitboard << step);
        step += 7;
    }

    return attacks;

}

//initialise attacks table
void init_leaper_attacks(){
    for (int square = 0; square < 64; square++){
        //initialise pawn tables
        pawn_attacks[white][square] = mask_pawn_attacks(white, square);
        pawn_attacks[black][square] = mask_pawn_attacks(black, square);

        //initialise knight tables
        knight_attacks[square] = mask_knight_attacks(square);

        //initialise king tables
        king_attacks[square] = mask_king_attacks(square);
    }
}

//initilaises rook attacks
void init_slider_attacks(){
    for (int square = 0; square < 64; square++){
        rook_attacks[square] = mask_rook_attacks(square);
    }
}