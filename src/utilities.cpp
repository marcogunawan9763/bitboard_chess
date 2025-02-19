/*************************************************************************************
 * File: utilities.cpp
 * Description: This program contains utility functions for the bitboard chess engine.
 *************************************************************************************/

#include "utilities.h"
#include "lookup.h"
#include "bitboard.h"

//parses a FEN string to initialise BITBOARDS, OCUUPANCIES & board state
void parse_FEN(string fen){
    //reset board positions and occupancies
    memset(&bitboards, 0ULL, sizeof(bitboards));
    memset(&occupancies, 0ULL, sizeof(occupancies));

    //reset game variables
    side = 0;
    enpassant = no_sq;
    castle = 0;

    //init square
    int square = 0;

    //seperate FEN string into sections
    istringstream fenStream(fen);
    string section;

    //loop over every section
    for (int i = 0; i <= 3; i++) {
        fenStream >> section;

        //section 1(index 0) -> board position
        if (i == 0){
            for(char c : section){
                if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')){
                    //get piece
                    int piece = char_pieces.at(c);

                    //set_bitboard piece
                    set_bit(&bitboards[piece], square);


                    //increment square
                    square++;
                }

                if (c >= '0' && c < '9'){
                    //change character to integer (offset)
                    int offset = c - '0';

                    //increment square by offset
                    square += offset;
                }
            }    
        }

        //section 2(index 1) -> side to move
        if (i == 1){
            side = (section == "w" ? 0 : 1);
        }

        //section 3(index 2) -> castling rights
        if (i == 2){
            if (section == "-")continue;
            for (char c : section){
                if (c == 'K')castle |= wk;
                if (c == 'Q')castle |= wq;
                if (c == 'k')castle |= bk;
                if (c == 'q')castle |= bq;
            }
        }

        //section 4(index 3) -> enpassant
        if (i == 3){
            if (section == "-")continue;
            //arithmetic to get enpassant square
            int file = (section[0] - 'a');
            int rank = 8 - (section[1] - '0');
            enpassant = rank * 8 + file;
        }
    }

    cout << "\n";

    //populate occupancies
    for (int piece = P; piece <= K; piece++){
        occupancies[white] |= bitboards[piece];
    }

    for (int piece = p; piece <= k; piece++){
        occupancies[black] |= bitboards[piece];
    }

    occupancies[both] |= occupancies[white];
    occupancies[both] |= occupancies[black];
}