typedef struct node0{
char val[20];
struct node0 *right, *left;
} * BT;

extern BT BTinit();
extern int BTempty(BT a);
extern BT InsertBST(BT t,char* x);
extern void InOrder(BT A);
extern int getfullCount_helper(BT root,int count);
extern int getfullCount(BT root);
extern int MAX(int x1,int x2);
extern int comparison(char *s,char *l);
