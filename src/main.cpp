#include "lookup.h"
#include "bitboard.h"
#include "attacks.h"
#include "utilities.h"

#include <chrono>
int main()
{     
    // Start measuring time
    auto start = std::chrono::high_resolution_clock::now();

    init_attacks();
    reset_board();
    std::string fen = "rnbqkb1r/pp1p1pPp/8/2p1pP2/1P1P4/3P3P/P1P1P3/RNBQKBNR w KQkq e6 0 1";

    parse_FEN(fen);
    print_board();
    print_bitboard(occupancies[white]);
    print_bitboard(occupancies[black]);
    print_bitboard(occupancies[both]);

    // Stop measuring time
    auto stop = std::chrono::high_resolution_clock::now();

    // Calculate duration in milliseconds
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    
    std::cout << "Execution Time: " << duration.count() << " ms" << std::endl;


    return 0;
}