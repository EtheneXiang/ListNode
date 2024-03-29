// ListNode.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <vector>

using namespace std;

/* 创建一个单链表 */
struct ListNode 
{
	int val;
	struct ListNode *next;
	ListNode(int x) :val(x), next(NULL) 
	{
	}
	ListNode() :val(0), next(NULL)
	{
	}
};/*链表打印*/

/*打印链表*/
void ListNode_print(ListNode *pHead)
{
	if (pHead == NULL) { printf("链表空\r\n"); return; }
	else cout << "链表如下：" << endl;
	while (pHead != NULL)
	{
		cout << pHead->val << "  ";
		pHead = pHead->next;
	}
	cout << endl;
}

/*生成指定长度链表*/
ListNode* ListNode_gen(int length)
{
	if (length < 0) { cout << "长度非法" << endl; exit(EXIT_FAILURE);}
	else cout << "链表生成Ing。。。长度为 " <<length<< endl;
	ListNode* cur = new ListNode, *res = cur;//res用于保存头指针，cur一直在移动，最后指向了末尾。
	// *tmp = new ListNode 为每个节点开辟空间//如果放在循环体外面，即使value一直在变，但是一直是一片内存，导致死循环。
	//必须放在循环体内部，开辟内存，这样每个节点都是用的不同内存区域。
	while (length)
	{
		ListNode *tmp = new ListNode;
		tmp->val = length/3;
		tmp->next = NULL;
		cur ->next = tmp;
		cur = cur->next;
		length--;
	}
	ListNode_print(res->next);
	return res->next;
}

/*删除链表*/
void ListNode_delete(ListNode *pHead)
{
	ListNode *tmp = pHead->next;
	ListNode *head = pHead;
	while (pHead != NULL)
	{
		tmp = pHead->next;
		delete pHead;
		pHead = tmp;
	}
	delete pHead;
	ListNode_print(head);
}

/*获取链表长度*/
int ListNode_length(ListNode *pHead)
{
	int length = 0;
	while (pHead != NULL)
	{
		pHead = pHead->next;
		length++;
	}
	return length;
}

//在指定位置插入元素
ListNode* ListNode_insert(ListNode *pHead, int value,int loc)
{
	ListNode *res = pHead;
	ListNode *tmp = new ListNode;
	int length = ListNode_length(pHead);

	if (pHead == NULL)
	{
		printf("链表空\r\n");
		pHead->val = value;
		pHead->next = NULL;
		return pHead;
	}
	else if (loc < 1 || loc>length+1) //loc==1 时插入表头,loc==length+1时，插入表尾
	{ 
		cout << "非法位置" << endl;
		cout << "你的输入是 " << loc << "    链表长度是" << length << endl;
		exit(EXIT_FAILURE);
	}
	else if (loc == 1)
	{
		tmp->next = pHead;
		tmp->val = value;
		pHead = tmp;
		ListNode_print(pHead);
		return pHead;
	}
	else ListNode_print(pHead);

	while (pHead->next !=NULL && loc>2)
	{
		loc--;
		pHead = pHead->next;//Loc次移动		
	}
	if(pHead->next!=NULL)
	{
		tmp->val = value;
		tmp->next = pHead->next;
		pHead->next = tmp;
	}
	else //添加尾节点
	{
		tmp->val = value;
		tmp->next = NULL;
		pHead->next = tmp;
	}
	ListNode_print(res);
	return res;

}

/*删除指定位置元素*/
ListNode* ListNode_delete(ListNode *pHead, int loc)
{
	int length = ListNode_length(pHead);
	ListNode *res = pHead;
	ListNode *tmp = new ListNode;
	if (pHead == NULL)
	{
		printf("链表空\r\n");
		return pHead;
	}
	else if (loc <=0 || loc>length) { cout << "非法位置" << endl; exit(EXIT_FAILURE); }
	else if (loc == 1) //删除首节点
	{
		tmp = pHead->next;
		delete pHead;
		ListNode_print(tmp);
		return tmp;
	}
	else ListNode_print(pHead);

	while (pHead->next != NULL && loc>2)
	{		
		loc--;
		pHead = pHead->next;//Loc次移动	

	}
	if (pHead->next != NULL) //链表长度大于loc
	{
		tmp = pHead->next->next;
		//pHead->next = NULL;
		//ListNode* del_tmp = pHead->next;
		delete pHead->next;//释放下个节点的内存
		pHead->next = tmp; //给当前节点的Next赋值
	}

	ListNode_print(res);
	return res;
}

