#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INIT_SIZE 5


typedef struct column {
    char *content;
    size_t width;
    size_t cap;
} column;

typedef struct row {
    column *col;
    size_t ncol;
    size_t col_cap;
} row;

typedef struct table {
    size_t nrows;
    size_t row_cap;
    size_t ncols;
    size_t col_cap;
    size_t *max_col_width;
    row *rows;
} table;

void column_all() ;
void fill_row(row *arow_ptr, char *line) ;
void fill_table(FILE *fptr, table *atable_ptr);
void print_row(row arow, size_t ncols, size_t *max_col_width) ;
void print_table(table atable) ;
void free_col(column acol) ;
void free_row(row arow) ;
void free_table(table atable) ;
column init_column() ;
column *init_columns() ;
row init_row() ;
row *init_rows() ;
table init_table();


table init_table(){
    table out;
    out.nrows = 0;
    out.row_cap = INIT_SIZE;
    out.ncols = 0;
    out.col_cap = INIT_SIZE;
    out.max_col_width = malloc(sizeof(size_t) * INIT_SIZE);
    if (out.max_col_width == NULL) {
        fprintf(stdout, "out of memory\n");
        exit(1);
    }
    out.rows = init_rows();
    return(out);
}

row *init_rows() {
    row *out = malloc(sizeof(row) * INIT_SIZE);
    if (out == NULL) {
        fprintf(stdout, "out of memory\n");
        exit(1);
    }
    for (size_t i=0; i<INIT_SIZE; i++){
        out[i] = init_row();
    }
    return(out);
}

row init_row() {
    row out;
    out.ncol = 0;
    out.col_cap = INIT_SIZE;
    out.col = init_columns();
    return(out);
}

column *init_columns() {
    column *out = malloc(sizeof(column) * INIT_SIZE);
    if (out == NULL) {
        fprintf(stdout, "out of memory\n");
        exit(1);
    }
    for (size_t i=0; i<INIT_SIZE; i++){
        out[i] = init_column();
    }
    return(out);
}

column init_column() {
    column out;
    out.width = 0;
    out.cap = INIT_SIZE;
    out.content = malloc(INIT_SIZE * sizeof(char));
    if (out.content == NULL) {
        fprintf(stdout, "out of memory\n");
        exit(1);
    }
    for (size_t i=0; i<INIT_SIZE; i++){
        out.content[i] = '\0';
    }
    return(out);
}

void free_table(table atable) {
    free(atable.max_col_width);
    for (size_t i=0; i<atable.row_cap; i++){
        free_row(atable.rows[i]);
    }
    free(atable.rows);
}

void free_row(row arow) {
    for (size_t i=0; i<arow.col_cap; i++) {
        free_col(arow.col[i]);
    }
    free(arow.col);
}

void free_col(column acol) {
    free(acol.content);
}

void print_table(table atable) {
    printf("nrows: %lu\n", atable.nrows);
    for (size_t i=0; i<atable.nrows; i++) {
        print_row(atable.rows[i], atable.ncols, atable.max_col_width);
    }
}

void print_row(row arow, size_t ncols, size_t *max_col_width) {
    for(size_t i=0; (i < ncols) && (i < arow.ncol); i++) {
        printf("%*s", max_col_width[i]+1, arow.col[i].content);
    }
    printf("\n");
}

void fill_table(FILE *fptr, table *atable_ptr){
    char *line = NULL;
    int rownum = 0;
    size_t size = 0;
    size_t len_read = 0;
    
    while ((len_read = getline(&line, &size, fptr)) != -1) {
        if (rownum >= atable_ptr->row_cap) {
            atable_ptr->rows = realloc(atable_ptr->rows, sizeof(row) * (2 * atable_ptr->row_cap));
            if (atable_ptr->rows == NULL) {
                fprintf(stderr, "out of memory!");
                exit(1);
            }
            for (size_t i=atable_ptr->row_cap; i<(2 * atable_ptr->row_cap); i++){
                atable_ptr->rows[i] = init_row();
            }
            atable_ptr->row_cap = 2 * atable_ptr->row_cap;
        }
        fill_row(&atable_ptr->rows[rownum], line);
        rownum++;
        atable_ptr->nrows = rownum;
    } 
    free(line);
}

void fill_row(row *arow_ptr, char *line) {
        char *token = strtok(line, " 	");
        size_t token_len = 0;
        size_t col_num = 0;
        while (token != NULL) {
            token_len = strlen(token);
            if (arow_ptr->col_cap <= col_num) {
                arow_ptr->col = realloc(arow_ptr->col, sizeof(column) * (2 * arow_ptr->col_cap));
                if (arow_ptr->col == NULL) {
                    fprintf(stderr, "out of memory!");
                    exit(1);
                }
                for (size_t i=arow_ptr->col_cap; i<(2 * arow_ptr->col_cap); i++){
                    arow_ptr->col[i] = init_column();
                }
                arow_ptr->col_cap = 2 * arow_ptr->col_cap;
            }
            if (arow_ptr->col[col_num].cap < (token_len + 1)) {
                arow_ptr->col[col_num].content = realloc(arow_ptr->col[col_num].content, (token_len+1) * sizeof(char));
                if (arow_ptr->col[col_num].content == NULL) {
                    fprintf(stderr, "out of memory!");;
                    exit(1);
                }
                arow_ptr->col[col_num].cap = token_len+1;
            }
            strncpy(arow_ptr->col[col_num].content, token, arow_ptr->col[col_num].cap);
            /*printf("content: %s\n", arow_ptr->col[col_num].content);*/
            
            arow_ptr->col[col_num].width = token_len;
            
            arow_ptr->ncol = col_num;
            token = strtok(NULL, " 	");
            col_num++;
        }
}

void column_all() {
    FILE *fptr = stdin;
    table atable = init_table();
    
    fill_table(fptr, &atable);
    print_table(atable);
    
    free_table(atable);
}

int main(int argc, char *argv[]){
    column_all();
    return(0);
}

/*
#include <stdio.h>

int main() {
    char *line = NULL;
    int findex = 0;
    size_t size;
    
    while (getline(&line, &size, stdin) != -1) {
        findex++;
        if (findex%4 == 1) {
            printf(">%s", line+1);
        }
        if (findex%4 == 2) {
            printf("%s",line);
        }
    } 
    return(0);
}
*/

/*
        nc += strlen(line);
        char *token = strtok(line, " ");
        while (token != NULL)
        {
            nf++;
            token = strtok(NULL, " ");
        }
        nr++;
*/
