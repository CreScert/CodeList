#include "stdafx.h"
// ����̽�ⷨ
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

// ��ȡ��ϣֵ
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
	// ��ȡ����
	int hashPos = GetHashValue(key);
	int pos = hashPos;
	int count = 0;
	while (1)
	{
		LP * lp = (LP *)LinearTable[pos];
		
		//���������ڵ�λ�ò����ڣ��˳�
		if (lp == NULL)
		{
			return NULL;
		}
		// ƥ�䵽��
		if (cmpKey(key, pos))
		{
			
			char * value = lp->value;
			LinearTable[pos] = 0;
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
// ����ֵ
template<class T,class R> int LinearProbing<T,R>::insert(T key, char *value)
{
	// ��ȡ�±�
	int hashPos = GetHashValue(key);
	// ����û��ֵ
	if (LinearTable[hashPos] == NULL)
	{
		LP *lp = (LP *)malloc(sizeof(LP));
		lp->key = key;
		lp->value = value;

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
					pos = GetPos(hashPos, ++count,key);
				}
				
				// ̽�⵽�˴�û��ֵ���ͷ��ڴ˴�
				if (LinearTable[pos] == NULL)
				{
					LP * lp = (LP*)malloc(sizeof(LP));
					lp->key = key;
					lp->value = value;

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
				cout << "̽�� "<<key<<" ʧ�ܣ��˴���ֵ�Ҳ�ƥ�䣬��ǰ��ֵΪ:" << pos << "��������һ��̽��" << endl;
			}while (1);
		}
	}
	return 0;
}

// �Ƚ��Ƿ����
template<class T,class R> bool LinearProbing<T,R>::cmpKey(T key, int pos)
{
	// �Ȼ�ȡ�ṹ
	LP * lp = (LP*)LinearTable[pos];
	// �Ƚ�
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
		//���ﲻ��Ϊ�մ���
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
	// ��ȡ����
	int hashPos = GetHashValue(key);
	int pos = hashPos;
	int count = 0;
	while (1)
	{
		LP * lp = (LP *)LinearTable[pos];

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
		cout << "����:" << i;
		if (lp != NULL)
		{
			cout << "\t�����:" << lp->key << "=" << lp->value;
		}
		cout << endl;
	}
}*/