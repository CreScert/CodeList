#pragma once

// 线性探测法

// 平方探测法
// 与线性探测法类似，只是冲突时的散列方法不同
// 散列方法：(pos + pf^n) % MOD;



// 双散列 / 再散列法
// 双散列 与 线性探测法以及平方探测法 类似，只是处理冲突的函数不同
// 暂时定双散列的函数为:
// pos + ( n * ( R - ( key % R ) ) ) ) %MOD;
//其中:pos ; 散列值（冲突的索引值）
//	   n   : 第几次遍历
//	   R   : 暂定 7 
//     key : 保存的值
//     MOD : 暂定10


#include <iostream>
using namespace std;
#define LINEARPROBOING 0
#define SQUAREPROBING 1
#define AGAINHASH 2


template <class T, class Ret> struct LINEARPROBING {
	T key; // 键
	Ret value; // 值
	int state; // 状态 0：为占用，非零：占用
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


	int LinearSize; // 数组的长度
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
// 线性探测法

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

// 获取哈希值
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
	// 获取索引
	int hashPos = GetHashValue(key);
	int pos = hashPos;
	int count = 0;
	while (1)
	{
		struct LINEARPROBING<T, Ret> * lp = (struct LINEARPROBING<T, Ret> *)LinearTable[pos];

		//该索引所在的位置不存在，退出
		if (lp == NULL)
		{
			return NULL;
		}
		// 匹配到了
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
			// 进行线性探测
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
// 插入值
template<class T, class Ret>int LinearProbing<T, Ret>::insert(T key, Ret value)
{
	// 获取下标
	int hashPos = GetHashValue(key);
	// 看有没有值
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
		// 发生了冲突
		// 先比较当前需要存放的值是否已经有保存了
		if (cmpKey(key, hashPos))
		{
			//存在了,替换
			update(key, value, hashPos);
		}
		else
		{
			int pos = hashPos;
			int exit = 0; // 控制退出
			int count = 0;
			//不存在，开始探测
			do {
				// 获取新的位置
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

				// 探测到此处没有值，就放在此处
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
					//此处有值，判断是不是已经存在
					if (cmpKey(key, pos))
					{
						update(key, value, pos);
					}
				}
				exit++;
				if (exit > LinearSize)
				{
					cout << "探测次数超过了数组的长度，退出探测，插入失败" << endl;
					return NULL;
				}
				cout << "探测 " << key << " 失败，此处有值且不匹配，当前的值为:" << pos << "，进行下一轮探测" << endl;
			} while (1);
		}
	}
	return 0;
}

// 比较是否存在
template<class T, class Ret> bool LinearProbing<T, Ret>::cmpKey(T key, int pos)
{
	// 先获取结构
	struct LINEARPROBING<T, Ret> * lp = (struct LINEARPROBING<T, Ret>*)LinearTable[pos];
	// 比较
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
		//这里不做为空处理
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
	// 获取索引
	int hashPos = GetHashValue(key);
	int pos = hashPos;
	int count = 0;
	while (1)
	{
		struct LINEARPROBING<T, Ret> * lp = (struct LINEARPROBING<T, Ret> *)LinearTable[pos];

		//该索引所在的位置不存在，退出
		if (lp == NULL)
		{
			return NULL;
		}
		// 匹配到了
		if (cmpKey(key, pos))
		{
			return lp;
		}
		if (flag == LINEARPROBOING)
		{
			// 进行线性探测
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
// 查询
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
		cout << "索引:" << i;
		if (lp != NULL)
		{
			cout << "\t保存的:" << lp->key << "=" << lp->value;
		}
		cout << endl;
	}
}

// 重新分配空间
template<class T, class Ret>
inline void LinearProbing<T, Ret>::CheckSize()
{
	cout << "表中条目数量:" << LPSize << "表的容量：" << capacity << endl;
	// 当大小大于了空间的一半时，进行空间 分配
	if (LPSize >= capacity*3 / 4 )
	{
		cout << "重新" << endl;
		
		queryAll();
		int *OldTable = LinearTable;// 保存旧的表。因为要替换
		int OldSize = LinearSize;//原来表的大小
		LPSize = 0;
		

		// 新的容量大小
		LinearSize = LinearSize + LinearSize;
		capacity = LinearSize;
		MOD = capacity;
		// 新的表
		LinearTable = (int*)calloc(LinearSize, sizeof(int));

		
		// 遍历原来的表，将原来的表的内容插入到新的表中
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
