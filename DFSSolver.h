
#include <bits/stdc++.h>
#include "../Model/RubiksCube.h"

#ifndef RUBIKS_CUBE_SOLVER_DFSSOLVER_H
#define RUBIKS_CUBE_SOLVER_DFSSOLVER_H

class DFSSolver {
private:
    vector<RubiksCube::MOVE> moves;
    int max_search_depth;

    // DFS code to find the solution (helper function)
    bool dfs(int dep) {
        // Base Cases
        if (rubiksCube.isSolved()) return true;
        if (dep > max_search_depth) return false;

        // Explore all 18 possible face-rotation configurations
        for (int i = 0; i < 18; i++) {
            RubiksCube::MOVE current_move = RubiksCube::MOVE(i);

            rubiksCube.move(current_move);
            moves.push_back(current_move);

            // Recurse deeper into the search tree
            if (dfs(dep + 1)) return true;

            // Backtrack: Undo the move if it didn't lead to a solution
            moves.pop_back();
            rubiksCube.invert(current_move);
        }
        return false;
    }

public:
    // Concrete 3D Cube instance instead of generic typename 'T'
    RubiksCube3d rubiksCube; 

    // Constructor updated to accept the 3D representation directly
    DFSSolver(RubiksCube3d _rubiksCube, int _max_search_depth = 8) {
        rubiksCube = _rubiksCube;
        max_search_depth = _max_search_depth;
    }

    // Triggers the solver and returns the winning move sequence
    vector<RubiksCube::MOVE> solve() {
        moves.clear(); // Clear any previous runs
        dfs(1);
        return moves;
    }
};

#endif //RUBIKS_CUBE_SOLVER_DFSSOLVER_H
