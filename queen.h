/* File:   queen.h
 * Author: Yan
 *
 * Created on May 3, 2022, 10:55 AM
 */


#ifndef QUEEN_H
#define QUEEN_H

#include "chessPiece.h"
//Queen: each side has 1 queen
class Queen :public ChessPiece{
public:
	Queen(ChessBoard* pBoard,Color _color,string _strCode):ChessPiece(pBoard,_color,_strCode){}
public:
	int legalMoves(list<string>& lstResult);
};

//**************************************************************************
// A queen combines the power of a rook and bishop and can move any number *
// of squares along a rank, file, or diagonal, but a queen cannot leap     *
// over other pieces.                                                      * 
//**************************************************************************

int Queen::legalMoves(list<string>& lstResult)
{
	int iRet = -1;
	int row = getRow();
	int column = getColumn();
	char szTemp[16] = {0};
	lstResult.clear();
	
	//calculate queen's row first
	for(int i = row + 1 ; i < CHESS_SIZE; i++ )
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
	
	//calculate queen's column
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
	
	//calculate the queen's diagonal direction
	//judge the upper right direction, both row and column increase
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
	
	//judge the upper left direction, the row increase and column decrease
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
	
	//judge the lower left direction, both row and column decrease
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
	
	//judge the lower right direction, the row decrease and column increase
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

#endif /* QUEEN_H */
