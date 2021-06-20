#include "BTForSynonyms.c"
typedef struct Main_node{
    char val[20];
    BT synonyms;
    struct Main_node *right, *left;

} *Main_BT;
extern Main_BT Main_BTinit();
extern int Main_BTempty(Main_BT a);
extern Main_BT InsertMain_BST(Main_BT t,BT syn,char* x);
extern void Main_InOrder(Main_BT A);
