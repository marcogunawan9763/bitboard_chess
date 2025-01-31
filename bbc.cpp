// system headers
#include <cstdio>
#include <cstdint>
#include <iostream>

// define bitboard data type
using namespace std;
using U64 = uint64_t;

//board squares
enum {
    a8, b8, c8, d8, e8, f8, g8, h8, 
    a7, b7, c7, d7, e7, f7, g7, h7, 
    a6, b6, c6, d6, e6, f6, g6, h6,  
    a5, b5, c5, d5, e5, f5, g5, h5, 
    a4, b4, c4, d4, e4, f4, g4, h4,  
    a3, b3, c3, d3, e3, f3, g3, h3, 
    a2, b2, c2, d2, e2, f2, g2, h2, 
    a1, b1, c1, d1, e1, f1, g1, h1
};

//bit operating macros for cleaner code
//check if there is a bit in a given square
bool get_bit(U64 bitboard, int square){
    return (bitboard & (1ULL << square));
    }

//set a bit in a given square
void set_bit(U64 *bitboard, int square){
    *bitboard |= (1ULL << square);
    }

//pop/remove a bit in a given square
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

