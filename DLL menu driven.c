//DLL MENU DRIVEN

#include <stdio.h>
#include <stdlib.h>

// A structure for a node in the doubly linked list
typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

// Global head and tail pointers for the first list
Node* head1 = NULL;
Node* tail1 = NULL;

// Global head and tail pointers for the second list (for merge operation)
Node* head2 = NULL;
Node* tail2 = NULL;

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// Function to display a list
void displayList(Node* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }
    Node* current = head;
    printf("List elements: ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// ------------------- INSERTION OPERATIONS -------------------

// Function to insert a node at the beginning of the list
// Returns the new head of the list.
Node* insertAtBeginning(Node** head, Node** tail, int data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = *tail = newNode;
    } else {
        newNode->next = *head;
        (*head)->prev = newNode;
        *head = newNode;
    }
    printf("Node with data %d inserted at the beginning.\n", data);
    return *head;
}

// Function to insert a node at the end of the list
// Returns the head of the list.
Node* insertAtEnd(Node** head, Node** tail, int data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = *tail = newNode;
    } else {
        (*tail)->next = newNode;
        newNode->prev = *tail;
        *tail = newNode;
    }
    printf("Node with data %d inserted at the end.\n", data);
    return *head;
}

// Function to insert a new node before a specific number
// Returns the head of the list.
Node* insertBeforeNode(Node** head, Node** tail, int target, int data) {
    if (*head == NULL) {
        printf("List is empty. Cannot insert.\n");
        return NULL;
    }
    Node* current = *head;
    while (current != NULL && current->data != target) {
        current = current->next;
    }
    if (current == NULL) {
        printf("Node with data %d not found.\n", target);
        return *head;
    }
    
    Node* newNode = createNode(data);
    if (current == *head) {
        newNode->next = *head;
        (*head)->prev = newNode;
        *head = newNode;
    } else {
        newNode->prev = current->prev;
        newNode->next = current;
        current->prev->next = newNode;
        current->prev = newNode;
    }
    printf("Node with data %d inserted before node with data %d.\n", data, target);
    return *head;
}

// Function to insert a new node after a specific number
// Returns the head of the list.
Node* insertAfterNode(Node** head, Node** tail, int target, int data) {
    if (*head == NULL) {
        printf("List is empty. Cannot insert.\n");
        return NULL;
    }
    Node* current = *head;
    while (current != NULL && current->data != target) {
        current = current->next;
    }
    if (current == NULL) {
        printf("Node with data %d not found.\n", target);
        return *head;
    }
    
    Node* newNode = createNode(data);
    if (current == *tail) {
        (*tail)->next = newNode;
        newNode->prev = *tail;
        *tail = newNode;
    } else {
        newNode->next = current->next;
        newNode->prev = current;
        current->next->prev = newNode;
        current->next = newNode;
    }
    printf("Node with data %d inserted after node with data %d.\n", data, target);
    return *head;
}

// Function to insert a node at a specific position
// Returns the head of the list.
Node* insertAtPosition(Node** head, Node** tail, int position, int data) {
    if (position < 1) {
        printf("Invalid position. Position must be 1 or greater.\n");
        return *head;
    }
    
    if (position == 1) {
        return insertAtBeginning(head, tail, data);
    }
    
    Node* current = *head;
    int count = 1;
    while (current != NULL && count < position - 1) {
        current = current->next;
        count++;
    }
    
    if (current == NULL) {
        printf("Position out of bounds. List has %d nodes.\n", count-1);
        return *head;
    }
    
    if (current->next == NULL) {
        // Inserting at the end
        return insertAtEnd(head, tail, data);
    } else {
        Node* newNode = createNode(data);
        newNode->next = current->next;
        newNode->prev = current;
        current->next->prev = newNode;
        current->next = newNode;
        printf("Node with data %d inserted at position %d.\n", data, position);
    }
    return *head;
}

// ------------------- DELETION OPERATIONS -------------------

// Function to delete the node at the beginning
// Returns the new head of the list.
Node* deleteAtBeginning(Node** head, Node** tail) {
    if (*head == NULL) {
        printf("List is empty. Cannot delete.\n");
        return NULL;
    }
    Node* temp = *head;
    if ((*head)->next == NULL) {
        *head = *tail = NULL;
    } else {
        *head = (*head)->next;
        (*head)->prev = NULL;
    }
    printf("Node with data %d deleted from the beginning.\n", temp->data);
    free(temp);
    return *head;
}

