/* File:   chessPiece.h
 * Author: Yan
 *
 * Created on May 3, 2022, 10:54 AM
 */
#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "chessPiece.h"

//Chess board
class ChessBoard{
public:
	//initialize the board to an 8X8 array, each element of the array is a square of the board
	ChessBoard();
	~ChessBoard();
public:
	//initialize the board with an opening state, calling placePiece() method below to place the pieces in the right position
	void initialize();
	//returns the chess piece at a given position
	ChessPiece* getPiece(string position);
	//place the given piece at a give position, and returns true if successfully
	//returns false if there is already a piece of the same player in the given position
	//If an opponent's piece exists in the given position, that piece is captured, and returns true
	 bool placePiece(ChessPiece* piece, string position);
	 
	 //checks if moving the piece from the fromPosition to toPosition is a legal move
	 bool move(string fromPosition, string toPosition);
	 
	 //print the chess board
	 void printBoard();
	 
	 //debug the program
	 string toString();
	 
	 int destroy();
	 
	 int initPosIndex();
public: 
	ChessPiece* board[8][8];	
	stack<int> stackStep;
	queue<string> queueHistoryOp;	
	int m_iStep;
	bool m_bWhite;
};

ChessBoard::ChessBoard()
{
	for(int i = 0;i < 8;i++)
	{
		for(int j =0;j < 8 ;j++)
		{
			board[i][j] = NULL;
		}
	}
	m_iStep = 0;
	m_bWhite = true;
}

ChessBoard::~ChessBoard()
{
	for(int i = 0;i < 8;i++)
	{
		for(int j =0;j < 8 ;j++)
		{
			if(board[i][j] != NULL)
			{
				delete board[i][j];
				board[i][j] = NULL;
			}			
		}
	}	
	
	while(!stackStep.empty())
	{
		stackStep.pop();
	}
	queue<string> empty;
  swap(empty,queueHistoryOp);
}

void ChessBoard::initialize()
{
	//Initialize the white pieces
	placePiece(new Rook(this,ChessPiece::WHITE,"\u2656"),"a1");
	placePiece(new Rook(this,ChessPiece::WHITE,"\u2656"),"h1");			
	placePiece(new Knight(this,ChessPiece::WHITE,"\u2658"),"b1");
	placePiece(new Knight(this,ChessPiece::WHITE,"\u2658"),"g1");	
	placePiece(new Bishop(this,ChessPiece::WHITE,"\u2657"),"c1");
	placePiece(new Bishop(this,ChessPiece::WHITE,"\u2657"),"f1");	
	placePiece(new Queen(this,ChessPiece::WHITE,"\u2655"),"d1");
	placePiece(new King(this,ChessPiece::WHITE,"\u2654"),"e1");	
	placePiece(new Pawn(this,ChessPiece::WHITE,"\u2659"),"a2");
	placePiece(new Pawn(this,ChessPiece::WHITE,"\u2659"),"b2");
	placePiece(new Pawn(this,ChessPiece::WHITE,"\u2659"),"c2");
	placePiece(new Pawn(this,ChessPiece::WHITE,"\u2659"),"d2");
	placePiece(new Pawn(this,ChessPiece::WHITE,"\u2659"),"e2");
	placePiece(new Pawn(this,ChessPiece::WHITE,"\u2659"),"f2");
	placePiece(new Pawn(this,ChessPiece::WHITE,"\u2659"),"g2");
	placePiece(new Pawn(this,ChessPiece::WHITE,"\u2659"),"h2");
					
	//Initialize the black pieces
	placePiece(new Rook(this,ChessPiece::BLACK,"\u265C"),"a8");
	placePiece(new Rook(this,ChessPiece::BLACK,"\u265C"),"h8");			
	placePiece(new Knight(this,ChessPiece::BLACK,"\u265E"),"b8");
	placePiece(new Knight(this,ChessPiece::BLACK,"\u265E"),"g8");	
	placePiece(new Bishop(this,ChessPiece::BLACK,"\u265D"),"c8");
	placePiece(new Bishop(this,ChessPiece::BLACK,"\u265D"),"f8");	
	placePiece(new Queen(this,ChessPiece::BLACK,"\u265B"),"d8");
	placePiece(new King(this,ChessPiece::BLACK,"\u265A"),"e8");	
	placePiece(new Pawn(this,ChessPiece::BLACK,"\u265F"),"a7");
	placePiece(new Pawn(this,ChessPiece::BLACK,"\u265F"),"b7");
	placePiece(new Pawn(this,ChessPiece::BLACK,"\u265F"),"c7");
	placePiece(new Pawn(this,ChessPiece::BLACK,"\u265F"),"d7");
	placePiece(new Pawn(this,ChessPiece::BLACK,"\u265F"),"e7");
	placePiece(new Pawn(this,ChessPiece::BLACK,"\u265F"),"f7");
	placePiece(new Pawn(this,ChessPiece::BLACK,"\u265F"),"g7");
	placePiece(new Pawn(this,ChessPiece::BLACK,"\u265F"),"h7");
}

//move a piece to a given position, and returns true if successfully
//if the given position has a piece of same color, returns false
//if the given position has the opponent's piece, then captures it and returns true
bool ChessBoard::placePiece(ChessPiece* piece, string position)
{
	mapPosToVirtualIndex::iterator itr = globalMapPosToVirtualIndex.find(position);
	if(itr == globalMapPosToVirtualIndex.end())
		return false;
	SPieceIndex sTmp = itr->second;
	if(board[sTmp.row][sTmp.column] == NULL)
	{
		board[sTmp.row][sTmp.column] = piece;
		piece->setRow(sTmp.row);
		piece->setColumn(sTmp.column);	
		return true;
	}
	
	ChessPiece* ptr = board[sTmp.row][sTmp.column];	
	if(ptr->getColor() == piece->getColor())
	{
		return false;
	}
	else
	{
		//capture the opponent's piece by the game rule and return true
		board[sTmp.row][sTmp.column] = piece;
		piece->setRow(sTmp.row);
		piece->setColumn(sTmp.column);
		return true;
	}
	
	return false;
}

