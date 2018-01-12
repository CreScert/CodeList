// testString.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


int main()
{
	LinearProbing<int,char *> lp;
	
	lp.flag = LINEARPROBOING;
	lp.insert(89,"a");
	lp.insert(18,"b");
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
	system("pause");
	return 0;
}