
// C++ code for linked list merged sort
#include <bits/stdc++.h>
using namespace std;
  
/* Link list node */
class Node {
public:
    int data;
    Node* next;
};
  
/* function prototypes */
Node* SortedMerge(Node* a, Node* b);
void FrontBackSplit(Node* source,
                    Node** frontRef, Node** backRef);
  
/* sorts the linked list by changing next pointers (not data) */
void MergeSort(Node** headRef)
{
    Node* head = *headRef;
    Node* a;
    Node* b;
  
    /* Base case -- length 0 or 1 */
    if ((head == NULL) || (head->next == NULL)) {
        return;
    }
  
    /* Split head into 'a' and 'b' sublists */
    FrontBackSplit(head, &a, &b);
  
    /* Recursively sort the sublists */
    MergeSort(&a);
    MergeSort(&b);
  
    /* answer = merge the two sorted lists together */
    *headRef = SortedMerge(a, b);
}
  
/* See https:// www.geeksforgeeks.org/?p=3622 for details of this 
function */
Node* SortedMerge(Node* a, Node* b)
{
    Node* result = NULL;
  
    /* Base cases */
    if (a == NULL)
        return (b);
    else if (b == NULL)
        return (a);
  
    /* Pick either a or b, and recur */
    if (a->data <= b->data) {
        result = a;
        result->next = SortedMerge(a->next, b);
    }
    else {
        result = b;
        result->next = SortedMerge(a, b->next);
    }
    return (result);
}
  
/* UTILITY FUNCTIONS */
/* Split the nodes of the given list into front and back halves, 
    and return the two lists using the reference parameters. 
    If the length is odd, the extra node should go in the front list. 
    Uses the fast/slow pointer strategy. */
void FrontBackSplit(Node* source,
                    Node** frontRef, Node** backRef)
{
    Node* fast;
    Node* slow;
    slow = source;
    fast = source->next;
  
    /* Advance 'fast' two nodes, and advance 'slow' one node */
    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }
  
    /* 'slow' is before the midpoint in the list, so split it in two 
    at that point. */
    *frontRef = source;
    *backRef = slow->next;
    slow->next = NULL;
}
  
/* Function to print nodes in a given linked list */
void printList(Node* node)
{
    while (node != NULL) {
        cout << node->data << " ";
        node = node->next;
    }
}
  
/* Function to insert a node at the beginning of the linked list */
void push(Node** head_ref, int new_data)
{
    /* allocate node */
    Node* new_node = new Node();
  
    /* put in the data */
    new_node->data = new_data;
  
    /* link the old list off the new node */
    new_node->next = (*head_ref);
  
    /* move the head to point to the new node */
    (*head_ref) = new_node;
}

// Given a reference (pointer to pointer) 
// to the head of a list and an int,
// appends a new node at the end
void append(Node** head_ref, int new_data)
{
    // 1. allocate node
    Node* new_node = new Node();
    //used in step 5
    Node *last = *head_ref;
    // 2. put in the data
    new_node->data = new_data;
    /* 3. This new node is going to be
    the last node, so make next of
    it as NULL*/
    new_node->next = NULL;
    /* 4. If the Linked List is empty,
    then make the new node as head */
    if (*head_ref == NULL)
    {
        *head_ref = new_node;
        return;
    }
 
    /* 5. Else traverse till the last node */
    while (last->next != NULL)
    {
        last = last->next;
    }
 
    /* 6. Change the next of last node */
    last->next = new_node;
    return;
}


/* Driver program to test above functions*/
int main()
{
    /* Start with the empty list */
    Node* res = NULL;
    Node* a = NULL;
  
    /* Let us create a unsorted linked lists to test the functions 
Created lists shall be a: 2->3->20->5->10->15 */
    push(&a, 15);
    push(&a, 10);
    push(&a, 5);
    push(&a, 20);
    push(&a, 3);
    push(&a, 2);
    append(&a, 277);
    append(&a, 0);
    append(&a, -277);

    /* Before Sort the created Linked List */
    cout << "Sorted Linked List is: \n";
    printList(a);

    /* Sort the above created Linked List */
    MergeSort(&a);
  
    cout << "Sorted Linked List is: \n";
    printList(a);
  
    return 0;
}
  
// This is code is contributed by rathbhupendra