void ChessBoard::printBoard()
{
	char szTemp[16] = {0};
	for(int i =0 ;i <= BLOCK_SIZE*CHESS_SIZE ; i++)
	{
		if(i == (i/BLOCK_SIZE)*BLOCK_SIZE + BLOCK_SIZE/2)
		{
			printf("%d",CHESS_SIZE- i/BLOCK_SIZE);
		}
		else
		{
			printf(" ");
		}
		for(int j = 0;j<= BLOCK_SIZE*CHESS_SIZE;j++)
		{
			sprintf(szTemp,"%d_%d",i,j);
			if(globalMapRealIndexToPos.find(szTemp) != globalMapRealIndexToPos.end())
			{
				string strPos = globalMapRealIndexToPos[szTemp];
				SPieceIndex sPieceIndex = globalMapPosToVirtualIndex[strPos];
				if(board[sPieceIndex.row][sPieceIndex.column] !=  NULL)
				{
					printf("%s",(board[sPieceIndex.row][sPieceIndex.column]) ->getStrCode().c_str());
				}
				else 
				{
					printf(" ");
				}
			}
			else if( i%BLOCK_SIZE == 0&& j%BLOCK_SIZE == 0)
      {
      	printf("+");
      }
      else if(i%BLOCK_SIZE == 0 && j%BLOCK_SIZE != 0)
      {
      	printf("-");
      }
      else if(j % BLOCK_SIZE == 0 && i % BLOCK_SIZE != 0)
      {
      	printf("|");
      }
      else
      {
      	printf(" ");
      }
		}
		/*
		if(i == (i/BLOCK_SIZE)*BLOCK_SIZE + BLOCK_SIZE/2)
		{
			printf(" %d",CHESS_SIZE- i/BLOCK_SIZE);
		}
		*/
		printf("\n");
	}	
	
	printf(" ");
	for(int j = 0;j<= BLOCK_SIZE*CHESS_SIZE;j++)
	{
		if(j == (j/BLOCK_SIZE)*BLOCK_SIZE + BLOCK_SIZE/2)
		{
			printf("%c", 'a' +  j/BLOCK_SIZE);
		}
		else
		{
			printf(" ");
		}
	}
	printf("\n");
}

bool ChessBoard::move(string fromPosition, string toPosition)
{
	//find the exact piece from its position
	mapPosToVirtualIndex::iterator itr = globalMapPosToVirtualIndex.find(fromPosition);
	if(itr == globalMapPosToVirtualIndex.end())
	{
            //the range of chess piece's position is between a1 to a8 horizontally and h1 to h8 vertically,
            //mapping in the globalMapPosToVirtualIndex, where will be illegal if the position is not included.
		printf("illegal position %s\n",fromPosition.c_str());
		return false;
	}
	
	SPieceIndex sPieceIndex = itr->second;
	ChessPiece* ptr = board[sPieceIndex.row][sPieceIndex.column];
	if( ptr == NULL)
	{
		// can't move if there are no chess pieces in the corresponding positions
		printf("position %s does not have a piece,can not move\n",fromPosition.c_str());
		return false;
	}
	else 
	{
		list<string> lstResult;
		ptr->legalMoves(lstResult);
		if(lstResult.size() == 0)
		{
			printf("%s can not move,no appropriate position\n",fromPosition.c_str());
			return false;
		}
		else 
		{
			int num = count(lstResult.begin(),lstResult.end(),toPosition);
			if(num == 0)
			{
                            // can't move if there are no chess pieces in the corresponding position.
				printf("%s can not move,no appropriate position\n",fromPosition.c_str());
				lstResult.clear();
				return false;
			}
			else 
			{
				SPieceIndex sPieceIndexTmp = globalMapPosToVirtualIndex[toPosition];
				//use the chess piece from fromPosition to replace the piece from toPosotion
				board[sPieceIndexTmp.row][sPieceIndexTmp.column] = ptr;
				//set the coordinate after replacing
				ptr->setRow(sPieceIndexTmp.row);
				ptr->setColumn(sPieceIndexTmp.column);
				//clear the pieces in the fromPosition
				board[sPieceIndex.row][sPieceIndex.column] = NULL;
				lstResult.clear();
				return true;
			}
		}
	}

	return false;
}


//judge the state of each chess piece
int ChessPiece::judgePieceStat(int row,int column)
{
	char szTemp[16] = {0};
	sprintf(szTemp,"%d_%d",row,column);
	if(globalMapvirtualIndexToPos.find(szTemp) == globalMapvirtualIndexToPos.end())
	{
            //out of the boarder, and the move is an illegal position
            return -1;
	}
	
	ChessBoard* curChessBoard = getChessBoard();
	//if the position is null, then no chess piece can move to this position
	if(curChessBoard->board[row][column] == NULL)
	{
            return 0;
	}
	
	ChessPiece* ptr = curChessBoard->board[row][column];
	//if the position has a chess piece which has the same color, then can't capture this piece
	//else, can capture this piece in this position by the opponent's piece
	if(ptr->getColor() == getColor())
	{
            return 1;
	}
	else
	{
            return 2;
	}
        return -1;
}
#endif /* CHESSBOARD_H */