// Function to delete the node at the end
// Returns the head of the list.
Node* deleteAtEnd(Node** head, Node** tail) {
    if (*head == NULL) {
        printf("List is empty. Cannot delete.\n");
        return NULL;
    }
    Node* temp = *tail;
    if ((*tail)->prev == NULL) {
        *head = *tail = NULL;
    } else {
        *tail = (*tail)->prev;
        (*tail)->next = NULL;
    }
    printf("Node with data %d deleted from the end.\n", temp->data);
    free(temp);
    return *head;
}

// Function to delete a node before a specific number
// Returns the head of the list.
Node* deleteBeforeNode(Node** head, Node** tail, int target) {
    if (*head == NULL) {
        printf("List is empty. Cannot delete.\n");
        return NULL;
    }
    Node* current = *head;
    while (current != NULL && current->data != target) {
        current = current->next;
    }
    if (current == NULL || current->prev == NULL) {
        printf("Cannot delete. Either node not found or it's the first node.\n");
        return *head;
    }
    Node* temp = current->prev;
    if (temp->prev == NULL) {
        // Deleting the head node
        deleteAtBeginning(head, tail);
    } else {
        temp->prev->next = current;
        current->prev = temp->prev;
        printf("Node with data %d deleted before node with data %d.\n", temp->data, target);
        free(temp);
    }
    return *head;
}

// Function to delete a node after a specific number
// Returns the head of the list.
Node* deleteAfterNode(Node** head, Node** tail, int target) {
    if (*head == NULL) {
        printf("List is empty. Cannot delete.\n");
        return NULL;
    }
    Node* current = *head;
    while (current != NULL && current->data != target) {
        current = current->next;
    }
    if (current == NULL || current->next == NULL) {
        printf("Cannot delete. Either node not found or it's the last node.\n");
        return *head;
    }
    
    Node* temp = current->next;
    if (temp->next == NULL) {
        // Deleting the tail node
        deleteAtEnd(head, tail);
    } else {
        current->next = temp->next;
        temp->next->prev = current;
        printf("Node with data %d deleted after node with data %d.\n", temp->data, target);
        free(temp);
    }
    return *head;
}

// Function to delete a node at a specific position
// Returns the head of the list.
Node* deleteAtPosition(Node** head, Node** tail, int position) {
    if (*head == NULL) {
        printf("List is empty. Cannot delete.\n");
        return NULL;
    }
    if (position < 1) {
        printf("Invalid position. Position must be 1 or greater.\n");
        return *head;
    }
    if (position == 1) {
        return deleteAtBeginning(head, tail);
    }
    
    Node* current = *head;
    int count = 1;
    while (current != NULL && count < position) {
        current = current->next;
        count++;
    }
    
    if (current == NULL) {
        printf("Position out of bounds. The list has fewer than %d nodes.\n", position);
        return *head;
    }
    
    if (current->next == NULL) {
        return deleteAtEnd(head, tail);
    } else {
        current->prev->next = current->next;
        current->next->prev = current->prev;
        printf("Node with data %d deleted from position %d.\n", current->data, position);
        free(current);
    }
    return *head;
}

// ------------------- SEARCH, COUNT, AND MERGE OPERATIONS -------------------

// Function to search for a specific node
// Returns the found node, or NULL if not found.
Node* searchNode(Node* head, int target) {
    Node* current = head;
    int position = 1;
    while (current != NULL) {
        if (current->data == target) {
            printf("Node with data %d found at position %d.\n", target, position);
            return current;
        }
        current = current->next;
        position++;
    }
    printf("Node with data %d not found in the list.\n", target);
    return NULL;
}

// Function to count the nodes in the list
void countNodes(Node* head) {
    int count = 0;
    Node* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    printf("Total number of nodes: %d\n", count);
}

// Function to merge two lists
// Returns the head of the merged list.
Node* mergeLists(Node** head1, Node** tail1, Node** head2, Node** tail2) {
    if (*head2 == NULL) {
        printf("Second list is empty. No merge performed.\n");
        return *head1;
    }
    if (*head1 == NULL) {
        *head1 = *head2;
        *tail1 = *tail2;
        *head2 = *tail2 = NULL;
        printf("Second list merged into the first list.\n");
        return *head1;
    }
    
    (*tail1)->next = *head2;
    (*head2)->prev = *tail1;
    *tail1 = *tail2;
    *head2 = *tail2 = NULL; // Clear the second list
    
    printf("Both lists have been successfully merged.\n");
    return *head1;
}

