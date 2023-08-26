/*Code Template for Binary Tree taken from https://www.geeksforgeeks.org/tree-traversals-inorder-preorder-and-postorder/
and https://www.geeksforgeeks.org/insertion-in-a-binary-tree-in-level-order/

Code Template for reading word by word is partially taken from https://stackoverflow.com/questions/26477345/using-fgetc-to-read-words
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define STRSIZ 99

struct keyword {
      int occurences;
      char word[STRSIZ];
};

struct node {
    struct keyword wordData;
    struct node* left;
    struct node* right;
};

/* Prototypes */
void printInOrder(struct node* node, int wordAmount);
struct node* newNode(char word1[STRSIZ]);

int main(int argc, char* argv[]){
    
    //Initializing Variables
    char in_name1[STRSIZ];
    FILE *inp1;

    char ch;
    char temp;
    int totalWords = 0;
    int totalLines = 0;

    //Initializing Binary Tree
    struct node* root = newNode("by");
    root->left = newNode("an");
    root->left->left = newNode("a");
    root->left->right = newNode("and");
    root->right = newNode("from");
    root->right->left = newNode("the");
    root->right->right = newNode("to");
    
    printf("Enter name of file you want to analyze> ");
    for  (scanf("%s", in_name1); (inp1 = fopen(in_name1, "r")) == NULL; scanf("%s", in_name1)) {
          printf("Cannot open %s for input\n", in_name1);
          printf("Re enter file name> ");
    }
    //Will check to see if the word has ended, and if it has, it will check to see what the word is
    for  (ch = tolower((char)fgetc(inp1));  ch != EOF;  ch = tolower((char)fgetc(inp1))){
        if (ch == '\n' || ch == '\0' ){
            totalLines += 1;
            totalWords += 1;
            strcpy(&temp, "");
        }
        if(ch == ' ' || ch == '\t' || ch == '.' || ch == ','){
            if (strcmp(&temp, "by") == 0){
                root->wordData.occurences += 1;
            }
            else if (strcmp(&temp, "an") == 0){
                root->left->wordData.occurences += 1;
            }
            else if (strcmp(&temp, "a") == 0){
                root->left->left->wordData.occurences += 1;
            }
            else if (strcmp(&temp, "and") == 0){
                root->left->right->wordData.occurences += 1;
            }
            else if (strcmp(&temp, "from") == 0){
                root->right->wordData.occurences += 1;
            }
            else if (strcmp(&temp, "the") == 0){
                root->right->left->wordData.occurences += 1;
            }
            else if (strcmp(&temp, "to") == 0){
                root->right->right->wordData.occurences += 1;
            }   
            totalWords += 1;
            strcpy(&temp, "");
        } 
        else {
            strncat(&temp, &ch, 2);
        }    

      }

    printInOrder(root, totalWords);
    printf("Total Amount of Lines: %d", totalLines);
    fclose(inp1);
    return (0);
}

/* Given a binary tree, print its nodes in inorder*/
void printInOrder(struct node* node, int wordAmount){
    if (node == NULL)
        return;
 
    /* first recur on left child */
    printInOrder(node->left, wordAmount);
 
    /* then print the data of node */
    double freqper1000 = ((node->wordData.occurences)/((double)wordAmount)) * 1000;
    printf("Frequency per 1000 words of '%s' is: %.2lf\n", node->wordData.word, freqper1000);
 
    /* now recur on right child */
    printInOrder(node->right, wordAmount);
}

/* Helper function that allocates a new node with the
   given data and NULL left and right pointers. */
struct node* newNode(char word1[STRSIZ])
{
    struct node* node
        = (struct node*)malloc(sizeof(struct node));
    strcpy(node->wordData.word, word1);
    node->wordData.occurences= 0;
    node->left = NULL;
    node->right = NULL;
 
    return (node);
}

struct node* search(struct node *root, int x)
{
    if(root==NULL || root->wordData.word==x) //if root->data is x then the element is found
        return root;
    else if(x>root->wordData.word) // x is greater, so we will search the right subtree
        return search(root->right, x);
    else //x is smaller than the data, so we will search the left subtree
        return search(root->left,x);
}