
#include "stdafx.h"

int *TableHeader = NULL; // ��ͷ,����

// ��ʼ�� ����
struct ListNode *InitChain()
{
	struct ListNode *listNodeHeader = NULL;
	// ���� �б�ͷ
	if (listNodeHeader == NULL)
	{
		// �ļ�ͷ
		listNodeHeader = (struct ListNode *)malloc(sizeof(struct ListNode));
		if (listNodeHeader == NULL)
		{
			puts("no spaces");
			return NULL;
		}
	}
	return listNodeHeader;
}

// ��ʼ��ɢ�б�
int *InitHashTable()
{
	// ��ʼ�� ��ͷ,
	TableHeader = (int *)calloc(TableSize * sizeof(int), 1);
	// ��ʼ�� ����
	// InitChain();
	return TableHeader;
}

// ����ɢ�б�
int HashTable()
{
	// ��ʼ��ɢ�б�
	InitHashTable();

	return 0;
}

// ��ȡ��ϣֵ
int GetHashValue(char*key)
{

	unsigned long h = 0;
	while (*key)
	{
		h = (h << 4) + *key++;
		unsigned long g = h & 0xF0000000L;
		if (g)
			h ^= g >> 24;
		h &= ~g;
	}
	return h % MOD;

}

// ���ݼ���ֵ
char *query(char *key)
{
	int hashPos = GetHashValue(key); // ��ȡ����hashֵ

									 // ���� ��� ����ĵ�ǰ�±���û�б���ĵ�ֵַ
	int pos = TableHeader[hashPos];

	// û���ҵ�
	if (pos == 0)
	{
		return NULL;
	}
	else
	{
		// ���� �õ��ĵ�ַ��ȡ������ͷ
		struct ListNode *HeaderList = (struct ListNode *)TableHeader[hashPos];
		// ����������������ڷ����˳�ͻ������û�г�ͻ������ֻ��һ������ͷҲ��ֻƥ������ͷ
		for (struct ListNode *CurList = HeaderList; CurList != NULL; CurList = CurList->next)
		{
			if (strcmp(CurList->key, key) == 0)
			{
				return CurList->value;
			}
		}
		return NULL;
	}
}
// ��ѯ
void queryAll()
{
	for (int hashPos = 0; hashPos < TableSize; hashPos++)
	{
		printf("����:%d:  ", hashPos);
		struct ListNode *HeaderList = (struct ListNode *)TableHeader[hashPos];
		for (struct ListNode *CurList = HeaderList; CurList != NULL; CurList = CurList->next)
		{
			printf("��ַ:%d,��:%s = %s\t", (int)TableHeader[hashPos], CurList->key, CurList->value);
		}
		printf("\n");
	}
}

// ɾ�������ֵ��
char * deleteKey(char *key)
{
	// ��ȡhashֵ��������������Ǹ�λ��
	int hashPos = GetHashValue(key);

	// �鿴��ǰ�±��Ƿ���ֵ
	int pos = TableHeader[hashPos];

	// û��ֵ
	if (pos == 0)
	{
		return NULL;
	}
	else
	{
		// ���� �õ��ĵ�ַ��ȡ������ͷ
		struct ListNode *HeaderList = (struct ListNode *)TableHeader[hashPos];

		// ɾ���ĺ������Ĳ�һ������ƥ������ͷ
		// ����ͷΪNULL������NULL
		if (HeaderList == NULL)
		{
			return NULL;
		}
		else
		{
			// ƥ�䵱ǰ��ֵ������У��ж�ֵ�Ƿ���ͬ
			if (strcmp(HeaderList->key, key) == 0)
			{
				TableHeader[hashPos] = (int)HeaderList->next;
				return HeaderList->value;
			}
			else
			{
				//���ֻ������ͷ
				if (HeaderList->next == NULL)
				{
					return NULL;
				}
				else
				{
					struct ListNode *CurList = HeaderList;
					// ͷ������ ��ʼ������
					for (; CurList->next != NULL; CurList = CurList->next)
					{
						if (strcmp(CurList->next->key, key) == 0)
						{
							char * value = CurList->next->value;
							CurList->next = CurList->next->next;
							return value;
						}
					}

					// �м�Ҳû���Ҽ�����ʼ��β��
					if (strcmp(CurList->next->key, key) == 0)
					{
						char * value = CurList->next->value;
						CurList->next = CurList->next->next;
						return value;
					}
				}
			}
		}


		return NULL;
	}
}
// ����
char* update(char *key, char *newValue)
{
	int hashPos = GetHashValue(key); // ��ȡ����hashֵ

									 // ���� ��� ����ĵ�ǰ�±���û�б���ĵ�ֵַ
	int pos = TableHeader[hashPos];

	// û���ҵ�
	if (pos == 0)
	{
		return NULL;
	}
	else
	{
		// ���� �õ��ĵ�ַ��ȡ������ͷ
		struct ListNode *HeaderList = (struct ListNode *)TableHeader[hashPos];
		// ����������������ڷ����˳�ͻ������û�г�ͻ������ֻ��һ������ͷҲ��ֻƥ������ͷ
		for (struct ListNode *CurList = HeaderList; CurList != NULL; CurList = CurList->next)
		{
			if (strcmp(CurList->key, key) == 0)
			{
				char *oldValue = CurList->value;
				CurList->value = newValue;
				return oldValue;
			}
		}
		return NULL;
	}
}
// ��ֵ��������
int insert(char *key, char *value)
{
	// ��ȡhashֵ��������������Ǹ�λ��
	int hashPos = GetHashValue(key);

	// �鿴��ǰ�±��Ƿ���ֵ
	int pos = TableHeader[hashPos];

	// û��ֵ
	if (pos == 0)
	{
		// ��ȡ����ͷ
		struct ListNode *listNodeHeader = InitChain();

		if (listNodeHeader == NULL)
		{
			puts("���ִ����ˣ��ռ䲻��");
			return -1;
		}
		else
		{
			// ����ֵ
			listNodeHeader->next = NULL;
			listNodeHeader->key = key;
			listNodeHeader->value = value;
			// ����ͷ��ַ
			TableHeader[hashPos] = (int)listNodeHeader;
		}
		//printf("��ַ��%d", TableHeader[hashPos]);
	}
	else
	{
		if (query(key) == NULL) {
			// ��ֵ��
			// �����ͷ��ַ
			struct ListNode *HeaderList = (struct ListNode *)TableHeader[hashPos];

			struct ListNode *NewList = (struct ListNode *)malloc(sizeof(struct ListNode));

			NewList->key = key;
			NewList->value = value;
			NewList->next = HeaderList;
			// ����ͷ��ַ
			TableHeader[hashPos] = (int)NewList;
		}
		else {
			update(key, value);
		}
	}

	return 0;
}