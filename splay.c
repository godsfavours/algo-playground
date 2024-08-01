// splay.c
#include "splay.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

struct SplaySplitNodes {
    struct node *left;
    struct node *right;
};

static void SplayTree_rotate_right(struct node *n);
static void SplayTree_rotate_left(struct node *n);
static void SplayTree_splay(struct SplayTree* t, struct node *n);
static struct SplaySplitNodes SplayTree_split(struct SplayTree* tree, int val);
static void SplayTree_join(struct node *n);


SplayTree *SplayTree_create() {
    SplayTree* tree = (struct SplayTree *)malloc(sizeof(struct SplayTree));
    tree->root = NULL;
    return tree;
}

static void SplayTree_print_helper(struct node *current) {
    if (current == NULL) {
        printf("()");
        return;
    }

    printf("( ");
    SplayTree_print_helper(current->left);

    printf(" <- ");
    printf("%d", current->val);
    printf(" -> ");
    SplayTree_print_helper(current->right);
    printf(" )");
}

void SplayTree_print(struct SplayTree* self) {
    SplayTree_print_helper(self->root);
    printf("\n");
}


struct node* SplayTree_search_helper(struct SplayTree* self, struct node *current, int val) {
        if (current == NULL)
            return NULL;

        if (val == current->val) {
            SplayTree_splay(self, current);
            return current;
        }

        struct node *c = val <= current->val ? current->left : current->right;
        if (c == NULL) {
            SplayTree_splay(self, current);
            return NULL;
        }

        return SplayTree_search_helper(self, c, val);
}


struct node* SplayTree_search(struct SplayTree* self, int val) {
    return SplayTree_search_helper(self, self->root, val);
}

static struct node* SplayTree_insert_helper(struct SplayTree* t, int val, struct node **current, struct node *parent) {
    if (*current == NULL) {
        *current = (struct node *)malloc(sizeof(struct node));
        (*current)->val = val;
        (*current)->left = NULL;
        (*current)->right = NULL;
        (*current)->parent = parent;

        SplayTree_splay(t, *current);
        return *current;
    }

    if (val <= (*current)->val)
        return SplayTree_insert_helper(t, val, &(*current)->left, *current);
    else
        return SplayTree_insert_helper(t, val, &(*current)->right, *current);
}


struct node* SplayTree_insert(struct SplayTree* self, int val) {
    return SplayTree_insert_helper(self, val, &(self->root), NULL);
}

struct node* SplayTree_delete(struct SplayTree* self, int val) {
    printf("SplayTree_delete(%p, %d) called\n", self, val);
    return NULL;
}

static void SplayTree_destroy_nodes(struct node *n) {
    if (n == NULL)
        return;
    
    SplayTree_destroy_nodes(n->left);
    SplayTree_destroy_nodes(n->right);
    free(n);

}

void SplayTree_destroy(struct SplayTree *self) {
    SplayTree_destroy_nodes(self->root);
    free(self);
}

static void SplayTree_rotate_right(struct node *n) {
    if (n->parent == NULL)
        return;

    struct node *r = n->right;
    struct node *p = n->parent;
    if (p->parent != NULL) {
        if (p == p->parent->left)
            p->parent->left = n;
        else
            p->parent->right = n;
    }
    n->parent = p->parent;
    p->parent = n;
    n->right = p;
    if (r != NULL) {
        r->parent = p;
    }
    p->left = r;
}

static void SplayTree_rotate_left(struct node *n) {
    if (n->parent == NULL)
        return;

    struct node *l = n->left;
    struct node *p = n->parent;
    if (p->parent != NULL) {
        if (p == p->parent->left)
            p->parent->left = n;
        else
            p->parent->right = n;
    }
    n->parent = p->parent;
    p->parent = n;
    n->left = p;
    if (l != NULL) {
        l->parent = p;
    }
    p->right = l;
}

void SplayTree_splay(struct SplayTree* t, struct node *n) {
    if (n->parent == NULL) {
        t->root = n;
        return;

    }

    if (n->parent->parent == NULL) { // node is zig from root
        if (n == n->parent->left)
            SplayTree_rotate_right(n);
        else
            SplayTree_rotate_left(n);
        t->root = n;
        return;
    }

    // Zig-zig from grandparent
    if (n->parent->parent != NULL && n->parent != NULL && n == n->parent->left && n->parent == n->parent->parent->left) {
        SplayTree_rotate_right(n->parent);
        SplayTree_rotate_right(n);
        goto done;
    }

    if (n->parent->parent != NULL && n->parent != NULL && n == n->parent->right && n->parent == n->parent->parent->right) {
        SplayTree_rotate_left(n->parent);
        SplayTree_rotate_left(n);

        goto done;
    }

    // Zig-zag from grandparent
    if (n->parent->parent != NULL && n->parent != NULL && n == n->parent->left && n->parent == n->parent->parent->right) {
        SplayTree_rotate_right(n);
        SplayTree_rotate_left(n);

        goto done; 
    }

    if (n->parent->parent != NULL && n->parent != NULL && n == n->parent->right && n->parent == n->parent->parent->left) {
        SplayTree_rotate_left(n);
        SplayTree_rotate_right(n);

        goto done;
    }

done:
    SplayTree_splay(t, n);
}

// static struct SplaySplitNodes SplayTree_split(struct SplayTree* tree, int val) {
//     printf("SplayTree_split(%p, %d) called\n", tree, val);
//     struct SplaySplitNodes res;
//     struct node *r = splay_search(v, root);

//     splay_split_res res;
//     res.left = r->left;
//     res.right = r->right;
//     r->left = NULL;
//     r->right = NULL;
//     return res;
// }

