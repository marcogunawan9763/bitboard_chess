#ifndef MOVEGEN_H
#define MOVEGEN_H

#include <cstdint>
#include <iostream>

using namespace std;
using U64 = uint64_t;

//macros for copy/make approach
#define copy_board() \
    U64 bitboards_copy[12], occupancies_copy[3]; \
    int side_copy = side, enpassant_copy = enpassant, castle_copy = castle; \
    memcpy(bitboards_copy, bitboards, sizeof(bitboards)); \
    memcpy(occupancies_copy, occupancies, sizeof(occupancies))

#define restore_board() \
    memcpy(bitboards, bitboards_copy, sizeof(bitboards)); \
    memcpy(occupancies, occupancies_copy, sizeof(occupancies)); \
    side = side_copy; \
    enpassant = enpassant_copy; \
    castle = castle_copy

//main move generation function
void generate_moves(moves_obj *move_list);

//encoding move 
uint32_t encode_move(uint8_t source, uint8_t target, uint8_t piece, uint8_t promoted, 
                    bool capture, bool d_pawn, bool enpassant, bool castling);

//decoding move
uint8_t get_move_source(uint32_t move);
uint8_t get_move_target(uint32_t move);
uint8_t get_move_piece(uint32_t move);
uint8_t get_move_promoted(uint32_t move);
bool get_move_capture(uint32_t move);
bool get_move_dpawn(uint32_t move);
bool get_move_enpassant(uint32_t move);
bool get_move_castling(uint32_t move);

//move list
void print_move(int move);
void print_move_list(moves_obj *move_list);
void add_move(moves_obj *move_list, int move);

#endif