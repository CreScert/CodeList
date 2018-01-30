#pragma once

// ����̽�ⷨ

// ƽ��̽�ⷨ
// ������̽�ⷨ���ƣ�ֻ�ǳ�ͻʱ��ɢ�з�����ͬ
// ɢ�з�����(pos + pf^n) % MOD;



// ˫ɢ�� / ��ɢ�з�
// ˫ɢ�� �� ����̽�ⷨ�Լ�ƽ��̽�ⷨ ���ƣ�ֻ�Ǵ����ͻ�ĺ�����ͬ
// ��ʱ��˫ɢ�еĺ���Ϊ:
// pos + ( n * ( R - ( key % R ) ) ) ) %MOD;
//����:pos ; ɢ��ֵ����ͻ������ֵ��
//	   n   : �ڼ��α���
//	   R   : �ݶ� 7 
//     key : �����ֵ
//     MOD : �ݶ�10


#include <iostream>
using namespace std;
#define LINEARPROBOING 0
#define SQUAREPROBING 1
#define AGAINHASH 2


template <class T, class Ret> struct LINEARPROBING {
	T key; // ��
	Ret value; // ֵ
	int state; // ״̬ 0��Ϊռ�ã����㣺ռ��
};


template <class T,class Ret> class LinearProbing{
public :

	int capacity = 10;

	int LPSize = 0;
	LinearProbing();
	~LinearProbing();
 
	int GetHashValue(T key);
	int insert(T key, Ret value);
	Ret update(T key, Ret newValue);
	Ret update(T key, Ret newValue, int pos);
	Ret deleteKey(T key);
	Ret queryKey(T key);
	void queryAll();
	void CheckSize();
	char *toChar(int);
	char *toChar(char*);
	bool cmpKey(T key,int pos);


	int LinearSize; // ����ĳ���
	int GetPos(int pos,int n);
	int GetPos(int pos, int n, T key);
	int MOD;
	int R;
	int flag = LINEARPROBOING;
	int *LinearTable;
	
private:
	struct LINEARPROBING<T,Ret> *queryList(T key);
	
};

#include "stdafx.h"
// ����̽�ⷨ

template<class T, class Ret>LinearProbing<T, Ret>::LinearProbing()
{
	LinearSize = capacity;
	MOD = 10;
	R = 7;
	LinearTable = (int*)calloc(sizeof(int), LinearSize*sizeof(int));
}

template<class T, class Ret> LinearProbing<T, Ret>::~LinearProbing()
{
	int count = 0;
	for (int i = 0; i < LinearSize; i++)
	{
		struct LINEARPROBING<T,Ret> *lp = (struct LINEARPROBING<T, Ret> *)LinearTable[i];
		if (lp != NULL)
		{
			free(lp);
			lp = NULL;
			count++;
		}
	}
	free(LinearTable);
	LinearTable = NULL;
}

// ��ȡ��ϣֵ
template<class T, class Ret> int LinearProbing<T, Ret>::GetHashValue(T key)
{
	char * nChar = toChar(key);
	unsigned long h = 0;
	while (*nChar)
	{
	h = (h << 4) + *nChar++;
	unsigned long g = h & 0xF0000000L;
	if (g)
	h ^= g >> 24;
	h &= ~g;
	}
	return h % MOD;
}

template<class T, class Ret> Ret LinearProbing<T, Ret>::deleteKey(T key)
{
	// ��ȡ����
	int hashPos = GetHashValue(key);
	int pos = hashPos;
	int count = 0;
	while (1)
	{
		struct LINEARPROBING<T, Ret> * lp = (struct LINEARPROBING<T, Ret> *)LinearTable[pos];

		//���������ڵ�λ�ò����ڣ��˳�
		if (lp == NULL)
		{
			return NULL;
		}
		// ƥ�䵽��
		if (cmpKey(key, pos))
		{
			Ret value = lp->value;
			LinearTable[pos] = 0;
			LPSize--;
			free(lp);
			return value;
		}
		if (flag == LINEARPROBOING)
		{
			// ��������̽��
			pos = GetPos(pos, ++count);
		}
		else if (flag == SQUAREPROBING) {
			pos = GetPos(hashPos, ++count);
		}
		else {
			pos = GetPos(hashPos, ++count, key);
		}


	}
	return NULL;
}

