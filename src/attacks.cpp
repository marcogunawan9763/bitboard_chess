/*************************************************************************************
 * File: attacks.cpp
 * Description: This program generates the precalculated attack tables of every piece for lookup.
 * Last updated: 2025-02-05
 *************************************************************************************/

#include "lookup.h"
#include "attacks.h"
#include "bitboard.h"

using U64 = uint64_t;

//Lookup Tables
//leapers
U64 pawn_attacks[2][64];
U64 knight_attacks[64];
U64 king_attacks[64];

//masks
U64 bishop_masks[64];
U64 rook_masks[64];

//sliders [square][occupancies]
U64 bishop_attacks[64][512];
U64 rook_attacks[64][4096];
U64 queen_attacks[64];


/*****************************
PAWN ATTACK TABLE INITIALISER
*****************************/

//generate pawn attack mask
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

/*****************************
KNIGHT ATTACK TABLE INITIALISER
*****************************/

//generate knight attack mask
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

/*****************************
KING ATTACK TABLE INITIALISER
*****************************/

//generates king attack mask
U64 mask_king_attacks(int square){
    //result attacks bitboard
    U64 attacks = 0ULL;

    //piece bitboard
    U64 bitboard = 0ULL;

    set_bit(&bitboard, square);

    //loop over all 8 directions
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


//initialise attacks table for leaper pieces (pawns, knights, kings)
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

/*****************************
ROOK ATTACK TABLE INITIALISER
*****************************/

//generates "important" squares for rook mask -> magic bitboard
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
    while (((bitboard >> step) & (not_a_file) & (not_h_file)) && step < 64){
        attacks |= (bitboard >> step);
        step += 1;
    }

     //horizontal right
    step = 1;
    while (((bitboard << step) & (not_h_file) & (not_a_file)) && step < 64){
        attacks |= (bitboard << step);
        step += 1;
    }

    return attacks;
}

//genrates valid rook moves based on set of blockers
U64 rook_attack_on_the_fly(int sq, U64 block) {
    //return attack map
    U64 result = 0ULL;

    //initialise ranks and files
    int rk = sq/8, fl = sq%8, r, f;

    //loop over all 4 directions -> breaks if there is is a blocker in a given path
    for(r = rk+1; r <= 7; r++) {
        result |= (1ULL << (fl + r*8));
        if(block & (1ULL << (fl + r*8))) break;
    }

    for(r = rk-1; r >= 0; r--) {
        result |= (1ULL << (fl + r*8));
        if(block & (1ULL << (fl + r*8))) break;
    }

    for(f = fl+1; f <= 7; f++) {
        result |= (1ULL << (f + rk*8));
        if(block & (1ULL << (f + rk*8))) break;
    }

    for(f = fl-1; f >= 0; f--) {
        result |= (1ULL << (f + rk*8));
        if(block & (1ULL << (f + rk*8))) break;
    }

    return result;
}

/*****************************
BISHOP ATTACK TABLE INITIALISER
*****************************/

//generates "important" squares for bishop mask -> magic bitboard
U64 mask_bishop_attacks(int square){
    //result attacks bitboard
    U64 attacks = 0ULL;

    //piece bitboard
    U64 bitboard = 0ULL;

    set_bit(&bitboard, square);

    //up right
    int step = 7;

    while (((bitboard >> step) & (not_h_file) & (not_8_rank ) & (not_a_file)) && step < 64){
        attacks |= (bitboard >> step);
        step += 7;
    }

    //up left
    step = 9;

    while (((bitboard >> step) & (not_a_file) & (not_8_rank ) & (not_h_file)) && step < 64){
        attacks |= (bitboard >> step);
        step += 9;
    }

    //down right
    step = 9;

    while (((bitboard << step) & (not_h_file) & (not_1_rank) & (not_a_file)) && step < 64){
        attacks |= (bitboard << step);
        step += 9;
    }

    //down left
    step = 7;

    while (((bitboard << step) & (not_a_file) & (not_1_rank ) & (not_h_file)) && step < 64){
        attacks |= (bitboard << step);
        step += 7;
    }

    return attacks;

}

//genrates valid bishop moves based on set of blockers
U64 bishop_attack_on_the_fly(int sq, U64 block) {
    //return value
    U64 result = 0ULL;

    //initialise ranks and files
    int rk = sq/8, fl = sq%8, r, f;

    //loop over all 4 directions -> breaks if there is is a blocker in a given path
    for(r = rk+1, f = fl+1; r <= 7 && f <= 7; r++, f++) {
        result |= (1ULL << (f + r*8));
        if(block & (1ULL << (f + r * 8))) break;
    }

    for(r = rk+1, f = fl-1; r <= 7 && f >= 0; r++, f--) {
        result |= (1ULL << (f + r*8));
        if(block & (1ULL << (f + r * 8))) break;
    }

    for(r = rk-1, f = fl+1; r >= 0 && f <= 7; r--, f++) {
        result |= (1ULL << (f + r*8));
        if(block & (1ULL << (f + r * 8))) break;
    }

    for(r = rk-1, f = fl-1; r >= 0 && f >= 0; r--, f--) {
        result |= (1ULL << (f + r*8));
        if(block & (1ULL << (f + r * 8))) break;
    }

    return result;
}


/*****************************
MAGIC NUMBERS (Tord Romstad's Proposal -https://www.chessprogramming.org/Looking_for_Magics)
*****************************/

