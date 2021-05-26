// Реализация двоичного дерева поиска на языке Си
//
#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

// Узел дерева
typedef struct node {
    int value; // Значение в узле
    struct node *left;  // Указатель на левого потомка
    struct node *right; // Указатель на правого потомка
} node;
 
// Дерево
typedef struct tree {
    node *root; // Корень дерева
    int count; // Количество узлов в дереве
} tree;


// Создание пустого дерева
tree *createTree(void) {
    tree *new_tree = malloc(sizeof *new_tree);
    if (new_tree == NULL) return NULL; // Не удалось выделить память
    new_tree->root = NULL;
    new_tree->count = 0;
    return new_tree; // Возвращаем указатель на дерево
}

// Получение размера дерева
// Возврат: количество узлов в дереве
extern int treeSize(tree *bst) {
    return bst->count;
}

// Получение значения из узла
// Возврат: Значение в узле
extern int nodeValue(node *n) {
    return n->value;
}

 
// Проверка наличия в дереве узла с заданным значением
// Возврат: 0 - такого узла нет, 1 -  такой узел есть
int containsNode(const tree *bst, int value) {
    const node *bst_node = bst->root;
    while(1) {
        if (bst_node == NULL) return 0;
        else if (value == bst_node->value) return 1;
             else if (value > bst_node->value) bst_node = bst_node->right;  
                  else bst_node = bst_node->left;  
    }
}
 
 
// Вставка узла в дерево
// Возврат: 0 - не удалось вставить узел, 1 - узел вставлен, 2 - такой узел уже есть в дереве
int addNode(tree *bst, int value) {
    node *bst_node = bst->root;
    node **new = &bst->root;

    while(1) {
        if(bst_node == NULL) { // Нашли место для вставки узла
           bst_node = *new = malloc(sizeof *bst_node);
           if(bst_node != NULL) { // Вставляем узел
                bst_node->value = value;
                bst_node->left = bst_node->right = NULL;
                bst->count++;
                return 1;
           }
           else return 0; // Не удалось добавить узел
        }

        if (value == bst_node->value) return 2; // Такой узел уже есть в дереве

        // Ищем место для вставки узла
        if(value > bst_node->value) { // Идем в правое поддерево 
            new = &bst_node->right;
            bst_node = bst_node->right;
        }
        else { // Идем в левое поддерево
           new = &bst_node->left;
           bst_node = bst_node->left;
        }
     } // end of while
}
 
 
// Удаление узла из дерева
// Возврат: 0 - не удалось удалить узел, 1 - узел удален
int removeNode(tree *bst, int value) {
    node *delNode = bst->root;  // Указатель на удаляемый узел
    node **aux = &bst->root;// Вспомогательный указатель

    // Ищем удаляемый узел в дереве
    while(1) {
        if (delNode == NULL) return 0; // Не нашли удаляемый узел
        else if (value == delNode->value) break; // Нашли удаляемый узел - выходим из цикла поиска
             else if (value > delNode->value) {
                       aux = &delNode->right;
                       delNode = delNode->right;
                  }
                  else {
                       aux = &delNode->left;
                       delNode = delNode->left;
                  }
    }        
     
     // Удаляем узел
    if (delNode->right == NULL) { // У удаляемого узла нет потомка справа
        *aux = delNode->left;
    }
    else { // У удаляемого узла есть потомок справа
        node *y = delNode->right; // Потомок справа
        if (y->left == NULL) { // У правого потомка удаляемого узла нет детей слева
            y->left = delNode->left; 
            *aux=y;
        }
        else { // У правого потомка удаляемого узла есть левое поддерево
            node *x = y->left;
            while(x->left != NULL) { // Идем по левому поддереву до конца
                y = x;
                x = y->left;
            }
            // Переносим узлы
            y->left = x->right;
            x->left = delNode->left;
            x->right = delNode->right;
            *aux=x;
        }
    }
    bst->count--; // Удалили узел - уменьшаем количество узлов в дереве
    free(delNode); // Освобождаем память
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

// Прямой обход дерева с выводом результата в заданный файл
static void preorder(node *root, FILE *f) {
    if (root == NULL) return;
    fprintNode(root, f);
    preorder(root->left, f);
    preorder(root->right, f);
}

// Обратный обход дерева с выводом результата в заданный файл
static void postorder(node *root, FILE *f) {
    if (root == NULL) return;
    postorder(root->left, f);
    postorder(root->right, f);
    fprintNode(root, f);
}
 
// Центрированный обход дерева с выводом результата в заданный файл
static void inorder(node *root, FILE *f) {
    if (root == NULL) return;
    inorder(root->left, f);
    fprintNode(root, f);
    inorder(root->right, f);
}

// Обход дерева в заданном порядке с выводом узлов в заданный файл
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


// Освобождение памяти, занятой узлом и его потомками
static void destroySubtree(node *bst_node) {
    if(bst_node == NULL) return;
    destroySubtree(bst_node->left);
    destroySubtree(bst_node->right);
    free(bst_node);
} 
 
 
// Освобождение памяти, занятой деревом
void destroyTree(tree *bst) {
    destroySubtree(bst->root);
    free(bst);
}
 
// Поиск минимального узла в дереве
node *minNode(tree *bst) {
    node *bst_node = bst->root;
    while (bst_node->left != NULL) bst_node = bst_node->left;
    return bst_node;
}
 
// Поиск максимального узла в дереве
node *maxNode(tree *bst) {
    node *bst_node = bst->root;
    while (bst_node->right != NULL) bst_node = bst_node->right;
    return bst_node;
}
