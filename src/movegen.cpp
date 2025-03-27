/*************************************************************************************
 * File: movegen.cpp
 * Description: This program creates the move generation for any given board,
 *************************************************************************************/

#include "lookup.h"
#include "attacks.h"
#include "bitboard.h"

//moves encoder (check lookup to see binary encoding of move)
uint32_t encode_move(uint8_t source, uint8_t target, uint8_t piece, uint8_t promoted, 
                     bool capture, bool d_pawn, bool enpassant, bool castling) {
    return (source) | (target << 6) | (piece << 12) | (promoted << 16) | 
           ((capture ? 1U : 0U) << 20) | ((d_pawn ? 1U : 0U) << 21) | 
           ((enpassant ? 1U : 0U) << 22) | ((castling ? 1U : 0U) << 23);
}

//moves decoder(s), takes out the neccesary portions of a move integer
uint8_t get_move_source(uint32_t move) {
    return (move & 0x3f);
}

uint8_t get_move_target(uint32_t move) {
    return ((move & 0xfc0) >> 6);
}

uint8_t get_move_piece(uint32_t move) {
    return ((move & 0xf000) >> 12);
}

uint8_t get_move_promoted(uint32_t move) {
    return ((move & 0xf0000) >> 16);
}

bool get_move_capture(uint32_t move) {
    return ((move & 0x100000) ? 1 : 0);
}

bool get_move_dpawn(uint32_t move) {
    return ((move & 0x200000) ? 1 : 0);
}

bool get_move_enpassant(uint32_t move) {
    return ((move & 0x400000) ? 1 : 0);
}

bool get_move_castling(uint32_t move) {
    return ((move & 0x800000) ? 1 : 0);
}

//add move to the movelist
void add_move(moves_obj *move_list, int move){
    //store move
    move_list -> moves[move_list -> count] = move;

    //increment move count
    move_list -> count ++;
}

//print move (for UCI purposes)
void print_move(int move){
    cout << square_to_coordinates[get_move_source(move)] << square_to_coordinates[get_move_target(move)] << promoted_pieces[get_move_promoted(move)];
}

//print move 
void print_move_list(moves_obj *move_list){

    cout << "\nmove    piece    capture    double    enpassant    castling\n";

    //loop over moves within a move list
    for (int move_count = 0; move_count < move_list -> count; move_count++){
        //init move
        int move = move_list->moves[move_count];

        cout << square_to_coordinates[get_move_source(move)]
        << square_to_coordinates[get_move_target(move)]
        << promoted_pieces[get_move_promoted(move)] << (promoted_pieces[get_move_promoted(move)] == 0 ? "    ": "   ")
        << unicode_pieces[get_move_piece(move)] << "        "
        << get_move_capture(move) << "         "
        << get_move_dpawn(move) << "         "
        << get_move_enpassant(move) << "            "
        << get_move_castling(move)
        << "\n";

    }
}


