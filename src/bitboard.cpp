/*
 * File: bitboard.cpp
 * Description: This program contains the bitwise operations, get_bit, set_bit, and pop_bit. It also
 * prints out the bitboard representation of the chess table.
 * Last Updated: 2025-01-31
 */


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


//helper function to count bits in a bitboard (Brian Kernighan's way)
int count_bits(U64 bitboard){
    int count = 0;

    while(bitboard){
        //incerement count
        count ++;

        bitboard &= bitboard - 1;

    }

    return count;
}

//get the least significant 1st bit index (as a coordinate)
int get_ls1b_index(U64 bitboard){

    //error case handling
    if (bitboard){
        //count trailing bits before LS
        return count_bits((bitboard & -bitboard) - 1);
    }

    else{
        //return illegal index
        return -1;
    }
}