static void SplayTree_join(struct node *n) {
    printf("SplayTree_join(%p) called\n", n);
}










struct node *root = NULL;

// struct node {
//     int val;
//     struct node *parent;
//     struct node *left;
//     struct node *right;
// };

// rotates right with its parent
// void rotate_right(struct node *n) {
//     if (n->parent == NULL)
//         return;

//     struct node *r = n->right;
//     struct node *p = n->parent;
//     if (p->parent != NULL) {
//         if (p == p->parent->left)
//             p->parent->left = n;
//         else
//             p->parent->right = n;
//     }
//     n->parent = p->parent;
//     p->parent = n;
//     n->right = p;
//     if (r != NULL) {
//         r->parent = p;
//     }
//     p->left = r;
// }

// rotates left with its parent
// void SplayTree_rotate_left(struct node *n) {
//     if (n->parent == NULL)
//         return;

//     struct node *l = n->left;
//     struct node *p = n->parent;
//     if (p->parent != NULL) {
//         if (p == p->parent->left)
//             p->parent->left = n;
//         else
//             p->parent->right = n;
//     }
//     n->parent = p->parent;
//     p->parent = n;
//     n->left = p;
//     if (l != NULL) {
//         l->parent = p;
//     }
//     p->right = l;
// }

// void splay(struct node *n) {
//     // printf("splaying %d\n", n->val);
//     if (n->parent == NULL) {
//         root = n;
//         return;

//     }

//     if (n->parent->parent == NULL) { // node is zig from root
//         if (n == n->parent->left)
//             rotate_right(n);
//         else
//             SplayTree_rotate_left(n);
//         root = n;
//         return;
//     }

//     // Zig-zig from grandparent
//     if (n->parent->parent != NULL && n->parent != NULL && n == n->parent->left && n->parent == n->parent->parent->left) {
//         rotate_right(n->parent);
//         rotate_right(n);
//         if (n->parent == NULL) {
//             root = n;
//             return;
//         }   
//     }

//     if (n->parent->parent != NULL && n->parent != NULL && n == n->parent->right && n->parent == n->parent->parent->right) {
//         rotate_left(n->parent);
//         rotate_left(n);

//          if (n->parent == NULL) {
//             root = n;
//             return;
//         }   
//     }

//     // Zig-zag from grandparent
//     if (n->parent->parent != NULL && n->parent != NULL && n == n->parent->left && n->parent == n->parent->parent->right) {
//         rotate_right(n);
//         rotate_left(n);

//          if (n->parent == NULL) {
//             root = n;
//             return;
//         }   
//     }

//     if (n->parent->parent != NULL && n->parent != NULL && n == n->parent->right && n->parent == n->parent->parent->left) {
//         rotate_left(n);
//         rotate_right(n);

//          if (n->parent == NULL) {
//             root = n;
//             return;
//         }   
//     }

//     splay(n);

// }

// struct node* splay_insert_helper(int val, struct node **r, struct node *p) {
//     if (*r == NULL) {
//         *r = (struct node *)malloc(sizeof(struct node));
//         (*r)->val = val;
//         (*r)->left = NULL;
//         (*r)->right = NULL;
//         (*r)->parent = p;

//         splay(*r);
//         return *r;
//     }

//     if (val <= (*r)->val)
//         return splay_insert_helper(val, &(*r)->left, *r);
//     else
//         return splay_insert_helper(val, &(*r)->right, *r);
// }

// struct node* splay_insert(int val, struct node **r) { //
//     return splay_insert_helper(val, r, NULL);
// }

// void splay_free(struct node *n) {
//     if (n == NULL)
//         return;
    
//     splay_free(n->left);
//     splay_free(n->right);
//     free(n);
// }

// struct node *splay_search(int val, struct node *r) {
//     if (r == NULL)
//         return NULL;

//     printf("%d->", r->val);
//     if (val == r->val) {
//         splay(r);
//         return r;
//     }

//     struct node *c = val <= r->val ? r->left : r->right;
//     if (c == NULL) {
//         splay(r);
//         return NULL;
//     }

//     return splay_search(val, c);
// }

// typedef struct {
//     struct node *left;
//     struct node *right;
// } splay_split_res;

// splay_split_res splay_split(int v, struct node *p) {
//     struct node *r = splay_search(v, root);

//     splay_split_res res;
//     res.left = r->left;
//     res.right = r->right;
//     r->left = NULL;
//     r->right = NULL;
//     return res;
// }

// struct node *splay_join(struct node *r1, struct node *r2) {
//     return NULL;
// }

// void splay_insert_many(int size) {
//     srand(time(NULL));
//     int range = 1000;

//     // int arr[4] = {1,2,3,4};

//     // for (int i = 0; i < 4; i++) {
//     //     splay_insert(arr[i], &root);
//     // }
//     for (int i = 0; i < size; i++) {
//         int n = rand() % range;
//         printf("%d, ", n);
//         splay_insert(n, &root);
//     }
//     printf("\n");
// }

// int main() {
//     return 0;
// }
// int main() {
//     splay_insert_many(1000);

//     // void *not_found = splay_search(0, root);
//     // printf("\n");
//     // printf("%d %s\n", 0, not_found == NULL ? "not found" : "found");
//     // printf("%d\n", root->val);

//     // not_found = splay_search(2, root);
//     // printf("\n");
//     // printf("%d %s\n", 2, not_found == NULL ? "not found" : "found");
//     // printf("%d\n", root->val);

//     splay_free(root);
//     return 0;
// }
