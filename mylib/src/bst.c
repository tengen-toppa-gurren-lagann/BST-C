// ���������� ��������� ������ ������ �� ����� ��
//
#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

// ���� ������
typedef struct node {
    int value; // �������� � ����
    struct node *left;  // ��������� �� ������ �������
    struct node *right; // ��������� �� ������� �������
} node;
 
// ������
typedef struct tree {
    node *root; // ������ ������
    int count; // ���������� ����� � ������
} tree;


// �������� ������� ������
tree *createTree(void) {
    tree *new_tree = malloc(sizeof *new_tree);
    if (new_tree == NULL) return NULL; // �� ������� �������� ������
    new_tree->root = NULL;
    new_tree->count = 0;
    return new_tree; // ���������� ��������� �� ������
}

// ��������� ������� ������
// �������: ���������� ����� � ������
extern int treeSize(tree *bst) {
    return bst->count;
}

// ��������� �������� �� ����
// �������: �������� � ����
extern int nodeValue(node *n) {
    return n->value;
}

 
// �������� ������� � ������ ���� � �������� ���������
// �������: 0 - ������ ���� ���, 1 -  ����� ���� ����
int containsNode(const tree *bst, int value) {
    const node *bst_node = bst->root;
    while(1) {
        if (bst_node == NULL) return 0;
        else if (value == bst_node->value) return 1;
             else if (value > bst_node->value) bst_node = bst_node->right;  
                  else bst_node = bst_node->left;  
    }
}
 
 
// ������� ���� � ������
// �������: 0 - �� ������� �������� ����, 1 - ���� ��������, 2 - ����� ���� ��� ���� � ������
int addNode(tree *bst, int value) {
    node *bst_node = bst->root;
    node **new = &bst->root;

    while(1) {
        if(bst_node == NULL) { // ����� ����� ��� ������� ����
           bst_node = *new = malloc(sizeof *bst_node);
           if(bst_node != NULL) { // ��������� ����
                bst_node->value = value;
                bst_node->left = bst_node->right = NULL;
                bst->count++;
                return 1;
           }
           else return 0; // �� ������� �������� ����
        }

        if (value == bst_node->value) return 2; // ����� ���� ��� ���� � ������

        // ���� ����� ��� ������� ����
        if(value > bst_node->value) { // ���� � ������ ��������� 
            new = &bst_node->right;
            bst_node = bst_node->right;
        }
        else { // ���� � ����� ���������
           new = &bst_node->left;
           bst_node = bst_node->left;
        }
     } // end of while
}
 
 
// �������� ���� �� ������
// �������: 0 - �� ������� ������� ����, 1 - ���� ������
int removeNode(tree *bst, int value) {
    node *delNode = bst->root;  // ��������� �� ��������� ����
    node **aux = &bst->root;// ��������������� ���������

    // ���� ��������� ���� � ������
    while(1) {
        if (delNode == NULL) return 0; // �� ����� ��������� ����
        else if (value == delNode->value) break; // ����� ��������� ���� - ������� �� ����� ������
             else if (value > delNode->value) {
                       aux = &delNode->right;
                       delNode = delNode->right;
                  }
                  else {
                       aux = &delNode->left;
                       delNode = delNode->left;
                  }
    }        
     
     // ������� ����
    if (delNode->right == NULL) { // � ���������� ���� ��� ������� ������
        *aux = delNode->left;
    }
    else { // � ���������� ���� ���� ������� ������
        node *y = delNode->right; // ������� ������
        if (y->left == NULL) { // � ������� ������� ���������� ���� ��� ����� �����
            y->left = delNode->left; 
            *aux=y;
        }
        else { // � ������� ������� ���������� ���� ���� ����� ���������
            node *x = y->left;
            while(x->left != NULL) { // ���� �� ������ ��������� �� �����
                y = x;
                x = y->left;
            }
            // ��������� ����
            y->left = x->right;
            x->left = delNode->left;
            x->right = delNode->right;
            *aux=x;
        }
    }
    bst->count--; // ������� ���� - ��������� ���������� ����� � ������
    free(delNode); // ����������� ������
    return 1;
}

static void fprintNode(node *curNode, FILE *f) {
    fprintf(f, "%d", curNode->value);
    if (curNode->left != NULL) {
        fprintf(f, "-");
        fprintf(f, "%d(L)", curNode->left->value);
        if (curNode->right != NULL) fprintf(f, ",%d(R)", curNode->right->value);
    }
    else if (curNode->right != NULL) {
             fprintf(f, "-");
             fprintf(f, "%d(R)", curNode->right->value);
         }
    fprintf(f, "\n");
}

// ������ ����� ������ � ������� ���������� � �������� ����
static void preorder(node *root, FILE *f) {
    if (root == NULL) return;
    fprintNode(root, f);
    preorder(root->left, f);
    preorder(root->right, f);
}

// �������� ����� ������ � ������� ���������� � �������� ����
static void postorder(node *root, FILE *f) {
    if (root == NULL) return;
    postorder(root->left, f);
    postorder(root->right, f);
    fprintNode(root, f);
}
 
// �������������� ����� ������ � ������� ���������� � �������� ����
static void inorder(node *root, FILE *f) {
    if (root == NULL) return;
    inorder(root->left, f);
    fprintNode(root, f);
    inorder(root->right, f);
}

// ����� ������ � �������� ������� � ������� ����� � �������� ����
void traverseTree(tree *bst, FILE *f, int order) {
    switch(order) {
        case PREORDER:
            preorder(bst->root, f);
            break;
        case POSTORDER:
            postorder(bst->root, f);
            break;
        case INORDER:
            inorder(bst->root, f);
    }
}


// ������������ ������, ������� ����� � ��� ���������
static void destroySubtree(node *bst_node) {
    if(bst_node == NULL) return;
    destroySubtree(bst_node->left);
    destroySubtree(bst_node->right);
    free(bst_node);
} 
 
 
// ������������ ������, ������� �������
void destroyTree(tree *bst) {
    destroySubtree(bst->root);
    free(bst);
}
 
// ����� ������������ ���� � ������
node *minNode(tree *bst) {
    node *bst_node = bst->root;
    while (bst_node->left != NULL) bst_node = bst_node->left;
    return bst_node;
}
 
// ����� ������������� ���� � ������
node *maxNode(tree *bst) {
    node *bst_node = bst->root;
    while (bst_node->right != NULL) bst_node = bst_node->right;
    return bst_node;
}
