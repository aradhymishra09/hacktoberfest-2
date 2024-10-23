#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node
{
          int data;
          struct Node *next;
          struct Node *prev;
} Node;

Node *createDoublyLinkedList(int n)
{
          if (n <= 0)
          {
                    printf("The number of nodes should be greater than 0.\n");
                    return NULL;
          }

          Node *head = (Node *)malloc(sizeof(Node));
          if (head == NULL)
          {
                    printf("Memory allocation failed\n");
                    exit(1);
          }

          printf("Enter data for node 1: ");
          scanf("%d", &(head->data));
          head->next = NULL;
          head->prev = NULL;

          Node *temp = head;
          for (int i = 2; i <= n; i++)
          {
                    Node *newNode = (Node *)malloc(sizeof(Node));
                    if (newNode == NULL)
                    {
                              printf("Memory allocation failed\n");
                              exit(1);
                    }

                    printf("Enter data for node %d: ", i);
                    scanf("%d", &(newNode->data));
                    newNode->next = NULL;
                    newNode->prev = temp; 
                    temp->next = newNode; 
                    temp = newNode;       
          }

          return head;
}

void displayDoublyLinkedListForward(Node *head)
{
          Node *temp = head;
          printf("NULL <- ");
          while (temp != NULL)
          {
                    printf("%d", temp->data);
                    temp = temp->next;
                    if (temp != NULL)
                    {
                              printf(" <-> ");
                    }
          }
          printf(" -> NULL\n");
}

void displayDoublyLinkedListBackward(Node *head)
{
          Node *temp = head;
          while (temp->next != NULL)
          {
                    temp = temp->next;
          }
          while (temp != NULL)
          {
                    printf("%d", temp->data);
                    if (temp->prev != NULL)
                    {
                              printf(" <-> ");
                    }
                    temp = temp->prev;
          }
          printf(" -> NULL\n");
}

int count(Node *head)
{
          Node *temp = head;
          int cnt = 0;
          while (temp != NULL)
          {
                    cnt++;
                    temp = temp->next;
          }
          return cnt;
}

bool checkListIsEmpty(Node *head)
{
          return head == NULL;
}

int SearchElement(Node *head)
{
          int pos = 0;
          Node *temp = head;
          int valTobeFound;
          printf("Enter the value to be searched: ");
          scanf("%d", &valTobeFound);

          while (temp != NULL)
          {
                    pos++;
                    if (temp->data == valTobeFound)
                    {
                              return pos;
                    }
                    temp = temp->next;
          }
          return 0;
}

Node *insertAtHead(Node *head)
{
          Node *newHead = (Node *)malloc(sizeof(Node));
          if (newHead == NULL)
          {
                    printf("Memory allocation failed\n");
                    exit(1);
          }
          printf("Enter data for new head: ");
          scanf("%d", &(newHead->data));
          newHead->next = head;
          newHead->prev = NULL;
          if (head != NULL)
          {
                    head->prev = newHead;
          }
          head = newHead;
          return head;
}

Node *insertAtTail(Node *head)
{
          Node *newTail = (Node *)malloc(sizeof(Node));
          if (newTail == NULL)
          {
                    printf("Memory allocation failed\n");
                    exit(1);
          }
          Node *temp = head;
          while (temp->next != NULL)
          {
                    temp = temp->next;
          }
          printf("Enter data for new tail: ");
          scanf("%d", &(newTail->data));
          newTail->next = NULL;
          newTail->prev = temp;
          temp->next = newTail;
          return head;
}

Node *insertAtPosition(Node *head, int position)
{
          if (position < 1)
          {
                    printf("Invalid position!\n");
                    return head;
          }
          if (position == 1)
          {
                    return insertAtHead(head);
          }

          Node *newNode = (Node *)malloc(sizeof(Node));
          if (newNode == NULL)
          {
                    printf("Memory allocation failed\n");
                    exit(1);
          }
          printf("Enter data for the new node: ");
          scanf("%d", &(newNode->data));

          Node *temp = head;
          for (int i = 1; i < position - 1 && temp != NULL; i++)
          {
                    temp = temp->next;
          }

          if (temp == NULL)
          {
                    printf("Position out of bounds\n");
                    free(newNode);
                    return head;
          }

          newNode->next = temp->next;
          if (temp->next != NULL)
          {
                    temp->next->prev = newNode;
          }
          temp->next = newNode;
          newNode->prev = temp;

          return head;
}
// Delete the node at the beginning of the list
Node *deleteAtHead(Node *head)
{
          if (head == NULL)
          {
                    printf("The list is empty.\n");
                    return NULL;
          }
          Node *temp = head;
          head = head->next;
          if (head != NULL)
          {
                    head->prev = NULL;
          }
          free(temp);
          return head;
}

