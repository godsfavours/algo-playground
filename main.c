#include "splay.h"
#include <stdio.h>

int main() {
    SplayTree *t = SplayTree_create();
    SplayTree_insert(t, 5);
    SplayTree_print(t);
    SplayTree_insert(t, 10);
    SplayTree_print(t);
    SplayTree_insert(t, 2);
    SplayTree_print(t);
    SplayTree_insert(t, 1);
    SplayTree_print(t);

    // SplayTree_destroy(t);
    // SplayTree_destroy_nodes(t->root);
    printf("%d\n", SplayTree_search(t, 6) != NULL);


    // MyClass obj;
    // MyClass_init(&obj, 10);
    // obj.print(&obj); // Prints: Data: 10
    // int result = obj.add(&obj, 5);
    // printf("New Data: %d\n", result); // Prints: New Data: 15
    // obj.print(&obj); // Prints: Data: 15

    return 0;
}