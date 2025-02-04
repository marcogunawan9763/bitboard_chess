#include "lookup.h"
#include "bitboard.h"
#include "attacks.h"

int main()
{     

    /*
    
    for(int rank = 0; rank < 8; rank ++){
        for(int file = 0; file < 8; file++){
            int square = rank * 8 + file;

            if (rank > 0){
                set_bit(&bitboard, square);
            }
        }
    }
    */
    init_pawn_attacks();    
    init_knight_attacks();

    print_bitboard(knight_attacks[e3]);
    print_bitboard(pawn_attacks[white][d3]);

    
    
    

    return 0;
}