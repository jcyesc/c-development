#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
	This program shows how to implement a binary tree. It provides the
	operations, insert, search and traverse the tree (inorder, postorder, preorder).
*/

/* The node contains two pointers, one for the left side and one for the right side.
	This recursive declaration of a node might look chancy, but it's correct. It is
	illegal for a structure to contain an instance of itself but

		struct node *leftptr;

	declares leftptr to be a pointer to a node, not a node itself.
*/
typedef struct node {
	char *data;
	struct node *leftptr;
	struct node *rightptr;
} Node;

typedef struct binarytree {
	Node *root;
} Tree;

/*
	When the structs are created, it's important to initialize the data with
	appropriated values.
*/
Node * createNode(char *data) {
	Node *tnode = (Node *) malloc (sizeof (Node));
	tnode->data = data;
	tnode->leftptr = NULL;
	tnode->rightptr = NULL;

	return tnode;
}

void insert(Tree *tree, char *data) {
	Node *tnode = createNode(data);

	if (tree->root != NULL) {
		// Existing tree.
		Node *tmp = tree->root;
		Node *current;
		int isLeft = 0;
		while (tmp != NULL) {
			current = tmp;
			if (strcmp(tnode->data, tmp->data) < 0) {
				tmp = tmp->leftptr;
				isLeft = 1;
			} else {
				tmp = tmp->rightptr;
				isLeft = 0;
			}
		}

		if (isLeft) {
			current->leftptr = tnode;
		} else {
			current->rightptr = tnode;
		}

	} else {
		// New tree
		tree->root = tnode;
	}
}

void inorder(Node *tnode) {
	if (tnode != NULL) {
		inorder(tnode->leftptr);
		printf("%s ", tnode->data);
		inorder(tnode->rightptr);
	}
}

void inorderTraverse(Tree *tree) {
	printf("------ INORDER ------\n");
	inorder(tree->root);
	printf("\n");
}

void preorder(Node *tnode) {
	if (tnode != NULL) {
		printf("%s ", tnode->data);
		preorder(tnode->leftptr);
		preorder(tnode->rightptr);
	}
}

void preorderTraverse(Tree *tree) {
	printf("------ PREORDER ------\n");
	preorder(tree->root);
	printf("\n");
}

void posorder(Node *tnode) {
	if (tnode != NULL) {
		posorder(tnode->leftptr);
		posorder(tnode->rightptr);
		printf("%s ", tnode->data);
	}
}

void posorderTraverse(Tree *tree) {
	printf("------ POSORDER ------\n");
	posorder(tree->root);
	printf("\n");
}

int depth(Node *root) {
	if (root != NULL) {
		int leftDepth = depth(root->leftptr);
		int rightDepth = depth(root->rightptr);

		int max = leftDepth > rightDepth ? leftDepth : rightDepth;
		return max + 1;
	}

	return 0;
}

int main() {
	char *strings[] = {"now", "is", "the", "time", "for", "all", "good", 
		"men", "to", "come", "to", "the", "aid", "of", "their", "party"};
	int numElements = 16;

	Tree tree;
	tree.root = NULL;

	printf("----------------- Binary Tree -----------------\n");

	int i;
	for (i = 0; i < numElements; i++) {
		printf("Inserting: %s\n", strings[i]);
		insert(&tree, strings[i]);
	}

	printf("\nDepth of the tree: %d\n", depth(tree.root));

	preorderTraverse(&tree);
	inorderTraverse(&tree);
	posorderTraverse(&tree);
}


