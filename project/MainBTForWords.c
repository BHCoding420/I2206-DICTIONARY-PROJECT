#include<stdio.h>
#include<stdlib.h>
#include "MainBT(words).h"

/*********************************************************************/
Main_BT Main_BTinit(){ return NULL;}
/*********************************************************************/
int Main_BTempty(Main_BT a){ return (a==NULL);}
/*********************************************************************/
Main_BT InsertMain_BST(Main_BT t,BT syn,char* x)
{

    if(Main_BTempty(t))
    {

        struct Main_node *n;
         n=(struct Main_node *)malloc(sizeof(struct Main_node));
         strcpy(n->val,x);
         n->synonyms = syn;
         n->right=NULL;
         n->left=NULL;

         return n;

    }

    else
    {

        if(comparison(t->val,x)==0)
        {

            t->right=InsertMain_BST(t->right,syn,x);
        }

        else
        {

            t->left=InsertMain_BST(t->left,syn,x);
        }

        return t;
    }

}
/*********************************************************************/
void Main_InOrder(Main_BT A)
{
    if (A ==NULL) return;
    Main_InOrder(A ->left);
    printf("word: %s \n\n", A->val);
    printf("synonyms: \n");
    InOrder(A->synonyms);
    printf("nb of synonyms : %d",getfullCount(A->synonyms));

    printf("\n---------- \n");
    Main_InOrder(A ->right);
}
/*********************************************************************/
