#pragma once

// 链地址法 / 拉链法
// 拉链法又叫链地址法，适合处理冲突比较严重的情况。基本思想是把所有关键字为同义词的记录存储在同一个线性链表中。



// 链表
struct ListNode {
	char *key;// 键值对
	char *value;
	struct ListNode *next;
};

const int TableSize = 15; // 表大小



const int MOD = 13; // 这个数字推荐是素数


// 初始化 链表
struct ListNode *InitChain();
// 初始化散列表
int *InitHashTable();
// 创建散列表
int HashTable();

// 获取哈希值
int GetHashValue(char*key);

// 根据键查值
char *query(char *key);

// 查询
void queryAll();


// 删除这个键值对
char * deleteKey(char *key);

//更新
char* update(char *key, char *newValue);

// 将值放入数组
int insert(char *key, char *value);