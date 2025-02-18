#include "lookup.h"
#include "bitboard.h"
#include "attacks.h"

#include <chrono>
int main()
{     
    // Start measuring time
    auto start = std::chrono::high_resolution_clock::now();

    init_all();

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

    print_board();

    // Stop measuring time
    auto stop = std::chrono::high_resolution_clock::now();

    // Calculate duration in milliseconds
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    
    std::cout << "Execution Time: " << duration.count() << " ms" << std::endl;


    return 0;
}