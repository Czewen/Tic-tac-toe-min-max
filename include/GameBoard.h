#ifndef GAMEBOARD_H
#define GAMEBOARD_H
#include <vector>
#include <list>
class GameBoard
{
    public:
        GameBoard();
        virtual ~GameBoard();
        void initializeBoard();
        void addMove(int column, int row, char player);
        void printBoard();
        void copyBoard(std::vector< std::vector< char > > board);
        void setMovesSoFar(int moves);
        void setAiTurn(int turn);
        void setNextAIMove(int& x, int& y);
        int makeMove(int x, int y);
        int winCheck();
        int winCheck(int player);
        void setBoardForAITest();
        GameBoard getNewState(GameBoard& new_state, int x, int y, int ai_turn_number);
        std::vector< std::vector<int> > getAvailableMoves( std::vector< std::vector<int> >& buffer);
        std::vector< std::vector< char> > grid = std::vector< std::vector<char> >(3, std::vector<char>(3) );
        int movesSoFar;
        int ai_turn;
        std::vector<int> nextAiMove = std::vector< int >(2, 10);
    protected:
    private:

};

#endif // GAMEBOARD_H
