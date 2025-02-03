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

//not A file constant
const U64 not_a_file = 18374403900871474942U;

//not H file constant
const U64 not_h_file = 9187201950435737471U;

//not AB file constant
const U64 not_ab_file = 18229723555195321596U;

//not HG file constant
const U64 not_hg_file = 4557430888798830399U;

//not 8 rank constant
const U64 not_8_rank = 18446744073709551360U;

//not 1 rank constant
const U64 not_1_rank = 72057594037927935U;

//not 78 rank constant
const U64 not_78_rank = 18446744073709486080U;

//not 12 rank constant
const U64 not_12_rank = 281474976710655U;




#endif