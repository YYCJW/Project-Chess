 /* File:   King.h
 * Author: Yan
 *
 * Created on May 3, 2022, 10:55 AM
 */

#ifndef KING_H
#define KING_H

#include "chessPiece.h"
//King: each side has 1 king
class King :public ChessPiece{
public:
	King(ChessBoard* pBoard,Color _color, string _strCode):ChessPiece(pBoard,_color,_strCode){}
public:
	virtual int legalMoves(list<string>& lstResult);	
	
};

//**************************************************************************
// The king moves only one square in any direction.                        *
//**************************************************************************

int King::legalMoves(list<string>& lstResult)
{
	int row = getRow();
	int column = getColumn();
	char szTemp[16] = {0};
	lstResult.clear();
	
	//calculate King's row first
	int iRet = judgePieceStat(row + 1,column);
	if(iRet == 0 || iRet == 2)
	{
		sprintf(szTemp,"%d_%d",row + 1,column);
		lstResult.push_back(globalMapvirtualIndexToPos[szTemp]);
	}
	
	iRet = judgePieceStat(row - 1,column);
	if(iRet == 0 || iRet == 2)
	{
		sprintf(szTemp,"%d_%d",row - 1,column);
		lstResult.push_back(globalMapvirtualIndexToPos[szTemp]);
	}
	
	//calculate King's column
	iRet = judgePieceStat(row,column + 1);
	if(iRet == 0 || iRet == 2)
	{
		sprintf(szTemp,"%d_%d",row,column + 1);
		lstResult.push_back(globalMapvirtualIndexToPos[szTemp]);
	}
	
	iRet = judgePieceStat(row,column - 1);
	if(iRet == 0 || iRet == 2)
	{
		sprintf(szTemp,"%d_%d",row,column - 1);
		lstResult.push_back(globalMapvirtualIndexToPos[szTemp]);
	}
	
	//calculate the King's diagonal direction
	//judge the upper right direction, both row and column increase
	iRet = judgePieceStat(row + 1,column + 1);
	if(iRet == 0 || iRet == 2)
	{
		sprintf(szTemp,"%d_%d",row + 1,column + 1);
		lstResult.push_back(globalMapvirtualIndexToPos[szTemp]);
	}
	
	//judge the lower right direction, the row decrease and column increase
	iRet = judgePieceStat(row - 1,column + 1);
	if(iRet == 0 || iRet == 2)
	{
		sprintf(szTemp,"%d_%d",row - 1,column + 1);
		lstResult.push_back(globalMapvirtualIndexToPos[szTemp]);
	}
	
	//judge the upper left direction, the row increase and column decrease
	iRet = judgePieceStat(row + 1,column - 1);
	if(iRet == 0 || iRet == 2)
	{
		sprintf(szTemp,"%d_%d",row + 1,column - 1);
		lstResult.push_back(globalMapvirtualIndexToPos[szTemp]);
	}
	
	//judge the lower left direction, both row and column decrease
	iRet = judgePieceStat(row - 1,column - 1);
	if(iRet == 0 || iRet == 2)
	{
		sprintf(szTemp,"%d_%d",row - 1,column - 1);
		lstResult.push_back(globalMapvirtualIndexToPos[szTemp]);
	}
	return 0;
}

#endif /* KING_H */

