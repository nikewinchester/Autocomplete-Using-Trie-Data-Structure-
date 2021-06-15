#include<stdio.h>
#include<malloc.h>
#include<stdbool.h>
#include<string.h>
#include <stdlib.h>
#include<conio.h>

int WordCount;

struct node
{
    char ch;
    struct node* character[26];
    bool EndOfWord;
}*root,*temp,*NewNode;

void createNode(char c,int t)
{
    NewNode = (struct node*)malloc(sizeof(struct node));
    NewNode->ch = c;
    int i;
    for(i=0;i<26;i++)
    {
        NewNode->character[i] = NULL;
    }
    temp->character[t] = NewNode;
    temp = NewNode;
}

void insertWord(char word[100],int LetterCount,int StringLength)
{
    char c = word[LetterCount];
    int t;
    t =0;
    t = ((int)c) - 97;
    if(temp->character[t]==NULL)
    {
        createNode(c,t);
        if(LetterCount<StringLength-1)
        {
            insertWord(word,LetterCount+1,StringLength);
        }
        else
        {
            temp->EndOfWord = true;
            temp = root;
        }
    }
    else
    {
        temp = temp->character[t];
        if(LetterCount<StringLength-1)
        {
            LetterCount = LetterCount +1;
            insertWord(word,LetterCount,StringLength);
        }
        else
        {
            temp->EndOfWord = true;
            temp = root;
        }
    }
}

bool isLastNode()
{
    int i;
    for(i = 0; i < 26; i++)
    {
        if(temp->character[i]!=NULL)
        {
            return false;
        }
    }
    return true;
}

char* substring(char *destination, const char *source, int beg, int n)
{
	while (n > 0)
	{
		*destination = *(source + beg);
		destination++;
		source++;
		n--;
	}
	*destination = '\0';
	return destination;
}

void suggestWords(struct node* temp, char word[100],int StringLength)
{
    if(WordCount>9)
    {
        return;
    }
    char word2[100];
    strcpy(word2,word);
    if(temp->EndOfWord == true)
    {
        substring(word,word,0,StringLength);
        printf("\n%s",word);
        WordCount++;
    }
    if(isLastNode()==true)
    {
        return;
    }
    int i;
    for(i = 0; i < 26; i++)
    {
        if(temp->character[i])
        {
            char append;
            append = (char)(i+97);
            word2[StringLength]= append;
            suggestWords(temp->character[i],word2,StringLength+1);
        }
    }
}

void searchWord(char words[100],int StringLength,char words2[2000], int StringLength2)
{
    if(StringLength2!=0)
    printf("\n\nEnter Sentence:\n%s",words2);
    char c = getche();
    system("cls");

    if((int)c != 13)
    {
        words[StringLength] = c;
        words2[StringLength2] = c;
    }

    if((int)c == 32)
    {
        memset(words, '\0', 100);
        StringLength = 0;
        temp = root;
        searchWord(words,StringLength,words2,StringLength2+1);
    }

    else
    {
        int t;
        if((int)c < 97)
        {
            t = ((int)c) - 65;
        }
        else
        {
            t = ((int)c) - 97;
        }
        if(temp->character[t]== NULL && (int)c!=13)
        {
            printf("\nNo suggestions found\n");
            searchWord(words,StringLength+1,words2,StringLength2+1);
        }
        else
        {
            if((int)c != 13)
            {
                temp = temp->character[t];
                WordCount = 0;
                printf("\nSuggested Words: \n");
                suggestWords(temp,words,StringLength+1);
                searchWord(words,StringLength+1,words2,StringLength2+1);
            }
            else
            {
                WordCount = 0;
                printf("\nEntered Sentence:\n%s\n",words2);
                printf("\nSuggested Words: \n");
                suggestWords(temp,words,StringLength);
            }
        }
    }
}

int main()
{
    root = (struct node*)malloc(sizeof(struct node));
    int i;
    int StringLength;
    for(i=0;i<26;i++)
    {
        root->character[i] = NULL;
    }
    char word[100];
    char word2[100];
    FILE *fptr;
    if ((fptr = fopen("EnglishWords.txt", "r")) == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }
    else
    {

        while(fscanf(fptr,"\n%s",word)!=0 && strcmp(word, "endoffile")!=0)
        {
            fopen("EnglishWords.txt", "r"); //
            strcpy(word2,word);
            temp = root;
            StringLength = strlen(word2);
            insertWord(word2,0,StringLength);
        }
    }
    printf("\nenter 1 to search for word or enter 0 to exit: ");
    int r;
    scanf("%d",&r);
    while(r==1)
    {
        char words[100];
        char words2[2000];
        memset(words, '\0', sizeof words);
        memset(words2, '\0', sizeof words2);
        system("cls");
        printf("\nEnter Sentence:\n");
        searchWord(words,0,words2,0);
        temp = root;
        memset(words, '\0', sizeof words);
        printf("\n\nenter 1 to search for word or enter 0 to exit:");
        scanf("%d",&r);
    }
}
