//Code Template for Binary Tree taken from https://www.geeksforgeeks.org/tree-traversals-inorder-preorder-and-postorder/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define STRSIZ 2000

//Array contains all files to be analyzed
char fileList[][50] = {"Federalist1.txt", "Federalist2.txt", "Federalist3.txt", "Federalist4.txt", "Federalist41.txt", 
"Federalist42.txt", "Federalist43.txt", "Federalist59.txt", "Federalist60.txt", "Federalist63.txt"};

struct keyword {
      int occurences;
      char word[30];
};

struct node {
    struct keyword wordData;
    struct node* left;
    struct node* right;
};

/* Prototypes */
void printInOrder(struct node* node, int wordAmount, FILE *output);
struct node* newNode(char word1[30]);
struct node* search(struct node *root, char* x);
struct node* insert(struct node *root, char* x);

int main(int argc, char* argv[]){
    
    //Initializing Variables
    char in_name1[STRSIZ];
    FILE *inp1, *outp1;
    char *ch;
    char temp[STRSIZ];
    int totalWords = 0;
    int totalSentences = 0;
    double averageWordLength = 0;
    int amountOfPapers = 10;

    //Creates .csv file to output data
    outp1 = fopen("FederalistPapersData.csv", "w+");
    
    for (int x = 0; x < amountOfPapers; x += 1){
        //Initializing Empty Binary Tree
        struct node* root = NULL;

        inp1 = fopen(fileList[x], "r");
        //Resetting Key Statistics
        totalSentences = 0;
        totalWords = 0;
        averageWordLength = 0;

        //Makes every character lowercase
        while (fgets(temp, STRSIZ, inp1) != NULL){
            for (int i = 0; temp[i]; i += 1){
                temp[i] = tolower(temp[i]);
            }
            
            //Tokenizes the string, and counts the amount of words, sentences, and characters
            ch = strtok(temp, " ,;:\"\xA");
            while (ch != NULL){
                if (ch[strlen(ch)-1] == '.' || ch[strlen(ch)-1] == '?' || ch[strlen(ch)-1] == '!'){
                    totalSentences += 1;
                    ch[strlen(ch)-1] = '\0';
                }
                if (search(root, ch) != NULL){
                    search(root,ch)->wordData.occurences += 1;
                }
                else {
                    root=insert(root, ch);
                }
                totalWords += 1;
                averageWordLength += strlen(ch);
                ch = strtok(NULL, " ,;:\"\xA");
            }
            
        }
        
        //Outputs Key Statistics
        fprintf(outp1, "Data for %s: \n", fileList[x]);
        fprintf(outp1, "Total Sentence Count: %d\n", totalSentences);
        fprintf(outp1, "Total Word Count: %d\n", totalWords);
        fprintf(outp1, "Average Word Length: %.2lf\n", (averageWordLength/(double)totalWords));
        printInOrder(root, totalWords, outp1);
        fprintf(outp1, "-----------------------------------------------------\n");
    }

    
    fclose(inp1);
    fclose(outp1);
    return (0);
}

/* Given a binary tree, print its nodes in inorder*/
void printInOrder(struct node* node, int wordAmount, FILE *output){
    if (node == NULL)
        return;
 
    /* first recur on left child */
    printInOrder(node->left, wordAmount, output);
 
    /* then print the data of node */
    double freqper1000 = ((node->wordData.occurences)/((double)wordAmount)) * 1000;
    fprintf(output, "Frequency per 1000 words of '%s' is: %.2lf\n", node->wordData.word, freqper1000);
 
    /* now recur on right child */
    printInOrder(node->right, wordAmount, output);
}

/* Helper function that allocates a new node with the
   given data and NULL left and right pointers. */
struct node* newNode(char word1[30]){
    struct node* node = (struct node*)malloc(sizeof(struct node));
    strcpy(node->wordData.word, word1);
    node->wordData.occurences= 1;
    node->left = NULL;
    node->right = NULL;
 
    return (node);
}

struct node* search(struct node *root, char* x){
    if(root==NULL || strcmp(root->wordData.word,x) == 0) //if root->data is x then the element is found
        return root;
    else if(strcmp(x, root->wordData.word)> 0) // x is greater, so we will search the right subtree
        return search(root->right, x);
    else //x is smaller than the data, so we will search the left subtree
        return search(root->left,x);
}

struct node* insert(struct node *root, char* x){
    //searching for the place to insert
    if(root==NULL)
        return newNode(x);
    else if(strcmp(x, root->wordData.word)> 0) // x is greater. Should be inserted to right
        root->right = insert(root->right, x);
    else // x is smaller should be inserted to left
        root->left = insert(root->left,x);
    return root;
}