#include "lookup.h"
#include "bitboard.h"
#include "attacks.h"

int main()
{     

    //initialise leaper pieces attacks
    init_pawn_attacks();
    print_bitboard(pawn_attacks[black][e2]);
    print_bitboard(not_a_file);
    
    

    return 0;
}