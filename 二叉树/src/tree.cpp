#include <iostream>
#include "../inc/binary_sort_tree.h"
#include "../inc/tools.h"


Status BST_init(BinarySortTreePtr tree) 
{
	Status state = failed;
	if (tree != NULL) {
		tree->root = NULL;
		state = succeed;
	}
	return state;
}

Status BST_insert(BinarySortTreePtr tree, ElemType n)
{
	Status state = failed;
	NodePtr p;
	NodePtr q;
	q = (NodePtr)malloc(sizeof(Node));
	if (q == NULL) {
		fprintf(stderr, "*** ����ڵ�ռ�ʧ�� ***\n");
		exit(EXIT_FAILURE);
	}
	else {
		q->value = n; /*��������Ľڵ��������һ��*/
		q->left = NULL;
		q->right = NULL;
		if (tree->root == NULL) { /*���ǿ���*/
			tree->root = q;
			state = succeed;
		}
		else { /*���ǿ���*/
			p = tree->root;
			while (p != NULL) {
				if (p->value == n) { /*�ظ�ֵ�����*/
					printf("*** ��֧�ֲ����ظ�ֵ ***\n");
					free(q);
					break;
				}
				else if (p->value > n) {
					if (p->left != NULL)
						p = p->left;
					else { /*����������ֱ�Ӳ���*/
						p->left = q;
						state = succeed;
						break;
					}
				}
				else if (p->value < n) {
					if (p->right != NULL)
						p = p->right;
					else { /*����������ֱ�Ӳ���*/
						p->right = q;
						state = succeed;
						break;
					}
				}
			}
		}
	}
	return state;
}

Status BST_delete(BinarySortTreePtr tree, ElemType n)
{
	Status state = failed;
	NodePtr p;
	NodePtr t1 = NULL, t2;
	NodePtr del;
	if (tree->root != NULL) {
		p = tree->root;
		while (p != NULL) { /*����Ŀ��ڵ㲢��¼Ŀ��ڵ�ĸ��ڵ�*/
			if (p->value == n) { /*�ҵ�Ŀ��ڵ�*/
				break;
			}
			else if (p->value > n) {
				t1 = p; /*��t1��¼p�ĸ��ڵ�*/
				p = p->left;
			}
			else if (p->value < n) {
				t1 = p;/*��t1��¼p�ĸ��ڵ�*/
				p = p->right;
			}
		}
		if (p == NULL) {
			printf("*** δ�ҵ�ָ������ ***\n");
		}
		else { /*�ҵ���Ҫɾ���Ľڵ�*/
			del = p;
			if (t1 != NULL) { /*�Ǹ��ڵ�*/
				if (del->value < t1->value) { /*del��t1����ڵ�*/
					if (del->left == NULL && del->right == NULL) { /*delΪҶ�ӽڵ�*/
						t1->left = NULL;
					}
					else if (del->left != NULL && del->right == NULL) { /*��������*/
						t1->left = del->left;
					}
					else if (del->right != NULL && del->left == NULL) { /*��������*/
						t1->left = del->right;
					}
					else { /*���Ҷ���*/
						t2 = p;
						p = p->left;
						if (p->right != NULL) {
							while (p->right != NULL) { /*�ҵ�ֱ��ǰ��*/
								t2 = p; /*t2��¼ֱ��ǰ���ĸ��ڵ�*/
								p = p->right;
							}
							t2->right = p->left;
							p->left = del->left;
						}
						p->right = del->right;
						t1->left = p;
					}
				}
				else if (del->value > t1->value) { /*del��t1���ҽڵ�*/
					if (del->left == NULL && del->right == NULL) { /*delΪҶ�ӽڵ�*/
						t1->right = NULL;
					}
					else if (del->left != NULL && del->right == NULL) { /*��������*/
						t1->right = del->left;
					}
					else if (del->right != NULL && del->left == NULL) { /*��������*/
						t1->right = del->right;
					}
					else { /*���Ҷ���*/
						t2 = p;
						p = p->left;
						if (p->right != NULL) {
							while (p->right != NULL) { /*�ҵ�ֱ��ǰ��*/
								t2 = p; /*t2��¼ֱ��ǰ���ĸ��ڵ�*/
								p = p->right;
							}
							t2->right = p->left;
							p->left = del->left;
						}
						p->right = del->right;
						t1->right = p;
					}
				}
			}
			else { /*Ҫɾ�����ڵ�*/
				if (del->left == NULL && del->right == NULL) { /*delΪҶ�ӽڵ�*/
					tree->root = NULL;
				}
				else if (del->left != NULL && del->right == NULL) {  /*��������*/
					tree->root = del->left;
				}
				else if (del->left == NULL && del->right != NULL) { /*��������*/
					tree->root = del->right;
				}
				else {  /*���Ҷ���*/
					t2 = p;
					p = p->left;
					if (p->right != NULL) {
						while (p->right != NULL) { /*�ҵ�ֱ��ǰ��*/
							t2 = p; /*t2��¼ֱ��ǰ���ĸ��ڵ�*/
							p = p->right;
						}
						t2->right = p->left;
						p->left = del->left;
					}
					p->right = del->right;
					tree->root = p;
				}
			}
			free(del);
			state = succeed;
		}
	}
	else {
		printf("*** ��Ϊ�������޷����� ***\n");
	}
	return state;
}

