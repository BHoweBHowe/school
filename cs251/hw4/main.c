//left = no overlap with parent, right = overlap with parent

#include <stdio.h>
#include <stdlib.h>

typedef struct line_struct {
    double l_pnt;
    double r_pnt;
    struct line_struct *left;
    struct line_struct *right;
} *LINE;

typedef struct bt_struct {
    LINE root;
} *BT;


void insert_r(LINE root, LINE line) {
    if(root == NULL) {
        root = line;
    }

    if(overlaps(line, root)) {
        insert_r(root->right, line);
    }

    if(overlaps(root, line)) {
        line
    }
}

void insert(BT lines, double left, double right) {
    LINE line = malloc(sizeof(LINE));

    line->l_pnt = left;
    line->r_pnt = right;

    insert_r(lines->root, line);
}


int main() {
    BT lines = malloc(sizeof(BT));

    insert(lines, 2, 6);
}
