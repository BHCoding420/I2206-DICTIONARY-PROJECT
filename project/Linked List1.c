#include "LLHeader.h"
#include<stdio.h>
#include<string.h>

List createList()
{
	List l;
	l.head = l.tail = NULL;
	return l;
}

int isEmpty(List l)
{
    return (l.head==NULL && l.tail==NULL);
}

void insertTail(List *l, char* element)
{
	LLNode *n = (LLNode *)malloc(sizeof(LLNode));
	strcpy(n->e,element);
	n->repetition = 0;

	n->next = NULL;
	if(isEmpty(*l))
	{
		l->tail = n;
		l->head = n;
	}
	else

	{
		l->tail->next = n;
		l->tail = n;
	}

}
void display(List l)
{
	while (l.head != NULL)
	{
		printf("word: %s\t", l.head->e);
		printf("repetition: %d\t", l.head->repetition);
		printf("\n");
		l.head = l.head->next;
	}
	printf("\n");
}

void search_and_increment(List *l,char* x)
{
    LLNode* temp = l->head;

    while(temp != NULL)
    {
        if(strcmp(temp->e,x) == 0)
        {
            temp->repetition += 1;
            return;
        }
        temp = temp->next;
    }
    insertTail(l,x);
}

