#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////Test 2007 ALGORITHMS 1///////////////////////////
//////////////////////////////////////////////////////////////////////////////////


///////////////////////q1///////////////////
/**
 * question number 1:
 * longest monotonic sub sequence:
 * the algo works in
 *      n(n-1)/2 => O(n^2)
 * @param str
 * @param str_len
 * @return
 */
int* longestSubSequance(int* str,int str_len )
{

    int count[str_len];
    for (int i = 0; i < str_len; ++i) { count[i] = 1; }
    ////////////////////////////////////////////////////
    int temp_size=-1;
    for (int j = 1; j < str_len; j++) {
        int i = 0;
        while (i < j) {
            if (*(str + i) <= *(str + j))
            {
                if (count[j] <= count[i])
                {
                    count[j] = count[i] + 1;
                }
            }
            ++i;
        }
        if (temp_size < count[j]) {
            temp_size = count[j];
        }
    }
        return temp_size;
}

///////////////////////q1-end///////////////////

///////////////////////q2///////////////////
/**
 *
 * question number 2:
 * calc x^n
 * the algo works in
 *      (O)log(n)
 * @param x
 * @param n
 * @return
 */
int power_logn(int x, int n){

    int R = 1;
    while(n!=0)
    {
        if(n%2!=0)
        {
            R=R*x;
        }
        n=n/2;
        x=x*x;
    }

   return R;
}
///////////////////////q2-end///////////////////


/**
 * question number 3:
 * airoplain problem:
 *      O(n*m) ~ O(n^2)
 */
///////////////////////q3///////////////////
typedef struct Node{
    int right;
    int down;
    int value;
    int count;
    char path[100];
    char Id;
} Node, *pNode;

void shortpath_airplain(Node mat[],int row,int col){

//  fill row 0

  for (int j = 1; j < row ; ++j) {
        Node *temp1 = mat+((j-1)*col);
        Node *temp2 = mat+(j*col);
        temp2->value = temp1->down+temp1->value;


    }
//fill col 0
    for (int j = 1; j < col ; ++j) {
        Node *temp1 = mat+((j-1));
        Node *temp2 = mat+(j);
        temp2->value = temp1->right+temp1->value;
    }

    for (int i = 1; i < row ; ++i)
    {
        for (int j = 1; j < col; ++j)
        {
            Node *temp      = mat+(((i)*row)+j)  ;//working node
            Node *temp1     = mat+((i-1)*row+j)  ;//from above
            Node *temp2     = mat+((i)*row+j-1)   ;//from the left hand side
            int value_and_down  =       temp1->value+temp1->down;
            int value_and_right =       temp2->value+temp2->right;
            if(value_and_down > value_and_right)
            {   temp->value = value_and_right;

            } else {
                temp->value = value_and_down;
            }
        }
    }

    Node *temp4 = mat+(row*col-1)  ;//working node
    char short_path[100];   int value =1; int i=row-1; int j=col-1;
                            int loc =row*col-1;
    char ch = ',';
    sprintf( short_path, "%d",temp4->value );
    strncat(short_path, &ch, 1);
    ch=temp4->Id;
    strncat(short_path, &ch, 1);

    while(value!=0){

        int i_l =row-i-1; int j_l =col-j-1;

        if(i != 0 && j != 0){

            Node *temp1 = mat+loc-col; // above
            Node *temp2 = mat+loc-1;   // left
            if((temp1->value + temp1->down)< (temp2->value+ temp2->right))
            {
                strncat(short_path, &temp1->Id,1);
                i=i-1; value=temp1->value; loc = loc-col;
            }else{
                strncat(short_path, &temp2->Id,1);
                j=j-1; value=temp2->value; loc = loc-1;
            }

        }
        else if( j == 0){
            Node *temp1 = mat+loc-col; // above
            strncat(short_path, &temp1->Id,1);
            i=i-1; value=temp1->value; loc = loc-col;
        }
        else if( i == 0){
            Node *temp2 = mat+loc-1;   // left
            strncat(short_path, &temp2->Id,1);
            j=j-1; value=temp2->value; loc = loc-1;
        }

    }

    char end = '\0';
    strncat(short_path, &end,1);
    printf("\n %s",short_path);

}
///////////////////////q3-end///////////////////

/**
 * question number 4:
 * pyramid game || numbers game (against the best player in the world)
 *
 *              O(n^2) -> O(n^2-3n+2)
 */
