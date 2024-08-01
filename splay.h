// splay.h

#ifndef SPLAY_H
#define SPLAY_H

struct node {
    int val;
    struct node *parent;
    struct node *left;
    struct node *right;
};

typedef struct SplayTree {
    struct node *root;
} SplayTree;

void SplayTree_print(struct SplayTree* self);
struct node* SplayTree_insert(struct SplayTree* self, int val);
struct node* SplayTree_search(struct SplayTree* self, int val);
struct node* SplayTree_delete(struct SplayTree* self, int val);
void SplayTree_destroy(struct SplayTree *self);
SplayTree *SplayTree_create();

#endif // SPLAY_H