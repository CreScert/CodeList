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
//������
BOOL InsertTree(const int num, TREE *Tree)
{
	//û���������������
	if (TreeHead == NULL)
	{
		TreeHead = (TREE *)malloc(sizeof(TREE*)*2);
		TreeHead->num = num;
		TreeHead->LeftTree = NULL;
		TreeHead->RightTree = NULL;
	}//���������Ϊ��ֱ�ӷ�������ڵ��£�����
	else if (Tree == NULL)
	{
		// �ս������Ӹ��ڵ㿪ʼѰ��
		// ��ڵ�
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
		// �ҽڵ�
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
		//������ֵ�����ڵĽ��󣬷����ұߵĽ������
		if (Tree->num < num) 
		{
			puts("��������");
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
			
		else if (Tree->num > num)//������ֵ�����ڵĽ��С��������ߵĽ������
		{
			puts("��������");
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