Status BST_search(BinarySortTreePtr tree, ElemType n)
{
	Status state = 0;
	NodePtr p;
	if (tree->root != NULL) {
		p = tree->root;
		while (p != NULL) {
			if (p->value == n) {
				state = 1;
				break;
			}
			else if (p->value > n) {
				p = p->left;
			}
			else if (p->value < n) {
				p = p->right;
			}
		}
	}
	return state;
}

Status BST_preorderI(BinarySortTreePtr tree, void (*visit)(NodePtr))
{
	StackNode* p, *q1, *q2;
	NodePtr t;
	LinkStack* s;
	s = (LinkStack*)malloc(sizeof(LinkStack)); /*��ʼ��ջ*/
	if (s == NULL) {
		fprintf(stderr, "error!\n");
		exit(EXIT_FAILURE);
	}
	else {
		s->top = NULL;
		s->count = 0;
	}
	t = tree->root;
	if (t != NULL) {
		p = (StackNode*)malloc(sizeof(StackNode));
		if (p == NULL) {
			fprintf(stderr, "ERROR�������½ڵ�ʧ�ܣ�\n");
			exit(EXIT_FAILURE);
		}
		p->node = t;
		p->next = s->top;
		s->top = p;
		s->count += 1;
		
		do {
			//��ջ
			p = s->top;
			s->top = s->top->next;
			s->count -= 1;
			t = p->node;
			visit(t);
			free(p);
			//��ջ(��һ����)
			if (t->right != NULL) {
				q1 = (StackNode*)malloc(sizeof(StackNode));
				if (q1 == NULL) {
					fprintf(stderr, "ERROR�������½ڵ�ʧ�ܣ�\n");
					exit(EXIT_FAILURE);
				}
				q1->node = t->right;
				q1->next = s->top;
				s->top = q1;
				s->count += 1;
			}
			if (t->left != NULL) {
				q2 = (StackNode*)malloc(sizeof(StackNode));
				if (q2 == NULL) {
					fprintf(stderr, "ERROR�������½ڵ�ʧ�ܣ�\n");
					exit(EXIT_FAILURE);
				}
				q2->node = t->left;
				q2->next = s->top;
				s->top = q2;
				s->count += 1;
			}
			//ֱ����
		} while (s->top != NULL);
	}
	return succeed;
}

