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
		fprintf(stderr, "*** 申请节点空间失败 ***\n");
		exit(EXIT_FAILURE);
	}
	else {
		q->value = n; /*把新申请的节点数据填充一下*/
		q->left = NULL;
		q->right = NULL;
		if (tree->root == NULL) { /*树是空树*/
			tree->root = q;
			state = succeed;
		}
		else { /*不是空树*/
			p = tree->root;
			while (p != NULL) {
				if (p->value == n) { /*重复值的情况*/
					printf("*** 不支持插入重复值 ***\n");
					free(q);
					break;
				}
				else if (p->value > n) {
					if (p->left != NULL)
						p = p->left;
					else { /*搜索到树底直接插入*/
						p->left = q;
						state = succeed;
						break;
					}
				}
				else if (p->value < n) {
					if (p->right != NULL)
						p = p->right;
					else { /*搜索到树底直接插入*/
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
		while (p != NULL) { /*搜索目标节点并记录目标节点的父节点*/
			if (p->value == n) { /*找到目标节点*/
				break;
			}
			else if (p->value > n) {
				t1 = p; /*用t1记录p的父节点*/
				p = p->left;
			}
			else if (p->value < n) {
				t1 = p;/*用t1记录p的父节点*/
				p = p->right;
			}
		}
		if (p == NULL) {
			printf("*** 未找到指定数据 ***\n");
		}
		else { /*找到了要删除的节点*/
			del = p;
			if (t1 != NULL) { /*非根节点*/
				if (del->value < t1->value) { /*del是t1的左节点*/
					if (del->left == NULL && del->right == NULL) { /*del为叶子节点*/
						t1->left = NULL;
					}
					else if (del->left != NULL && del->right == NULL) { /*有左无右*/
						t1->left = del->left;
					}
					else if (del->right != NULL && del->left == NULL) { /*有右无左*/
						t1->left = del->right;
					}
					else { /*左右都有*/
						t2 = p;
						p = p->left;
						if (p->right != NULL) {
							while (p->right != NULL) { /*找到直接前驱*/
								t2 = p; /*t2记录直接前驱的父节点*/
								p = p->right;
							}
							t2->right = p->left;
							p->left = del->left;
						}
						p->right = del->right;
						t1->left = p;
					}
				}
				else if (del->value > t1->value) { /*del是t1的右节点*/
					if (del->left == NULL && del->right == NULL) { /*del为叶子节点*/
						t1->right = NULL;
					}
					else if (del->left != NULL && del->right == NULL) { /*有左无右*/
						t1->right = del->left;
					}
					else if (del->right != NULL && del->left == NULL) { /*有右无左*/
						t1->right = del->right;
					}
					else { /*左右都有*/
						t2 = p;
						p = p->left;
						if (p->right != NULL) {
							while (p->right != NULL) { /*找到直接前驱*/
								t2 = p; /*t2记录直接前驱的父节点*/
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
			else { /*要删除根节点*/
				if (del->left == NULL && del->right == NULL) { /*del为叶子节点*/
					tree->root = NULL;
				}
				else if (del->left != NULL && del->right == NULL) {  /*有左无右*/
					tree->root = del->left;
				}
				else if (del->left == NULL && del->right != NULL) { /*有右无左*/
					tree->root = del->right;
				}
				else {  /*左右都有*/
					t2 = p;
					p = p->left;
					if (p->right != NULL) {
						while (p->right != NULL) { /*找到直接前驱*/
							t2 = p; /*t2记录直接前驱的父节点*/
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
		printf("*** 树为空树，无法操作 ***\n");
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
	s = (LinkStack*)malloc(sizeof(LinkStack)); /*初始化栈*/
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
			fprintf(stderr, "ERROR：申请新节点失败！\n");
			exit(EXIT_FAILURE);
		}
		p->node = t;
		p->next = s->top;
		s->top = p;
		s->count += 1;
		
		do {
			//出栈
			p = s->top;
			s->top = s->top->next;
			s->count -= 1;
			t = p->node;
			visit(t);
			free(p);
			//入栈(出一入两)
			if (t->right != NULL) {
				q1 = (StackNode*)malloc(sizeof(StackNode));
				if (q1 == NULL) {
					fprintf(stderr, "ERROR：申请新节点失败！\n");
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
					fprintf(stderr, "ERROR：申请新节点失败！\n");
					exit(EXIT_FAILURE);
				}
				q2->node = t->left;
				q2->next = s->top;
				s->top = q2;
				s->count += 1;
			}
			//直到空
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
			fprintf(stderr, "*** 申请空间失败 ***");
			exit(EXIT_FAILURE);
		}
		visit(p); /*前序*/
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
	s = (LinkStack*)malloc(sizeof(LinkStack)); /*初始化栈*/
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
			//左节点全部入栈
			while (t != NULL) {
				p = (StackNode*)malloc(sizeof(StackNode));
				if (p == NULL) {
					fprintf(stderr, "ERROR：申请新节点失败！\n");
					exit(EXIT_FAILURE);
				}
				p->node = t;
				p->next = s->top;
				s->top = p;
				s->count += 1;
				t = t->left;
			}
			//出一个中并访问
			p = s->top;
			s->top = s->top->next;
			s->count -= 1;
			t = p->node;
			visit(t);
			free(p);
			//右一入栈
			if (t->right != NULL) {
				q1 = (StackNode*)malloc(sizeof(StackNode));
				if (q1 == NULL) {
					fprintf(stderr, "ERROR：申请新节点失败！\n");
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
			//重新把所有左节点入栈
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
			fprintf(stderr, "*** 申请空间失败 ***");
			exit(EXIT_FAILURE);
		}
		tree1->root = p->left;
		tree2->root = p->right;
		BST_inorderR(tree1, visit);
		visit(p); /*中序*/
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
	s = (LinkStack*)malloc(sizeof(LinkStack)); /*初始化栈*/
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
			while (t != NULL) { /*每一层最左端的节点入栈*/
				p = (StackNode*)malloc(sizeof(StackNode));
				if (p == NULL) {
					fprintf(stderr, "ERROR：申请新节点失败！\n");
					exit(EXIT_FAILURE);
				}
				p->node = t;
				p->n = 0;
				p->next = s->top;
				s->top = p;
				s->count += 1;
				t = t->left;
			}
			//取栈顶先不访问，判断
			p = s->top;
			t = p->node;
			//判断右枝
			if (t->right != NULL && p->n==0) { //右枝不为空且未遍历过就装右枝
				t = t->right;
				p->n = 1;
			}
			else if(t->right!=NULL&& p->n==1){ //右枝不为空且已遍历
				visit(t);
				s->top = s->top->next;
				s->count -= 1;
				free(p);
				t = NULL;
			}
			else if (t->right == NULL) { /*右枝为空就出栈并访问*/
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
			fprintf(stderr, "*** 申请空间失败 ***");
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
			fprintf(stderr, " *** 申请新节点失败！ *** \n");
			exit(EXIT_FAILURE);
		}
		p->next = NULL; /*为新节点填充数据*/
		p->node = t;
		Q->front = p;
		Q->rear = p;
		Q->length += 1;
		do {
			//出队列
			p = Q->front;
			Q->front = Q->front->next;
			Q->length -= 1;
			if (Q->length == 0 && Q->front == NULL) /*出掉队列唯一节点的情况*/
				Q->rear = NULL;
			t = p->node;
			visit(t);
			free(p);

			//入两个
			if (t->left != NULL) {
				p = (LNode*)malloc(sizeof(LNode));
				if (p == NULL) {
					fprintf(stderr, " *** 申请新节点失败！ *** \n");
					exit(EXIT_FAILURE);
				}
				p->next = NULL; /*为新节点填充数据*/
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
					fprintf(stderr, " *** 申请新节点失败！ *** \n");
					exit(EXIT_FAILURE);
				}
				p->next = NULL; /*为新节点填充数据*/
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