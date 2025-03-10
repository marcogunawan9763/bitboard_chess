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

    //loop over every piece
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
        if ((side == white) ? piece == N : piece == n){
            //loop over every knight(s)
            while (bitboard){
                //get one knight
                src_square = get_ls1b_index(bitboard);

                //init attack bitboard (~occupancies means we ignore our own pieces)
                attacks = knight_attacks[src_square] & ((side == white) ? ~occupancies[white] : ~occupancies[black]);

                while(attacks){
                    //init target square
                    target_square = get_ls1b_index(attacks);

                    //quite move
                    if(!get_bit(((side == white) ? occupancies[black] : occupancies[white]), target_square)){
                        cout << "piece move: N" << square_to_coordinates[target_square] << "\n";
                    }

                    //capture move
                    else{
                        cout << "piece capture: Nx" << square_to_coordinates[target_square] << "\n";
                    }

                    //pop lsb in attacks
                    pop_bit(&attacks, target_square);
                }

                //pop lsb of knight
                pop_bit(&bitboard, src_square);

            }
        }
        


        //generate king moves
        if ((side == white) ? piece == K : piece == k){
            //loop over every kings(s)
            while (bitboard){
                //get one king
                src_square = get_ls1b_index(bitboard);

                //init attack bitboard (~occupancies means we ignore our own pieces)
                attacks = king_attacks[src_square] & ((side == white) ? ~occupancies[white] : ~occupancies[black]);

                while(attacks){
                    //init target square
                    target_square = get_ls1b_index(attacks);

                    //quite move
                    if(!get_bit(((side == white) ? occupancies[black] : occupancies[white]), target_square)){
                        cout << "piece move: K" << square_to_coordinates[target_square] << "\n";
                    }

                    //capture move
                    else{
                        cout << "piece capture: Kx" << square_to_coordinates[target_square] << "\n";
                    }

                    //pop lsb in attacks
                    pop_bit(&attacks, target_square);
                }

                //pop lsb of king
                pop_bit(&bitboard, src_square);

            }
        }

        //generate bishop moves
        if ((side == white) ? piece == B : piece == b){
            //loop over every bishop(s)
            while (bitboard){
                //get one bishop
                src_square = get_ls1b_index(bitboard);

                //init attack bitboard (~occupancies means we ignore our own pieces)
                attacks = get_bishop_attacks(src_square, occupancies[both]) & ((side == white) ? ~occupancies[white] : ~occupancies[black]);

                while(attacks){
                    //init target square
                    target_square = get_ls1b_index(attacks);

                    //quite move
                    if(!get_bit(((side == white) ? occupancies[black] : occupancies[white]), target_square)){
                        cout << "piece move: B" << square_to_coordinates[target_square] << "\n";
                    }

                    //capture move
                    else{
                        cout << "piece capture: Bx" << square_to_coordinates[target_square] << "\n";
                    }

                    //pop lsb in attacks
                    pop_bit(&attacks, target_square);
                }

                //pop lsb of bishop
                pop_bit(&bitboard, src_square);

            }
        }

        //generate rooks moves
        if ((side == white) ? piece == R : piece == r){
            //loop over every rook(s)
            while (bitboard){
                //get one rook
                src_square = get_ls1b_index(bitboard);

                //init attack bitboard (~occupancies means we ignore our own pieces)
                attacks = get_rook_attacks(src_square, occupancies[both]) & ((side == white) ? ~occupancies[white] : ~occupancies[black]);

                while(attacks){
                    //init target square
                    target_square = get_ls1b_index(attacks);

                    //quite move
                    if(!get_bit(((side == white) ? occupancies[black] : occupancies[white]), target_square)){
                        cout << "piece move: R" << square_to_coordinates[target_square] << "\n";
                    }

                    //capture move
                    else{
                        cout << "piece capture: Rx" << square_to_coordinates[target_square] << "\n";
                    }

                    //pop lsb in attacks
                    pop_bit(&attacks, target_square);
                }

                //pop lsb of rook
                pop_bit(&bitboard, src_square);

            }
        }

        //generate queen moves
        if ((side == white) ? piece == Q : piece == q){
            //loop over every queen(s)
            while (bitboard){
                //get one queen
                src_square = get_ls1b_index(bitboard);

                //init attack bitboard (~occupancies means we ignore our own pieces)
                attacks = get_queen_attacks(src_square, occupancies[both]) & ((side == white) ? ~occupancies[white] : ~occupancies[black]);

                while(attacks){
                    //init target square
                    target_square = get_ls1b_index(attacks);

                    //quite move
                    if(!get_bit(((side == white) ? occupancies[black] : occupancies[white]), target_square)){
                        cout << "piece move: Q" << square_to_coordinates[target_square] << "\n";
                    }

                    //capture move
                    else{
                        cout << "piece capture: Qx" << square_to_coordinates[target_square] << "\n";
                    }

                    //pop lsb in attacks
                    pop_bit(&attacks, target_square);
                }

                //pop lsb of queen
                pop_bit(&bitboard, src_square);

            }
        }

    }
}