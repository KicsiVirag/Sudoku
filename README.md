# Sudoku

A graphical implementation of the classic Sudoku puzzle game written in C++. The application uses SDL2, SDL2_ttf and a graphics library to provide an interactive desktop interface.

## Features

- Classic 9 × 9 Sudoku grid with 3 × 3 subgrids.
- Random puzzle generation using a recursive backtracking algorithm.
- 41 predefined cells and 40 empty cells in each generated puzzle.
- Mouse-based cell selection and keyboard input.
- Real-time conflict detection across rows, columns and subgrids.
- Color-coded cells for visual feedback.
- Automatic completion detection and the option to start a new game.
- Hungarian-language menu and victory screen.

## Technologies

- C++ (object-oriented programming)
- SDL2 and SDL2_ttf
- Code::Blocks and GCC/MinGW
- Recursive backtracking

## Getting Started

The included Code::Blocks project is configured for Windows.

1. Clone or download this repository and extract it if necessary.
2. Open `GraphicsProject.cbp` in Code::Blocks with a compatible MinGW compiler installed.
3. Select the C++14 standard if required (`std::random_shuffle` is used in the source code).
4. Make sure `jatekmester.cpp` is included in the project build target; add it if it is missing.
5. Build and run the project using **F9**.

A prebuilt Windows executable is also included at `bin/Debug/GraphicsProject.exe`. If required, copy the bundled runtime DLLs into the executable's directory and use the repository root as the working directory so that the font resource is accessible.

## How to Play

Fill every empty cell with a number from 1 to 9. Each row, column and 3 × 3 subgrid must contain every number exactly once.

| Control | Action |
| --- | --- |
| Any key on the main menu | Start the game (except Escape) |
| Left mouse button | Select an editable cell |
| 1–9 | Enter a number |
| Backspace / Delete | Clear the selected cell |
| Escape | Exit the game |
| Any key on the victory screen except Escape | Start a new puzzle |

### Cell Colors

| Color | Meaning |
| --- | --- |
| Gray | Fixed, non-editable clue |
| White | Unselected editable cell |
| Light blue | Selected editable cell |
| Red | Editable cell containing a conflicting value |

## Project Structure

```text
Sudoku/
├── main.cpp                  # Application entry point
├── jatekmester.cpp/.hpp      # Game controller and state management
├── sudokuboard.cpp/.hpp      # Puzzle generation and validation
├── sudokucell.cpp/.hpp       # Cell rendering and input handling
├── widget.cpp/.hpp           # Base widget class
├── graphicslib/             # Graphics library
├── include/                 # SDL headers
├── lib/                     # Linker libraries
├── bin/                     # Prebuilt executable
├── GraphicsProject.cbp      # Code::Blocks project configuration
└── README.md
```

## How Puzzle Generation Works

The generator fills an empty board using randomized recursive backtracking. It checks Sudoku constraints before placing each number. After producing a complete valid board, it randomly remaps the digits and removes 40 cells to create a playable puzzle.

During gameplay, the board checks for duplicate values after input events. The game is completed when all 81 cells are filled and no conflicts remain.

## Known Limitations

- Generated puzzles have at least one solution, but solution uniqueness is not verified.
- The number of removed cells is fixed; there is no difficulty selection.
- The supplied build configuration targets Windows.
