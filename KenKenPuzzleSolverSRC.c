/*
 * KEN KEN Puzzle solver
 * Student:Nivedita Manjunath
 * Student ID: 5635379228
 * Course: AI, CSCI561
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>


    /*
     * KEN KEN Puzzle Solution 
     * Two stuctures are going to be used, the Input structure and the tree
     * structure.
     */

    /*
     * The Num variable will hold the total number of 
     * square grids present in the board
     */

    int Num = 0;

    /*
     * Size of the board
     */
    int Matrix_size = 0;


    /*
     * A stucture for the tree
     */

    typedef struct tree *Tree;
    struct tree{
        int index;
        int node_value[1000];
    };

    Tree root_tree;

    /*
     * A struct to hold the input 
     * this will help me in validating and hence
     * defining constraints.
     */

    typedef struct input *Input;
    struct input{
        int value;
        char operation[10];
        int grid[100];
        int cnt;
        Input next;
    };

    Input root;

    /*
     * I will be using a Stack to keep track of the child 
     * nodes, the method used would be a variant of DFS
     * And yes there will be backtracking with the help of this Stack
     */

    typedef struct stack *Stack;

    struct stack{
        Tree T;
        Stack next;
    };

    Stack Sroot = NULL;

    void push_stack(Stack S)
    {

        if(Sroot == NULL) {
            Sroot = S;
            S->next == NULL;
        } else{
            S->next = Sroot;
            Sroot = S;
        }
    }

    Stack pop_stack()
    {
        Stack temp;

        if(Sroot == NULL) { 
            return NULL;
        } else {
            temp = Sroot;
            Sroot = Sroot->next;
            return temp;
        }
    }

    void add_to_stack(Tree T)
    {
        Stack S;
        S = malloc(sizeof(struct stack));
    memset(S, 0, sizeof(struct stack)); 
    S->T = T;
    push_stack(S);
}



/*
 * Add the input node to the file
 */
