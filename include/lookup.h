#ifndef LOOKUP_H
#define LOOKUP_H

#include <cstdint>
#include <iostream>

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

//sides (colour)
enum{white, black};

extern const char* square_to_coordinates[64];
extern const int bishop_relevant_bits[64];
extern const int rook_relevant_bits[64];

/*
    not a file
8  0 1 1 1 1 1 1 1
7  0 1 1 1 1 1 1 1
6  0 1 1 1 1 1 1 1
5  0 1 1 1 1 1 1 1
4  0 1 1 1 1 1 1 1
3  0 1 1 1 1 1 1 1
2  0 1 1 1 1 1 1 1
1  0 1 1 1 1 1 1 1
   a b c d e f g h
*/

//not A file extern constant
extern const U64 not_a_file;

//not H file extern constant
extern const U64 not_h_file;

//not AB file extern constant
extern const U64 not_ab_file;

//not HG file extern constant
extern const U64 not_hg_file;

//not 8 rank extern constant
extern const U64 not_8_rank;

//not 1 rank extern constant
extern const U64 not_1_rank;

//not 78 rank extern constant
extern const U64 not_78_rank;

//not 12 rank extern constant
extern const U64 not_12_rank;




#endif