#pragma once

/*
此项目是为了练习二叉树

利用链表实现，分为左子树与右子树

31,63,23,41,85,
*/
struct TREE
{
	int num;

	struct TREE *LeftTree;//左树
	struct TREE *RightTree;//右树


};


TREE * GetTreeHead();

BOOL InsertTree(const int num,TREE *TreeNow);
//增加树
BOOL AddTree(const int num);