//
//  main.c
//  pattern
//
//  Created by Haodan Tan on 9/29/21.
//

#include <stdio.h>

// declare the function

// compute the new u_ij and v_ij for each element
void computeNewValue(double* u, double* v, double* res, int i, int j, int p);

// update the updated whole 50 * 50 grid
void buildNewGrid(double* u_val, double* v_val, int p);

// exact 11 * 11 grid and print the X graph based on specific condition
void printXgraph(double* v_val);



int main(int argc, const char * argv[]) {
    int p = 0;
    if (argc == 1){
        p = 1;
    }


    // initial the grid
    double u_val[51*51] = {0};     // Set every element into 0
    double v_val[51*51] = {0};     // Set every element into 0
    
    
    // initial the u_val and v_val
    for (int i = 0; i < 51; i++){
        for (int j = 0; j < 51; j++){
            if ((i >= 10 && i <= 20) && (j >=10 && j<= 20)){
                v_val[i*51 + j] = 1;
            }
            
            else{
                u_val[i*51 + j] = 1;
            }
        }
    }
    
    
    // iterative 10000 times
    int time = 0;
    while (time < 10000){
        buildNewGrid(u_val, v_val, p);
        time ++;
    }
    
    printXgraph(v_val);
    
}


// compute the new u_ij, and v_ij
void computeNewValue(double* u, double* v,double* res, int i, int j, int p){
    double f = 0.05;
    double k = 0.063;
    double r_u = 0.21;
    double r_v = 0.105;
    double x = 1.6;
    double t = 0.5;
    
    double u_ori = u[51*i+j];
    double v_ori = v[51*i+j];
    double u_rowPlus,u_rowMinus, u_colPlus, u_colMinus;
    double v_rowPlus,v_rowMinus, v_colPlus, v_colMinus;
    
    // find the elements around grid(i,j)
    // control the upper bound (i-1, j)
    if (p == 1) {
        if (i == 0){
            u_rowMinus = u[51 + j];     // update the bound to the first second row (1, j)
            v_rowMinus = v[51 + j];
        }
        else{
            u_rowMinus = u[51 * (i-1) + j];
            v_rowMinus = v[51 * (i-1) + j];
        }
        
        // control the floor bound
        if (i == 51 - 1){
            u_rowPlus = u[51 * (i-1) + j];     // update the bound to the last second row (n - 2, j)
            v_rowPlus = v[51 * (i-1) + j];
        }
        else{
            u_rowPlus = u[51 * (i+1) + j];
            v_rowPlus = v[51 * (i+1) + j];
        }
        
        // control the right bound
        if (j == 51 - 1){
            u_colPlus = u[51 * i + (51 - 2)];     // update the bound to the last second column (i, n - 2)
            v_colPlus = v[51 * i + (51 - 2)];
        }
        else{
            u_colPlus = u[51 * i + (j + 1)];
            v_colPlus = v[51 * i + (j + 1)];
        }
        
        // control the left bound
        if (j == 0){
            u_colMinus = u[51 * i + 1];     // update the bound to the first second column (i, 1)
            v_colMinus = v[51 * i + 1];
        }
        else{
            u_colMinus = u[51 * i + (j - 1)];
            v_colMinus = v[51 * i + (j - 1)];
        }
    }
    
    else {
        // find the elements aroung grid(i,j) by peri
        // control the upper bound (i-1, j)
        if (i == 0){
            u_rowMinus = u[51 * 50 + j];     // update the bound to the first second row (1, j)
            v_rowMinus = v[51 * 50 + j];
        }
        else{
            u_rowMinus = u[51 * (i-1) + j];
            v_rowMinus = v[51 * (i-1) + j];
        }
        
        // control the floor bound
        if (i == 51 - 1){
            u_rowPlus = u[j];     // update the bound to the last second row (n - 2, j)
            v_rowPlus = v[j];
        }
        else{
            u_rowPlus = u[51 * (i+1) + j];
            v_rowPlus = v[51 * (i+1) + j];
        }
        
        // control the right bound
        if (j == 51 - 1){
            u_colPlus = u[51 * i];     // update the bound to the last second column (i, n - 2)
            v_colPlus = v[51 * i];
        }
        else{
            u_colPlus = u[51 * i + (j + 1)];
            v_colPlus = v[51 * i + (j + 1)];
        }
        
        // control the left bound
        if (j == 0){
            u_colMinus = u[51 * i + 50];     // update the bound to the first second column (i, 1)
            v_colMinus = v[51 * i + 50];
        }
        else{
            u_colMinus = u[51 * i + (j - 1)];
            v_colMinus = v[51 * i + (j - 1)];
        }
    }
    
    
    
    
    
    res[0] = u_ori + t * (f * (1 - u_ori) - u_ori * (v_ori) * (v_ori) + r_u * ((u_rowPlus + u_rowMinus + u_colMinus + u_colPlus - 4 * u_ori)/(x * x)));
    
    res[1] = v_ori + t * (u_ori * v_ori * v_ori - (f + k) * v_ori + r_v * ((v_rowPlus + v_rowMinus + v_colMinus + v_colPlus - 4 * v_ori)/(x * x)));
    
}



void buildNewGrid(double* u_ori, double* v_ori, int p){
    double u_new[51*51] = {0};
    double v_new[51*51] = {0};
    double res[2] = {0};
    for(int i = 0; i<51;i++){
        for (int j =0;j<51;j++){
            computeNewValue(u_ori, v_ori, res,  i, j, p);
            u_new[i * 51 + j] = res[0];
            v_new[i * 51 + j] = res[1];
        }
    }
    
    // put the u_new and v_new to the original u and v
    for (int i = 0; i < 51 * 51; i++){
        double tmp = u_ori[i];
        double tmp1 = v_ori[i];
        u_ori[i] = u_new[i];
        v_ori[i] = v_new[i];
        u_new[i] = tmp;
        v_new[i] = tmp1;
    }

    
}



// pring the "X" graph
void printXgraph(double* v_val){
    // print 11 * 11 grid X graph
    for (int i = 0; i <= 50 ; i++){
        for (int j = 0; j <= 50; j++){
            if (v_val[51 * i + j] >= 0.25) {
//                printf("%.2f",v_val[51*i + j]);
                printf("X");
            }
            else{
                printf(" ");
            }
        }
        printf("\n");
    }
    
}


