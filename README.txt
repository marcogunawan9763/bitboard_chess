Bitboard CHESS ENGINE

Features List:
    bitboard board representation
    pre-calculated attack tables
    magic bitboards for sliding pieces
    encoding moves as integers
    copy/make approach
    negamax search with alpha-beta pruning
    PV/killer/history move ordering
    iterative deepening
    transposition tables
    material/positions/pawns/mobility/king safety evaluation
    UCI protocol

Matches versus other engine(s) + players

Bitboard representation relative to array based representation greatly 
optimises the problem and increases efficiency. The main benefit on the
otherhand comes from the evaluation functions being greatly more expensive
(isolated pawn islands, double pawn, etc)

compile with:
