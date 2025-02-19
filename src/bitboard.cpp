/*************************************************************************************
 * File: bitboard.cpp
 * Description: This program contains the bitwise operations that acts as helper functions for debugging,
 * and other programs.
 *************************************************************************************/


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

//function to print out the chess board
void print_board(){
    //loop over ranks
    for(int rank = 0; rank < 8; rank++){

        //loop over files
        for(int file = 0; file < 8; file++){

            //init square
            int square = rank * 8 + file;

            //print ranks
            if(!file){
                cout << (8 - rank) << " ";
            }

            //define piece variable 
            int piece = -1;

            //loop over every bitboard piece
            for (int bb_piece = P; bb_piece < k + 1; bb_piece++){
                if (get_bit(bitboards[bb_piece], square)){
                    piece = bb_piece;
                }
            }

            cout << " ";

            if (piece == -1){
                cout << ".";
            }

            else {
                cout << unicode_pieces[piece];
            }
        }
        cout << "\n";
    }
    // print board files
    cout << "\n" << "   a b c d e f g h" << "\n";

    //print useful info
    cout << "side_move: " << (side ? "black" : "white") << "\n";
    cout << "enpassant: " << (square_to_coordinates[enpassant]) << "\n";
    cout << "castling:  " << ((castle & wk) ? "K" : "-") <<
                            ((castle & wq) ? "Q" : "-") <<
                            ((castle & bk) ? "k" : "-") <<
                            ((castle & bq) ? "q" : "-") << 
                            "\n\n";
}

void reset_board(){
    //init white pieces (pawns)
    set_bit(&bitboards[P], a2);
    set_bit(&bitboards[P], b2);
    set_bit(&bitboards[P], c2);
    set_bit(&bitboards[P], d2);
    set_bit(&bitboards[P], e2);
    set_bit(&bitboards[P], f2);
    set_bit(&bitboards[P], g2);
    set_bit(&bitboards[P], h2);

    //knights
    set_bit(&bitboards[N], b1);
    set_bit(&bitboards[N], g1);

    //bishops
    set_bit(&bitboards[B], c1);
    set_bit(&bitboards[B], f1);

    //rooks
    set_bit(&bitboards[R], a1);
    set_bit(&bitboards[R], h1);
    
    //queen
    set_bit(&bitboards[Q], d1);

    //king
    set_bit(&bitboards[K], e1);

    //init black pieces (pawns)
    set_bit(&bitboards[p], a7);
    set_bit(&bitboards[p], b7);
    set_bit(&bitboards[p], c7);
    set_bit(&bitboards[p], d7);
    set_bit(&bitboards[p], e7);
    set_bit(&bitboards[p], f7);
    set_bit(&bitboards[p], g7);
    set_bit(&bitboards[p], h7);

    //knights
    set_bit(&bitboards[n], b8);
    set_bit(&bitboards[n], g8);

    //bishops
    set_bit(&bitboards[b], c8);
    set_bit(&bitboards[b], f8);

    //rooks
    set_bit(&bitboards[r], a8);
    set_bit(&bitboards[r], h8);
    
    //queen
    set_bit(&bitboards[q], d8);

    //king
    set_bit(&bitboards[k], e8);

    //reset other variable
    side = 0;
    enpassant = no_sq;
    castle |= wk;
    castle |= wq;
    castle |= bk;
    castle |= bq;
}