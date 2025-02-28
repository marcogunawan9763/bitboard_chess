/*************************************************************************************
 * File: movegen.cpp
 * Description: This program creates the move generation for any given board,
 *************************************************************************************/

#include "lookup.h"
#include "attacks.h"
#include "bitboard.h"

void generate_moves(){
    //define source squre and target square
    int src_square, target_square;

    //define current piece's bitboard and is attacks
    U64 bitboard, attacks;

    cout << "side: " << white << "\n";

    for(int piece = P; piece <=k; piece++){
        //init piece bitboard
        bitboard = bitboards[piece];

        //generate white pawns and white castling moves
        if(side == white){
            //white pawns
            if (piece == P){
                //loop over every pawns
                while(bitboard){
                    //init source square
                    src_square = get_ls1b_index(bitboard);

                    //init target square
                    target_square = src_square - 8;

                    //generate quite pawn moves (promotion, 1 ahead, 2 ahead)
                    if(!(target_square < a8) && !get_bit(occupancies[both], target_square)){
                        //pawn promotion
                        if (src_square >= a7 && src_square <= h7){
                            //loop over all promotion pieces
                            for(int p = N; p <= Q; p++){
                                cout << "pawn promotion: " << square_to_coordinates[src_square] << square_to_coordinates[target_square] << ascii_pieces[p] << "\n";
                            }
                        }

                        else{
                            //one square ahead
                            cout << "pawn push: " << square_to_coordinates[src_square] << square_to_coordinates[target_square] << "\n";

                            //two square ahead
                            if ((src_square >= a2 && src_square <= h2) && !get_bit(occupancies[both] , target_square - 8)){
                                cout << "pawn double push: " << square_to_coordinates[src_square] <<  square_to_coordinates[target_square - 8] << "\n";
                            }
                        }
                    }

                    //init pawn attacks bitboard
                    attacks = pawn_attacks[side][src_square] & occupancies[black];

                    //generate pawn attacks
                    while (attacks){
                        //init target square
                        target_square = get_ls1b_index(attacks);

                        //pawn capture promotion
                        if (src_square >= a7 && src_square <= h7){
                            //loop over all promotion pieces
                            for(int p = N; p <= Q; p++){
                                cout << "pawn capture promotion: " << square_to_coordinates[src_square] << "x" << square_to_coordinates[target_square] << ascii_pieces[p] << "\n";
                            }
                        }

                        else{
                            //other captures
                            cout << "pawn capture: " << square_to_coordinates[src_square] << "x" << square_to_coordinates[target_square] << "\n";
                        }

                        //pop bit
                        pop_bit(&attacks, target_square);
                    }

                    //enpassants
                    if (enpassant != no_sq){
                        U64 enpassant_attacks = pawn_attacks[side][src_square] & (1ULL << enpassant);
                        int target_square = get_ls1b_index(enpassant_attacks);

                        if(enpassant_attacks){
                            cout << "pawn enpassant capture: " << square_to_coordinates[src_square] << "x" << square_to_coordinates[target_square] << "\n";
                        }
                    }

                    //pop lsb1 bit
                    pop_bit(&bitboard, src_square);
                }
            }
        }

        //generate black pawns and black castling moves
        else{
            //black pawns
            if (piece == p){
                //loop over every pawns
                while(bitboard){
                    //init source square
                    src_square = get_ls1b_index(bitboard);

                    //init target square
                    target_square = src_square + 8;

                    //generate quite pawn moves (promotion, 1 ahead, 2 ahead)
                    if(!(target_square > a1) && !get_bit(occupancies[both], target_square)){
                        //pawn promotion
                        if (src_square >= a2 && src_square <= h2){
                            //loop over all promotion pieces
                            for(int p = n; p <= q; p++){
                                cout << "pawn promotion: " << square_to_coordinates[src_square] << square_to_coordinates[target_square] << ascii_pieces[p] << "\n";
                            }
                        }

                        else{
                            //one square ahead
                            cout << "one ahead: " << square_to_coordinates[target_square] << "\n";

                            //two square ahead
                            if ((src_square >= a7 && src_square <= h7) && !get_bit(occupancies[both] , target_square + 8)){
                                cout << "two ahead: " << square_to_coordinates[target_square + 8] << "\n";
                            }
                        }
                    }

                    //init pawn attacks bitboard
                    attacks = pawn_attacks[side][src_square] & occupancies[white];

                    //generate pawn attacks
                    while (attacks){
                        //init target square
                        target_square = get_ls1b_index(attacks);

                        //pawn capture promotion
                        if (src_square >= a2 && src_square <= h2){
                            //loop over all promotion pieces
                            for(int p = n; p <= q; p++){
                                cout << "pawn capture promotion: " << square_to_coordinates[src_square] << "x" << square_to_coordinates[target_square] << ascii_pieces[p] << "\n";
                            }
                        }

                        else{
                            //other captures
                            cout << "pawn capture: " << square_to_coordinates[src_square] << "x" << square_to_coordinates[target_square] << "\n";
                        }

                        //pop bit
                        pop_bit(&attacks, target_square);
                    }

                    //enpassants
                    if (enpassant != no_sq){
                        U64 enpassant_attacks = pawn_attacks[side][src_square] & (1ULL << enpassant);
                        int target_square = get_ls1b_index(enpassant_attacks);

                        if(enpassant_attacks){
                            cout << "pawn enpassant capture: " << square_to_coordinates[src_square] << "x" << square_to_coordinates[target_square] << "\n";
                        }
                    }

                    //pop lsb1 bit
                    pop_bit(&bitboard, src_square);
                }
            }
        }

        //generate knight moves

        //generate king moves

        //generate bishop moves

        //generate rooks moves

        //generate queen moves

    }
}