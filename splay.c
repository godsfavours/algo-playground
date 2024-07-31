#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>


struct node *root = NULL;

struct node {
    int val;
    struct node *parent;
    struct node *left;
    struct node *right;
};

// rotates right with its parent
void rotate_right(struct node *n) {
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

// rotates left with its parent
void rotate_left(struct node *n) {
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

void splay(struct node *n) {
    // printf("splaying %d\n", n->val);
    if (n->parent == NULL) {
        root = n;
        return;

    }

    if (n->parent->parent == NULL) { // node is zig from root
        if (n == n->parent->left)
            rotate_right(n);
        else
            rotate_left(n);
        root = n;
        return;
    }

    // Zig-zig from grandparent
    if (n->parent->parent != NULL && n->parent != NULL && n == n->parent->left && n->parent == n->parent->parent->left) {
        rotate_right(n->parent);
        rotate_right(n);
        if (n->parent == NULL) {
            root = n;
            return;
        }   
    }

    if (n->parent->parent != NULL && n->parent != NULL && n == n->parent->right && n->parent == n->parent->parent->right) {
        rotate_left(n->parent);
        rotate_left(n);

         if (n->parent == NULL) {
            root = n;
            return;
        }   
    }

    // Zig-zag from grandparent
    if (n->parent->parent != NULL && n->parent != NULL && n == n->parent->left && n->parent == n->parent->parent->right) {
        rotate_right(n);
        rotate_left(n);

         if (n->parent == NULL) {
            root = n;
            return;
        }   
    }

    if (n->parent->parent != NULL && n->parent != NULL && n == n->parent->right && n->parent == n->parent->parent->left) {
        rotate_left(n);
        rotate_right(n);

         if (n->parent == NULL) {
            root = n;
            return;
        }   
    }

    splay(n);

}

struct node* splay_insert_helper(int val, struct node **r, struct node *p) {
    if (*r == NULL) {
        *r = (struct node *)malloc(sizeof(struct node));
        (*r)->val = val;
        (*r)->left = NULL;
        (*r)->right = NULL;
        (*r)->parent = p;

        splay(*r);
        return *r;
    }

    if (val <= (*r)->val)
        return splay_insert_helper(val, &(*r)->left, *r);
    else
        return splay_insert_helper(val, &(*r)->right, *r);
}

struct node* splay_insert(int val, struct node **r) { //
    return splay_insert_helper(val, r, NULL);
}

void splay_free(struct node *n) {
    if (n == NULL)
        return;
    
    splay_free(n->left);
    splay_free(n->right);
    free(n);
}

struct node *splay_search(int val, struct node *r) {
    if (r == NULL)
        return NULL;

    printf("%d->", r->val);
    if (val == r->val) {
        splay(r);
        return r;
    }

    struct node *c = val <= r->val ? r->left : r->right;
    if (c == NULL) {
        splay(r);
        return NULL;
    }

    return splay_search(val, c);
}

typedef struct {
    struct node *left;
    struct node *right;
} splay_split_res;

splay_split_res splay_split(int v, struct node *p) {
    struct node *r = splay_search(v, root);

    splay_split_res res;
    res.left = r->left;
    res.right = r->right;
    r->left = NULL;
    r->right = NULL;
    return res;
}

struct node *splay_join(struct node *r1, struct node *r2) {
    
}

void splay_insert_many(int size) {
    srand(time(NULL));
    int range = 1000;

    // int arr[4] = {1,2,3,4};

    // for (int i = 0; i < 4; i++) {
    //     splay_insert(arr[i], &root);
    // }
    for (int i = 0; i < size; i++) {
        int n = rand() % range;
        printf("%d, ", n);
        splay_insert(n, &root);
    }
    printf("\n");
}


int main() {
    splay_insert_many(1000);

    // void *not_found = splay_search(0, root);
    // printf("\n");
    // printf("%d %s\n", 0, not_found == NULL ? "not found" : "found");
    // printf("%d\n", root->val);

    // not_found = splay_search(2, root);
    // printf("\n");
    // printf("%d %s\n", 2, not_found == NULL ? "not found" : "found");
    // printf("%d\n", root->val);

    splay_free(root);
    return 0;
}