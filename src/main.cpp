#include "bitboard.h"

int main()
{   
    //define bitboard
    U64 bitboard = 0ULL;

    //setting some bits
    set_bit(&bitboard, e2);
    set_bit(&bitboard, c4);
    set_bit(&bitboard, g7);

    pop_bit(&bitboard, e2);

    //print bitboard
    print_bitboard(bitboard);


    return 0;
}