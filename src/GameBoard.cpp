#include "GameBoard.h"
#include <iostream>
#include <vector>
#include "tree.hh"
using namespace std;

GameBoard::GameBoard()
{
    movesSoFar = 0;
    //ctor
}

GameBoard::~GameBoard()
{
    //dtor
}

void GameBoard::initializeBoard(){
    int a  = 1;
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            grid[i][j] = '*';
        }
    }
}



void GameBoard::printBoard(){
     for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            cout << grid[j][i];
            if(j<2)
                cout<< "|";
        }
        if(i<2)
            cout <<"\n- - -"<< endl;
    }
    cout << "" << endl;
}


void GameBoard::copyBoard(std::vector< vector< char > > board){
    for(int i=0; i< board.size(); i++){
        vector<char> temp = board[i];
        for(int j = 0; j<temp.size();j++){
            grid[i][j] = board[i][j];
        }
    }
}

void GameBoard::setMovesSoFar(int move){
    movesSoFar = move;
}

void GameBoard::setAiTurn(int turn){
    ai_turn = turn;
}

void GameBoard::setBoardForAITest(){
    grid[0][0] = '*';
    grid[1][0] = '*';
    grid[2][0] = '*';

    grid[0][1] = '*';
    grid[1][1] = 'x';
    grid[2][1] = '*';

    grid[0][2] = '*';
    grid[1][2] = '*';
    grid[2][2] = '*';

    movesSoFar = 1;
}

vector<vector< int > > GameBoard::getAvailableMoves( vector< vector < int > >& buffer){
    int k = 0;
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            if(grid[i][j]=='*'){
                buffer[k][0] = i;
                buffer[k][1] = j;
                k++;
            }
        }
    }
    return buffer;
}

int GameBoard::makeMove(int x, int y){
    //check whose turn it is based on the number of total moves on the board so far
    //cout << "make move: " << x << " " << y << endl;
    char player_move = (movesSoFar % 2 == 0)? 'x' : 'o';
    //char player_move = (current_player) == 1 ? 'x' : 'o';
    //illegal move check
    if(x>2 || y>2){
        std::string error = "Illegal move: specified coordinates are out of bounds.";
        cout << error << endl;
    }
    if(!(grid[x][y] == '*')){
        std:string error = "Illegal move: Specified coordinates have already been taken.";
        cout << error << endl;
    }
    else{
        grid[x][y] = player_move;
        movesSoFar = movesSoFar + 1;
        return 1;
    }
    return 0;
}

GameBoard GameBoard::getNewState(GameBoard& new_state, int x, int y, int ai_turn_number){
    new_state.copyBoard(grid);
    new_state.setMovesSoFar(movesSoFar);
    new_state.makeMove(x, y);
    new_state.setAiTurn(ai_turn_number);
    return new_state;
}


int GameBoard::winCheck(){
    char move_type;
    if(movesSoFar%2 == 0){
        move_type = 'o';
    }
    else{
        move_type = 'x';
    }
    // horizontal and vertical check
    for(int i=0; i<3; i++){
        if(grid[i][0] == move_type && grid[i][1] == move_type && grid[i][2] == move_type){
            return 1;
        }
        if(grid[0][i] == move_type && grid[1][i] == move_type && grid[2][i] == move_type){
            return 1;
        }
    }
    //diagonal check
    if(grid[0][0] == move_type && grid[1][1] == move_type && grid[2][2] == move_type){
        return 1;
    }
    if(grid[0][2] == move_type && grid[1][1] == move_type && grid[2][0] == move_type){
        return 1;
    }
    return 0;
}


int GameBoard::winCheck(int player){
    char move_type;
    if(player == 1){
        move_type = 'x';
    }
    else{
        move_type = 'o';
    }
     // horizontal and vertical check
    for(int i=0; i<3; i++){
        if(grid[i][0] == move_type && grid[i][1] == move_type && grid[i][2] == move_type){
            return 1;
        }
        if(grid[0][i] == move_type && grid[1][i] == move_type && grid[2][i] == move_type){
            return 1;
        }
    }
    //diagonal check
    if(grid[0][0] == move_type && grid[1][1] == move_type && grid[2][2] == move_type){
        return 1;
    }
    if(grid[0][2] == move_type && grid[1][1] == move_type && grid[2][0] == move_type){
        return 1;
    }
    return 0;
}

void GameBoard::setNextAIMove(int& x, int& y){
    nextAiMove[0] = x;
    nextAiMove[1] = y;
}


