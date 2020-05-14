#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

typedef struct bookData
{
	int bookCod;
	int libNumb;
}Data;

typedef struct tree_node
{
	Data inf;
	struct tree_node* right, * left;
}Node;

int getData();
void AddNode(Node* proot, Node* pnew);
Node* newNode(Data buf);
void PrintTreeDirect(Node* proot);
int findAllbooksinLib(int libnumb);
void ShowTree(Node* proot, int level);
void ShowTreeStructure(void);
int TreeHeight(Node* proot);
void ShowLevels(void);
void treeBalanced(Node* proot);
void freeTree(Node* proot);

Node* root;

int main()
{
	if (!getData())
	{
		return -1;
	}
	PrintTreeDirect(root);
	puts("--------------------------");
	puts("Chek tree balance: ");
	printf("Tree height: %i\n", TreeHeight(root));
	if (TreeHeight(root->left) != TreeHeight(root->right))
		treeBalanced(root);
	else
		printf("Tree is balanced!\n");
	puts("--------------------------");
	int lib_numb;
	printf("Choose library: ");
	scanf("%i", &lib_numb);
	if (!findAllbooksinLib(lib_numb))
	{
		puts("No books in this library!");
	}
	puts("--------------------------");
	ShowTreeStructure();
	freeTree(root);
}

int getData()
{
	FILE* file;
	Data buf;
	Node* nbuf;
	printf("Choose file:\n1. 1.txt\n2. 2.txt\n");
	int fchoose;
	scanf("%i", &fchoose);
	if (fchoose == 1)
		file = fopen("1.txt", "r");
	else if (fchoose == 2)
		file = fopen("2.txt", "r");
	else
	{
		puts("incorrect file");
		return 0;
	}
		if (file == NULL)
	{
		puts("Incorrect file name!");
		return 0;
	}
	while (fscanf_s(file,"%i%i",&buf.bookCod,&buf.libNumb) != EOF)
	{
		nbuf = newNode(buf);
		AddNode(root, nbuf);
	}
	return 1;
}

Node* newNode(Data buf)
{
	Node* nNode;
	nNode = (Node*)malloc(sizeof(Node));
	nNode->inf = buf;
	nNode->left = nNode->right = NULL;
	return nNode;
}

void AddNode(Node* proot, Node* pnew) 
{
    if (root == NULL) {
        root = pnew;                        /* кореневий елемент дерева */
        return;
    }
	int cmp = (proot->inf.bookCod == pnew->inf.bookCod) ? 0 : (proot->inf.bookCod > pnew->inf.bookCod ? 1 : 2);
    if (cmp == 0) {             /* слово вже є */

        free(pnew);   /* витираємо елемент, бо повтори недопустимі */
        return;
    }
    if (cmp == 1)             /* новий вузол треба ввести у ліве піддерево */
        if (proot->left == NULL)               /* можна під’єднати зліва */
            proot->left = pnew;
        else
            AddNode(proot->left, pnew);           /*  шукаємо листок */
    else                   /* новий вузол треба ввести у праве піддерево */
        if (proot->right == NULL)
            proot->right = pnew;      /* під’єднуємо як правий дочірній */
        else
            AddNode(proot->right, pnew);   /* ввести у праве піддерево */
}

void PrintTreeDirect(Node* proot)
{
	if (proot == NULL)
		return;
	printf(" [ Book: %5i - Library: %3i ] \n", proot->inf.bookCod,proot->inf.libNumb);
	PrintTreeDirect(proot->right);
	PrintTreeDirect(proot->left);
}

int findAllbooksinLib(int libnumb)
{
	Node* pt = root, *pnext;
	Node** stak = (Node**)calloc(TreeHeight(root), sizeof(Node*));
	int i = 0;
	int chek = 0;
	while (pt != NULL)
	{
		if (pt->left != NULL)
		{
			pnext = pt->left;
			if (pt->right != NULL)
			{
				stak[++i] = pt->right;
			}
		}
		else
		{
			if (pt->right != NULL)
				pnext = pt->right;
			else
			{
				pnext = stak[i--];
			}
		}
		if (pt->inf.libNumb == libnumb)
		{
			chek = 1;
			printf(" [ Book: %5i - Library: %3i ] \n", pt->inf.bookCod, pt->inf.libNumb);
		}
		pt = pnext;
	}
	free(stak);
	return chek;
}

void ShowTree(Node* proot, int level)
{
	if (proot == NULL) return;
	ShowTree(proot->right, level + 1);
	printf("%*c%i.%i\n", level * 5 + 10, ' ', proot->inf.bookCod,proot->inf.libNumb);  
	ShowTree(proot->left, level + 1); 
}

void ShowLevels(void)
{
	int lev;
	printf(" Level:   ");
	for (lev = 1; lev <= TreeHeight(root); lev++) 
		printf("%-5d", lev);
	printf("\n\n");
}

int TreeHeight(Node* proot)
{
	int lh, rh;
	if (proot == NULL) return 0;
	lh = TreeHeight(proot->left);        
	rh = TreeHeight(proot->right);
	return lh > rh ? lh + 1 : rh + 1;          
}

void ShowTreeStructure(void)
{
	ShowLevels();           
	ShowTree(root, 0);
	puts("\n\n");
}

void treeBalanced(Node* proot)
{
	int rootdif = TreeHeight(proot->left) - TreeHeight(proot->right);
	if (rootdif >= 1)
	{
		printf("Node [%i] is not balanced!\n", proot->inf.bookCod);
		treeBalanced(proot->left);
	}
	else if (rootdif <= -1)
	{
		printf("Node [%i] is not balanced!\n", proot->inf.bookCod);
		treeBalanced(proot->right);
	}
	else
	{
		return;
	}
}

void freeTree(Node* proot)
{
	if (proot == NULL)
		return;
	freeTree(proot->left);
	freeTree(proot->right);
	free(proot);
}