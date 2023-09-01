# Chess Engine
Hello there! This is my C++ 17 chess engine. The project objective is to create a decent and (at least a bit) challenging chess engine, with a good modern C++ architecture. The engine will use a so called "handcrafted" approach, which means that the move decisions will depend on the crafted algorithms and heuristics (i.e. no deep learning). The work is still on progress!

## Board Representation
The board representation classes are in the `chess::board` namespace.
### Piece centric
The `chess::board::PositionBitBoards` is the piece centric representation. It contains bitboards for representing the pieces, attack, rotated occupancy, etc.
### Square centric
A square centric representation is also important to constaint-time check board squares, and the `chess::board::PositionSquares` class serves such purpose. It contains the usual 64 length array storing which piece is at each board square.
