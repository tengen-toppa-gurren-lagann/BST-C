#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // ��� getopt()
#include "bst.h"

// ���������������� ���������, ������������ ����������� ���������� ��������� ������ ������
int main(int argc, char **argv) {
    // ��������� �� ������������� ���������
    const char *sUsage = "myapp (binary search tree test program) usage:\nmyapp -a inputFileWithNumbersToAdd -d inputFileWithNumbersToDelete -o outputFile\n";

    // ��������� ��������� ������
    if(argc < 7) { // E��� ���������� ������������, ������� �������
        printf("%s", sUsage);
        return -1;
    }
    char *opts = "a:d:o:"; // �����, ������ ����� ��������
    char *inputFilenameAdd = 0;
    char *inputFilenameDel = 0;
    char *outputFilename = 0;
    int  opt; // ����������� �����
    while ((opt = getopt(argc, argv, opts)) != -1 ) { // �������� getopt(), ���� ��� �� ������ -1
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
    if (inputFilenameAdd == NULL || inputFilenameDel == NULL || outputFilename == NULL) { // � ��������� ������ �� ������ ��� ������� ������ ����� ������
        printf("%s", sUsage);
        return -1;
    }

    // ����������� ����� ����������� �� ��������� ������ ���� ������, �������� ������
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

    // ������� ������
    tree *test_tree = createTree();

    // ��������� � ������ ����, �������� �� ������� �����
    int value;
    while (fscanf(inputFileAdd, "%d", &value) != EOF) {
        addNode(test_tree, value);
    };

//	outputFile = stdout; // ��� ������� (����� �� � ����, � � �������)
    
    // ������� �������������� ������ (����� ��������� ������), ��� ������, � ����� ����������� � ������������ ����
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

    // �� ������� ������� �� ������ ����, �������� �� ������� �����, � ������� ������, ��� ������, ����������� � ������������ ����,
    // � ����� ��������� ������� � ������ ���� ����������� �������� �����
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

    // ��������� �����
    fclose(inputFileAdd);
    fclose(inputFileDel);
    fclose(outputFile);

    // ����������� ������, ������� �������
    destroyTree(test_tree);
     
    return 0;
 
}