//set occupancies map for all possible "blockers" in a given path - for slider pieces
U64 set_occupancies(int index, int bits_in_mask, U64 attack_mask){
    //occupancy map
    U64 occupancy = 0ULL;

    //loop over the range of bits in a given mask
    for (int count = 0; count < bits_in_mask; count++){
    
        //get lsb1 index(attack map)
        int square = get_ls1b_index(attack_mask);

        //pop LSB in map
        pop_bit(&attack_mask, square);

        //populates occupancy map
        if (index & (1 << count)){
            occupancy |= (1ULL << square);
        }
    }

    return occupancy;

}


//creates a pseudorandom U64 number 
U64 random_U64() {
  U64 u1, u2, u3, u4;

  //take 4 random integers and slice them into their 16 bit(s) counterparts
  u1 = (U64)(random()) & 0xFFFF; u2 = (U64)(random()) & 0xFFFF;
  u3 = (U64)(random()) & 0xFFFF; u4 = (U64)(random()) & 0xFFFF;

  //combine them into a 64bit value that will "random"
  return u1 | (u2 << 16) | (u3 << 32) | (u4 << 48);
}


//creates a sparse random U64 number (not a lot of 1s) - > optimiser
U64 random_U64_fewbits() {
  return random_U64() & random_U64() & random_U64();
}


//transforms a bitboard by its multiplication to a magic number
int transform(U64 bitboard, U64 magic, int bits){
    return (int)((bitboard * magic) >> (64 - bits));
}


//find the magic number (square, num bits, bishop flag)
U64 find_magic(int sq, int m, int bishop){
    //Get bishop or rook mask
    U64 mask = bishop ? mask_bishop_attacks(sq) : mask_rook_attacks(sq); 

    // blockers, attacks, used attacks, magic
    U64 b[4096], a[4096], used[4096], magic;

    //indexes, fail flag
    int i, j, k, fail;

    // Number of relevant squares
    int n = count_bits(mask);  

    // Generate all possible blocker combinations
    for(i = 0; i < (1 << n); i++) {
        b[i] = set_occupancies(i, n, mask);
        // Get attack set
        a[i] = bishop ? bishop_attack_on_the_fly(sq, b[i]) : rook_attack_on_the_fly(sq, b[i]); 
    }

    // Try up to 100M random magic numbers
    for(k = 0; k < 100000000; k++) {
        magic = random_U64_fewbits(); // Generate a candidate magic number
        if(count_bits((mask * magic) & 0xFF00000000000000ULL) < 6) continue; // Quick rejection 

    // Reset used table
    for(i = 0; i < 4096; i++) used[i] = 0ULL;

    // Test if this magic number results in unique mappings
    for(i = 0, fail = 0; !fail && i < (1 << n); i++) {
        j = transform(b[i], magic, m);
        if(used[j] == 0ULL) used[j] = a[i];  // First time seeing this index
        else if(used[j] != a[i]) fail = 1;  // Collision: magic number is invalid
    }

    // Found a valid magic number
    if(!fail) return magic; 
    }

    printf("***Failed***\n");
    return 0ULL;
}

/*****************************
INITIALISE SLIDER ATTACKS
*****************************/

void init_slider_attacks(int bishop){
    //loop over squares
    for (int square = 0; square < 64; square++){
        //init bishop & rook masks
        bishop_masks[square] = mask_bishop_attacks(square);
        rook_masks[square] = mask_rook_attacks(square);

        //init current mask
        U64 attack_mask = bishop ? bishop_masks[square] : rook_masks[square];

        //init relevant occupancy bit count
        int relevant_bits = count_bits(attack_mask);

        //int occupancy indices
        int occupancy_indices = (1 << relevant_bits);

        for(int index = 0; index < occupancy_indices; index++){
            //bishop
            if (bishop){
                U64 occupancy = set_occupancies(index, relevant_bits, attack_mask);

                int magic_index = (occupancy * bishop_magic[square]) >> (64 - bishop_relevant_bits[square]);

                bishop_attacks[square][magic_index] = bishop_attack_on_the_fly(square,occupancy);
            }

            else{
                U64 occupancy = set_occupancies(index, relevant_bits, attack_mask);

                int magic_index = (occupancy * rook_magic[square]) >> (64 - rook_relevant_bits[square]);

                rook_attacks[square][magic_index] = rook_attack_on_the_fly(square,occupancy);
            }
        }
    }
}

U64 get_bishop_attacks(int square, U64 occupancy){
    //get bishop attacks assuming board occupancy
    occupancy &= bishop_masks[square];
    occupancy *= bishop_magic[square];
    occupancy >>= 64 - bishop_relevant_bits[square];

    return bishop_attacks[square][occupancy];
}

U64 get_rook_attacks(int square, U64 occupancy){
    //get rook attacks assuming board occupancy
    occupancy &= rook_masks[square];
    occupancy *= rook_magic[square];
    occupancy >>= 64 - rook_relevant_bits[square];

    return rook_attacks[square][occupancy];
}

U64 get_queen_attacks(int square, U64 occupancy){
    //init result attacks bitboard
    U64 queen_attacks = 0ULL;

    //get bishop attacks
    queen_attacks = get_bishop_attacks(square, occupancy);

    //get rook attacks
    queen_attacks |= get_rook_attacks(square, occupancy);

    return queen_attacks;
}

void init_all(){
    init_leaper_attacks();
    init_slider_attacks(0);
    init_slider_attacks(1);
}


