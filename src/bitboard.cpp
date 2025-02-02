#include "lookup.h"
#include "bitboard.h"


//checks if there is a bit in a given square
bool get_bit(U64 bitboard, int square){
    return (bitboard & (1ULL << square));
    }

//set a bit in a given square
void set_bit(U64 *bitboard, int square){
    *bitboard |= (1ULL << square);
    }

//remove a bit in a given square
void pop_bit(U64 *bitboard, int square){
    get_bit(*bitboard, square) ? *bitboard ^= (1ULL << square) : 0;
    }

//print bitboard
void print_bitboard(U64 bitboard){

    cout << "\n";

    //loop over board ranks
    for (int rank = 0; rank < 8; rank++){

        //loop over board files
        for (int file = 0; file < 8; file++){

            //convert file & rank into square index
            int square = rank * 8 + file;

            //print ranks
            if(!file){
                cout << (8 - rank) << " ";
            }

            //print bitboard state (either 1 or 0)
            cout << " " << (get_bit(bitboard, square) ? 1 : 0);
        }

        //print new line every rank
        cout << "\n";
    }

    // print board files
    cout << "   a b c d e f g h";

    //print bitboard as unsigned decimal number
    cout << "\n\nBitboard: " << bitboard << "\n\n";
}