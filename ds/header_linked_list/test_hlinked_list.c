#include "hlinked_list.h"
#include <assert.h>


void test_append();
void test_insert();
void test_get();
void test_count();
void test_index();
void test_remove();
void test_pop();
void test_reverse();
void test_print();

void test_dhlinkedlist() {
    // Initialize the linked list
    dhlinkedlist_t *list = dhll_init();
    if (!list) {
        printf("Failed to initialize linked list.\n");
        return;
    }

    // Run all test functions
    puts("\n append ==================================");
    test_append(list);

    puts("\n insert ==================================");
    test_insert(list);

    puts("\n get ==================================");
    test_get(list);

    puts("\n count ==================================");
    test_count(list);

    puts("\n index ==================================");
    test_index(list);

    puts("\n remove ==================================");
    test_remove(list);

    puts("\n pop ==================================");
    test_pop(list);

    puts("\n reverse ==================================");
    test_reverse(list);

    puts("\n print ==================================");
    test_print(list);

    // Free the linked list
    dhll_free(list);
}

void test_append(dhlinkedlist_t *list) {
    int a = 10, b = 20, c = 30;
    float f1 = 1.1, f2 = 2.2;
    char *s1 = "Hello", *s2 = "World";

    printf("Appending integers...\n");
    dhll_append(list, INT, &a);
    dhll_append(list, INT, &b);
    dhll_append(list, INT, &c);
    dhll_print(list); // Expected: [10, 20, 30]

    printf("Appending floats...\n");
    dhll_append(list, FLO, &f1);
    dhll_append(list, FLO, &f2);
    dhll_print(list); // Expected: [10, 20, 30, 1.1, 2.2]

    printf("Appending strings...\n");
    dhll_append(list, STR, s1);
    dhll_append(list, STR, s2);
    dhll_print(list); // Expected: [10, 20, 30, 1.1, 2.2, "Hello", "World"]
}

void test_insert(dhlinkedlist_t *list) {
    int d = 5;
    printf("Inserting at the beginning...\n");
    dhll_insert(list, 0, INT, &d);
    dhll_print(list); // Expected: [5, 10, 20, 30, 1.1, 2.2, "Hello", "World"]

    int e = 15;
    printf("Inserting in the middle...\n");
    dhll_insert(list, 2, INT, &e);
    dhll_print(list); // Expected: [5, 10, 15, 20, 30, 1.1, 2.2, "Hello", "World"]

    int f = 35;
    printf("Inserting at the end...\n");
    dhll_insert(list, 9, INT, &f);
    dhll_print(list); // Expected: [5, 10, 15, 20, 30, 1.1, 2.2, "Hello", "World", 35]
}

void test_get(dhlinkedlist_t *list) {
    printf("Getting element at index 3...\n");
    node_t *node = dhll_get(list, 3);
    if (node) {
        printf("Element at index 3: %d\n", node->data.value.ival); // Expected: 20
    }
}

void test_count(dhlinkedlist_t *list) {
    int b = 20;
    printf("Counting occurrences of 20...\n");
    int count = dhll_count(list, INT, &b);
    printf("Count of 20: %d\n", count); // Expected: 1
}

void test_index(dhlinkedlist_t *list) {
    float f1 = 1.1;
    printf("Finding index of 1.1...\n");
    int index = dhll_index(list, FLO, &f1);
    printf("Index of 1.1: %d\n", index); // Expected: index of 1.1
}

void test_remove(dhlinkedlist_t *list) {
    int b = 20;
    printf("Removing 20...\n");
    bool removed = dhll_remove(list, INT, &b);
    printf("Removed 20: %s\n", removed ? "true" : "false");
    dhll_print(list); // Expected: [5, 10, 15, 30, 1.1, 2.2, "Hello", "World"]
}

void test_pop(dhlinkedlist_t *list) {
    printf("Popping last element...\n");
    node_t *popped = dhll_pop(list);
    if (popped) {
        printf("Popped element: %d\n", popped->data.value.ival); // Expected: 35
        dhll_free_node(popped); // Free the popped node
    }
    dhll_print(list); // Expected: [5, 10, 15, 30, 1.1, 2.2, "Hello", "World"]
}

void test_reverse(dhlinkedlist_t *list) {
    printf("Reversing the list...\n");
    dhll_reverse(list);
    dhll_print(list); // Expected: ["World", "Hello", 2.2, 1.1, 30, 15, 10, 5]
}

void test_print(dhlinkedlist_t *list) {
    printf("Final state of the list:\n");
    dhll_print(list); // Print the final state of the list
}

int main() {
    test_dhlinkedlist();

    puts("\n*** ALL TEST PASSES *** \n");
    return 0;
}
