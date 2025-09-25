#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};


struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;

    return newNode;
}

struct Node* insertAtBeginning(struct Node* head, int data) {
    struct Node* newNode = createNode(data);
    newNode->next = head;
 
    return newNode;
}

struct Node* insertAtEnd(struct Node* head, int data) {
    struct Node* newNode = createNode(data);
    if (head == NULL) return newNode;

    struct Node* temp = head;
    while (temp->next != NULL)
        temp = temp->next;

    temp->next = newNode;
 
    return head;
}

struct Node* insertBeforeKey(struct Node* head, int key, int data) {
    struct Node* newNode = createNode(data);
    if (head == NULL || head->data == key) {
        newNode->next = head;
 
        return newNode;
    }

    struct Node* temp = head;
    while (temp->next != NULL && temp->next->data != key)
        temp = temp->next;

    if (temp->next != NULL) {
        newNode->next = temp->next;
        temp->next = newNode;
    } else {
        printf("Key not found. Inserting at end.\n");
        temp->next = newNode;
    }

    return head;
}

struct Node* insertAfterKey(struct Node* head, int key, int data) {
    struct Node* newNode = createNode(data);
    struct Node* temp = head;

    while (temp != NULL && temp->data != key)
        temp = temp->next;

    if (temp != NULL) {
        newNode->next = temp->next;
        temp->next = newNode;
    } else {
        printf("Key not found. Inserting at end.\n");
        if (head == NULL)
            return newNode;

        temp = head;
        while (temp->next != NULL)
            temp = temp->next;

        temp->next = newNode;
    }

    return head;
}

struct Node* insertAtPosition(struct Node* head, int position, int data) {
    struct Node* newNode = createNode(data);

    if (position == 0) {
        newNode->next = head;
        return newNode;
    }

    struct Node* temp = head;
    for (int i = 0; i < position - 1 && temp != NULL; i++)
        temp = temp->next;

    if (temp != NULL) {
        newNode->next = temp->next;
        temp->next = newNode;
    } else {
        printf("Position out of bounds. Inserting at end.\n");
        if (head == NULL) return newNode;
        temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newNode;
    }

    return head;
}

struct Node* deleteAtBeginning(struct Node* head) {
    if (head == NULL) {
        printf("List is empty. Nothing to delete.\n");
        return NULL;
    }

    struct Node* temp = head;
    head = head->next;
    free(temp);
 
    return head;
}

struct Node* deleteAtEnd(struct Node* head) {
    if (head == NULL) {
        printf("List is empty. Nothing to delete.\n");
 
        return NULL;
    }

    if (head->next == NULL) {
        free(head);
 
        return NULL;
    }

    struct Node* temp = head;
    while (temp->next->next != NULL)
        temp = temp->next;

    free(temp->next);
    temp->next = NULL;
 
    return head;
}

struct Node* deleteBeforeKey(struct Node* head, int key) {
    if (head == NULL || head->data == key) {
        printf("No node exists before the given key.\n");
 
        return head;
    }

    if (head->next != NULL && head->next->data == key) {
        struct Node* temp = head;
        head = head->next;
        free(temp);
 
        return head;
    }

    struct Node* temp = head;
    while (temp->next != NULL && temp->next->next != NULL && temp->next->next->data != key)
        temp = temp->next;

    if (temp->next != NULL && temp->next->next != NULL) {
        struct Node* toDelete = temp->next;
        temp->next = toDelete->next;
        free(toDelete);
    } else {
        printf("No node exists before the given key.\n");
    }

    return head;
}

struct Node* deleteAfterKey(struct Node* head, int key) {
    struct Node* temp = head;
    while (temp != NULL && temp->data != key)
        temp = temp->next;

    if (temp != NULL && temp->next != NULL) {
        struct Node* toDelete = temp->next;
        temp->next = toDelete->next;
        free(toDelete);
    } else {
        printf("No node exists after the given key.\n");
    }

    return head;
}

struct Node* deleteAtPosition(struct Node* head, int position) {
    if (head == NULL) {
        printf("List is empty. Nothing to delete.\n");
        return NULL;
    }

    if (position == 0) {
        struct Node* temp = head;
        head = head->next;
        free(temp);
 
        return head;
    }

    struct Node* temp = head;
    for (int i = 0; i < position - 1 && temp->next != NULL; i++)
        temp = temp->next;

    if (temp->next != NULL) {
        struct Node* toDelete = temp->next;
        temp->next = toDelete->next;
        free(toDelete);
    } else {
        printf("Position out of bounds. Nothing to delete.\n");
    }
 
