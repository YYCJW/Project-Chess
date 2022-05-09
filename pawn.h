/* File:   pawn.h
 * Author: Yan
 *
 * Created on May 3, 2022, 10:56 AM
 */

#ifndef PAWN_H
#define PAWN_H

#include "chessPiece.h"
//Pawn: each side has 8 pawns
class Pawn :public ChessPiece{
public:
	Pawn(ChessBoard* pBoard,Color _color,string _strCode):ChessPiece(pBoard,_color,_strCode){}
public:
	int legalMoves(list<string>& lstResult);
};

//**************************************************************************
// A pawn in the initial position may move one or two squares vertically   *
// forward to an empty square, but cannot leap over any piece, and it can  *
// never move backwards. Subsequently it can move only one square          * 
// vertically forward to an empty square.                                  *    
// A pawn may also capture (replace) an opponent's piece diagonally one    *
// square in front of it.                                                  *
//**************************************************************************

int Pawn::legalMoves(list<string>& lstResult)
{
	int iRet = -1;
	int row = getRow();
	int column = getColumn();
	SPieceIndex sPieceIndex;
	char szTemp[16] = {0};
	lstResult.clear();
	
	//if it is a white pawn, it moves upwards, which is from the row 2 to 8 corresponding to the opposite direction(6 to 0) in the printing board.
	if(getColor() == WHITE)
	{
		//judge if the white pawn can move one square	
		iRet = judgePieceStat(row - 1,column);
		if(iRet == 0)
		{
			sprintf(szTemp,"%d_%d",row - 1,column);
			lstResult.push_back(globalMapvirtualIndexToPos[szTemp]);
			if(iRet == 0 && row == 6 /*6 is the initial row in the printing board*/)
			{
				//When the white pawn is in the initial position, if there is no other piece in front of it, it can move two squares
				iRet = judgePieceStat(row - 2,column);
				if(iRet == 0)
				{
					sprintf(szTemp,"%d_%d",row - 2,column);
					lstResult.push_back(globalMapvirtualIndexToPos[szTemp]);
				}
			}
		}	
		//judge if the pawn can replace the opponent's piece which is located in the upper right position 
		iRet = judgePieceStat(row - 1,column + 1);
		if(iRet == 2)
		{
			sprintf(szTemp,"%d_%d",row - 1,column + 1);
			lstResult.push_back(globalMapvirtualIndexToPos[szTemp]);
		}
		
		//judge if the pawn can replace the opponent's piece which is located in the upper left position 
		iRet = judgePieceStat(row - 1,column - 1);
		if(iRet == 2)
		{
			sprintf(szTemp,"%d_%d",row - 1,column - 1);
			lstResult.push_back(globalMapvirtualIndexToPos[szTemp]);
		}
	}
	
	//else it is a black pawn, it moves downwards, which moves from the row 7 to 1 
  //corresponding to the opposite direction(1 to 7) in the printing board.
	else 
	{
		iRet = judgePieceStat(row + 1,column);
		if(iRet == 0)
		{
			sprintf(szTemp,"%d_%d",row + 1,column);
			lstResult.push_back(globalMapvirtualIndexToPos[szTemp]);
			//When the black pawn is in the initial position, if there is no other piece in front of it, it can move two squares
			if(iRet == 0 && row == 1)
			{
				iRet = judgePieceStat(row + 2,column);
				if(iRet == 0)
				{
					sprintf(szTemp,"%d_%d",row + 2,column);
					lstResult.push_back(globalMapvirtualIndexToPos[szTemp]);
				}
			}
		}
		
		//judge if the pawn can replace the opponent's piece which is located in the upper right position  
		iRet = judgePieceStat(row + 1,column - 1);
		if(iRet == 2)
		{
			sprintf(szTemp,"%d_%d",row + 1,column - 1);
			lstResult.push_back(globalMapvirtualIndexToPos[szTemp]);
		}
		
		//judge if the pawn can replace the opponent's piece which is located in the upper left position 
		iRet = judgePieceStat(row + 1,column + 1);
		if(iRet == 2)
		{
			sprintf(szTemp,"%d_%d",row + 1,column + 1);
			lstResult.push_back(globalMapvirtualIndexToPos[szTemp]);
		}
	}
	
	return 0;
}

#endif /* PAWN_H */


