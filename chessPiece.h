/* File:   chessPiece.h
 * Author: Yan
 *
 * Created on May 3, 2022, 10:54 AM
 */

#ifndef CHESSPIECE_H
#define CHESSPIECE_H

//define the size of each square be 3X3 in the chess board
#define BLOCK_SIZE 3
//define the size of the chess board
#define CHESS_SIZE 8

typedef struct SPieceIndex{
	int row;
	int column;
}SPieceIndex;

typedef map<string,SPieceIndex> mapPosToVirtualIndex ;
typedef map<string,string> mapVirtualIndexToPos;
typedef map<string,string> mapRealIndexToPos;

mapPosToVirtualIndex globalMapPosToVirtualIndex; 	
mapVirtualIndexToPos globalMapvirtualIndexToPos;	
mapRealIndexToPos globalMapRealIndexToPos;

class ChessBoard;

class ChessPiece{
public:
	enum Color {WHITE, BLACK};

	//set the attribute and color of the chess board
	ChessPiece(ChessBoard* pBoard, Color _color, string _strCode) : board(pBoard),color(_color),strCode(_strCode)	{}

	//returns the row
	int getRow(){return row;}
	
	//returns the column
	int getColumn(){return column;}
	
	//set the row
	void setRow(int i) { row = i;}
	
	//set the column
	void setColumn(int i) {column = i;}
	
	//get piece color no need for a setColor method because a piece cannot change color.
	Color getColor() {return color;}
	 
	//returns the position of the piece in the format single letter (a..h) followed by a single digit (1..8).
	string getPosition();
	 
	//sets the position of the piece to the appropriate row and column based on the argument 
	//which in the format single letter (a..h) followed by a single digit (1..8)  
	void setPosition(string position);
	 
	 //will be implemented in the concrete subclasses corresponding to each chess piece
	 //This method returns a string composed of a single character that corresponds to which piece it is
/*
character     piece
----------   -----------
  "\u2654"   white king
  "\u2655"   white queen
  "\u2656"   white rook
  "\u2657"   white bishop
  "\u2658"   white knight
  "\u2659"   white pawn
  "\u265A"   black king
  "\u265B"   black queen
  "\u265C"   black rook
  "\u265D"   black bishop
  "\u265E"   black knight
  "\u265F"   black pawn
*/
	 string toString();
	 
	 //This method will be implemented in the concrete subclasses corresponding to each chess piece. 
	 //This method returns all the legal moves that piece can make based on the rules described above in the assignment
	 virtual int legalMoves(list<string>& lstResult)
	 {
	 	lstResult.clear();
	 	return 0;
	 };
	 
	 void setStrCode(string str) {strCode = str;}
	 
	 string getStrCode() {return strCode;}
	
	 ChessBoard* getChessBoard() {return board;}
	 
	 /*judge the state of the pieces at the given position, returns 0 if there is no piece,
         returns 1 if there is a piece with the same color, returns 2 if there is an opponent's piece*/
	 int judgePieceStat(int row,int column);
	 
protected:
	ChessBoard* board; // the board it belongs to, default null
	int row; // the index of the horizontal rows 0..7
	int column; // the index of the vertical column 0..7
	Color color; // the color of the piece
	string strCode;
};

//debug the program
string ChessPiece::toString()
{
	char szTemp[16] = {0};
	sprintf(szTemp,"%d_%d",row,column);
	
	if(globalMapvirtualIndexToPos.find(szTemp) == globalMapvirtualIndexToPos.end())
	{
            return string("");
	}
	else 
	{
            return globalMapvirtualIndexToPos[szTemp];
	}	
	return string("");
}

#endif /* CHESSPIECE_H */