    return head;
}
struct Node* deleteSpecificValue(struct Node* head, int value) {
    if (head == NULL) {
        printf("List is empty. Nothing to delete.\n");
 
        return NULL;
    }

    if (head->data == value) {
        struct Node* temp = head;
        head = head->next;
        free(temp);
 
        return head;
    }

    struct Node* temp = head;
    while (temp->next != NULL && temp->next->data != value)
        temp = temp->next;

    if (temp->next != NULL) {
        struct Node* toDelete = temp->next;
        temp->next = toDelete->next;
        free(toDelete);
    } else {
        printf("Value not found. Nothing to delete.\n");
    }

    return head;
}

    void display(struct Node* head) {
    printf("List: ");
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

struct Node* search(struct Node* head, int k) {
    int p = 1;
    while (head != NULL) {
        if (head->data == k) {
            printf("Element %d found at position %d\n", k, p);
            return head;
        }
        head = head->next;
        p++;
    }
    printf("Element %d not found\n", k);
 
    return NULL;
}

struct Node* merge(struct Node* head1, struct Node* head2) {
    if (head1 == NULL) return head2;
    if (head2 == NULL) return head1;
    struct Node* head = NULL;
    if (head1->data < head2->data) {
        head = head1;
        head->next = merge(head1->next, head2);
    } else {
        head = head2;
        head->next = merge(head1, head2->next);
    }
 
    return head;
}

int count(struct Node* head) {
    int c = 0;
    while (head != NULL) {
        c++;
        head = head->next;
    }
  
    return c;
}

int main() {
    struct Node* head = NULL;
    int choice, val, key, position, k;

    while (1) {
        printf("\nSingly Linked List Operations\n");
        printf("1. Insert at Beginning\n");
        printf("2. Insert at End\n");
        printf("3. Insert before key\n");
        printf("4. Insert after key\n");
        printf("5. Insert at position\n");
        printf("6. Delete at Beginning\n"); 
        printf("7. Delete at End\n");
        printf("8. Delete before key\n");
        printf("9. Delete after key\n");
        printf("10. Delete at position\n");
        printf("11. Delete specific value\n");
        printf("12. Search for value\n");
        printf("13. Count nodes\n");
        printf("14. Merge with another list\n");
        printf("15. Display list\n");
        printf("0. EXIT\n");
        printf("\nEnter your choice:\n ");
        scanf("%d", &choice);

        switch (choice) {

        case 1:
            printf("Enter value to insert at beginning: ");
            scanf("%d", &val);
            head = insertAtBeginning(head, val);
            break;

        case 2:
            printf("Enter value to insert at end: ");
            scanf("%d", &val);
            head = insertAtEnd(head, val);
            break;

        case 3:
            printf("Enter key and value to insert before key: ");
            scanf("%d %d", &key, &val);
            head = insertBeforeKey(head, key, val);
            break;

        case 4:
            printf("Enter key and value to insert after key: ");
            scanf("%d %d", &key, &val);
            head = insertAfterKey(head, key, val);
            break;

        case 5:
            printf("Enter position and value to insert at position: ");
            scanf("%d %d", &position, &val);
            head = insertAtPosition(head, position, val);
            break;

        case 6:
            head = deleteAtBeginning(head);
            break;

        case 7:
            head = deleteAtEnd(head);
            break;

        case 8:
            printf("Enter key to delete before key: ");
            scanf("%d", &key);
            head = deleteBeforeKey(head, key);
            break;

        case 9:
            printf("Enter key to delete after key: ");
            scanf("%d", &key);
            head = deleteAfterKey(head, key);
            break;

        case 10:
            printf("Enter position to delete at position: ");
            scanf("%d", &position);
            head = deleteAtPosition(head, position);
            break;

        case 11:
            printf("Enter value to delete specific value: ");
            scanf("%d", &val);
            head = deleteSpecificValue(head, val);
            break;
        
        case 12:
            printf("Enter value to search: ");
            scanf("%d", &k);
            search(head, k);
            break;
     
        case 13:
            printf("Count of nodes: %d\n", count(head));
            break;

        case 14: {
            struct Node* head2 = NULL;
            int n, value;
            printf("Enter number of elements for second list: ");
            scanf("%d", &n);
            for (int i = 0; i < n; i++) {
                printf("Enter value %d: ", i + 1);
                scanf("%d", &value);
                head2 = insertAtEnd(head2, value);
            }
            head = merge(head, head2);
            printf("Lists merged.\n");
            break;
        }

        case 15:
            display(head);
            break;

        case 0:
            exit(0);
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }
 
    return 0;
}