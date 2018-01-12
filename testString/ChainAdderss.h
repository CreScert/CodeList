#pragma once

// ����ַ�� / ������
// �������ֽ�����ַ�����ʺϴ����ͻ�Ƚ����ص����������˼���ǰ����йؼ���Ϊͬ��ʵļ�¼�洢��ͬһ�����������С�



// ����
struct ListNode {
	char *key;// ��ֵ��
	char *value;
	struct ListNode *next;
};

const int TableSize = 15; // ���С



const int MOD = 13; // ��������Ƽ�������


// ��ʼ�� ����
struct ListNode *InitChain();
// ��ʼ��ɢ�б�
int *InitHashTable();
// ����ɢ�б�
int HashTable();

// ��ȡ��ϣֵ
int GetHashValue(char*key);

// ���ݼ���ֵ
char *query(char *key);

// ��ѯ
void queryAll();


// ɾ�������ֵ��
char * deleteKey(char *key);

//����
char* update(char *key, char *newValue);

// ��ֵ��������
int insert(char *key, char *value);