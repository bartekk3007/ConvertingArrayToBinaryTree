#include <stdio.h>
#include <stdlib.h>

struct TreeNode 
{
	int val;
	struct TreeNode* left;
	struct TreeNode* right;
};

void createTree(struct TreeNode** tree, int* arr, int i, int size)
{
	if (i < size)
	{
		struct TreeNode* vertex = (struct TreeNode*) malloc(sizeof(struct TreeNode));
		if (vertex)
		{
			*tree = vertex;
			vertex->val = arr[i];
			createTree(&(*tree)->left, arr, 2 * i + 1, size);
			createTree(&(*tree)->right, arr, 2 * i + 2, size);
		}
	}
	else
	{
		*tree = NULL;
	}
}

struct TreeNode* convertToTree(int* arr, int size)
{
	struct TreeNode* tree = NULL;
	createTree(&tree, arr, 0, size);
	return tree;
}

void freeTree(struct TreeNode* tree)
{
	if (tree->left != NULL)
	{
		freeTree(tree->left);
	}
	if (tree->right != NULL)
	{
		freeTree(tree->right);
	}
	free(tree);
}

void printArray(int* tab, int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("%d ", tab[i]);
	}
	printf("\n");
}

void fillArray(struct TreeNode* tree, int* tab, int i)
{
	if (tree != NULL)
	{
		tab[i] = tree->val;
		fillArray(tree->left, tab, 2 * i + 1);
		fillArray(tree->right, tab, 2 * i + 2);
	}
}

int* convertToArray(struct TreeNode* tree, int *size)
{
	*size = treeSize(tree);
	int* tab = (int*)malloc(sizeof(int) * *size);
	fillArray(tree, tab, 0);
	return tab;
}

struct TreeNode* KthNode(struct TreeNode* tree, int n)
{
	if (n == 0)
	{
		return tree;
	}
	else
	{
		if (n % 2 == 1)
		{
			return KthNode(tree, (n - 1) / 2)->left;
		}
		else
		{
			return KthNode(tree, (n - 1) / 2)->right;
		}
	}
}

int treeSize(struct TreeNode* tree)
{
	if (tree == NULL)
	{
		return 0;
	}
	else
	{
		return treeSize(tree->left) + 1 + treeSize(tree->right);
	}	
}

void swapValues(struct TreeNode* tree, int a, int b)
{
	int temp = KthNode(tree, a)->val;
	KthNode(tree, a)->val = KthNode(tree, b)->val;
	KthNode(tree, b)->val = temp;
}

void swapArray(int* arr, int a, int b)
{
	int temp = arr[a];
	arr[a] = arr[b];
	arr[b] = temp;
}

void heapifyArray(int* arr, int i, int size)
{
	int l = 2 * i + 1;
	int r = 2 * i + 2;

	int largest = i;

	if (l < size && arr[l] > arr[largest])
	{
		largest = l;
	}
	if (r < size && arr[r] > arr[largest])
	{
		largest = r;
	}

	if (largest != i)
	{
		swapArray(arr, i, largest);
		heapifyArray(arr, largest, size);
	}
}

void heapify(struct TreeNode* tree, int i)
{
	int largest = i;

	if (KthNode(tree, i)->left != NULL && KthNode(tree, i)->left->val > KthNode(tree, largest)->val)
	{
		largest = 2 * i + 1;
	}
	if (KthNode(tree, i)->right != NULL && KthNode(tree, i)->right->val > KthNode(tree, largest)->val)
	{
		largest = 2 * i + 2;
	}

	if (largest != i)
	{
		swapValues(tree, i, largest);
		heapify(tree, largest);
	}
}

void sortTree(struct TreeNode* tree)
{
	int size = treeSize(tree);
	int nonLeaf = size / 2 - 1;
	for (int i = nonLeaf; i >= 0; i--)
	{
		heapify(tree, i);
	}
}

int* createSortedArray(int* arr, int size)
{
	struct TreeNode* p = convertToTree(arr, size);
	sortTree(p);
	int i;
	int* tab = (int*)malloc(sizeof(int) * size);
	if (tab)
	{
		for (i = size - 1; i >= 0; i--)
		{
			tab[i] = p->val;
			swapValues(p, 0, i);
			free(KthNode(p, i));
			if (i > 0)
			{
				heapify(p, 0);
			}
		}
		return tab;
	}
	return NULL;
}

void sortArray(int* arr, int size)
{
	struct TreeNode* p = convertToTree(arr, size);
	sortTree(p);
	int i;
	for (i = size - 1; i >= 0; i--)
	{
		arr[i] = p->val;
		swapValues(p, 0, i);
		free(KthNode(p, i));
		if (i > 0)
		{
			heapify(p, 0);
		}
	}
}

void sort(int* arr, int size)
{
	int nonLeaf = size / 2 - 1;
	for (int i = nonLeaf; i >= 0; i--)
	{
		heapifyArray(arr, i, size);
	}
	int i;
	for (i = size - 1; i >= 0; i--)
	{
		swapArray(arr, 0, i);
		heapifyArray(arr, 0, i);
	}
}

int main(void)
{
	int arr[] = { 55, 13, 34, 21, 89, 5, 8, 144 };
	int size = sizeof(arr) / sizeof(*arr);
	struct TreeNode* p = convertToTree(arr, size);

	int v = KthNode(p, 3)->val;
	printf("%d\n", v);

	sortTree(p);

	int s;
	int *a = convertToArray(p, &s);

	printArray(a, s);
	free(a);

	freeTree(p);

	int arr2[] = { 55, 13, 34, 21, 89, 5, 8, 144 };
	int size2 = sizeof(arr2) / sizeof(*arr2);

	int* a2 = createSortedArray(arr2, size2);

	printArray(a2, size2);
	free(a2);
	
	int arr3[] = { 55, 13, 34, 21, 89, 5, 8, 144 };
	int size3 = sizeof(arr3) / sizeof(*arr3);

	sortArray(arr3, size3);

	printArray(arr3, size3);

	int arr4[] = { 55, 13, 34, 21, 89, 5, 8, 3 };
	int size4 = sizeof(arr4) / sizeof(*arr4);

	sort(arr4, size4);
	
	printArray(arr4, size4);

	return 0;
}