#include <stdio.h> 
#include <stdlib.h>

// 定义二叉链表结点结构
typedef struct Node
{
    int data;
    struct Node *lchild, *rchild;
} BiTNode, *BiTree;

int N; // 全局变量：数组有效长度

// 递归创建二叉树（顺序存储 -> 二叉链表）
BiTree CreateBiTree(int *nodelist, int position)
{
    BiTree p;
    
    // 核心修复：position 必须小于 N，且对应位置值为 0 才表示空节点
    if (position >= N || nodelist[position] == 0)
        return NULL;

    p = (BiTree)malloc(sizeof(BiTNode));
    p->data = nodelist[position]; // 直接存储整数（无需转 ASCII）
    
    // 左右孩子下标计算正确
    p->lchild = CreateBiTree(nodelist, 2 * position + 1);
    p->rchild = CreateBiTree(nodelist, 2 * position + 2);

    return p;
}

// 计算表达式值
int Get_Value(int oper, int oper1, int oper2)
{
    switch (oper) // oper 直接是整数（'+' 的 ASCII 码 43）
    {
        case '*': return oper1 * oper2;
        case '/': return oper1 / oper2;
        case '+': return oper1 + oper2;
        case '-': return oper1 - oper2;
        default:  return 0; // 防止未知运算符
    }
}

// 递归计算表达式二叉树
int Calculate(BiTree T)
{
    int oper1, oper2;
    
    // 叶子节点：数字（假设数字节点 data 直接是整数）
    if (T->lchild == NULL && T->rchild == NULL)
        return T->data;

    oper1 = Calculate(T->lchild);
    oper2 = Calculate(T->rchild);

    return Get_Value(T->data, oper1, oper2);
}

int main()
{
    BiTree T = NULL;
    int cal_result;

    // 数组设计：
    // nodelist[0] = '+' (根节点)
    // nodelist[1] = '*' (左子)
    // nodelist[2] = '-' (右子)
    // nodelist[3] = 1, nodelist[4] = 2, nodelist[5] = 6, nodelist[6] = 3 (叶子)
    // 有效长度 N = 7
    int nodelist[7] = { '+', '*', '-', 1, 2, 6, 3 }; 
    
    N = 7; // 设置有效长度
    T = CreateBiTree(nodelist, 0); // 从下标 0 开始创建
    
    cal_result = Calculate(T);
    printf("Calculate result is [ %d ]\n", cal_result);

    return 0;
}