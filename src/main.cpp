#include "lookup.h"
#include "bitboard.h"
#include "attacks.h"
#include "utilities.h"
#include "movegen.h"

#include <chrono>

// FEN dedug positions
#define empty_board "8/8/8/8/8/8/8/8 w - - "
#define start_position "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1 "
#define tricky_position "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1 "
#define killer_position "rnbqkb1r/pp1p1pPp/8/2p1pP2/1P1P4/3P3P/P1P1P3/RNBQKBNR w KQkq e6 0 1"
#define cmk_position "r2q1rk1/ppp2ppp/2n1bn2/2b1p3/3pP3/3P1NPP/PPP1NPB1/R1BQ1RK1 b - - 0 9 "

int main()
{     
    // Start measuring time
    auto start = std::chrono::high_resolution_clock::now();

    init_attacks();
    reset_board();
    std::string fen = tricky_position;

    parse_FEN(fen);
    print_board();

    //create move
    int move = encode_move(e2, e4, P, 0, 0, 0, 0, 0);

    //extract target square from move
    int target_square = get_move_target(move);

    cout << ("src_square: ") << square_to_coordinates[get_move_source(move)] << "\n";

    cout << ("target_square: ") << square_to_coordinates[target_square] << "\n";

    cout << ("piece: ") << unicode_pieces[get_move_piece(move)] << "\n";

    cout << ("castling: ") << get_move_castling(move);


    // Stop measuring time
    auto stop = std::chrono::high_resolution_clock::now();

    // Calculate duration in milliseconds
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    
    std::cout << "Execution Time: " << duration.count() << " ms" << std::endl;


    return 0;
}