///////////////////////q4///////////////////
typedef struct NodeLoc{
    int id;
    int val;
    int previd;
    int initVal;
}NodeLoc, *pNodeloc;
void PyramidGame(int n , int *numbers){

    NodeLoc mat[n][n];

    int j = 0; int counter=(n*(n+1))/2;
    for(int i = n-1; i>=0; --i){
        for(int j = i; j >= 0 ; --j){

            NodeLoc           temp1;
            temp1.id        = (i)*n + j;
            temp1.val       = *(numbers+counter-1);
            temp1.initVal   = *(numbers+counter-1);
            mat[i][j]       = temp1;
            counter--;
        }
    }

    for (int i = n-2; i >= 0 ; --i) { // row
        for (int j = 0; j <= i ; ++j) { // col
            mat [i][j]; // current position
            mat[i+1][j]; // left child
            mat[i+1][j+1]; // right child

            int left_and_root = mat [i][j].val + mat[i+1][j].val;
            int right_and_root = mat [i][j].val + mat[i+1][j+1].val;

            if(left_and_root > right_and_root){
                mat [i][j].val = left_and_root;
                mat [i][j].previd = mat[i+1][j].id;
            }else{
                mat [i][j].val = right_and_root;
                mat [i][j].previd = mat[i+1][j+1].id;
            }
        }
    }
    int temp=0;
    int prev=0;
    char path[n+1];
    for (int k = 0; k <=n-1  ; ++k) {
        if(k==0){
            sprintf( &path[k], "%d", mat[0][0].initVal);
            prev = mat[0][0].previd;
        }else{
            prev = prev%n;
            temp =  mat[k][prev].previd;
            sprintf( &path[k], "%d", mat[k][prev].initVal);

            prev = temp;
        }
    }


    char end = '\0';
    strncat(path, &end,1);
    printf("%s",path);
}


///////////////////////q4-end///////////////////

    int main() {
////////////////////////////////////////////////
//////////////question 1////////////////////////
///////////////////////////////////////////////

//        printf("Enter variables");
//        int *str_ptr = (int*)malloc(sizeof(int)*1);
//        int num; int i=1;
//
//        while (scanf("%d",&num)!=0)
//        {
//            str_ptr = realloc(str_ptr,i* sizeof(int));
//            *(str_ptr+(i-1))=num;
//            i++;
//        }
//
//        int size = i;
//        int res = longestSubSequance(str_ptr, size);
//        printf("%d", res);


////////////////////////////////////////////////
/////////////question 2/////////////////////////
///////////////////////////////////////////////

//    int x,n;
//    printf("enter x \n");
//    scanf("%d", &x);
//    printf("enter n \n");
//    scanf("%d", &n);
//
//    int ans = power_logn(x,n);
//
//    printf("\n%d",ans);

////////////////////////////////////////////////
/////////////question 3/////////////////////////
///////////////////////////////////////////////


//    Node a;    Node b;    Node c;    Node d;
//
//    Node e;    Node f;    Node g;    Node h;
//
//    Node i;    Node j;    Node k;    Node l;
//
//    Node m;    Node n;    Node o;    Node p;
//
//        a.down=1; a.right=1; a.count=0; a.Id='a';        b.down=1; b.right=2; b.count=0; b.Id='b';
//        c.down=2; c.right=2; c.count=0; c.Id='c';        d.down=2; d.right=2; d.count=0; d.Id='d';
//        e.down=3; e.right=3; e.count=0; e.Id='e';        f.down=3; f.right=2; f.count=0; f.Id='f';
//        g.down=4; g.right=4; g.count=0; g.Id='g';        h.down=4; h.right=2; h.count=0; h.Id='h';
//        i.down=5; i.right=5; i.count=0; i.Id='i';        j.down=5; j.right=2; j.count=0; j.Id='j';
//        k.down=6; k.right=6; k.count=0; k.Id='k';        l.down=6; l.right=2; l.count=0; l.Id='l';
//        m.down=7; m.right=7; m.count=0; m.Id='m';        n.down=7; n.right=2; n.count=0; n.Id='n';
//        o.down=8; o.right=8; o.count=0; o.Id='o';        p.down=8; p.right=2; p.count=0; p.Id='p';
//
//
//    a.value=0;b.value=0;c.value=0;d.value=0;
//    e.value=0;f.value=0;g.value=0;h.value=0;
//    i.value=0;j.value=0;k.value=0;l.value=0;
//    m.value=0;n.value=0;o.value=0;p.value=0;
//
//
//        Node mat[4][4] = {a,b,c,d,
//                          e,f,g,h,
//                          i,j,k,l,
//                          m,n,o,p};
//        int col=4;        int row=4;
//        char pathing[100];
//        char * ptr = &pathing;
//        shortpath_airplain(mat,col,row);
//        printf("%s",*ptr);
//

////////////////////////////////////////////////
/////////////question 4/////////////////////////
///////////////////////////////////////////////


    int numbers [15] ={5,5,4,2,1,8,1,7,4,3,1,1,1,1,20};
    int *num_ptr = numbers;
        PyramidGame(5,num_ptr);


        return 0;
    }
