#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Linked List1.c"
#include "MainBTForWords.c"
/***********************************************************************/
// 3-Test if a word is present in the dictionary.
int search(Main_BT root, char* key)
{
    // Base Cases: root is null or key is present at root
    if (root == NULL)
       return 0;
    if(strcmp(root->val,key) == 0)
    {
        return 1;
    }

    // Key is greater than root's key
    if (comparison(root->val,key)==0)
       return search(root->right, key);

    // Key is smaller than root's key
    return search(root->left, key);
}
/***********************************************************************************/
//4. Given a word found in the dictionary, print all the synonyms for that word
void SynonymsOfWord(Main_BT root, char* key)
{

    if (root == NULL)
    {
        printf("the word you entered is not available \n");
       return;
    }

    if(strcmp(root->val,key) == 0)
    {
        printf("the synonyms of %s are \n",root->val);
        InOrder(root->synonyms);
        return;

    }


    if (comparison(root->val,key)==0)
    {

       return SynonymsOfWord(root->right, key);
    }


    else
    {

        return SynonymsOfWord(root->left, key);
    }
}
/**********************************************************************************/
/*5. Given a word m and one of its synonyms s, add to the dictionary the synonym s of the word
m (if it is already present, add a synonym among its synonyms, if it is not present, then add
it to dictionary, with the synonym s as the only synonym)*/
int search_in_synonyms(BT synonyms,char* key)
{
    if (synonyms == NULL)
       return 0;
    if(strcmp(synonyms->val,key) == 0)
    {
        return 1;
    }

    // Key is greater than root's key
    if (comparison(synonyms->val,key)==0)
       return search_in_synonyms(synonyms->right, key);

    // Key is smaller than root's key
    return search_in_synonyms(synonyms->left, key);
}

Main_BT  search2(Main_BT root, char* key)
{
    // Base Cases: root is null or key is present at root
    if (root == NULL)
       return root;
    if(strcmp(root->val,key) == 0)
    {
        return root;
    }

    // Key is greater than root's key
    if (comparison(root->val,key)==0)
       return search2(root->right, key);

    // Key is smaller than root's key
    return search2(root->left, key);
}
void AddSynonym(Main_BT root,char* word,char* synonym)
{
    Main_BT temp = search2(root,word);
    if(temp != NULL)
    {
        temp->synonyms = InsertBST(temp->synonyms,synonym);
    }

    else
    {
        BT new_synonym = BTinit();
        new_synonym = InsertBST(new_synonym,synonym);
        root = InsertMain_BST(root,new_synonym,word);
    }
}
/**********************************************************************************/
/*6- You must also suggest other operations such as:
                   a . Find the word with the highest number of synonyms*/

void most_synonyms(Main_BT A,int* count,char* res)
{


    if(A==NULL) return;

    most_synonyms(A->left,count,res);


    if(getfullCount(A->synonyms) > *count)
    {

        *count = getfullCount(A->synonyms);


        strcpy(res,A->val);

    }
    most_synonyms(A->right,count,res);
}

char* most_synonyms_main(Main_BT root)
{
    char* s =(char*)malloc(20*sizeof(char));
    int count = 0;
    most_synonyms(root,&count,s);
    return s;
}
/**************************************************************************/
//6-b. Given a word m, find the dictionary words for which m is a synonym
void words_having_synonym(Main_BT root,char* key)
{
    if (root ==NULL) return;
    words_having_synonym(root ->left,key);


    if(search_in_synonyms(root->synonyms,key) == 1)
    {
        printf("%s-",root->val);
    }

    words_having_synonym(root ->right,key);
}
/**************************************************************************/
//6-c Find the most repeated word as a synonym in the dictionary
void synonyms_to_list(BT root,List* l)
{
    if (root ==NULL) return;
    synonyms_to_list(root ->left,l);
    search_and_increment(l,root->val);
    synonyms_to_list(root ->right,l);
}
void most_repeated_synonym_helper(Main_BT root,List* l)
{
    if(root == NULL) return;
    most_repeated_synonym_helper(root->left,l);

    synonyms_to_list(root->synonyms,l);


    most_repeated_synonym_helper(root->right,l);
}

char* most_repeated_synonym(Main_BT root)
{
    List l = createList();
    most_repeated_synonym_helper(root,&l);
    LLNode* temp = l.head;
     int max = 0;
    char* result = (char*)malloc(20*sizeof(char));
    while(temp != NULL)
    {
        if(temp->repetition > max)
        {
            max = temp->repetition;
            strcpy(result,temp->e);
        }
        temp = temp->next;
    }

    return result;
}
/***********************************************************************************/
// 6-d. Balance the dictionary to improve complexity.
void storeBSTNodes(Main_BT root, Main_BT nodes[],int* i)
{
    if (root==NULL)
        return;
    storeBSTNodes(root->left, nodes,i);
    nodes[*i] = root;
    (*i)++;
    storeBSTNodes(root->right, nodes,i);
}