void generate_moves(moves_obj *move_list){
    //init move count
    move_list -> count = 0;

    //define source squre and target square
    int src_square, target_square;

    //define current piece's bitboard and is attacks
    U64 bitboard, attacks;

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
                                add_move(move_list, encode_move(src_square,  target_square, piece, p, 0, 0, 0, 0));
                            }
                        }

                        else{
                            //one square ahead
                            add_move(move_list, encode_move(src_square,  target_square, piece, 0, 0, 0, 0, 0));

                            //two square ahead
                            if ((src_square >= a2 && src_square <= h2) && !get_bit(occupancies[both] , target_square - 8)){
                                add_move(move_list, encode_move(src_square,  target_square - 8, piece, 0, 0, 1, 0, 0));
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
                                add_move(move_list, encode_move(src_square,  target_square, piece, p, 1, 0, 0, 0));
                            }
                        }

                        else{
                            //other captures
                            add_move(move_list, encode_move(src_square,  target_square, piece, 0, 1, 0, 0, 0));
                        }

                        //pop bit
                        pop_bit(&attacks, target_square);
                    }

                    //enpassants
                    if (enpassant != no_sq){
                        U64 enpassant_attacks = pawn_attacks[side][src_square] & (1ULL << enpassant);
                        int target_square = get_ls1b_index(enpassant_attacks);

                        if(enpassant_attacks){
                            add_move(move_list, encode_move(src_square,  target_square, piece, 0, 1, 0, 1, 0));
                        }
                    }

                    //pop lsb1 bit
                    pop_bit(&bitboard, src_square);
                }
            }

            //castling
            if (piece == K){
                //king side castling
                if (castle & wk){
                    //make sure squares between king and rook are empty
                    if (!get_bit(occupancies[both], f1) && !get_bit(occupancies[both], g1)){
                        //square between is not under attack
                        if(!is_square_attacked(e1, black) && !is_square_attacked(f1, black) && !is_square_attacked(g1,black)){
                            add_move(move_list, encode_move(e1,  g1, piece, 0, 0, 0, 0, 1));
                        }
                    }
                }

                //queen side castling
                if(castle & wq){
                    //squares are empty between
                    if (!get_bit(occupancies[both], d1) && !get_bit(occupancies[both], c1) && !get_bit(occupancies[both], b1)){
                        //square between is not under attack
                        if(!is_square_attacked(e1, black) && !is_square_attacked(d1, black) && !is_square_attacked(c1,black)){
                            add_move(move_list, encode_move(e1,  c1, piece, 0, 0, 0, 0, 1));
                        }
                    }
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
                                add_move(move_list, encode_move(src_square,  target_square, piece, p, 0, 0, 0, 0));
                            }
                        }

                        else{
                            //one square ahead
                            add_move(move_list, encode_move(src_square,  target_square, piece, 0, 0, 0, 0, 0));

                            //two square ahead
                            if ((src_square >= a7 && src_square <= h7) && !get_bit(occupancies[both] , target_square + 8)){
                                add_move(move_list, encode_move(src_square,  target_square + 8, piece, 0, 0, 1, 0, 0));
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
                                add_move(move_list, encode_move(src_square,  target_square, piece, p, 1, 0, 0, 0));
                            }
                        }

                        else{
                            //other captures
                            add_move(move_list, encode_move(src_square,  target_square, piece, 0, 1, 0, 0, 0));
                        }

                        //pop bit
                        pop_bit(&attacks, target_square);
                    }

                    //enpassants
                    if (enpassant != no_sq){
                        U64 enpassant_attacks = pawn_attacks[side][src_square] & (1ULL << enpassant);
                        int target_square = get_ls1b_index(enpassant_attacks);

                        if(enpassant_attacks){
                            add_move(move_list, encode_move(src_square,  target_square, piece, 0, 1, 0, 1, 0));
                        }
                    }

                    //pop lsb1 bit
                    pop_bit(&bitboard, src_square);
                }
            }

            //castling
            if (piece == k){
                //king side castling
                if (castle & wk){
                    //make sure squares between king and rook are empty
                    if (!get_bit(occupancies[both], f8) && !get_bit(occupancies[both], g8)){
                        //square between is not under attack
                        if(!is_square_attacked(e8, white) && !is_square_attacked(f8, white) && !is_square_attacked(g8,white)){
                            add_move(move_list, encode_move(e8,  g8, piece, 0, 0, 0, 0, 1));
                        }
                    }
                }

                //queen side castling
                if(castle & wq){
                    //squares are empty between
                    if (!get_bit(occupancies[both], d8) && !get_bit(occupancies[both], c8) && !get_bit(occupancies[both], b8)){
                        //square between is not under attack
                        if(!is_square_attacked(e8, white) && !is_square_attacked(d8, white) && !is_square_attacked(c8,white)){
                            add_move(move_list, encode_move(e8,  c8, piece, 0, 0, 0, 0, 1));
                        }
                    }
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
                        add_move(move_list, encode_move(src_square,  target_square, piece, 0, 0, 0, 0, 0));
                    }

                    //capture move
                    else{
                        add_move(move_list, encode_move(src_square,  target_square, piece, 0, 1, 0, 0, 0));
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
                        add_move(move_list, encode_move(src_square,  target_square, piece, 0, 0, 0, 0, 0));
                    }

                    //capture move
                    else{
                        add_move(move_list, encode_move(src_square,  target_square, piece, 0, 1, 0, 0, 0));
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
                        add_move(move_list, encode_move(src_square,  target_square, piece, 0, 0, 0, 0, 0));
                    }

                    //capture move
                    else{
                        add_move(move_list, encode_move(src_square,  target_square, piece, 0, 1, 0, 0, 0));
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
                        add_move(move_list, encode_move(src_square,  target_square, piece, 0, 0, 0, 0, 0));
                    }

                    //capture move
                    else{
                        add_move(move_list, encode_move(src_square,  target_square, piece, 0, 1, 0, 0, 0));
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
                        add_move(move_list, encode_move(src_square,  target_square, piece, 0, 0, 0, 0, 0));
                    }

                    //capture move
                    else{
                        add_move(move_list, encode_move(src_square,  target_square, piece, 0, 1, 0, 0, 0));
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