Status BST_preorderR(BinarySortTreePtr tree, void (*visit)(NodePtr))
{
	NodePtr p = tree->root;
	BinarySortTreePtr tree1, tree2;
	if (p != NULL) {
		tree1 = (BinarySortTreePtr)malloc(sizeof(BinarySortTree));
		tree2 = (BinarySortTreePtr)malloc(sizeof(BinarySortTree));
		if (tree1 == NULL || tree2 == NULL) {
			fprintf(stderr, "*** ����ռ�ʧ�� ***");
			exit(EXIT_FAILURE);
		}
		visit(p); /*ǰ��*/
		tree1->root = p->left;
		tree2->root = p->right;
		BST_preorderR(tree1, visit);
		BST_preorderR(tree2, visit);
		free(tree1);
		free(tree2);
	}
	return succeed;
}

Status BST_inorderI(BinarySortTreePtr tree, void (*visit)(NodePtr))
{
	StackNode* p, * q1;
	NodePtr t;
	LinkStack* s;
	s = (LinkStack*)malloc(sizeof(LinkStack)); /*��ʼ��ջ*/
	if (s == NULL) {
		fprintf(stderr, "error!\n");
		exit(EXIT_FAILURE);
	}
	else {
		s->top = NULL;
		s->count = 0;
	}
	t = tree->root;
	if (t != NULL) {
		do {
			//��ڵ�ȫ����ջ
			while (t != NULL) {
				p = (StackNode*)malloc(sizeof(StackNode));
				if (p == NULL) {
					fprintf(stderr, "ERROR�������½ڵ�ʧ�ܣ�\n");
					exit(EXIT_FAILURE);
				}
				p->node = t;
				p->next = s->top;
				s->top = p;
				s->count += 1;
				t = t->left;
			}
			//��һ���в�����
			p = s->top;
			s->top = s->top->next;
			s->count -= 1;
			t = p->node;
			visit(t);
			free(p);
			//��һ��ջ
			if (t->right != NULL) {
				q1 = (StackNode*)malloc(sizeof(StackNode));
				if (q1 == NULL) {
					fprintf(stderr, "ERROR�������½ڵ�ʧ�ܣ�\n");
					exit(EXIT_FAILURE);
				}
				q1->node = t->right;
				q1->next = s->top;
				s->top = q1;
				s->count += 1;
				t = t->right->left;
			}
			else {
				t = NULL;
			}
			//���°�������ڵ���ջ
		} while (s->top != NULL);
	}
	return succeed;
}

Status BST_inorderR(BinarySortTreePtr tree, void (*visit)(NodePtr))
{
	NodePtr p = tree->root;
	BinarySortTreePtr tree1, tree2;
	if (p!= NULL) {
		tree1 = (BinarySortTreePtr)malloc(sizeof(BinarySortTree));
		tree2 = (BinarySortTreePtr)malloc(sizeof(BinarySortTree));
		if (tree1 == NULL || tree2 == NULL) {
			fprintf(stderr, "*** ����ռ�ʧ�� ***");
			exit(EXIT_FAILURE);
		}
		tree1->root = p->left;
		tree2->root = p->right;
		BST_inorderR(tree1, visit);
		visit(p); /*����*/
		BST_inorderR(tree2, visit);
		free(tree1);
		free(tree2);
	}
	return succeed;
}

Status BST_postorderI(BinarySortTreePtr tree, void (*visit)(NodePtr)) 
{
	StackNode* p;
	NodePtr t;
	LinkStack* s;
	s = (LinkStack*)malloc(sizeof(LinkStack)); /*��ʼ��ջ*/
	if (s == NULL) {
		fprintf(stderr, "error!\n");
		exit(EXIT_FAILURE);
	}
	else {
		s->top = NULL;
		s->count = 0;
	}
	if (tree->root != NULL) {
		t = tree->root;
		do{
			while (t != NULL) { /*ÿһ������˵Ľڵ���ջ*/
				p = (StackNode*)malloc(sizeof(StackNode));
				if (p == NULL) {
					fprintf(stderr, "ERROR�������½ڵ�ʧ�ܣ�\n");
					exit(EXIT_FAILURE);
				}
				p->node = t;
				p->n = 0;
				p->next = s->top;
				s->top = p;
				s->count += 1;
				t = t->left;
			}
			//ȡջ���Ȳ����ʣ��ж�
			p = s->top;
			t = p->node;
			//�ж���֦
			if (t->right != NULL && p->n==0) { //��֦��Ϊ����δ��������װ��֦
				t = t->right;
				p->n = 1;
			}
			else if(t->right!=NULL&& p->n==1){ //��֦��Ϊ�����ѱ���
				visit(t);
				s->top = s->top->next;
				s->count -= 1;
				free(p);
				t = NULL;
			}
			else if (t->right == NULL) { /*��֦Ϊ�վͳ�ջ������*/
				visit(t);
				s->top = s->top->next;
				s->count -= 1;
				free(p);
				t = NULL;
			}
		} while (s->top != NULL);
	}
	return succeed;
}

