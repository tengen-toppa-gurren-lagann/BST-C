#include <stdio.h>
#include <stdlib.h>
#include "mytests.h"
#include "bst.h"

// Тестовая программа, реализующая модульные тесты для функций статической библиотеки двоичного дерева поиска
int main() {
    int result;
	
    // Тест для createTree()
    tree *bst = NULL;
    ASSERT_NULL(bst);
    bst = createTree();
    ASSERT_NOT_NULL(bst);
    int size = treeSize(bst);
    ASSERT_EQUALS(size,0); // Дерево должно быть пустое
   
    // Тесты для addNode(), containsNode() и treeSize()
    const int iMin = 1;  // Зададим минимальный узел
    const int iMax = 101; // Зададим максимальный узел
    const int iStep = 10;// Шаг изменения в цикле
    int cnt = 0;
    printf("Adding nodes to tree:");
    for (int i=iMin; i<=iMax; i+=iStep) { // Добавляем узлы в дерево (от минимального до максимального) и проверяем как они добавились
        result = addNode(bst, i);
        ASSERT_EQUALS(result, 1); // Должен быть добавлен
        cnt++;
        int contains = containsNode(bst, i); // Узел (i) добавили 
        ASSERT_TRUE(contains);               //  - проверим, что он есть в дереве
        contains = containsNode(bst, i+1);   // Узел (i+1) не добавляли
        ASSERT_FALSE(contains);              //  - проверим, что его нет в дереве
        size = treeSize(bst); // Проверим увеличение размера дерева
        ASSERT_EQUALS(size,cnt);
        printf("\n");
        traverseTree(bst, stdout, INORDER); // Посмотрим на изменение дерева
    }
	
    // Тест для addNode() - попытка вставить уже существующий узел
    result = addNode(bst, iMin);
    ASSERT_EQUALS(result, 2);
    // Тест для minNode()
    int min = nodeValue(minNode(bst));
    ASSERT_EQUALS(min, iMin);
    // Тест для maxNode()
    int max = nodeValue(maxNode(bst));
    ASSERT_EQUALS(max, iMax);

    // Тест для removeNode() - попытка удалить несуществующий узел
    result = removeNode(bst, iMin+1);
    ASSERT_EQUALS(result, 0);

    printf("\n\nRemoving nodes from tree:");
    // Тесты для removeNode(), containsNode() и treeSize()
    for (int i=iMin; i<=iMax; i+=iStep) {
        result=removeNode(bst, i);
        ASSERT_EQUALS(result, 1); // Должен быть удален
        cnt--;
        int contains = containsNode(bst, i); // Узел (i) удалили
        ASSERT_FALSE(contains);              //  - проверим, что его нет в дереве
        size = treeSize(bst); // Проверим уменьшение размера дерева
        ASSERT_EQUALS(size,cnt);
        printf("\n");
        traverseTree(bst, stdout, INORDER); // Посмотрим на изменение дерева
    }
    ASSERT_EQUALS(size,0); // Проверим, что удалены все узлы

    destroyTree(bst); // Удаляем дерево - освобождаем память

    return 0;
}
