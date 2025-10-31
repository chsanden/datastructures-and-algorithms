#include <ctime>
#include "FUtils.h"

TQueue q;

int main()
{
    // --- Part 2: quick demos ---
    std::cout << "Reverse(\"stackqueue\") = " << ReverseString("stackqueue") << "\n";
    std::cout << "Factorial(6) = " << Factorial(6) << "\n";

    TQueue q;
    std::cout << "\n-- Wait line simulation --\n";
    SimulateWaitLine(5, 2, q);   // 5 arrive, serve 2 now
    SimulateWaitLine(3, 6, q);   // 3 arrive, then serve the rest

    // --- Part 3.6: set up grid and visited arrays ---
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    int  grid[GRID_ROWS][GRID_COLS];
    bool visitedDFS[GRID_ROWS][GRID_COLS];
    bool visitedBFS[GRID_ROWS][GRID_COLS];

    for (int r = 0; r < GRID_ROWS; ++r)
        for (int c = 0; c < GRID_COLS; ++c) {
            grid[r][c] = std::rand() % 10;  // 0..9
            visitedDFS[r][c] = false;
            visitedBFS[r][c] = false;
        }

    int startR = std::rand() % GRID_ROWS;
    int startC = std::rand() % GRID_COLS;
    std::cout << "\nStart cell: (" << startR << ", " << startC
              << ") value=" << grid[startR][startC] << "\n";

    // --- Part 3.7: DFS ---
    int dR=-1, dC=-1;
    bool dfsFound = DFSFindZero(grid, visitedDFS, startR, startC, dR, dC);
    if (dfsFound) std::cout << "[DFS] Found 0 at (" << dR << "," << dC << ")\n";
    else          std::cout << "[DFS] No 0 found\n";

    // --- Part 3.8: BFS ---
    int bR=-1, bC=-1;
    bool bfsFound = BFSFindZero(grid, visitedBFS, startR, startC, bR, bC);
    if (bfsFound) std::cout << "[BFS] Found 0 at (" << bR << "," << bC << ")\n";
    else          std::cout << "[BFS] No 0 found\n";

    return 0;
}