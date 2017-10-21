#include <stdio.h>
#include <stdlib.h>
#include "linktable.h"
#include "string.h"

/*CMD functions*/
int help();
int hello();
int add();
int sub();
int quit();

#define CMD_MAX_LEN 128
#define DESC_LEN    1024
#define CMD_NUM     10

char cmd[CMD_MAX_LEN];

/* data struct and its operations */

typedef struct DataNode
{
    tLinkTableNode * pNext;
    char*   cmd;
    char*   desc;
    int     (*handler)();
} tDataNode;

int SearchCondition(tLinkTableNode * pLinkTableNode)
{
    tDataNode * pNode = (tDataNode *)pLinkTableNode;
    if(strcmp(pNode->cmd, cmd) == 0)
    {
        return  SUCCESS;  
    }
    return FAILURE;	       
}

/* find a cmd in the linklist and return the datanode pointer */
tDataNode* FindCmd(tLinkTable * head, char * cmd)
{
    return  (tDataNode*)SearchLinkTableNode(head,SearchCondition);
}

/* show all cmd in listlist */
int ShowAllCmd(tLinkTable * head)
{
    tDataNode * pNode = (tDataNode*)GetLinkTableHead(head);
    while(pNode != NULL)
    {
        printf("%s - %s\n", pNode->cmd, pNode->desc);
        pNode = (tDataNode*)GetNextLinkTableNode(head,(tLinkTableNode *)pNode);
    }
    return 0;
}

int InitMenuData(tLinkTable ** ppLinktable)
{
    *ppLinktable = CreateLinkTable();
    tDataNode* pNode = (tDataNode*)malloc(sizeof(tDataNode));
    pNode->cmd = "help";
    pNode->desc = "show this help list.";
    pNode->handler = help;
    AddLinkTableNode(*ppLinktable,(tLinkTableNode *)pNode);
    pNode = (tDataNode*)malloc(sizeof(tDataNode));
    pNode->cmd = "hello";
    pNode->desc = "say hello to you.";
    pNode->handler = hello; 
    AddLinkTableNode(*ppLinktable,(tLinkTableNode *)pNode);
    pNode = (tDataNode*)malloc(sizeof(tDataNode));
    pNode->cmd = "add";
    pNode->desc = "a+b";
    pNode->handler = add; 
    AddLinkTableNode(*ppLinktable,(tLinkTableNode *)pNode);
    pNode = (tDataNode*)malloc(sizeof(tDataNode));
    pNode->cmd = "sub";
    pNode->desc = "a-b";
    pNode->handler = sub; 
    AddLinkTableNode(*ppLinktable,(tLinkTableNode *)pNode);
    pNode = (tDataNode*)malloc(sizeof(tDataNode));
    pNode->cmd = "quit";
    pNode->desc = "exit cmd";
    pNode->handler = quit; 
    AddLinkTableNode(*ppLinktable,(tLinkTableNode *)pNode);
    return 0; 
}

/* menu program */

tLinkTable * head = NULL;

int main()
{
    InitMenuData(&head); 
   /* cmd line begins */
    while(1)
    {
        printf("Input a cmd number > ");
        scanf("%s", cmd);
        tDataNode *p = FindCmd(head, cmd);
        if( p == NULL)
        {
            printf("This is a wrong cmd!\n ");
            continue;
        }
        printf("%s - %s\n", p->cmd, p->desc); 
        if(p->handler != NULL) 
        { 
            p->handler();
        }
   
    }
}

/*CMD functions*/
int help()
{
	ShowAllCmd(head);
	return 0;
}
int hello()
{
	printf("Hello, I am glad to meet you here.\n");
	return 0;
}
int add()
{
	int a,b,c;
	printf("input a and b:");
	scanf("%d %d",&a,&b);
	c=a+b;
	printf("result is %d\n",c);
	return 0;
}
int sub()
{
	int a,b,c;
	printf("input a and b:");
	scanf("%d %d",&a,&b);
	c=a-b;
	printf("result is %d\n",c);
	return 0;
}
int quit()
{
	exit(0);
}
