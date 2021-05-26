#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // Для getopt()
#include "bst.h"

// Демонстрационная программа, использующая статическую библиотеку двоичного дерева поиска
int main(int argc, char **argv) {
    // Подсказка об использовании программы
    const char *sUsage = "myapp (binary search tree test program) usage:\nmyapp -a inputFileWithNumbersToAdd -d inputFileWithNumbersToDelete -o outputFile\n";

    // Разбираем командную строку
    if(argc < 7) { // Eсли аргументов недостаточно, выводим справку
        printf("%s", sUsage);
        return -1;
    }
    char *opts = "a:d:o:"; // Опции, каждая имеет аргумент
    char *inputFilenameAdd = 0;
    char *inputFilenameDel = 0;
    char *outputFilename = 0;
    int  opt; // Прочитанная опция
    while ((opt = getopt(argc, argv, opts)) != -1 ) { // Вызываем getopt(), пока она не вернет -1
        switch(opt) {
            case 'a':
                inputFilenameAdd = optarg;
                break;
            case 'd':
                inputFilenameDel = optarg;
                break;
            case 'o':
                outputFilename = optarg;
                break;
        }
    }
    if (inputFilenameAdd == NULL || inputFilenameDel == NULL || outputFilename == NULL) { // В командной строке не заданы или неверно заданы имена файлов
        printf("%s", sUsage);
        return -1;
    }

    // Контрольный вывод прочитанных из командной строки имен файлов, открытие файлов
    printf("File with numbers to add: %s\nFile with numbers to delete: %s\nOutput file: %s\n", inputFilenameAdd, inputFilenameDel, outputFilename);
    FILE *inputFileAdd, *inputFileDel, *outputFile;
    inputFileAdd = fopen(inputFilenameAdd, "r");
    inputFileDel = fopen(inputFilenameDel, "r");
    outputFile = fopen(outputFilename, "w");
    if (inputFileAdd == NULL) {
        printf("Input file with numbers to add opening error!\n");
        return -1;
    }
    if (inputFileDel == NULL) {
        printf("Input file with numbers to delete opening error!\n");
        return -1;
    }
    if (outputFile == NULL) {
        printf("Output file opening error!\n");
        return -1;
    }

    // Создаем дерево
    tree *test_tree = createTree();

    // Добавляем в дерево узлы, заданные во входном файле
    int value;
    while (fscanf(inputFileAdd, "%d", &value) != EOF) {
        addNode(test_tree, value);
    };

//	outputFile = stdout; // Для отладки (вывод не в файл, а в консоль)
    
    // Выводим сформированное дерево (тремя способами обхода), его размер, а также минимальный и максимальный узлы
    fprintf(outputFile, "Binary Search Tree\n");
    fprintf(outputFile, "==================\n");
    fprintf(outputFile, "PREORDER TRAVERSAL:\n");
    fprintf(outputFile, "-------------------\n");
    traverseTree(test_tree, outputFile, PREORDER);
    fprintf(outputFile, "--------------------\n");
    fprintf(outputFile, "POSTORDER TRAVERSAL:\n");
    fprintf(outputFile, "--------------------\n");
    traverseTree(test_tree, outputFile, POSTORDER);
    fprintf(outputFile, "------------------\n");
    fprintf(outputFile, "INORDER TRAVERSAL:\n");
    fprintf(outputFile, "------------------\n");
    traverseTree(test_tree, outputFile, INORDER);
    fprintf(outputFile, "-------------\n");
    fprintf(outputFile, "Tree size: %d\n", treeSize(test_tree));
    node *tree_min = minNode(test_tree);
    node *tree_max = maxNode(test_tree);
    fprintf(outputFile, "Min node: %d\n", nodeValue(tree_min));
    fprintf(outputFile, "Max node: %d\n", nodeValue(tree_max));
    fprintf(outputFile, "-------------\n");

    // По очереди удаляем из дерева узлы, заданные во входном файле, и выводим дерево, его размер, минимальный и максимальный узлы,
    // а также проверяем наличие в дереве двух произвольно заданных узлов
    while (fscanf(inputFileDel, "%d", &value) != EOF) {
        removeNode(test_tree, value);
        fprintf(outputFile, "\nTree after deleting %d:\n", value);
        fprintf(outputFile, "-------------------\n");
        fprintf(outputFile, "PREORDER TRAVERSAL:\n");
        fprintf(outputFile, "-------------------\n");
        traverseTree(test_tree, outputFile, PREORDER);
        fprintf(outputFile, "--------------------\n");
        fprintf(outputFile, "POSTORDER TRAVERSAL:\n");
        fprintf(outputFile, "--------------------\n");
        traverseTree(test_tree, outputFile, POSTORDER);
        fprintf(outputFile, "------------------\n");
        fprintf(outputFile, "INORDER TRAVERSAL:\n");
        fprintf(outputFile, "------------------\n");
        traverseTree(test_tree, outputFile, INORDER);
        fprintf(outputFile, "-------------\n");
        fprintf(outputFile, "Tree size: %d\n", treeSize(test_tree));
        tree_min = minNode(test_tree);
        tree_max = maxNode(test_tree);
        fprintf(outputFile, "Min node: %d\n", nodeValue(tree_min));
        fprintf(outputFile, "Max node: %d\n", nodeValue(tree_max));
        value=4;	
        fprintf(outputFile, "Value=%d -> node is %s\n", value, containsNode(test_tree, value)? "present" : "not present");
        value=12;	
        fprintf(outputFile, "Value=%d -> node is %s\n", value, containsNode(test_tree, value)? "present" : "not present");
        fprintf(outputFile, "-------------\n");
    };

    // Закрываем файлы
    fclose(inputFileAdd);
    fclose(inputFileDel);
    fclose(outputFile);

    // Освобождаем память, занятую деревом
    destroyTree(test_tree);
     
    return 0;
 
}

