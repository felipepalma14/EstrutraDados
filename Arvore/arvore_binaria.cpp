#include<stdlib.h>
#include<stdio.h>

struct Arvore {
int data;
struct Arvore * direita, * esquerda;
};

void insert(Arvore ** raiz, int val)
{
    Arvore *temp = NULL;
    if(!(*raiz))
    {
        temp = (Arvore *)malloc(sizeof(Arvore));
        temp->esquerda = temp->direita = NULL;
        temp->data = val;
        *raiz = temp;
        return;
    }

    if(val < (*raiz)->data)
    {
        insert(&(*raiz)->esquerda, val);
    }
    else if(val > (*raiz)->data)
    {
        insert(&(*raiz)->direita, val);
    }

}

void print_preorder(Arvore *raiz)
{
    if (raiz)
    {
        printf("%d\n",raiz->data);
        print_preorder(raiz->esquerda);
        print_preorder(raiz->direita);
    }

}

void print_inorder(Arvore *raiz)
{
    if (raiz)
    {
        print_inorder(raiz->esquerda);
        printf("%d\n",raiz->data);
        print_inorder(raiz->direita);
    }
}

void print_postorder(Arvore *raiz)
{
    if (raiz)
    {
        print_postorder(raiz->esquerda);
        print_postorder(raiz->direita);
        printf("%d\n",raiz->data);
    }
}

void deltree(Arvore *raiz)
{
    if (raiz)
    {
        deltree(raiz->esquerda);
        deltree(raiz->direita);
        free(raiz);
    }
}

Arvore* search(Arvore ** raiz, int val)
{
    if(!(*raiz))
    {
        return NULL;
    }

    if(val < (*raiz)->data)
    {
        search(&((*raiz)->esquerda), val);
    }
    else if(val > (*raiz)->data)
    {
        search(&((*raiz)->direita), val);
    }
    else if(val == (*raiz)->data)
    {
        return *raiz;
    }
}

int main()
{
    Arvore *root;
    Arvore *tmp;
    //int i;

    root = NULL;
    /* Inserting nodes into tree */
    insert(&root, 9);
    insert(&root, 4);
    insert(&root, 15);
    insert(&root, 6);
    insert(&root, 12);
    insert(&root, 17);
    insert(&root, 2);

    /* Printing nodes of tree */
    printf("Pre Order Display\n");
    print_preorder(root);

    printf("In Order Display\n");
    print_inorder(root);

    printf("Post Order Display\n");
    print_postorder(root);

    /* Search node into tree */
    tmp = search(&root, 4);
    if (tmp)
    {
        printf("Searched node=%d\n", tmp->data);
    }
    else
    {
        printf("Data Not found in tree.\n");
    }

    /* Deleting all nodes of tree */
    deltree(root);
}
