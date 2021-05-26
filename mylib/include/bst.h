#ifndef BST_H
#define BST_H

// Реализация двоичного дерева поиска на языке Си
//

// Узел дерева
struct node;
typedef struct node node;
 
// Дерево
struct tree;
typedef struct tree tree;
 
// Создание пустого дерева
// Возврат: указатель на дерево (NULL если дерево не создано)
extern tree *createTree(void);

// Получение размера дерева
// Возврат: количество узлов в дереве
extern int treeSize(tree *bst);
 
// Проверка наличия в дереве узла с заданным значением
// Возврат: 0 - такого узла нет, 1 -  такой узел есть
extern int containsNode(const tree *bst, int value);

// Получение значения из узла
// Возврат: Значение в узле
extern int nodeValue(node *n);
 
// Вставка узла в дерево
// Возврат: 0 - не удалось вставить узел, 1 - узел вставлен, 2 - такой узел уже есть в дереве
extern int addNode(tree *bst, int value);
 
// Удаление узла из дерева
// Возврат: 0 - не удалось удалить узел, 1 - узел удален
extern int removeNode(tree *bst, int value);

// Поиск минимального узла в дереве
// Возврат: указатель на узел с минимальным значением в дереве
extern node *minNode(tree *bst);
 
// Поиск максимального узла в дереве
// Возврат: указатель на узел с максимальным значением в дереве
extern node *maxNode(tree *bst);
 
// Обход дерева с выводом узлов в заданный файл
#define PREORDER  0 // Прямой обход 
#define POSTORDER 1 // Обратный обход
#define INORDER   2 // Центрированный обход
extern void traverseTree(tree *bst, FILE *f, int order);

// Освобождение памяти, занятой деревом
extern void destroyTree(tree *bst);
 

#endif