/*查询某个元素,返回首次出现的位置*/
int ListNode_query(ListNode *pHead, int value)
{
	int loc = 0;
	if (pHead == NULL) { cout << "链表为空" << endl; return false; }
	else if (pHead->next == NULL) return pHead->val == value ? 1 : -1;
	while (pHead != NULL)
	{
		loc++;
		if (pHead->val == value) return loc;
		else pHead = pHead->next;
	}
	return -1;
}

/*查询指定位置的元素,返回位置上的数值*/
int ListNode_oneout(ListNode *pHead, int loc)
{
	int length = ListNode_length(pHead);
	if (pHead == NULL) { cout << "链表为空" << endl; exit(EXIT_FAILURE);}
	else if (loc <= 0 || loc>length) { cout << "非法位置" << endl; exit(EXIT_FAILURE); }
	while (--loc)
	{
		 pHead = pHead->next;
	}
	return pHead->val;
}

/*逆序(不使用栈)*/
ListNode* ListNode_inverse_m1(ListNode *pHead)
{
	int length = ListNode_length(pHead);
	if (pHead == NULL) { cout << "链表为空" << endl; return pHead; }
	else if(pHead->next==NULL) { return pHead; }

	ListNode *pre=NULL, *tmp=pHead->next;
	while (pHead != NULL)
	{
		tmp = pHead->next;
		pHead ->next = pre;
		pre = pHead;
		pHead = tmp;
	}
	ListNode_print(pre);
	return pre;
}

void test_(ListNode *pHead)
{
	ListNode *res = pHead, *tmp = new ListNode;
	tmp = pHead->next;
	delete pHead;//只是删除指针所指向的内存空间，指针本身还在，可以继续赋值
	pHead = tmp;//
	ListNode_print(res);//pHead和res指向的同一片内存区，delete掉这片内存区后，两个指针就指向无效区域了，需要重新赋值，现在只给pHead赋值了，res依然指向无效区域，所以输出的时候有问题。

}
ListNode* delete_duplication_node(ListNode *pHead)//删除重复节点
{
	if (pHead == NULL || pHead->next == NULL) return pHead;
	ListNode *post = pHead;//记录尾指针

	ListNode *new_list = new ListNode(pHead->val+1);//记录首指针
	ListNode *new_phead = new_list;
	new_list->next = pHead; //将原链表加长

	ListNode *tmp;

	int flag = pHead->val + 1;
	while (post!=nullptr && post->next!= nullptr)
	{
		//ListNode_print(pHead);
		
		if (post->val == post->next->val)
		{
			flag = post->val;
			tmp = post->next->next;
			post = tmp;
			delete new_list->next->next;
			delete new_list->next;
			new_list->next = tmp;
		}
		else if (post->val == flag) //如果连续三个数一样
		{
			flag = new_phead->val;
			tmp = post->next;
			post = post->next;
			delete new_list->next;
			new_list->next = tmp;
		}
		else //不相等
		{
			new_list = new_list->next;
			post = post->next;
		}
		ListNode_print(new_list);
	}
	//经过while循环后，要么剩一个数，要么剩0个数
	//剩一个数，就要考虑这个数是够和之前的数一样
	if (post == NULL) ;
	else if (post->val == flag) //如果连续三个数一样
	{
		flag = new_phead->val;
		tmp = post->next;
		post = post->next;
		delete new_list->next;
		new_list->next = tmp;
	}

	if (new_phead->next == nullptr) cout << "链表元素全一样" << endl;
	else ListNode_print(new_phead->next);
	tmp=new_phead->next;
	delete new_phead;//new_phead指向的是new来的那片内存区域，通过delete new_phead，就可以删除这片内存。
	return tmp;
}


int main()
{
	//ListNode_insert(ListNode_gen(19), 100,18);
	//ListNode_delete(ListNode_gen(19),19);
	//cout << ListNode_query(ListNode_gen(19), 10) << endl;
	//cout << ListNode_oneout(ListNode_gen(1129), 20) << endl;
	ListNode_inverse_m1(ListNode_gen(119));
	//ListNode_delete(ListNode_gen(10));
	//test_(ListNode_gen(10));
	//ListNode_print(delete_duplication_node(ListNode_gen(6)));


    return 0;
}

