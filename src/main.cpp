#include "lookup.h"
#include "bitboard.h"
#include "attacks.h"

#include <chrono>
int main()
{     
    // Start measuring time
    auto start = std::chrono::high_resolution_clock::now();

    /*
    
    for(int rank = 0; rank < 8; rank ++){
        for(int file = 0; file < 8; file++){
            int square = rank * 8 + file;

            if (rank > 0){
                set_bit(&bitboard, square);
            }
        }
    }
    */

    init_leaper_attacks();
    print_bitboard(mask_king_attacks(h1));
    cout << "number of bits: " << count_bits(mask_king_attacks(h1)) << '\n'; 

    // Stop measuring time
    auto stop = std::chrono::high_resolution_clock::now();

    // Calculate duration in milliseconds
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    
    std::cout << "Execution Time: " << duration.count() << " ms" << std::endl;


    return 0;
}