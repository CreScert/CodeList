#pragma once

/*
����Ŀ��Ϊ����ϰ������

��������ʵ�֣���Ϊ��������������

31,63,23,41,85,
*/
struct TREE
{
	int num;

	struct TREE *LeftTree;//����
	struct TREE *RightTree;//����


};


TREE * GetTreeHead();

BOOL InsertTree(const int num,TREE *TreeNow);
//������
BOOL AddTree(const int num);