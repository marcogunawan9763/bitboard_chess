#ifndef MOVEGEN_H
#define MOVEGEN_H

#include <cstdint>
#include <iostream>

using namespace std;
using U64 = uint64_t;

void generate_moves();

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

#endif