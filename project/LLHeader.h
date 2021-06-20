typedef struct LLNode {
	char e[20];
	int repetition;
	struct LLNode *next;
} LLNode;

typedef struct List {
	LLNode *head;
	LLNode *tail;
} List;

extern List createList();
extern int isEmpty(List l);
extern void insertTail(List *l, char* element);
extern void display(List l);
extern void search_and_increment(List *l,char* x);
