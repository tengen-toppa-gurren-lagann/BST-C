#include <stdio.h>
#include <stdlib.h>
#include "mytests.h"
#include "bst.h"

// �������� ���������, ����������� ��������� ����� ��� ������� ����������� ���������� ��������� ������ ������
int main() {
    int result;
	
    // ���� ��� createTree()
    tree *bst = NULL;
    ASSERT_NULL(bst);
    bst = createTree();
    ASSERT_NOT_NULL(bst);
    int size = treeSize(bst);
    ASSERT_EQUALS(size,0); // ������ ������ ���� ������
   
    // ����� ��� addNode(), containsNode() � treeSize()
    const int iMin = 1;  // ������� ����������� ����
    const int iMax = 101; // ������� ������������ ����
    const int iStep = 10;// ��� ��������� � �����
    int cnt = 0;
    printf("Adding nodes to tree:");
    for (int i=iMin; i<=iMax; i+=iStep) { // ��������� ���� � ������ (�� ������������ �� �������������) � ��������� ��� ��� ����������
        result = addNode(bst, i);
        ASSERT_EQUALS(result, 1); // ������ ���� ��������
        cnt++;
        int contains = containsNode(bst, i); // ���� (i) �������� 
        ASSERT_TRUE(contains);               //  - ��������, ��� �� ���� � ������
        contains = containsNode(bst, i+1);   // ���� (i+1) �� ���������
        ASSERT_FALSE(contains);              //  - ��������, ��� ��� ��� � ������
        size = treeSize(bst); // �������� ���������� ������� ������
        ASSERT_EQUALS(size,cnt);
        printf("\n");
        traverseTree(bst, stdout, INORDER); // ��������� �� ��������� ������
    }
	
    // ���� ��� addNode() - ������� �������� ��� ������������ ����
    result = addNode(bst, iMin);
    ASSERT_EQUALS(result, 2);
    // ���� ��� minNode()
    int min = nodeValue(minNode(bst));
    ASSERT_EQUALS(min, iMin);
    // ���� ��� maxNode()
    int max = nodeValue(maxNode(bst));
    ASSERT_EQUALS(max, iMax);

    // ���� ��� removeNode() - ������� ������� �������������� ����
    result = removeNode(bst, iMin+1);
    ASSERT_EQUALS(result, 0);

    printf("\n\nRemoving nodes from tree:");
    // ����� ��� removeNode(), containsNode() � treeSize()
    for (int i=iMin; i<=iMax; i+=iStep) {
        result=removeNode(bst, i);
        ASSERT_EQUALS(result, 1); // ������ ���� ������
        cnt--;
        int contains = containsNode(bst, i); // ���� (i) �������
        ASSERT_FALSE(contains);              //  - ��������, ��� ��� ��� � ������
        size = treeSize(bst); // �������� ���������� ������� ������
        ASSERT_EQUALS(size,cnt);
        printf("\n");
        traverseTree(bst, stdout, INORDER); // ��������� �� ��������� ������
    }
    ASSERT_EQUALS(size,0); // ��������, ��� ������� ��� ����

    destroyTree(bst); // ������� ������ - ����������� ������

    return 0;
}