void add_Input(Input I)
{
    int i;
    Input temp;
    bool first = false;

    /*
     * Finding out the NxN grid
     * This following finds out the 
     * maximum of the grid and hence the N value
     */

    for(i=0; i < I->cnt; i++) {
        if(I->grid[i] > Num) {
            Num = I->grid[i];
        }
    }
    if(root == NULL) {
        I->next = NULL;
        root = I;
        first = true;
    }
    if (!first){
        temp = root;
        while(temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = I;
        I->next = NULL;
    }
}


/*
 * Input File parser
 */

void fill_input(char *in)
{
    Input I;
    int value = 0;
    int grid_value = 0;
    int i;
    I = malloc(sizeof(struct input));
    memset(I, 0, sizeof(struct input));
    while (in != NULL)
    {
        if(strcmp(in,"\n") == 0){
            break;
        }
                
        if(I->value == 0)
        {
            value = atoi(in);
            I->value = value;
        } else if(I->operation[0] == '\0') {
            strcpy(I->operation,in);
        } else if((I->grid[0] == 0) || (I->cnt > 0))
        {
            if(I->cnt == 0)
            {
                grid_value = atoi(in);
                I->grid[0] = grid_value;
                I->cnt++;
            } else {
                grid_value = atoi(in);
                I->grid[I->cnt] = grid_value;
                I->cnt++;
            }
        }

        in = strtok(NULL, " ");
    }
    add_Input(I);
}



int read_input_file(char *file)
{
    FILE *fid;
    char line[80];
    char *tok;
    bool first = true;


    fid = fopen(file, "r");
    if(fid == NULL) {
        return 0;
    }

    //Need to read the file now and lay out the constraint
    while(fgets(line, 80, fid) != NULL)
    {
        /*Using strtok to parse the file
         *plan to put this in an array
         */
        tok = strtok(line," ");
        fill_input(tok);
    }
    
    fclose(fid);
    return 1;
}

void free_input()
{
    Input temp, temp2;
    temp = root;

    while(temp->next != NULL) {
        temp2 = temp;
        temp = temp->next;
        free(temp2);
    }
    
    free(temp);
}


Tree initialize_tree(Tree P)
{
    Tree T;
    int i;

    T = malloc(sizeof(struct tree));
    memset(T, 0, sizeof(struct tree));
    if(P != root_tree){
        for(i = 0; i<= Num; i++) {
            T->node_value[i] = P->node_value[i];
        }
        T->index = P->index + 1;
    }
    return T;
}

/*Their exists 4 operations division, multiplication, addition
 * , and subtraction. There also exist on no operation where the number needs to directly be entered.
 */

bool validate_rows_columns(Tree T, Input temp)
{
    int row; 
    int column;
    int i = 0;

    row = (T->index) / Matrix_size;
    column = (T->index) % Matrix_size;
    i = column;
    /*Check column for conflicts*/
    while(1) {
        if((T->node_value[T->index] == T->node_value[i]) && (T->index != i)) {
            return false;
        } else {
            i = i + Matrix_size;
            if (i > Num) {
                break;
            }
        }
    }

    /*Check row for conflict*/
    i = Matrix_size*row;
    while(1) {
        if(T->node_value[T->index] == T->node_value[i] && (T->index != i)) {
            return false;
        } else {
            i = i + 1;
                if((i/Matrix_size) == (row+1)) {
                return true;
            }
        }
    }
}



bool validation_sub_div(Tree T, Input I, bool div)
{
    int X, Y;
    float res;
    int i;

    for(i = 0; i< I->cnt; i++) {
        if(I->grid[i] == T->index) {
            X = T->node_value[T->index];
        } else {
            Y = I->grid[i];
        }
    }

    if(T->node_value[Y] != 0) {
        if(X > T->node_value[Y]) {
            if(div && (res = ((float)X/(float)T->node_value[Y])) == (float)I->value){
                return true;
            } else if((X - T->node_value[Y]) == I->value){
                return true;
            }
        } else if( div && (res = (float)(T->node_value[Y])/(float)X) == (float)I->value){
            return true;
        } else if((T->node_value[Y] - X) == I->value){
            return true;
        }
        return false;
    }

    return true;
}

bool validation_add_mul(Tree T, Input I, bool mul)
{
    int X, cnt = 0, i, res;
    int array[50];

    for(i = 0; i < I->cnt; i++) {
        if(I->grid[i] == T->index) {
            X = T->node_value[T->index];
        } else {
            array[cnt] = I->grid[i];
            cnt++;
        }
    }
    for(i = 0; i < cnt; i++) {
        if(T->node_value[array[i]] == 0) {
            return true;
        }
    }

    if(mul) { 
        res = 1;
    }else {
        res =0;
    }

    for(i = 0; i < cnt; i++) {
        if(mul) {
            res = res * T->node_value[array[i]];
        } else {
            res = res + T->node_value[array[i]];
        }
    }
    if(mul) {
        res = res * X;
    } else {
        res = res + X;
    }
    if(res == I->value) { 
        return true;
    }
    return false;
}


bool validation_nop(Tree T, Input I)
{
    if(T->node_value[T->index]  == I->value) {
        return true;
    }
    return false;
}


bool validate(Tree T)
{
    Input temp;
    bool found = false;
    int i;

    temp = root;
    while(temp != NULL) {
        for(i = 0; i< temp->cnt; i++) {
            if(temp->grid[i] == T->index) {
               found = true;
               break;
            }
        }
        if(found == true)
            break;
        temp = temp->next;
    }


    if(!validate_rows_columns(T,temp)) {
        return false;
    }

    if(strcmp(temp->operation, "-") == 0){
        if(!validation_sub_div(T,temp, false)){
            return false;
        }
        return true;
    }
    
    if(strcmp(temp->operation,"+") == 0){
        if(!validation_add_mul(T,temp, false)) {
            return false;
        }
        return true;
    }

    if(strcmp(temp->operation,"/") == 0){
        if(!validation_sub_div(T,temp, true)) {
            return false;
        }
        return true;
    }

    if(strcmp(temp->operation,"*") == 0){
        if(!validation_add_mul(T,temp, true)) {
            return false;
        }
        return true;
    }

    if(strcmp(temp->operation,".") == 0){
        if(!validation_nop(T, temp)) {
            return false;
        }
        return true;
    }
    return false;
}

/*
 * Expansion of the parent node
 * Each child will be verified 
 * the rightmost valid child will be 
 * expanded
 */

Tree Parent_node(Tree T)
{
    Tree child[30];
    int i, j;
    bool result = false;

    for(i = 1; i<= Matrix_size; i++){
        child[i] = initialize_tree(T);
        if(T == root_tree) {
            child[i]->node_value[T->index] = i;
        } else {
            child[i]->node_value[T->index + 1] = i;
        }
        result = validate(child[i]);
        if(result && (child[i]->index == Num))
        {
            free(T);
            return child[i];
        }
        if(result) {
            add_to_stack(child[i]);
        } else {
            free(child[i]);
        }
    }
    if(T != root_tree){
        free(T);
    }
    return NULL;
}

/*
 * Display to a given output
 * file
 */
void print(Tree T, char *file)
{
    int i = 0, j;
    FILE *fid;
    fid = fopen(file, "a+");
    fprintf(fid,"\n");
    while(i <= Num) {
        for(j = 0; j < Matrix_size; j++) {
            fprintf(fid,"%d ", T->node_value[i]);
            i++;
        }
        fprintf(fid,"\n");
    }
    fclose(fid);
}

/*
 * need to carry out depth first search
 */
void create_tree(char *file)
{
    Tree T;
    Stack q;

    root_tree = initialize_tree(NULL);
    T = root_tree;
    T->index = 0;
    do{
        T = Parent_node(T);
        if(T != NULL) {
            print(T, file);
            free(T);
        }
        q = pop_stack();
        if(q == NULL) {
            return;
        }
        T = q->T;
        free(q);
    }while(T != NULL);
}



/*
 * This would be the main function which would 
 * put the constraints on the game. The four main 
 * function which this function would be handling are
 * "+,-,*,/,and ."
*/

int main(int argc, char *argv[])
{
    int res;
    if(argc > 2) {
        res = read_input_file(argv[1]);
        if(!res) {
            printf("Input file does not exist, please provide an input file \n");
            return;
        }
    } else {
        printf(" Input file  or the Output file missing \n");
        return 0;
    }
    Matrix_size = sqrt(Num+1);
    create_tree(argv[2]);
    free_input(root);
    free(root_tree);
    return 0;
}

