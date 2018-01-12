
#include "stdafx.h"

int *TableHeader = NULL; // 表头,数组

// 初始化 链表
struct ListNode *InitChain()
{
	struct ListNode *listNodeHeader = NULL;
	// 创建 列表头
	if (listNodeHeader == NULL)
	{
		// 文件头
		listNodeHeader = (struct ListNode *)malloc(sizeof(struct ListNode));
		if (listNodeHeader == NULL)
		{
			puts("no spaces");
			return NULL;
		}
	}
	return listNodeHeader;
}

// 初始化散列表
int *InitHashTable()
{
	// 初始化 表头,
	TableHeader = (int *)calloc(TableSize * sizeof(int), 1);
	// 初始化 链表
	// InitChain();
	return TableHeader;
}

// 创建散列表
int HashTable()
{
	// 初始化散列表
	InitHashTable();

	return 0;
}

// 获取哈希值
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

// 根据键查值
char *query(char *key)
{
	int hashPos = GetHashValue(key); // 获取键的hash值

									 // 查找 这个 数组的当前下标有没有保存的地址值
	int pos = TableHeader[hashPos];

	// 没有找到
	if (pos == 0)
	{
		return NULL;
	}
	else
	{
		// 根据 得到的地址获取到链表头
		struct ListNode *HeaderList = (struct ListNode *)TableHeader[hashPos];
		// 遍历链表，这个是由于发生了冲突。即便没有冲突，而且只有一个链表头也会只匹配链表头
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
// 查询
void queryAll()
{
	for (int hashPos = 0; hashPos < TableSize; hashPos++)
	{
		printf("索引:%d:  ", hashPos);
		struct ListNode *HeaderList = (struct ListNode *)TableHeader[hashPos];
		for (struct ListNode *CurList = HeaderList; CurList != NULL; CurList = CurList->next)
		{
			printf("地址:%d,键:%s = %s\t", (int)TableHeader[hashPos], CurList->key, CurList->value);
		}
		printf("\n");
	}
}

// 删除这个键值对
char * deleteKey(char *key)
{
	// 获取hash值，存放在数组中那个位置
	int hashPos = GetHashValue(key);

	// 查看当前下标是否有值
	int pos = TableHeader[hashPos];

	// 没有值
	if (pos == 0)
	{
		return NULL;
	}
	else
	{
		// 根据 得到的地址获取到链表头
		struct ListNode *HeaderList = (struct ListNode *)TableHeader[hashPos];

		// 删除的和其他的不一样，先匹配链表头
		// 链表头为NULL，返回NULL
		if (HeaderList == NULL)
		{
			return NULL;
		}
		else
		{
			// 匹配当前的值，如果有，判断值是否相同
			if (strcmp(HeaderList->key, key) == 0)
			{
				TableHeader[hashPos] = (int)HeaderList->next;
				return HeaderList->value;
			}
			else
			{
				//如果只有链表头
				if (HeaderList->next == NULL)
				{
					return NULL;
				}
				else
				{
					struct ListNode *CurList = HeaderList;
					// 头查完了 开始往后找
					for (; CurList->next != NULL; CurList = CurList->next)
					{
						if (strcmp(CurList->next->key, key) == 0)
						{
							char * value = CurList->next->value;
							CurList->next = CurList->next->next;
							return value;
						}
					}

					// 中间也没有找见，开始找尾部
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
// 更新
char* update(char *key, char *newValue)
{
	int hashPos = GetHashValue(key); // 获取键的hash值

									 // 查找 这个 数组的当前下标有没有保存的地址值
	int pos = TableHeader[hashPos];

	// 没有找到
	if (pos == 0)
	{
		return NULL;
	}
	else
	{
		// 根据 得到的地址获取到链表头
		struct ListNode *HeaderList = (struct ListNode *)TableHeader[hashPos];
		// 遍历链表，这个是由于发生了冲突。即便没有冲突，而且只有一个链表头也会只匹配链表头
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
// 将值放入数组
int insert(char *key, char *value)
{
	// 获取hash值，存放在数组中那个位置
	int hashPos = GetHashValue(key);

	// 查看当前下标是否有值
	int pos = TableHeader[hashPos];

	// 没有值
	if (pos == 0)
	{
		// 获取链表头
		struct ListNode *listNodeHeader = InitChain();

		if (listNodeHeader == NULL)
		{
			puts("出现错误了，空间不足");
			return -1;
		}
		else
		{
			// 保存值
			listNodeHeader->next = NULL;
			listNodeHeader->key = key;
			listNodeHeader->value = value;
			// 保存头地址
			TableHeader[hashPos] = (int)listNodeHeader;
		}
		//printf("地址：%d", TableHeader[hashPos]);
	}
	else
	{
		if (query(key) == NULL) {
			// 有值了
			// 保存表头地址
			struct ListNode *HeaderList = (struct ListNode *)TableHeader[hashPos];

			struct ListNode *NewList = (struct ListNode *)malloc(sizeof(struct ListNode));

			NewList->key = key;
			NewList->value = value;
			NewList->next = HeaderList;
			// 保存头地址
			TableHeader[hashPos] = (int)NewList;
		}
		else {
			update(key, value);
		}
	}

	return 0;
}