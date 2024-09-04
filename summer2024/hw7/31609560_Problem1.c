#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 4
#define NxN (N*N)
#define TRUE 1
#define FALSE 0

struct node {
    int tiles[N][N];
    int f, g, h;
    short zero_row, zero_column;
    struct node *next;
    struct node *parent;
};

int goal_rows[NxN];
int goal_columns[NxN];
struct node *start,*goal;
struct node *open = NULL, *closed = NULL;
struct node *succ_nodes[4];

void print_a_node(struct node *pnode) {
    int i,j;
    for (i=0;i<N;i++) {
        for (j=0;j<N;j++)
            printf("%2d ", pnode->tiles[i][j]);
        printf("\n");
    }
    printf("\n");
}

struct node *initialize(char **argv){
    int i,j,k,index, tile;
    struct node *pnode;

    pnode=(struct node *) malloc(sizeof(struct node));
    index = 1;
    for (j=0;j<N;j++)
        for (k=0;k<N;k++) {
            tile=atoi(argv[index++]);
            pnode->tiles[j][k]=tile;
            if(tile==0) {
                pnode->zero_row=j;
                pnode->zero_column=k;
            }
        }
    pnode->f=0;
    pnode->g=0;
    pnode->h=0;
    pnode->next=NULL;
    pnode->parent=NULL;
    start=pnode;
    printf("initial state\n");
    print_a_node(start);

    pnode=(struct node *) malloc(sizeof(struct node));
    goal_rows[0]=3;
    goal_columns[0]=3;

    for(index=1; index<NxN; index++){
        j=(index-1)/N;
        k=(index-1)%N;
        goal_rows[index]=j;
        goal_columns[index]=k;
        pnode->tiles[j][k]=index;
    }
    pnode->tiles[N-1][N-1]=0;
    pnode->f=0;
    pnode->g=0;
    pnode->h=0;
    pnode->next=NULL;
    goal=pnode;
    printf("goal state\n");
    print_a_node(goal);

    return start;
}

void merge_to_open() {
    for(int i = 0; i < N; i++){
        if(succ_nodes[i] == NULL){
            continue;
        }
        struct node *insert = (struct node *) malloc(sizeof(struct node));
        memcpy(insert->tiles, succ_nodes[i]->tiles, NxN*sizeof(int));
        insert->f = succ_nodes[i]->f;
        insert->g = succ_nodes[i]->g;
        insert->h = succ_nodes[i]->h;
        insert->zero_row = succ_nodes[i]->zero_row;
        insert->zero_column = succ_nodes[i]->zero_column;
        insert->parent = succ_nodes[i]->parent;

        if (open == NULL)
        {
            open = insert;
            continue;
        }

        struct node *temp = open;

        int inserted = FALSE;

        while(temp != NULL && temp->next != NULL){
            if(insert->f < temp->next->f){
                insert->next = temp->next;
                temp->next = insert;
                inserted = TRUE;
                break;
            }
            temp = temp->next;
        }

        if(inserted == FALSE){
            temp->next = insert;
        }

    }

}

void swap(int row1,int column1,int row2,int column2, struct node * pnode){
    pnode->tiles[row1][column1] += pnode->tiles[row2][column2];
    pnode->tiles[row2][column2] = pnode->tiles[row1][column1] - pnode->tiles[row2][column2];
    pnode->tiles[row1][column1] -= pnode->tiles[row2][column2];
}

int heursitic(int entry, int row, int col){
    if(entry == 0){
        return 0;
    }
    for(int i = 0; i < NxN; i++){
        for(int j = 0; j < NxN; j++){
            if(goal->tiles[i][j] == entry){
                return abs(row - i) + abs(col - j);
            }
        }
    }
}


void update_fgh(struct node *pnode){
    if(pnode->parent != NULL){
        pnode->g = pnode->parent->g + 1;
    }else{
        pnode->g = 1;
    }

    int h2 = 0;
    for(int i = 0; i < NxN; i++){
        for(int j = 0; i < NxN; i++){
            h2 += heursitic(pnode->tiles[j][i], j, i);
        }
    }
    pnode->h = h2;
    pnode->f = pnode->g + pnode->h;
}



void move_down(struct node * pnode){
    if(pnode->zero_row+1 < N){
        swap(pnode->zero_row, pnode->zero_column, pnode->zero_row+1, pnode->zero_column, pnode);
        pnode->zero_row++;
    }else{
        pnode = NULL;
    }
}

void move_right(struct node * pnode){
    if(pnode->zero_column+1 < N){
        swap(pnode->zero_row, pnode->zero_column, pnode->zero_row, pnode->zero_column+1, pnode);
        pnode->zero_column++;
    }else{
        pnode = NULL;
    }
}

void move_up(struct node * pnode){
    if(pnode->zero_row-1 > -1){
        swap(pnode->zero_row, pnode->zero_column, pnode->zero_row-1, pnode->zero_column, pnode);
        pnode->zero_row--;
    }else{
        pnode = NULL;
    }

}

void move_left(struct node * pnode){
    if(pnode->zero_column-1 > -1) {
        swap(pnode->zero_row, pnode->zero_column, pnode->zero_row, pnode->zero_column - 1, pnode);
        pnode->zero_column--;
    }else{
        pnode = NULL;
    }
}


void expand(struct node *selected) {
    for(int i = 0; i < N; i++){
        succ_nodes[i] = (struct node *) malloc(sizeof(struct node));
        memcpy(succ_nodes[i]->tiles, selected->tiles, NxN*sizeof(int));
        succ_nodes[i]->zero_row = selected->zero_row;
        succ_nodes[i]->zero_column = selected->zero_column;
        succ_nodes[i]->parent = selected;

    }

    move_down(succ_nodes[0]);
    move_right(succ_nodes[1]);
    move_up(succ_nodes[2]);
    move_left(succ_nodes[3]);

    for(int i = 0; i < N; i++){
        update_fgh(succ_nodes[i]);
    }
}

int nodes_same(struct node *a,struct node *b) {
    int flg=FALSE;
    if (memcmp(a->tiles, b->tiles, sizeof(int)*NxN) == 0)
        flg=TRUE;
    return flg;
}

void filter(int i, struct node *pnode_list){
    if(pnode_list == NULL || succ_nodes[i] == NULL){
        return;
    }
    struct node *temp = pnode_list;
    while(temp != NULL){
        if(nodes_same(succ_nodes[i], temp)){
            succ_nodes[i] = NULL;
            return;
        }
        temp = temp->next;
    }
}

int main(int argc,char **argv) {
    int i, iter, pathlen = 0;
    struct node *copen, *solution_path;

    solution_path = NULL;
    start = initialize(argv);
    open = start;
    iter = 0;
    while (open != NULL) {
        copen = open;
        open = open->next;
        if(nodes_same(copen, goal)){
            do{
                copen->next = solution_path;
                solution_path = copen;
                copen = copen->parent;
                pathlen++;
            } while(copen != NULL);
            printf("Path (length = %d):\n", pathlen);
            do{
                print_a_node(solution_path);
                solution_path = solution_path->next;
            }while(solution_path != NULL);
            break;
        }
        expand(copen);
        for(i = 0; i<4; i++){
            filter(i, open);
            filter(i, closed);
        }
        merge_to_open();
        copen->next = closed;
        closed = copen;

        iter++;
        if(iter % 1000 == 0){
            printf("iter %d\n", iter);
        }
    }
    return 0;
}
