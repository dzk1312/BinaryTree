#include<iostream>
#include<stdio.h>
#include<stack>
#include <queue>
#include<stdlib.h>
using namespace std;

typedef char ElemType;
#define END '#'
template<typename T>
const T &Max(const T &a, const T &b)
{
	return a > b ? a : b;
}
typedef struct BtNode
{
	//	BtNode *parent;
	BtNode *leftchild;
	BtNode *rightchild;
	ElemType data;
}BtNode, *BinaryTree;

BtNode * _Buynode()
{
	BtNode *s = (BtNode *)malloc(sizeof(BtNode));
	if (NULL == s) exit(1);
	memset(s, 0, sizeof(BtNode));
	return s;
}
void _Freenode(BtNode *p)
{
	free(p);
}

void PreOrder(BtNode *p)
{
	if (p != NULL)
	{
		cout << p->data << " ";
		PreOrder(p->leftchild);
		PreOrder(p->rightchild);
	}
}
void InOrder(BtNode *p)
{
	if (p != NULL)
	{
		InOrder(p->leftchild);
		cout << p->data << " ";
		InOrder(p->rightchild);
	}
}

void PastOrder(BtNode *p)
{
	if (p != NULL)
	{
		PastOrder(p->leftchild);
		PastOrder(p->rightchild);
		cout << p->data << " ";
	}
}

BtNode * CreateTree1()
{
	ElemType x;
	cin >> x;
	BtNode *s = NULL;
	if (x != END)
	{
		s = _Buynode();
		s->data = x;
		s->leftchild = CreateTree1();
		s->rightchild = CreateTree1();
	}
	return s;
}

int Size(BtNode *ptr)
{
	if (ptr == NULL)
	{
		return 0;
	}
	else
		return (Size(ptr->leftchild) + Size(ptr->rightchild)+1);
}
int Depth(BtNode *ptr)
{
	if (ptr == NULL)
	{
		return 0;
	}
	else
		//return ((Depth(ptr->leftchild) > Depth(ptr->rightchild)) ? Depth(ptr->leftchild) : Depth(ptr->rightchild)+1);
		return Max(Depth(ptr->leftchild), Depth(ptr->rightchild))+1;
}
BtNode * FindValue(BtNode *ptr, ElemType x)
{
	if (ptr == NULL || ptr->data == x) return ptr;
	else
	{
		BtNode *p = FindValue(ptr->leftchild, x);
		if (NULL == p)
		{
			p = FindValue(ptr->rightchild, x);
		}
		return p;
	}
}

int IndexIs(ElemType *is, ElemType x, int n)
{
	for (int i = 0; i < n; ++i)
	{
		if (is[i] == x) return i;
	}
	return -1;
}
BtNode * CreatePI(ElemType *ps, ElemType *is, int n)
{
	BtNode *s = NULL;
	if (n > 0)
	{
		s = _Buynode();
		s->data = ps[0];
		int pos = IndexIs(is, ps[0], n);
		if (pos == -1) exit(1);
		s->leftchild = CreatePI(ps + 1, is, pos);
		s->rightchild = CreatePI(ps + pos + 1, is + pos + 1, n - pos - 1);
	}
	return s;
}
BtNode * CreateTreePI(ElemType *ps, ElemType *is, int n)
{
	if (ps == NULL || is == NULL || n < 1)
		return NULL;
	else
		return CreatePI(ps, is, n);
}
BtNode * CreateIL(ElemType *is, ElemType *ls, int n)
{
	BtNode *s = NULL;
	if (n > 0)
	{
		s = _Buynode();
		s->data = ls[n - 1];
		int pos = IndexIs(is, ls[n - 1], n);
		if (pos == -1) exit(1);
		s->leftchild = CreateIL(is, ls, pos);
		s->rightchild = CreateIL(is + pos + 1, ls + pos, n - pos - 1);
	}
	return s;
}
BtNode * CreateTreeIL(ElemType *is, ElemType *ls, int n)
{
	if (is == NULL || ls == NULL || n < 1)
		return NULL;
	else
		return CreateIL(is, ls, n);
}
void CreateTree2(BtNode *ptr)
{

}
void CreateTree3(BtNode **const ptr)
{
	ElemType x;
	cin >> x;
	if (x == END)
		*ptr = NULL;
	else
	{
		(*ptr) = _Buynode();
		(*ptr)->data = x;
		CreateTree3(&(*ptr)->leftchild);
		CreateTree3(&(*ptr)->rightchild);
	}
}
BtNode * CreateTree4(ElemType *&str)
{
	BtNode * s = NULL;
	if (str != NULL && *str != END)
	{
		s = _Buynode();
		s->data = *str;
		s->leftchild = CreateTree4(++str);
		s->rightchild = CreateTree4(++str);
	}
	return s;
}
BtNode * CreateTree5(ElemType ** const str)
{
	BtNode * s = NULL;
	if (*str != NULL && **str != END)
	{
		s = _Buynode();
		s->data = *(*str);
		s->leftchild = CreateTree5(&(++(*str)));
		s->rightchild = CreateTree5(&(++(*str)));
	}
	return s;
}

