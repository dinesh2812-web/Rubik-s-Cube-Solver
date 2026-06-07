
#include <bits/stdc++.h>
#include "../Model/RubiksCube.h"
#include "DFSSolver.h"

#ifndef RUBIKS_CUBE_SOLVER_IDDFSSOLVER_H
#define RUBIKS_CUBE_SOLVER_IDDFSSOLVER_H

class IDDFSSolver {

private:
    int max_search_depth;
    vector<RubiksCube::MOVE> moves;

public:
    RubiksCube3d rubiksCube;

    IDDFSSolver(RubiksCube3d _rubiksCube, int _max_search_depth = 7) {
        rubiksCube = _rubiksCube;
        max_search_depth = _max_search_depth;
    }

    vector<RubiksCube::MOVE> solve() {
        moves.clear(); 
        
        for (int i = 1; i <= max_search_depth; i++) {
            DFSSolver dfsSolver(rubiksCube, i);
            
            moves = dfsSolver.solve();
            
            if (dfsSolver.rubiksCube.isSolved()) {
                rubiksCube = dfsSolver.rubiksCube; 
                break;
            }
        }
        return moves;
    }
};

#endif //RUBIKS_CUBE_SOLVER_IDDFSSOLVER_H
