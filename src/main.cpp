#include "lookup.h"
#include "bitboard.h"
#include "attacks.h"

#include <chrono>
int main()
{     
    // Start measuring time
    auto start = std::chrono::high_resolution_clock::now();

    init_all();

    U64 occupancy = 0ULL;
    
    set_bit(&occupancy, c5);
    set_bit(&occupancy, f2);
    set_bit(&occupancy, g7);
    set_bit(&occupancy, b2);
    set_bit(&occupancy, g5);
    

    print_bitboard(occupancy);

    print_bitboard(get_rook_attacks(f5, occupancy));
    
    // Stop measuring time
    auto stop = std::chrono::high_resolution_clock::now();

    // Calculate duration in milliseconds
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    
    std::cout << "Execution Time: " << duration.count() << " ms" << std::endl;


    return 0;
}