int main() {
    int choice, data, target, position;
    
    while (1) {
        printf("\n--- Doubly Linked List Menu ---\n");
        printf("1. Insert at the beginning\n");
        printf("2. Insert at the end\n");
        printf("3. Insert before a specific number\n");
        printf("4. Insert after a specific number\n");
        printf("5. Insert at a specific position\n");
        printf("6. Delete at the beginning\n");
        printf("7. Delete at the end\n");
        printf("8. Delete before a specific number\n");
        printf("9. Delete after a specific number\n");
        printf("10. Delete at a specific position\n");
        printf("11. Search a specific node\n");
        printf("12. Merge two linked lists (List 2 into List 1)\n");
        printf("13. Count the nodes\n");
        printf("14. Display List 1\n");
        printf("15. Display List 2\n");
        printf("16. Exit\n");
        
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            // Clear input buffer on invalid input
            while (getchar() != '\n');
            printf("Invalid input. Please enter a number.\n");
            continue;
        }
        
        switch (choice) {
            case 1:
                printf("Enter data to insert at the beginning: ");
                scanf("%d", &data);
                insertAtBeginning(&head1, &tail1, data);
                break;
            case 2:
                printf("Enter data to insert at the end: ");
                scanf("%d", &data);
                insertAtEnd(&head1, &tail1, data);
                break;
            case 3:
                printf("Enter the target number to insert before: ");
                scanf("%d", &target);
                printf("Enter data to insert: ");
                scanf("%d", &data);
                insertBeforeNode(&head1, &tail1, target, data);
                break;
            case 4:
                printf("Enter the target number to insert after: ");
                scanf("%d", &target);
                printf("Enter data to insert: ");
                scanf("%d", &data);
                insertAfterNode(&head1, &tail1, target, data);
                break;
            case 5:
                printf("Enter the position to insert at: ");
                scanf("%d", &position);
                printf("Enter data to insert: ");
                scanf("%d", &data);
                insertAtPosition(&head1, &tail1, position, data);
                break;
            case 6:
                deleteAtBeginning(&head1, &tail1);
                break;
            case 7:
                deleteAtEnd(&head1, &tail1);
                break;
            case 8:
                printf("Enter the target number to delete before: ");
                scanf("%d", &target);
                deleteBeforeNode(&head1, &tail1, target);
                break;
            case 9:
                printf("Enter the target number to delete after: ");
                scanf("%d", &target);
                deleteAfterNode(&head1, &tail1, target);
                break;
            case 10:
                printf("Enter the position to delete: ");
                scanf("%d", &position);
                deleteAtPosition(&head1, &tail1, position);
                break;
            case 11:
                printf("Enter the number to search: ");
                scanf("%d", &target);
                Node* foundNode = searchNode(head1, target);
                if (foundNode != NULL) {
                    printf("Found node data: %d\n", foundNode->data);
                }
                break;
            case 12:
                // To merge, we first need to populate List 2
                printf("\nPopulating a second list for merging.\n");
                printf("Enter a few numbers for List 2 (-1 to stop): ");
                while (scanf("%d", &data) == 1 && data != -1) {
                    insertAtEnd(&head2, &tail2, data);
                }
                while (getchar() != '\n'); // Clear buffer
                
                printf("Merging List 2 into List 1...\n");
                mergeLists(&head1, &tail1, &head2, &tail2);
                break;
            case 13:
                countNodes(head1);
                break;
            case 14:
                displayList(head1);
                break;
            case 15:
                displayList(head2);
                break;
            case 16:
                printf("Exiting program.\n");
                exit(0);
            default:
                printf("Invalid choice. Please enter a number between 1 and 16.\n");
        }
    }
    
    return 0;
}
Output:- --- Doubly Linked List Menu ---
1. Insert at the beginning
2. Insert at the end
3. Insert before a specific number
4. Insert after a specific number
5. Insert at a specific position
6. Delete at the beginning
7. Delete at the end
8. Delete before a specific number
9. Delete after a specific number
10. Delete at a specific position
11. Search a specific node
12. Merge two linked lists (List 2 into List 1)
13. Count the nodes
14. Display List 1
15. Exit