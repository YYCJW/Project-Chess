/* File:   rook.h
 * Author: Yan
 *
 * Created on May 3, 2022, 10:56 AM
 */

#ifndef ROOK_H
#define ROOK_H

#include "chessPiece.h"
//Rook: each side has 2 rooks
class Rook :public ChessPiece{
public:
	Rook(ChessBoard* pBoard,Color _color,string _strCode):ChessPiece(pBoard,_color,_strCode){}
public:
	int legalMoves(list<string>& lstResult);
};

//***********************************************************
// A rook can move any number of squares horizontally and  *
// vertically, forward or backward, but rooks cannot leap  *
// over other pieces                                       *
//***********************************************************

int Rook::legalMoves(list<string>& lstResult)
{
	int iRet = -1;
	int row = getRow();
	int column = getColumn();
	char szTemp[16] = {0};
	lstResult.clear();
	
	//calculate the row first
  //judge the state and position of the previous rows for rook
	for(int i = row + 1 ; i < CHESS_SIZE; i++ )
	{
		iRet = judgePieceStat(i,column);
		if(iRet == 0 || iRet == 2)
		{
			sprintf(szTemp,"%d_%d",i,column);
			lstResult.push_back(globalMapvirtualIndexToPos[szTemp]);
			//the rook can move to the given position and capture the opponent's piece, but can't move further
			if(iRet == 2)
			{
				break;
			}
		}
		else 
		{
			break;
		}
	}
	//judge the state and position of the rear rows for rook
	for(int i = row - 1 ; i >= 0 ; i-- )
	{
		iRet = judgePieceStat(i,column);
		if(iRet == 0 || iRet == 2)
		{
			sprintf(szTemp,"%d_%d",i,column);
			lstResult.push_back(globalMapvirtualIndexToPos[szTemp]);
			if(iRet == 2)
			{
				break;
			}
		}
		else 
		{
			break;
		}
	}
	
	//calculate the column for rook
  //judge the state and position of the right columns for rook
	for(int i = column + 1 ; i < CHESS_SIZE; i++ )
	{
		iRet = judgePieceStat(row,i);
		if(iRet == 0 || iRet == 2)
		{
			sprintf(szTemp,"%d_%d",row,i);
			lstResult.push_back(globalMapvirtualIndexToPos[szTemp]);
			if(iRet == 2)
			{
				break;
			}
		}
		else 
		{
			break;
		}
	}
	
	//judge the state and position of the left columns for rook
	for(int i = column - 1 ; i >= 0 ; i-- )
	{
		iRet = judgePieceStat(row,i);
		if(iRet == 0 || iRet == 2)
		{
			sprintf(szTemp,"%d_%d",row,i);
			lstResult.push_back(globalMapvirtualIndexToPos[szTemp]);
			if(iRet == 2)
			{
				break;
			}
		}
		else 
		{
			break;
		}
	}
	return 0;	
}

#endif /* ROOK_H */