Status BST_postorderR(BinarySortTreePtr tree, void (*visit)(NodePtr))
{
	NodePtr p = tree->root;
	BinarySortTreePtr tree1, tree2;
	if (p!= NULL) {
		tree1 = (BinarySortTreePtr)malloc(sizeof(BinarySortTree));
		tree2 = (BinarySortTreePtr)malloc(sizeof(BinarySortTree));
		if (tree1 == NULL || tree2 == NULL) {
			fprintf(stderr, "*** ����ռ�ʧ�� ***");
			exit(EXIT_FAILURE);
		}
		tree1->root = p->left;
		tree2->root = p->right;
		BST_postorderR(tree1, visit);
		BST_postorderR(tree2, visit);
		visit(p);
		free(tree1);
		free(tree2);
	}
	return succeed;
}

Status BST_levelOrder(BinarySortTreePtr tree, void (*visit)(NodePtr))
{
	NodePtr t;
	LNode* p;
	LQueue* Q;
	Q = (LQueue*)malloc(sizeof(LQueue));
	if (Q == NULL) {
		fprintf(stderr, "error!\n");
		exit(EXIT_FAILURE);
	}
	else {
		Q->front = NULL;
		Q->rear = NULL;
		Q->length = 0;
	}
	t = tree->root;
	if (t != NULL) {
		p = (LNode*)malloc(sizeof(LNode));
		if (p == NULL) {
			fprintf(stderr, " *** �����½ڵ�ʧ�ܣ� *** \n");
			exit(EXIT_FAILURE);
		}
		p->next = NULL; /*Ϊ�½ڵ��������*/
		p->node = t;
		Q->front = p;
		Q->rear = p;
		Q->length += 1;
		do {
			//������
			p = Q->front;
			Q->front = Q->front->next;
			Q->length -= 1;
			if (Q->length == 0 && Q->front == NULL) /*��������Ψһ�ڵ�����*/
				Q->rear = NULL;
			t = p->node;
			visit(t);
			free(p);

			//������
			if (t->left != NULL) {
				p = (LNode*)malloc(sizeof(LNode));
				if (p == NULL) {
					fprintf(stderr, " *** �����½ڵ�ʧ�ܣ� *** \n");
					exit(EXIT_FAILURE);
				}
				p->next = NULL; /*Ϊ�½ڵ��������*/
				p->node = t->left;
				if (Q->length == 0) {
					Q->front = p;
					Q->rear = p;
				}
				else {
					Q->rear->next = p;
					Q->rear = p;
				}
				Q->length += 1;
			}
			if (t->right != NULL) {
				p = (LNode*)malloc(sizeof(LNode));
				if (p == NULL) {
					fprintf(stderr, " *** �����½ڵ�ʧ�ܣ� *** \n");
					exit(EXIT_FAILURE);
				}
				p->next = NULL; /*Ϊ�½ڵ��������*/
				p->node = t->right;
				if (Q->length == 0) {
					Q->front = p;
					Q->rear = p;
				}
				else {
					Q->rear->next = p;
					Q->rear = p;
				}
				Q->length += 1;
			}
		} while (Q->front != NULL);
	}
	return succeed;
}