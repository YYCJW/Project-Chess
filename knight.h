/* File:   knight.h
 * Author: Yan
 *
 * Created on May 3, 2022, 10:55 AM
 */

#ifndef KNIGHT_H
#define KNIGHT_H

#include "chessPiece.h"
//Knight: each side has 2 knights
class Knight :public ChessPiece{
public:
	Knight(ChessBoard* pBoard,Color _color,string _strCode):ChessPiece(pBoard,_color,_strCode){}
public:
	int legalMoves(list<string>& lstResult);
};

//**************************************************************************
// A knight's move forms an "L"-shape: two squares vertically and one      *
// square horizontally, or two squares horizontally and one square         *
// vertically.                                                             * 
// The knight is the only piece that can leap over other pieces.           *   
// it can move two squares vertically and one square horizontally, or two  *
// squares horizontally and one square vertically                          *
//**************************************************************************

int Knight::legalMoves(list<string>& lstResult)
{
	int row = getRow();
	int column = getColumn();
	char szTemp[16] = {0};
	lstResult.clear();

  //there are 8 ways that a knight can move
	//the first way: move 1 column right and 2 rows upper
	int iRet = judgePieceStat(row + 2,column + 1);
	if(iRet == 0 || iRet == 2)
	{
		sprintf(szTemp,"%d_%d",row + 2,column + 1);
		lstResult.push_back(globalMapvirtualIndexToPos[szTemp]);
	}
	
	//the second way: move 2 columns right and 1 row upper
	iRet = judgePieceStat(row + 1,column + 2);
	if(iRet == 0 || iRet == 2)
	{
		sprintf(szTemp,"%d_%d",row + 1,column + 2);
		lstResult.push_back(globalMapvirtualIndexToPos[szTemp]);
	}
	
	//the third way: move 1 column right and 2 rows downward
	iRet = judgePieceStat(row -2,column + 1);
	if(iRet == 0 || iRet == 2)
	{
		sprintf(szTemp,"%d_%d",row -2,column + 1);
		lstResult.push_back(globalMapvirtualIndexToPos[szTemp]);
	}
	
	//the fourth way: move one column right and 1 row downwards
	iRet = judgePieceStat(row -1,column +2);
	if(iRet == 0 || iRet == 2)
	{
		sprintf(szTemp,"%d_%d",row -1,column +2);
		lstResult.push_back(globalMapvirtualIndexToPos[szTemp]);
	}
	
	//the fifth way: move 1 column left and 2 rows upper
	iRet = judgePieceStat(row + 2,column -1);
	if(iRet == 0 || iRet == 2)
	{
		sprintf(szTemp,"%d_%d",row + 2,column -1);
		lstResult.push_back(globalMapvirtualIndexToPos[szTemp]);
	}
	
	//the sixth way: move 2 columns left and 1 row upper
	iRet = judgePieceStat(row + 1,column -2);
	if(iRet == 0 || iRet == 2)
	{
		sprintf(szTemp,"%d_%d",row + 1,column -2);
		lstResult.push_back(globalMapvirtualIndexToPos[szTemp]);
	}
	
	//the seventh way: move 1 column left and 2 rows 7 downwards
	iRet = judgePieceStat(row -2,column - 1);
	if(iRet == 0 || iRet == 2)
	{
		sprintf(szTemp,"%d_%d",row -2,column - 1);
		lstResult.push_back(globalMapvirtualIndexToPos[szTemp]);
	}
	
	//the eighth way: move 2 columns left and 1 row 8 downwards
	iRet = judgePieceStat(row - 1,column - 2);
	if(iRet == 0 || iRet == 2)
	{
		sprintf(szTemp,"%d_%d",row - 1,column - 2);
		lstResult.push_back(globalMapvirtualIndexToPos[szTemp]);
	}
	return 0;
}

#endif /* KNIGHT_H */