template<class T, class Ret> int LinearProbing<T, Ret> ::GetPos(int pos, int n)
{
	if (flag == LINEARPROBOING) {
		return (pos + n) % MOD;
	}
	else {
		return (pos + n*n) % MOD;
	}
}


template<class T, class Ret> char* LinearProbing<T, Ret>::toChar(int key)
{
	char *temp = (char*)calloc(sizeof(char*), 3);
	sprintf_s(temp,sizeof(char*)*3, "%d", key);
	return temp;
}
template<class T, class Ret> char* LinearProbing<T, Ret>::toChar(char* key)
{
	return key;
}
template<class T, class Ret> int LinearProbing<T, Ret>::GetPos(int pos, int n, T key)
{
	//int aaa = toChar(key)[0];
	//cout << aaa << endl;
	//sprintf(name, "%s", key);
	//return (pos + (n * (R - (key % R)))) % MOD;
	return 1;
}
// ����ֵ
template<class T, class Ret>int LinearProbing<T, Ret>::insert(T key, Ret value)
{
	// ��ȡ�±�
	int hashPos = GetHashValue(key);
	// ����û��ֵ
	if (LinearTable[hashPos] == NULL)
	{
		struct LINEARPROBING<T,Ret> *lp = (struct LINEARPROBING<T, Ret> *)malloc(sizeof(struct LINEARPROBING<T, Ret>));
		lp->key = key;
		lp->value = value;
		LPSize++;
		CheckSize();
		LinearTable[hashPos] = (int)lp;
	}
	else
	{
		// �����˳�ͻ
		// �ȱȽϵ�ǰ��Ҫ��ŵ�ֵ�Ƿ��Ѿ��б�����
		if (cmpKey(key, hashPos))
		{
			//������,�滻
			update(key, value, hashPos);
		}
		else
		{
			int pos = hashPos;
			int exit = 0; // �����˳�
			int count = 0;
			//�����ڣ���ʼ̽��
			do {
				// ��ȡ�µ�λ��
				//newPos = (newPos +1)%MOD;
				if (flag == LINEARPROBOING) {
					pos = GetPos(pos, ++count);
				}
				else if (flag == SQUAREPROBING) {
					pos = GetPos(hashPos, ++count);
				}
				else {
					pos = GetPos(hashPos, ++count, key);
				}

				// ̽�⵽�˴�û��ֵ���ͷ��ڴ˴�
				if (LinearTable[pos] == NULL)
				{
					struct LINEARPROBING<T, Ret> * lp = (struct LINEARPROBING<T, Ret>*)malloc(sizeof(struct LINEARPROBING<T, Ret>));
					lp->key = key;
					lp->value = value;
					LPSize++;
					CheckSize();
					LinearTable[pos] = (int)lp;
					break;
				}
				else {
					//�˴���ֵ���ж��ǲ����Ѿ�����
					if (cmpKey(key, pos))
					{
						update(key, value, pos);
					}
				}
				exit++;
				if (exit > LinearSize)
				{
					cout << "̽���������������ĳ��ȣ��˳�̽�⣬����ʧ��" << endl;
					return NULL;
				}
				cout << "̽�� " << key << " ʧ�ܣ��˴���ֵ�Ҳ�ƥ�䣬��ǰ��ֵΪ:" << pos << "��������һ��̽��" << endl;
			} while (1);
		}
	}
	return 0;
}

