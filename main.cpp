/* File:   main.cpp
 * Author: Yan
 *
 * Created on May 3, 2022, 10:50 AM
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <set>
#include <stack>
#include <queue>
#include <list>
#include <string>
#include <map>
#include <algorithm>
using namespace std;
#include "king.h"
#include "knight.h"
#include "bishop.h"
#include "rook.h"
#include "queen.h"
#include "pawn.h"
#include "chessBoard.h"

//Function prototypes
int print_prompt(bool);
int initPosIndex();
int destroy();

//Execution Begins Here
int main(int argc,char* argv[])
{
	//initialize all the variables
	char szfrom[8] = {0},szTo[8] = {0};
	int seque = 0;
	fd_set set;
	struct timeval timeout = {0};
	timeout.tv_sec = 60;
	int fd = fileno(stdin);
	initPosIndex();
	ChessBoard* board = new ChessBoard;
	board->initialize();
	board->printBoard();
	while(1)
	{
		print_prompt(board->m_bWhite);
		fflush(stdin);
		FD_SET(fd,&set);
		if(select(fd + 1,&set,NULL,NULL,&timeout))
	  {
	  	scanf("%s %s",&szfrom,&szTo);
	  	if( board->move(szfrom,szTo) == false)
	  	{
	  		continue;
	  	}
	  	
	  	board->printBoard();
	  	printf("is withdraw? 1:yes 2:no\n");
	  	fflush(stdin);
	  	FD_SET(fd,&set);
	  	if(select(fd + 1,&set,NULL,NULL,&timeout))
	  	{
	  		scanf("%d",&seque);
	  		if(seque == 1)
	  		{
	  			if( !board->stackStep.empty())
	  			{
	  				int step = board->stackStep.top();
	  				board->stackStep.pop();
	  				ChessBoard* board1 = new ChessBoard;
						board1->initialize();
						string strHistroyMove;
						for(int i = 1; i < step;i++)
						{
							strHistroyMove = board->queueHistoryOp.front();
							board->queueHistoryOp.pop();
							size_t pos = strHistroyMove.find("_");
							string strfrom = strHistroyMove.substr(0,pos);
							string strTo = strHistroyMove.substr(pos+1);
							board1->move(strfrom,strTo);
							board1->m_iStep = i;
							board1->stackStep.push(i);
              board1->queueHistoryOp.push(strHistroyMove);
						}
						board1->printBoard();
						board1->m_bWhite = board->m_bWhite;
						delete board;
						board = board1;
						continue;
	  			}
	  			else
	  			{
	  				ChessBoard* board1 = new ChessBoard;
						board1->initialize();
						board1->printBoard();
						board1->m_bWhite = board->m_bWhite;
						delete board;
						board = board1;
						continue;
	  			} 			
	  		}
	  	}	
	  	
	  	board->m_iStep++;
  		string strOperation = string(szfrom) + string("_") + szTo;
  		board->stackStep.push(board->m_iStep);
  		board->queueHistoryOp.push(strOperation);
	  }
	  else
	  {
	  	if(board->m_bWhite)
	  	{
	  		printf("after 60 second,the white bide have no input\n");
	  	}
	  	else
	  	{
	  		printf("after 60 second,the black bide have no input\n");
	  	}
	  	printf("do you lose? 1:yes 2:no\n");
	  	int succFlag = 0;	  	
	  	scanf("%d",&succFlag);
	  	if(succFlag == 1)
	  	{
	  		if(board->m_bWhite)
	  		{
	  			printf("the white bide succ\n");
	  		}
	  		else
	  		{
	  			printf("the black bide succ\n");
	  		}
	  		break;
	  	}
	  	else
	  	{
	  		continue;
	  	}
	  }
	  
	  if(board->m_bWhite)
		{
			board->m_bWhite = false;
		}
		else
		{
			board->m_bWhite = true;
		}
	}
	delete board;
	destroy();
	return 0;
}

int print_prompt(bool flag)
{
	if(flag)
	{
		printf("please white side move\n");
	}
	else
	{
		printf("please black side move\n");
	}
	return 0;
}

int initPosIndex()
{
	globalMapPosToVirtualIndex.clear();
	globalMapvirtualIndexToPos.clear();
	globalMapRealIndexToPos.clear();
	char szTemp[16] = {0};
	char szTemp1[16] = {0};
	SPieceIndex sPieceIndexTemp;
	for(int i= CHESS_SIZE;i > 0; i--)
	{
		for(int j = 'a'; j < 'i'; j++)
		{
			sprintf(szTemp,"%c%d",j,i);
			sPieceIndexTemp.row = CHESS_SIZE - i;
			sPieceIndexTemp.column = j -'a';
			globalMapPosToVirtualIndex.insert(mapPosToVirtualIndex::value_type(szTemp,sPieceIndexTemp));
			sprintf(szTemp1,"%d_%d",CHESS_SIZE - i,j -'a');
			globalMapvirtualIndexToPos.insert(mapVirtualIndexToPos::value_type(szTemp1,szTemp));
			int iRealRow = (CHESS_SIZE - i)*BLOCK_SIZE + BLOCK_SIZE/2;
			int iRealColumn = ( j - 'a')*BLOCK_SIZE + BLOCK_SIZE/2;
			sprintf(szTemp1,"%d_%d",iRealRow,iRealColumn);
			globalMapRealIndexToPos.insert(mapRealIndexToPos::value_type(szTemp1,szTemp));
		}
	}
}

int destroy()
{
	globalMapPosToVirtualIndex.clear();
	globalMapvirtualIndexToPos.clear();
	globalMapRealIndexToPos.clear();
}
