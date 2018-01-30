// testString.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

void testProbing()
{
	LinearProbing<int, char *> lp;

	lp.flag = LINEARPROBOING;
	lp.insert(89, "a");
	lp.insert(18, "b");
	lp.insert(49, "c");
	lp.insert(58, "d");

	lp.insert(69, "e");


	//	cout<<"491的值为："<<linearProbing.queryKey(58)<<endl;
	lp.update(58, "444");
	lp.queryAll();
	cout << endl;
	cout << endl;
	lp.deleteKey(58);
	lp.queryAll();
	lp.insert(58, "d");
	cout << endl;
	cout << endl;
	lp.queryAll();
}

void testTree() 
{
	int arr[] = { 1,23,32,5,9,2,46,11,258,632,45 };
	int length = sizeof(arr) / sizeof(arr[0]);
	for (int i = 0; i < length; i++)
	{
		AddTree(arr[i]);
	}
	TREE * head = GetTreeHead();
}
int main()
{
	LinearProbing<char*, int> lp;


	lp.flag = LINEARPROBOING;
	lp.insert("aa",10);
	lp.insert("aaf", 130);
	lp.insert("sdfsdf", 1330);
	lp.insert("fffdf", 1430);
	lp.insert("sdfsdfsdfsd", 1350);
	lp.insert("sdfsdfsdddfsd", 1340);
	lp.insert("ada", 1360);
	lp.insert("ffe", 1370);
	lp.insert("faffdf", 14307);
	lp.insert("ssdfsdfsdfsd", 1358);
	lp.insert("sddfsdfsdddfsd", 1349);
	lp.insert("afda", 1361);
	lp.insert("fgffdf", 1432);
	lp.insert("sdfhsdfsdfsd", 1356);
	lp.insert("sdfjsdfsdddfsd", 1343);
	lp.insert("ajjda", 1367);
	cout << lp.queryKey("ada");
	lp.queryAll();

	system("pause");
	return 0;
}