Main_BT balanceTreeUtil(Main_BT nodes[], int start,int end)
{
    if (start > end)
        return NULL;
    int mid = (start + end)/2;
    Main_BT root = nodes[mid];
    root->left  = balanceTreeUtil(nodes, start, mid-1);
    root->right = balanceTreeUtil(nodes, mid+1, end);

    return root;
}
int n=1;
int CountNodes(Main_BT root)
{
	if(root==NULL)
		return 0;
	if(root->left!=NULL)
	{
		n=n+1;
		n=CountNodes(root->left);
	}
	if(root->right!=NULL)
	{
		n=n+1;
		n=CountNodes(root->right);
	}
	return n;
}

Main_BT balanceTree(Main_BT root)
{

    int n = CountNodes(root);
    Main_BT nodes[n];
    int i = 0;
    storeBSTNodes(root, nodes,&i);

    return balanceTreeUtil(nodes, 0, n-1);
}
/**************************************************************************************/
/* 7- Given a dictionary represented as a binary search tree, store the dictionary in a file, further
             ensuring that the words are arranged in alphabetical order*/
char* synonyms_content(BT root,char* content)
{
    if(root == NULL) return content;
    synonyms_content(root->left,content);

    char word[20];
    strcpy(word,root->val);
    strcat(content,word);
    char c[] = ",";
    strcat(content,c);

    synonyms_content(root->right,content);
}

char* FileAddition_Helper(Main_BT root,char* content)
{
    if(root == NULL) return content;
    FileAddition_Helper(root->left,content);

    char word[20];
    strcpy(word,root->val);
    strcat(content,word);
    char space[] = " ";
    strcat(content,space);
    char c[] = "-";
    strcat(content,c);
    strcat(content,space);

    synonyms_content(root->synonyms,content);
    content[strlen(content)-1] = '\0';
    FileAddition_Helper(root->right,content);
}

char* FileAddition(Main_BT root)
{
    char* content = (char*)malloc(20000 * sizeof(char));
    content = FileAddition_Helper(root,content);
}



/***************************************************************************************************/
int main()
{

    printf("welcome to the dictionary app : \n");
    int flag = 1;

    Main_BT Main_root = Main_BTinit();





/************************************************************************************************/
// 2- . Load the dictionary (given as a file) into memory.
     FILE * fp;
    fp = fopen("dictionary.txt", "r");
    if(fp == NULL)
    {
        perror("error:");
    }
    char sentence[2000];
    int j = 0;

    char word[20]="";
    while(fgets(sentence, sizeof(sentence), fp) != NULL)
    {

        int i = 0;

           const char s[] = "- ,";
           char *token;
           token = strtok(sentence, s);

           BT syn = BTinit();

           char temp[20];
           int flag = 0;
           while( token != NULL ) {

              if(flag == 0)
              {
                  strcpy(temp,token);
              }
              else
              {
                  syn = InsertBST(syn,token);
              }

              flag = 1;
              token = strtok(NULL, s);
           }

            Main_root = InsertMain_BST(Main_root,syn,temp);
    }

    fclose(fp);

/************************************************************************************************/




    while(flag)
    {
        int command;
        printf("**************************************************\n");
        printf("please enter one of the following commands : \n");
        printf("1-print the dictionary : \n");
        printf("2-check for a word : \n");
        printf("3-print synonyms of a certain word : \n");
        printf("4-add synonyms to a certain word : \n");
        printf("5-find the word with highest nb of synonyms : \n");
        printf("6-find the words that have a certain synonym : \n");
        printf("7-most repeated word as synonym : \n");
        printf("8-save current dictionary to file : \n");
        printf("9-balance the dictionary \n");
        printf("other-save & exit the program \n");
        printf("**************************************************\n");

        scanf("%d",&command);

        switch(command){
        case 1:
            {
                Main_InOrder(Main_root);
                break;
            }
        case 2:
            {
                char s[20];
                printf("enter the word you want to search for : \n");
                scanf("%s",s);
                printf("%d \n\n",search(Main_root,s));
                break;
            }
        case 3:
            {
                char s[20];
                printf("enter the word whose synonyms you want : \n");
                scanf("%s",s);
                SynonymsOfWord(Main_root,s);
                break;
            }
        case 4:
            {
                char s[20];
                printf("enter the word you want to add a synonym to : \n");
                scanf("%s",s);

                char synonym[20];
                printf("enter the synonym : \n");
                scanf("%s",synonym);

                AddSynonym(Main_root,s,synonym);
                break;
            }

        case 5:
            {
                char res[20];
               printf("the word with most synonyms is : %s \n",most_synonyms_main(Main_root));
                break;
            }
        case 6:
            {
                char s[20];
                printf("enter the synonym : \n");
                scanf("%s",s);
                words_having_synonym(Main_root,s);
                printf("\n\n");
                break;
            }
        case 7:
            {
                printf("the most repeated word as synonym is : %s \n",most_repeated_synonym(Main_root));
                break;
            }
        case 8:
            {
                char* res = FileAddition(Main_root);
                 fp = fopen("newdictionary.txt","w");

                if(fp == NULL)
                {
                    perror("error:");
                }

                fprintf(fp,res);

                fclose(fp);

                printf("file succesfully updated \n");
                break;
            }
        case 9:
            {
                Main_root = balanceTree(Main_root);
                printf("tree succesfully balanced \n");
                n = 1;
                break;
            }
        default:
            {
                printf("\n\nBye!");
                flag = 0;
            }
        }
    }


  

    return 0;
}
