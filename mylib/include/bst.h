#ifndef BST_H
#define BST_H

// ���������� ��������� ������ ������ �� ����� ��
//

// ���� ������
struct node;
typedef struct node node;
 
// ������
struct tree;
typedef struct tree tree;
 
// �������� ������� ������
// �������: ��������� �� ������ (NULL ���� ������ �� �������)
extern tree *createTree(void);

// ��������� ������� ������
// �������: ���������� ����� � ������
extern int treeSize(tree *bst);
 
// �������� ������� � ������ ���� � �������� ���������
// �������: 0 - ������ ���� ���, 1 -  ����� ���� ����
extern int containsNode(const tree *bst, int value);

// ��������� �������� �� ����
// �������: �������� � ����
extern int nodeValue(node *n);
 
// ������� ���� � ������
// �������: 0 - �� ������� �������� ����, 1 - ���� ��������, 2 - ����� ���� ��� ���� � ������
extern int addNode(tree *bst, int value);
 
// �������� ���� �� ������
// �������: 0 - �� ������� ������� ����, 1 - ���� ������
extern int removeNode(tree *bst, int value);

// ����� ������������ ���� � ������
// �������: ��������� �� ���� � ����������� ��������� � ������
extern node *minNode(tree *bst);
 
// ����� ������������� ���� � ������
// �������: ��������� �� ���� � ������������ ��������� � ������
extern node *maxNode(tree *bst);
 
// ����� ������ � ������� ����� � �������� ����
#define PREORDER  0 // ������ ����� 
#define POSTORDER 1 // �������� �����
#define INORDER   2 // �������������� �����
extern void traverseTree(tree *bst, FILE *f, int order);

// ������������ ������, ������� �������
extern void destroyTree(tree *bst);
 

#endif