int FindIndex(ElemType pi, ElemType *is, int n)
{
	for (int i = 0; i < n; ++i)
	{
		if (is[i] == pi)
		{
			return i;
		}
	}
	return -1;
}
BtNode * CreateTreePI(ElemType *pi, ElemType *is, int n)
{
	BtNode *s = NULL;
	if (n > 0)
	{
		s = _Buynode();
		s->data = pi[0];
		int index = FindIndex(pi[0], is, n);
		if (index == -1) exit(1);

		CreateTreePI(pi + 1, is, index);
		CreateTreePI(pi+index+1, is + index+1, n - index - 1);
	}
	return s;
}

BtNode *Find_Parent(BtNode *ptr, BtNode *child);
BtNode *FindParent(BtNode *ptr, BtNode *child)
{
	if (ptr == NULL||ptr==child||child==NULL)
	{
		return NULL;
	}
	return Find_Parent(ptr, child);
	
}
BtNode *Find_Parent(BtNode *ptr, BtNode *child)
{
	if (ptr->leftchild == child || ptr->rightchild == child||ptr==NULL)
	{
		return ptr;
	}
	else
	{
		ptr = FindParent(ptr->leftchild, child);
		if (ptr == NULL)
		{
			ptr = FindParent(ptr->rightchild, child);
		}
		return ptr;
	}
}
bool Is_Full_BinaryTree(BtNode *ptr)
{
	if (ptr == NULL)
	{
		return true;
	}
	else if(ptr->leftchild==NULL&&ptr->rightchild==NULL)
	{
		return true;
	}
	else if(ptr->leftchild!=NULL&&ptr->rightchild!=NULL)
	{
		return Is_Full_BinaryTree(ptr->leftchild) &&Is_Full_BinaryTree(ptr->rightchild)&&Depth(ptr->leftchild) == Depth(ptr->rightchild);
	}
	else
	{
		return false;
	}
}
bool Is_Full_BinaryTree2(BtNode *ptr)
{
	return (Size(ptr->leftchild) == Size(ptr->rightchild)) && Is_Full_BinaryTree(ptr->leftchild) && Is_Full_BinaryTree(ptr->rightchild);
}
//bool IsCompBinaryTree(BtNode *ptr)
//{
//	if (ptr == NULL)
//		return;
//	
//}
void NicePreOrder(BtNode *ptr)
{
	//static int local_int = 3;
	if (ptr == NULL) return;
	stack<BtNode *> st;
	st.push(ptr);
	while (!st.empty())
	{
		ptr = st.top();
		st.pop();
		cout << ptr->data << " ";
		if (ptr->rightchild != NULL)
		{
			st.push(ptr->rightchild);
		}
		if (ptr->leftchild != NULL)
		{
			st.push(ptr->leftchild);
		}
	}
}
void NiceInOrder(BtNode *ptr)
{
	if (ptr == NULL)return;
	stack<BtNode *> st;
	while (!st.empty()||ptr!=NULL)
	{
		while (ptr != NULL)
		{
			st.push(ptr);
			ptr = ptr->leftchild;
		}
		ptr = st.top();
		st.pop();
		cout << ptr->data << " ";
		ptr = ptr->rightchild;
	}

}
//如果先入栈的话，中序遍历       
//事实证明这种做法做不出来
//void NiceInOrder2(BtNode *ptr)
//{
//	if (ptr == NULL)return;
//	stack<BtNode *> st;
//	st.push(ptr);
//	BtNode *tag = NULL;
//	while (!st.empty())
//	{
//		while (ptr != NULL && (ptr->leftchild != tag || ptr->leftchild != NULL))
//		{
//			st.push(ptr);
//			ptr = ptr->leftchild;
//			tag = ptr;
//		}
//		ptr = st.top();
//		st.pop();
//		cout << ptr->data << " ";
//		if (ptr->rightchild != NULL)
//		{
//			ptr = ptr->rightchild;
//		}
//	}
//}
void NicePastOrder(BtNode *ptr)
{
	if (ptr == NULL)return;
	stack<BtNode *> st;
	BtNode *tag = NULL;
	while (!st.empty() || ptr != NULL)
	{
		while (ptr != NULL)
		{
			st.push(ptr);
			ptr = ptr->leftchild;
		}
		ptr = st.top();
		st.pop();
		if (ptr->rightchild != NULL&&ptr->rightchild != tag)
		{
				 st.push(ptr);
				ptr = ptr->rightchild;
		}
		else 
		{
			cout << ptr->data << " ";
			tag = ptr;
			ptr=NULL;
		}
	}
}

