# Chess Console

A two-player, console-based chess game written in C++. 

For each requested move, the game generates possible moves based on the selected piece's movement rules and validates their legality.

Move validation also considers special chess rules, such as castling and en passant, and ensures that a move does not leave the player's own king in check.

## Requirements

- C++20-compatible compiler (GCC, Clang or MSVC)
- CMake 3.20 or newer
- Git

## Configuration and build

Clone the repository:

```bash
git clone https://github.com/Yannick-TU/chess-console.git
cd chess-console
```

Configure the project:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
```

Build the application:

```bash
cmake --build build --config Release
```

Run the application:

**Windows:**

```powershell
.\build\chess_console.exe
```

**Linux / macOS:**

```bash
./build/chess_console
```

## How to play

Chess Console supports two players playing locally on the same computer. 

Use the help command to display the available commands and instructions.
Special moves such as castling, en passant and pawn promotion are supported.

```text
    a b c d e f g h
  +-----------------+                                   
8 | r n b q k b n r | 8
7 | p p p p p p p p | 7     
6 | . . . . . . . . | 6     
5 | . . . . . . . . | 5
4 | . . . . . . . . | 4
3 | . . . . . . . . | 3
2 | P P P P P P P P | 2
1 | R N B Q K B N R | 1
  +-----------------+
    a b c d e f g h
```
Enter moves using algebraic chess notation: e2 e4

```text
    a b c d e f g h
  +-----------------+
8 | r n b q k b n r | 8
7 | p p p p p p p p | 7
6 | . . . . . . . . | 6
5 | . . . . . . . . | 5
4 | . . . . P . . . | 4
3 | . . . . . . . . | 3
2 | P P P P . P P P | 2
1 | R N B Q K B N R | 1
  +-----------------+
    a b c d e f g h
```


## Architecture


- Figure: Abstract base class for all chess pieces.

- Individual Figures: Implement piece-specific movement and attack rules.

- Board: Manages the chessboard and the figures.

- Chess Game: Handles game state, move validation and chess rules.

- Position: Represents board coordinates and handles coordinate conversions.

Polymorphism allows different chess pieces to be handled through a common interface. Smart pointers (std::unique_ptr) are used to manage figure ownership and memory.

## Stillig missing

ome additional official draw conditions are not yet implemented:
- The 50-move rule
- Threefold repetition
- Draw due to insufficient material