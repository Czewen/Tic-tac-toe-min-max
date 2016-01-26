#include <iostream>
#include "GameBoard.h"
#include <cstdlib>
#include <limits>
#include <iterator>


using namespace std;

int getInput(int value){
    while(!(cin >> value)){
        cout << "Invalid value. Please enter 0, 1 or 2." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return value;
}

void two_player(){
    GameBoard gameboard = GameBoard();
    gameboard.initializeBoard();
    gameboard.printBoard();
    int current_player = 1;
    while(gameboard.winCheck()== false && gameboard.movesSoFar <9){
        int x;
        int y;
        cout << "Player " << current_player << "'s turn" << endl;
        int legal_move = 0;
        while(legal_move==0){
            cout << "Enter x coordinate" << endl;
            x = getInput(x);
            cout << "Enter y coordinate" << endl;
            y = getInput(y);
            legal_move = gameboard.makeMove(x,y);
            cout << "Moves so far: " << gameboard.movesSoFar << endl;
        }
        gameboard.printBoard();
        if(gameboard.winCheck() == 1){
            cout << "Player " << current_player << " wins." << endl;
        }
        else if(gameboard.movesSoFar == 9 ){
            cout << "Draw " << endl;
        }
        if(current_player == 1){
            current_player = 2;
        }
        else{
            current_player = 1;
        }
    }
}



int checkGameStatus(GameBoard gameboard, int current_player){
    if(gameboard.winCheck() == 1){
        cout << "Player " << current_player << " wins." << endl;
        return 1;
    }
    else if(gameboard.movesSoFar == 9 ){
        cout << "Draw " << endl;
        return 1;
    }
    return 0;
}


int score(GameBoard& board, int depth){
    int ai_turn =  board.ai_turn;
    if(board.winCheck(ai_turn) == 1){
        return 10-depth;
    }
    //draw
    else if(board.movesSoFar == 9 && board.winCheck()==0){
        return 0;
    }
    //player won
    else{
        return -10+depth;
    }
}

int max(std::vector<int> scores){
    int max = scores[0];
    int max_index = 0;
    for(int i=0; i<scores.capacity(); i++){
        if(scores[i]>max){
            max = scores[i];
            max_index = i;
        }
    }
    return max_index;
}

int min(std::vector<int> scores){
    int min = scores[0];
    int min_index =  0;
    for(int i=0; i<scores.capacity(); i++){
        if(min > scores[i]){
            min = scores[i];
            min_index = i;
        }
    }
    return min_index;
}

int min_max(GameBoard& board, int depth){

    if(board.winCheck() == 1 || board.movesSoFar==9){
        return score(board, depth);
    }
    depth = depth+1;
    int current_player;
    //check whether the previous move was odd or even and determine whose turn is it right now based on that
    if(board.movesSoFar%2 == 0){
        current_player = 1;
    }
    else{
        current_player = 2;
    }

    vector< vector<int> > possible_moves = vector< vector<int> >(9, vector<int>(2, -1));
    board.getAvailableMoves(possible_moves);
    vector<int> scores = vector<int>();
    int k =0;
    for(int i = 0; i<possible_moves.capacity(); i++){
        vector<int> possible_move = possible_moves[i];
        if(!(possible_move[0] < 0)){
            GameBoard new_state = GameBoard();
            new_state = board.getNewState(new_state, possible_move[0], possible_move[1], board.ai_turn);
            scores.push_back(min_max(new_state, depth));
            k++;
        }
    }

    if(current_player == board.ai_turn){
        int max_index = max(scores);
        vector<int> best_move = possible_moves[max_index];
        board.setNextAIMove(possible_moves[max_index][0], possible_moves[max_index][1]);
        return scores[max_index];
    }
    else{
        int min_index = min(scores);
        vector<int> best_move = possible_moves[min_index];
        board.setNextAIMove(possible_moves[min_index][0], possible_moves[min_index][1]);
        return scores[min_index];
    }
}

void test(){
    GameBoard gameboard = GameBoard();
    gameboard.initializeBoard();
    gameboard.setAiTurn(2);
    gameboard.setBoardForAITest();
    GameBoard test = GameBoard();
    test = gameboard.getNewState(test, 0,0, gameboard.ai_turn);
    int result = min_max(test, 0);
    cout << result << endl;
}

void play_against_ai(){
    int ai_turn = 0;
    cout << "Who should start first? " << endl;

    while(ai_turn!= 1 && ai_turn != 2){
        cout << "Enter 1 to let the AI start first." << endl;
        cout << "Enter 2 to let the player start first" << endl;
        ai_turn = getInput(ai_turn);
    }
    GameBoard gameboard = GameBoard();
    gameboard.setAiTurn(ai_turn);
    int human_player;
    int current_turn;
    if(ai_turn == 2){
        human_player = 1;
        current_turn = human_player;
    }
    else{
        human_player = 2;
        current_turn = ai_turn;
    }
    gameboard.initializeBoard();
    gameboard.printBoard();

    while(gameboard.winCheck()== false && gameboard.movesSoFar <9){
        //player's turn
        if(current_turn == human_player){
            int x;
            int y;
            cout << "Player " << human_player << "'s turn" << endl;
            int legal_move = 0;
            while(legal_move==0){
                cout << "Enter x coordinate" << endl;
                x = getInput(x);
                cout << "Enter y coordinate" << endl;
                y = getInput(y);
                legal_move = gameboard.makeMove(x,y);
            }
        }
        //ai's turn
        else{
            cout << "AI's turn" << endl;
            min_max(gameboard, 0);
            vector<int> ai_move = gameboard.nextAiMove;
            gameboard.makeMove(ai_move[0], ai_move[1]);
            cout << "\nAI has made its move" << endl;
        }
        gameboard.printBoard();
        if(checkGameStatus(gameboard, current_turn) == 1){
            break;
        };
        if(current_turn == ai_turn){
            //now it's the player's turn
            current_turn = human_player;
        }
        else{
            //now its the ai's turn
            current_turn = ai_turn;
        }
    }
}

int main()
{
    int choice = 0;
    int valid_input = 0;
    cout << "Tic tac toe by Cze Wen." <<endl;
    cout <<"Enter 1 for AI." << endl;
    cout <<"Enter 2 for 2 players." <<endl;
    while(valid_input == 0){
        try{
            cin>>choice;
            switch(choice){
            case 1:
                valid_input = 1;
                break;
            case 2:
                valid_input = 1;
                break;
            case 3:
                valid_input = 1;
                break;
            default:
                cout << "Invalid input. Please enter your choice again" << endl;
                valid_input = 0;
                break;
            }

        }
        catch(int choice){
            cout << "Invalid input! Please enter your choice again." << endl;
        }
    }
    cout << choice << endl;
    if(choice==2){
        two_player();
    }
    else if(choice == 1){
        play_against_ai();
    }
    else if(choice == 3){
        test();
    }
    return 0;
}