struct StkNode
{
	BtNode *pnode;
	int popnum;
public:
	StkNode(BtNode *p = NULL) :pnode(p), popnum(0) {}
};
//void StkInOrder(BtNode *ptr)
//{
//	if (ptr == NULL) return;
//	stack<StkNode> st;
//	st.push(StkNode(ptr));
//	while (!st.empty())
//	{
//		StkNode node = st.top();
//		st.pop();
//		if (++node.popnum == 2)
//		{
//			cout << node.pnode->data << " ";
//			if (node.pnode->rightchild != NULL)
//			{
//				st.push(StkNode(node.pnode->rightchild));
//			}
//		}
//		else if(++node.popnum==1)
//		{
//			st.push(StkNode(node.pnode->leftchild));
//			
//		}
//	}
//}
void Print_K_Level_Item(BtNode *ptr,int k)
{
	if (ptr == NULL || k<0 || k>Depth(ptr))
	{
		return;
	}
	if (k == 0&&ptr!=NULL)
	{
		cout << ptr->data << " ";
	}
	else
	{
		Print_K_Level_Item(ptr->leftchild, k - 1);
		Print_K_Level_Item(ptr->rightchild, k - 1);
	}
}

void LevelOrder(BtNode *ptr)
{
	if (ptr == NULL) return;
	int n = Depth(ptr);
	for (int i = 0; i < n; ++i)
	{
		Print_K_Level_Item(ptr, i);
	}
	cout << endl;
}

void NiceLevelOrder(BtNode *ptr)
{
	if (ptr == NULL)
	{return;}
	queue<BtNode *>qu;
	qu.push(ptr);
	while (!qu.empty())
	{
		ptr = qu.front();
		qu.pop();
		cout << ptr->data << " ";
		if (ptr->leftchild != NULL)
		{
			qu.push(ptr->leftchild);
		}
		if (ptr->rightchild != NULL)
		{
			qu.push(ptr->rightchild);
		}
	}
	cout << endl;
}
void PrintInOrder(int *arr, int i,int j)
{
	if (arr != NULL&&i < j)
	{
		PrintInOrder(arr, 2 * i + 1, j);
		cout << arr[i] << " ";
		PrintInOrder(arr, 2 * i + 2, j);
	}
}
void NicePrintInOrder(int *arr, int i, int j)
{
	if (arr == NULL||i>j)
		return;
	stack<int> st;
	while (!st.empty()||arr!=NULL&&i<j)
	{
		while (i < j)
		{
			st.push(i);
			i = i * 2 + 1;
		}
		i = st.top();
		st.pop();
		cout << arr[i] << " ";
		i = i * 2 + 2;
	}
	cout << endl;
}
int main()
{
	BinaryTree root = NULL;
	ElemType 
}
//void main()
//{
//	int ar[] = { 31,23,12,66,94,5,17,70,62,49,55,88};
//	int n = sizeof(ar) / sizeof(ar[0]);
//	PrintInOrder(ar, 0, n);
//	cout << endl;
//	NicePrintInOrder(ar, 0, n );
//	//NiceLevelOrder(ptr);
//}
//void main()
//{
//	/*char ps[] = { "ABCDEFGH" };
//	char is[] = { "CBEDFAGH" };
//	char ls[] = { "CEFDBHGA" };
//	int n = sizeof(ps) / sizeof(ps[0]) - 1;
//
//	BinaryTree root = NULL;
//	root = CreateTreeIL(is, ls, n);
//	PreOrder(root);
//	cout << endl;
//	InOrder(root);
//	cout << endl;
//	PastOrder(root);
//	cout << endl;*/
//	char *str = "ABC###D#E#F##";
//	BinaryTree root = NULL;
//	root=CreateTree5(&str);
//	NicePreOrder(root);
//	cout << endl;
//	NiceInOrder(root);
//	cout << endl;
//	NicePastOrder(root);
//	cout << endl;
//	/*BtNode *s = root->leftchild->rightchild;
//	cout << s->data << endl;
//	BtNode *t=FindParent(root, s);
//	cout << t->data << endl;*/
//	
//	cout <<"该树的深度为：" <<Depth(root) << endl;
//	cout << "是否为满二叉树"<<Is_Full_BinaryTree2(root) << endl;
//	//NicePreOrder(root);
//	//NiceInOrder2(root);
//	cout << "打印第K层结点" << endl;
//	Print_K_Level_Item(root,2);
//	cout << endl;
//	cout << "层序遍历" << endl;
//	NiceLevelOrder(root);
//    //StkInOrder(root);
//	/*cout << endl;
//	NicePastOrder(root);*/
//
//
//}