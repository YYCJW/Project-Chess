/* File:   bishop.h
 * Author: Yan
 *
 * Created on May 3, 2022, 11:02 AM
 */

#ifndef BISHOP_H
#define BISHOP_H

#include "chessPiece.h"
//Bishop: each side has 2 bishops
class Bishop :public ChessPiece{
public:
	Bishop(ChessBoard* pBoard,Color _color,string _strCode):ChessPiece(pBoard,_color,_strCode){}
public:
	int legalMoves(list<string>& lstResult);	
};

//***********************************************************
// A bishop can move any number of squares diagonally in   *
// any direction as long as it does not have to leap over  *
// other pieces                                       *
//***********************************************************

int Bishop::legalMoves(list<string>& lstResult)
{
	
	int iRet = -1;
	int row = getRow();
	int column = getColumn();
	char szTemp[16] = {0}; 
	lstResult.clear();
	
	//judge the bishop's upper right direction, both the row and column increase
	for(int i = row + 1 ,j= column + 1;i < CHESS_SIZE && j < CHESS_SIZE; i++,j++)
	{
		iRet = judgePieceStat(i,j);
		if(iRet == 0 || iRet == 2)
		{
			sprintf(szTemp,"%d_%d",i,j);
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
	
	//judge the bishop's upper left direction, the row increase and the column decrease
	for(int i = row + 1 ,j= column - 1;i < CHESS_SIZE && j >= 0; i++,j--)
	{
		iRet = judgePieceStat(i,j);
		if(iRet == 0 || iRet == 2)
		{
			sprintf(szTemp,"%d_%d",i,j);
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
	
	//judge the bishop's lower left direction, both the row and column decrease
	for(int i = row - 1 ,j= column - 1;i >= 0 && j >= 0; i--,j--)
	{
		iRet = judgePieceStat(i,j);
		if(iRet == 0 || iRet == 2)
		{
			sprintf(szTemp,"%d_%d",i,j);
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
	
	//judge the bishop's lower right direction, the row decrease and the column increase
	for(int i = row - 1 ,j= column + 1;i >= 0 && j < CHESS_SIZE; i--,j++)
	{
		iRet = judgePieceStat(i,j);
		if(iRet == 0 || iRet == 2)
		{
			sprintf(szTemp,"%d_%d",i,j);
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

#endif /* BISHOP_H */