Node *deleteAtTail(Node *head)
{
          if (head == NULL)
          {
                    printf("The list is empty.\n");
                    return NULL;
          }
          if (head->next == NULL)
          {
                    free(head);
                    return NULL;
          }

          Node *temp = head;
          while (temp->next != NULL)
          {
                    temp = temp->next;
          }
          temp->prev->next = NULL;
          free(temp);
          return head;
}

Node *deleteAtPosition(Node *head, int position)
{
          if (position < 1 || head == NULL)
          {
                    printf("Invalid position or empty list!\n");
                    return head;
          }

          Node *temp = head;
          if (position == 1)
          {
                    head = head->next;
                    if (head != NULL)
                    {
                              head->prev = NULL;
                    }
                    free(temp);
                    return head;
          }

          for (int i = 1; i < position && temp != NULL; i++)
          {
                    temp = temp->next;
          }

          if (temp == NULL)
          {
                    printf("Position out of bounds\n");
                    return head;
          }

          if (temp->next != NULL)
          {
                    temp->next->prev = temp->prev;
          }
          if (temp->prev != NULL)
          {
                    temp->prev->next = temp->next;
          }
          free(temp);

          return head;
}

Node *deleteByKey(Node *head, int key)
{
          Node *temp = head;

          while (temp != NULL && temp->data != key)
          {
                    temp = temp->next;
          }

          if (temp == NULL)
          {
                    printf("Key not found in the list.\n");
                    return head;
          }

          if (temp->next != NULL)
          {
                    temp->next->prev = temp->prev;
          }
          if (temp->prev != NULL)
          {
                    temp->prev->next = temp->next;
          }
          else
          {
                    head = temp->next; 
          }

          free(temp);
          return head;
}

void freeLinkedList(Node *head)
{
          Node *temp = head;
          while (temp != NULL)
          {
                    Node *next = temp->next;
                    free(temp);
                    temp = next;
          }
}

int main()
{
          Node *head = NULL;
          int choice, position, key, n;

          printf("Enter the number of nodes: ");
          scanf("%d", &n);
          head = createDoublyLinkedList(n);

          do
          {
                    printf("\nMenu:\n");
                    printf("1. Traverse the list forward\n");
                    printf("2. Traverse the list backward\n");
                    printf("3. Insert a node at the beginning\n");
                    printf("4. Insert a node at the end\n");
                    printf("5. Insert a node at a specific position\n");
                    printf("6. Delete a node at the beginning\n");
                    printf("7. Delete a node at the end\n");
                    printf("8. Delete a node at a specific position\n");
                    printf("9. Delete a node by key\n");
                    printf("10. Count total number of nodes\n");
                    printf("11. Search for an element\n");
                    printf("12. Check if the list is empty\n");
                    printf("13. Exit\n");
                    printf("Enter your choice: ");
                    scanf("%d", &choice);

                    switch (choice)
                    {
                    case 1:
                              displayDoublyLinkedListForward(head);
                              break;
                    case 2:
                              displayDoublyLinkedListBackward(head);
                              break;
                    case 3:
                              head = insertAtHead(head);
                              break;
                    case 4:
                              head = insertAtTail(head);
                              break;
                    case 5:
                              printf("Enter the position to insert: ");
                              scanf("%d", &position);
                              head = insertAtPosition(head, position);
                              break;
                    case 6:
                              head = deleteAtHead(head);
                              break;
                    case 7:
                              head = deleteAtTail(head);
                              break;
                    case 8:
                              printf("Enter the position to delete: ");
                              scanf("%d", &position);
                              head = deleteAtPosition(head, position);
                              break;
                    case 9:
                              printf("Enter the key to delete: ");
                              scanf("%d", &key);
                              head = deleteByKey(head, key);
                              break;
                    case 10:
                              printf("Total number of nodes: %d\n", count(head));
                              break;
                    case 11:
                              position = SearchElement(head);
                              if (position != 0)
                              {
                                        printf("Element found at position: %d\n", position);
                              }
                              else
                              {
                                        printf("Element not found in the list.\n");
                              }
                              break;
                    case 12:
                              if (checkListIsEmpty(head))
                              {
                                        printf("The list is empty.\n");
                              }
                              else
                              {
                                        printf("The list is not empty.\n");
                              }
                              break;
                    case 13:
                              printf("Exiting the program.\n");
                              freeLinkedList(head);
                              break;
                    default:
                              printf("Invalid choice! Please enter a number between 1 and 13.\n");
                              break;
                    }
          } while (choice != 13);

          return 0;
}
