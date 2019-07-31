#include <stdio.h>
#include <stdlib.h>
#define INIT_SIZE 5

struct column {
    char *content;
    size_t width;
    size_t cap;
}

struct row {
    column *col;
    size_t ncol;
    size_t col_cap;
} row;

struct table {
    size_t nrows;
    size_t row_cap;
    size_t ncols;
    size_t col_cap;
    size_t *max_col_width;
    row *rows;
} table;

table init_table(){
    table out;
    out.nrows = 0;
    out.row_cap = INIT_SIZE;
    out.ncols = 0;
    out.col_cap = INIT_SIZE;
    out.max_col_width = malloc(sizeof(size_t) * INIT_SIZE)
    if (out.max_col_width == NULL) {
        fprintf(stdout, "out of memory\n");
        exit(1);
    }
    rows = init_rows();
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
    out.cap = INIT_SIZE;
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
    out.content = malloc(INIT_SIZE * sizeof(char))
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
    free(atable.max_col_widths)
    for (size_t i=0; i<atable.row_cap; i++){
        free_row(atable.rows[i]);
    }
    free(atable.rows);
}

void free_row(row arow) {
    for (i=0; i<arow.col_cap; i++) {
        free_col(arow.col[i]);
    }
    free(arow.col);
}

void free_col(column acol) {
    free(acol.content);
}

void column() {
    FILE *fptr = stdin;
    table atable = init_table();
    
    fill_table(fptr, &atable);
    print_table(atable);
    
    free_table(atable);
}

int main(int argc, char *argv[]){
    column();
    return(0);
}
