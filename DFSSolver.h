
#include <bits/stdc++.h>
#include "../Model/RubiksCube.h"

#ifndef RUBIKS_CUBE_SOLVER_BFSSOLVER_H
#define RUBIKS_CUBE_SOLVER_BFSSOLVER_H

class BFSSolver {
private:
    vector<RubiksCube::MOVE> moves;
    
    map<RubiksCube3d, bool> visited;
    map<RubiksCube3d, RubiksCube::MOVE> move_done;

    // Performs breadth-first-search and returns a solved Rubik's Cube
    RubiksCube3d bfs() {
        queue<RubiksCube3d> q;
        q.push(rubiksCube);
        visited[rubiksCube] = true;

        while (!q.empty()) {
            RubiksCube3d node = q.front();
            q.pop();
            
            if (node.isSolved()) {
                return node;
            }
            
            for (int i = 0; i < 18; i++) {
                auto curr_move = RubiksCube::MOVE(i);
                node.move(curr_move);
                
                if (!visited[node]) {
                    visited[node] = true;
                    move_done[node] = curr_move;
                    q.push(node);
                }
                
                node.invert(curr_move); // Backtrack the temporary mutation
            }
        }
        return rubiksCube;
    }

public:
    // Explicit 3D Cube instance
    RubiksCube3d rubiksCube;

    BFSSolver(RubiksCube3d _rubiksCube) {
        rubiksCube = _rubiksCube;
    }

    // Performs BFS and returns the vector of moves done to solve the cube
    vector<RubiksCube::MOVE> solve() {
        RubiksCube3d solved_cube = bfs();
        assert(solved_cube.isSolved());
        
        RubiksCube3d curr_cube = solved_cube;
        while (!(curr_cube == rubiksCube)) {
            RubiksCube::MOVE curr_move = move_done[curr_cube];
            moves.push_back(curr_move);
            curr_cube.invert(curr_move);
        }
        
        rubiksCube = solved_cube;
        reverse(moves.begin(), moves.end());
        return moves;
    }
};

#endif //RUBIKS_CUBE_SOLVER_BFSSOLVER_H
