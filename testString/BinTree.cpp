#include "stdafx.h"
TREE * TreeHead = NULL;
BOOL AddTree(const int num)
{
	InsertTree(num, NULL);
	return TRUE;
}

TREE * GetTreeHead() 
{
	return TreeHead;
}
//增加树
BOOL InsertTree(const int num, TREE *Tree)
{
	//没有树，创建根结点
	if (TreeHead == NULL)
	{
		TreeHead = (TREE *)malloc(sizeof(TREE*)*2);
		TreeHead->num = num;
		TreeHead->LeftTree = NULL;
		TreeHead->RightTree = NULL;
	}//如果这个结点为空直接放在这个节点下，返回
	else if (Tree == NULL)
	{
		// 刚进来，从根节点开始寻找
		// 左节点
		if (TreeHead->num > num) 
		{
			if (TreeHead->LeftTree == NULL) 
			{
				TREE * TreeTemp = (TREE *)malloc(sizeof(TREE*)*2);
				TreeTemp->num = num;
				TreeTemp->LeftTree = NULL;
				TreeTemp->RightTree = NULL;
				TreeHead->LeftTree = TreeTemp;
			}
			else 
			{
				InsertTree(num, TreeHead->LeftTree);
			}
		}
		// 右节点
		else if (TreeHead->num < num)
		{
			if (TreeHead->RightTree == NULL) 
			{
				TREE * TreeTemp = (TREE *)malloc(sizeof(TREE*)*2);
				TreeTemp->num = num;
				TreeTemp->LeftTree = NULL;
				TreeTemp->RightTree = NULL;
				TreeHead->RightTree = TreeTemp;
			}
			else 
			{
				InsertTree(num, TreeHead->RightTree);
			}
			
		}
	}
	else
	{
		//如果这个值比现在的结点大，放在右边的结点树下
		if (Tree->num < num) 
		{
			puts("插入右树");
			if (Tree->RightTree == NULL) 
			{
				TREE * TreeTemp = (TREE *)malloc(sizeof(TREE*)*2);
				TreeTemp->num = num;
				TreeTemp->LeftTree = NULL;
				TreeTemp->RightTree = NULL;
				Tree->RightTree = TreeTemp;
			}
			else
			{
				InsertTree(num, Tree->RightTree);
			}
			
		}
			
		else if (Tree->num > num)//如果这个值比现在的结点小，放在左边的结点树下
		{
			puts("插入左树");
			if (Tree->LeftTree == NULL) 
			{
				TREE * TreeTemp = (TREE *)malloc(sizeof(TREE*)*2);
				TreeTemp->num = num;
				TreeTemp->LeftTree = NULL;
				TreeTemp->RightTree = NULL;
				Tree->LeftTree = TreeTemp;
			}
			else
			{
				InsertTree(num, Tree->LeftTree);
			}
			
		}

	}

	return TRUE;
}
