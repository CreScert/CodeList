#include "stdafx.h"
// 线性探测法
/*
template<class T,class R>LinearProbing<T,R>::LinearProbing()
{
	LinearSize = 10;
	MOD = 10;
	R = 7;
	LinearTable = (int*)calloc(sizeof(int), LinearSize);
}

template<class T,class R> LinearProbing<T,R>::~LinearProbing()
{
	int count = 0;
	for (int i = 0; i < LinearSize; i++) 
	{
		LP *lp = (LP *)LinearTable[i];
		if (lp != NULL)
		{
			free(lp);
			count++;
		}
	}
	free(LinearTable);
}

// 获取哈希值
template<class T,class R> int LinearProbing<T,R>::GetHashValue(T key)
{
	
	/*unsigned long h = 0;
	while (*key)
	{
		h = (h << 4) + *key++;
		unsigned long g = h & 0xF0000000L;
		if (g)
			h ^= g >> 24;
		h &= ~g;
	}
	return h % MOD;*

	return 0;
}

template<class T,class R> char *LinearProbing<T,R>::deleteKey(T key)
{
	// 获取索引
	int hashPos = GetHashValue(key);
	int pos = hashPos;
	int count = 0;
	while (1)
	{
		LP * lp = (LP *)LinearTable[pos];
		
		//该索引所在的位置不存在，退出
		if (lp == NULL)
		{
			return NULL;
		}
		// 匹配到了
		if (cmpKey(key, pos))
		{
			
			char * value = lp->value;
			LinearTable[pos] = 0;
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

template<class T,class R> int LinearProbing<T,R> :: GetPos(int pos,int n) 
{
	if (flag == LINEARPROBOING) {
		return (pos + n) % MOD;
	}
	else{
		return (pos + n*n) % MOD;
	}
}


template<class T,class R> int LinearProbing<T,R>::GetPos(int pos, int n, T key)
{
	return (pos + (n * (R - (key % R)))) % MOD;
}
// 插入值
template<class T,class R> int LinearProbing<T,R>::insert(T key, char *value)
{
	// 获取下标
	int hashPos = GetHashValue(key);
	// 看有没有值
	if (LinearTable[hashPos] == NULL)
	{
		LP *lp = (LP *)malloc(sizeof(LP));
		lp->key = key;
		lp->value = value;

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
					pos = GetPos(hashPos, ++count,key);
				}
				
				// 探测到此处没有值，就放在此处
				if (LinearTable[pos] == NULL)
				{
					LP * lp = (LP*)malloc(sizeof(LP));
					lp->key = key;
					lp->value = value;

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
				cout << "探测 "<<key<<" 失败，此处有值且不匹配，当前的值为:" << pos << "，进行下一轮探测" << endl;
			}while (1);
		}
	}
	return 0;
}

// 比较是否存在
template<class T,class R> bool LinearProbing<T,R>::cmpKey(T key, int pos)
{
	// 先获取结构
	LP * lp = (LP*)LinearTable[pos];
	// 比较
	/*if (lp != NULL && strcmp(lp->key, key) == 0)
	{
		return true;
	}*

	if (lp != NULL && lp->key == key)
	{
		return true;
	}
	return false;
}
template<class T,class R> char *LinearProbing<T,R>::update(T key, char *newValue, int pos)
{
	if (pos != -1) {
		//这里不做为空处理
		LP *lp = (LP *)LinearTable[pos];
		char * value = lp->value;
		lp->value = newValue;
		return value;
	}
	else {
		LP *lp = queryList(key);
		char * oldValue = lp->value;
		lp->value = newValue;
		return oldValue;
	}
}
template<class T,class R> char *LinearProbing<T,R>::update(T key, char* newValue)
{
	return update(key, newValue, -1);
}

template<class T,class R> LP *LinearProbing<T,R>::queryList(T key)
{
	// 获取索引
	int hashPos = GetHashValue(key);
	int pos = hashPos;
	int count = 0;
	while (1)
	{
		LP * lp = (LP *)LinearTable[pos];

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
template<class T,class R> char *LinearProbing<T,R>::queryKey(T key)
{
	LP *lp = queryList(key);
	return lp == NULL ? NULL : lp->value;
}

template<class T,class R> void LinearProbing<T,R>::queryAll()
{
	for (int i = 0; i < LinearSize; i++)
	{
		LP *lp = (LP *)LinearTable[i];
		cout << "索引:" << i;
		if (lp != NULL)
		{
			cout << "\t保存的:" << lp->key << "=" << lp->value;
		}
		cout << endl;
	}
}*/