// �Ƚ��Ƿ����
template<class T, class Ret> bool LinearProbing<T, Ret>::cmpKey(T key, int pos)
{
	// �Ȼ�ȡ�ṹ
	struct LINEARPROBING<T, Ret> * lp = (struct LINEARPROBING<T, Ret>*)LinearTable[pos];
	// �Ƚ�
	/*if (lp != NULL && strcmp(lp->key, key) == 0)
	{
	return true;
	}*/

	if (lp != NULL && lp->key == key)
	{
		return true;
	}
	return false;
}
template<class T, class Ret> Ret LinearProbing<T, Ret>::update(T key, Ret newValue, int pos)
{
	if (pos != -1) {
		//���ﲻ��Ϊ�մ���
		struct LINEARPROBING<T, Ret> *lp = (struct LINEARPROBING<T, Ret> *)LinearTable[pos];
		Ret value = lp->value;
		lp->value = newValue;
		return value;
	}
	else {
		struct LINEARPROBING<T, Ret> *lp = queryList(key);
		Ret oldValue = lp->value;
		lp->value = newValue;
		return oldValue;
	}
}
template<class T,class Ret>
Ret LinearProbing<T, Ret>::update(T key,Ret newValue)
{
	return update(key, newValue, -1);
}

template<class T, class Ret>  struct LINEARPROBING<T,Ret> *LinearProbing<T, Ret>::queryList(T key)
{
	// ��ȡ����
	int hashPos = GetHashValue(key);
	int pos = hashPos;
	int count = 0;
	while (1)
	{
		struct LINEARPROBING<T, Ret> * lp = (struct LINEARPROBING<T, Ret> *)LinearTable[pos];

		//���������ڵ�λ�ò����ڣ��˳�
		if (lp == NULL)
		{
			return NULL;
		}
		// ƥ�䵽��
		if (cmpKey(key, pos))
		{
			return lp;
		}
		if (flag == LINEARPROBOING)
		{
			// ��������̽��
			pos = GetPos(pos, ++count);
		}
		else  if (flag == SQUAREPROBING) {
			pos = GetPos(hashPos, ++count);
		}
		else {
			pos = GetPos(hashPos, ++count, key);
		}


	}
	return NULL;
}
// ��ѯ
template<class T, class Ret> Ret LinearProbing<T, Ret>::queryKey(T key)
{
	struct LINEARPROBING<T,Ret> *lp = queryList(key);
	return lp == NULL ? NULL : lp->value;
}

template<class T, class Ret> void LinearProbing<T, Ret>::queryAll()
{
	for (int i = 0; i < LinearSize; i++)
	{
		struct LINEARPROBING<T, Ret> *lp = (struct LINEARPROBING<T, Ret> *)LinearTable[i];
		cout << "����:" << i;
		if (lp != NULL)
		{
			cout << "\t�����:" << lp->key << "=" << lp->value;
		}
		cout << endl;
	}
}

// ���·���ռ�
template<class T, class Ret>
inline void LinearProbing<T, Ret>::CheckSize()
{
	cout << "������Ŀ����:" << LPSize << "���������" << capacity << endl;
	// ����С�����˿ռ��һ��ʱ�����пռ� ����
	if (LPSize >= capacity*3 / 4 )
	{
		cout << "����" << endl;
		
		queryAll();
		int *OldTable = LinearTable;// ����ɵı���ΪҪ�滻
		int OldSize = LinearSize;//ԭ����Ĵ�С
		LPSize = 0;
		

		// �µ�������С
		LinearSize = LinearSize + LinearSize;
		capacity = LinearSize;
		MOD = capacity;
		// �µı�
		LinearTable = (int*)calloc(LinearSize, sizeof(int));

		
		// ����ԭ���ı���ԭ���ı�����ݲ��뵽�µı���
		for (int i = 0; i < OldSize; i++)
		{
			if (OldTable[i] != NULL)
			{
				struct LINEARPROBING<T, Ret> *lp = (struct LINEARPROBING<T, Ret> *)OldTable[i];
				if (lp != NULL)
				{
					insert(lp->key, lp->value);
					free(lp);
					lp = NULL;
				}
			}
		}
		 
		free(OldTable);
		OldTable = NULL;
		queryAll();
	}

}
