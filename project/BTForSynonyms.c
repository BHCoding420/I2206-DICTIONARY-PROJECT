#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "BTHeader(syn).h"
/**********************************************************************/
int MAX(int x1,int x2)
{
    if(x1 > x2)
    {
        return x1;
    }
    else
    {
        return x2;
    }
}
/**********************************************************************/
int comparison(char *s,char *l)
{
    if(strcmp(s,l)==0)
       return 1;

  int i=0 , j=0;
  int size1 = strlen(s);
  int size2 = strlen(l);
  int max = MAX(size1,size2);
    while(i<max&&j<max)
    {
        if(s[i]>l[j])
        {

            return 1;
        }

        else if(s[i]<l[j])
        {

            return 0;
        }

        else
        {
            i++;
            j++;
        }
    }
}
/**********************************************************************/
BT BTinit(){ return NULL;}
/**********************************************************************/
int BTempty(BT a){ return (a==NULL);}
/**********************************************************************/
BT InsertBST(BT t,char* x)
{
    if(BTempty(t))
    {
        struct node0 * n;
         n=(struct node0 *)malloc(sizeof(struct node0));
         strcpy(n->val,x);
         n->right=NULL;
         n->left=NULL;

         return n;

    }

    else
    {

        if(comparison(t->val,x) == 0)
        {

             t->right=InsertBST(t->right,x);
        }

        else
        {

            t->left=InsertBST(t->left,x);
        }

        return t;
    }

}
/**********************************************************************/
void InOrder(BT A)
{
    if (A ==NULL) return;
    InOrder(A ->left);
    printf("word: %s \n", A->val);


    InOrder(A ->right);
}
/**********************************************************************/
int getfullCount_helper(BT root,int count)
{

    if (root ==NULL) return count;
    getfullCount_helper(root ->left,count);
    count++;


    getfullCount_helper(root ->right,count);
}
/**********************************************************************/
int getfullCount(BT root)
{
    return getfullCount_helper(root,0);
}

