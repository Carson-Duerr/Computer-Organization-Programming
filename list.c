/**
 * CS 2110 - Fall 2019 - Project 5
 *
 * @author cduerr3
 *
 * list.c: Complete the functions!
 */

/**
 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!-IMPORTANT-!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 * For any function that must use malloc, if malloc returns NULL, the function
 * itself should return NULL if needs to return something (or return 0 if
 * the function returns a int).
 */

// Do not add ANY additional includes!!!
#include "list.h"
// This is used so that you guys can print stuff out
#include <stdio.h>

/* You should NOT have any global variables. */

/* The create_node function is static because this is the only file that should
   have knowledge about the nodes backing the linked struct list. */
// static inline ListNode *create_node(Crab *data);

/** create_node
  *
  * Helper function that creates a struct list_node by allocating memory for it on the heap.
  * Be sure to initialize its next pointer to NULL.
  *
  * If malloc returns NULL, you should return NULL to indicate failure.
  *
  * @param data a void pointer to data the user wants to store in the struct list
  * @return a struct list_node
  */
ListNode *create_node(Crab *data)
{
    UNUSED_PARAMETER(data);

    ListNode *newNode = (ListNode *) malloc(sizeof(ListNode));
    if (!newNode) {
      return NULL;
    }

    newNode->next = NULL;
    newNode->data = data;

    return newNode;
}

/** create_list
  *
  * Creates a struct list by allocating memory for it on the heap.
  * Be sure to initialize head to NULL.
  *
  * If malloc returns NULL, you should return NULL to indicate failure.
  *
  * @return a pointer to a new struct list or NULL on failure
  */
List *create_list(void)
{
    List *newList = (List *) malloc(sizeof(List));
    if(!newList) {
      return NULL;
    }

    newList->head = NULL;

    return newList;
}

/** push_back
  *
  * Adds the ListNode to the back of the list
  *
  * @param listToAddTo a pointer to the List structure
  * @param node the node to add to the list
  * @return 0 if the list or if the node is null (do not add the data in this case)
  *         (if the data is NULL, you still add it)
  *         otherwise return 1
  */
int push_back(List *listToAddTo, ListNode *node)
{
    UNUSED_PARAMETER(listToAddTo);
    UNUSED_PARAMETER(node);

    if (listToAddTo == NULL || node == NULL) {
      return 0;
    }

    if (listToAddTo->head == NULL) {
      listToAddTo->head = node;
      return 1;
    } else {
      ListNode *current = listToAddTo->head;
      while (current->next != NULL) {
        current = current->next;
      }
      current->next = node;
      return 1;
    }

    return 0;
}

/** remove_node
  *
  * Remove the first node with which the crab data's crabtitude is the specified crabbiness.
  * The node should be removed completely, but the node's data should be returned through the
  * dataOut parameter
  *
  * @param listToAddTo a pointer to the struct list structure
  * @param dataOut a double pointer to return the Crab data that is being removed from the list
  * @param crabbiness the specific crabtitude of which crab you wil be removing
  * @return 0 if the struct list is NULL, there is no crab with the specified crabbiness,
  *         or the dataOut is NULL
  *         otherwise return 1
  */
int remove_node(List *listToRemoveFrom, Crab **dataOut, int crabbiness)
{
    UNUSED_PARAMETER(listToRemoveFrom);
    UNUSED_PARAMETER(dataOut);
    UNUSED_PARAMETER(crabbiness);

    if (listToRemoveFrom == NULL || dataOut == NULL) {
      return 0;
    }

    ListNode *current = listToRemoveFrom->head;
    if (crabbiness == current->data->crabtitude) {
        *dataOut = current->data;
        listToRemoveFrom->head = current->next;
        free(current);
        return 1;
    }
    while (current->next != NULL) {
      if (crabbiness == current->next->data->crabtitude) {
        *dataOut = current->next->data;
        ListNode *newNext = current->next->next;
        free(current->next);
        current->next = newNext;
        return 1;
      }

      current = current->next;
    }

    return 0;
}

/** destroy_crab
  *
  * Destroys all data in the crab. Make sure to free any crab attributes that have memory
  * allocated for them.
  *
  * @param crab The crab to destroy
*/
void destroy_crab(Crab *crab) {
    UNUSED_PARAMETER(crab);
    if (crab == NULL) {
      return;
    }
    free(crab->name);
    free(crab);
}

/** destroy
  *
  * Destroys the list. This frees the list, nodes within the list, and data within the nodes
  * (destroy_crab can help with free'ing the data within the nodes). Make sure to check that listToEmpty
  * and is not NULL before using it.
  *
  * @param listToEmpty a pointer to the struct list structure
  */
void destroy(List *listToEmpty)
{
    UNUSED_PARAMETER(listToEmpty);

    if (listToEmpty == NULL) {
      return;
    }

    ListNode *current = listToEmpty->head;
    while (current != NULL) {
      if (current->data != NULL) {
        destroy_crab(current->data);
      }
      ListNode *destroyedNode = current;
      current = current->next;
      free(destroyedNode);
    }

    free(listToEmpty);


}

/** copy_crab
  *
  * A function that will deep copy the crab and all its attributes. For any malloc
  * failures, you must not leak memory. This means that if any memory failures occur, before
  * you return 0, you must go back and free any data that you allocated memory for.
  *
  * @param crab_to_copy The crab to copy
  * @param copied_crab A double pointer used to return the copied crab
  * @return 0 if malloc fails, crab_to_copy is null, or copied_crab is null
  *         1 otherwise
*/
int copy_crab(Crab *crab_to_copy, Crab **copied_crab) {
    UNUSED_PARAMETER(crab_to_copy);
    UNUSED_PARAMETER(copied_crab);

    if (crab_to_copy == NULL || copied_crab == NULL) {
      return 0;
    }

    Crab *newCrab = (Crab *) malloc(sizeof(Crab));
    if(!newCrab) {
      return 0;
    }
    char *newName = (char *) malloc(sizeof(crab_to_copy->name) *sizeof(char)+5);
    if (!newName) {
      free(newCrab);
      return 0;
    }
    strcpy(newName, crab_to_copy->name);

    newCrab->name = newName;
    newCrab->crabtitude = crab_to_copy->crabtitude;
    *copied_crab = newCrab;

    return 1;
}

/** copy_list
  *
  * Create a new list structure, new nodes, and new copies of the data
  * (use the copy_crab function for this).
  *
  * If listToCopy is NULL or empty return NULL. For memory allocations
  * failures, including if crab_copy returns 0 (indicating a memory
  * allocation failure), your code must not leak memory. This means that if any
  * memory allocation failures occur, before you return NULL, you must go back
  * and free all data in the new list, nodes in the new list, and
  * the new list itself (you may find the destroy function useful for
  * this).
  *
  *
  * @param listToCopy A pointer to the struct list structure to make a copy of
  * @return The list structure created by copying the old one, or NULL on
  *         failure (includes any of the parameters being null)
  */
List *copy_list(List *listToCopy)
{
    UNUSED_PARAMETER(listToCopy);

    if (listToCopy == NULL ) {
      return NULL;
    }

    List *newList = (List *) malloc(sizeof(List));
    if (!newList) {
      return NULL;
    }

    Crab **dataOutCrab = (Crab **) malloc(sizeof(Crab*));
    if (!dataOutCrab) {
      free(newList);
      return NULL;
    }

    Crab** anything = dataOutCrab;
    copy_crab(listToCopy->head->data, dataOutCrab);
    ListNode *current = create_node(*dataOutCrab);
    if (!current) {
      free(newList);
      free(anything);
      return NULL;
    }
    newList->head = current;
    ListNode *nodeToCopy = listToCopy->head;

    while(nodeToCopy->next) {
      Crab **dataOutCrab1 = (Crab **) malloc(sizeof(Crab*));
      if (!dataOutCrab) {
        free(newList);
        return NULL;
      }

      Crab** anything1 = dataOutCrab1;
      copy_crab(nodeToCopy->next->data, dataOutCrab1);
      ListNode *copiedNode = create_node(*dataOutCrab1);
      if (!copiedNode) {
        destroy(newList);
        free(anything);
        free(dataOutCrab);
        free(anything1);
        return NULL;
      }
      current->next = copiedNode;
      current = copiedNode;
      nodeToCopy = nodeToCopy->next;
      free(anything1);
    }

    current->next = NULL;
    free(anything);
    return newList;
}

/** compare_crabtitude
 *
 * This method compares the crabtitudes of two crabs
 * A null crab has a larger crabtitude than a non-null crab
 *
 * @param a A crab
 * @param b Another crab
 * @return >0 if crab a's crabtitude > crab b's crabtitude
 *          0 if crab a's crabtitude = crab b's crabtitude
 *         <0 if crab a's crabtitude < crab b's crabtitude
 **/
int compare_crabtitude(Crab *a, Crab *b) {
    UNUSED_PARAMETER(a);
    UNUSED_PARAMETER(b);
    if (a == NULL || b == NULL) {
      if (a == NULL && b != NULL) {
        return 1;
      }
      if (b == NULL && a != NULL ) {
        return -1;
      }
      return 0;
    }


    if (a->crabtitude > b->crabtitude) {
      return 1;
    }

    if (a->crabtitude < b->crabtitude) {
      return -1;
    }

    return 0;
}

/** compare_name
 *
 * This method compares the name of two crabs
 * A null crab has a larger name than a non-null crab
 * (Hint) Take a look at the strcmp man page
 *
 * @param a A crab
 * @param b Another crab
 * @return >0 if crab a's name > crab b's name
 *          0 if crab a's name = crab b's name
 *         <0 if crab a's name < crab b's name
 **/
int compare_name(Crab *a, Crab *b) {
    UNUSED_PARAMETER(a);
    UNUSED_PARAMETER(b);

    if (a == NULL || b == NULL) {
      if (a == NULL && b != NULL) {
        return 1;
      }
      if (b == NULL && a != NULL ) {
        return -1;
      }
      return 0;
    }

    if (strcmp(a->name, b->name) < 0) {
      return -1;
    }
    if (strcmp(a->name, b->name) > 0) {
      return 1;
    }

    return 0;
}

/** swap_nodes
 *
 * This method swaps two nodes in place. For example if our list was
 * A -> B -> C -> D and we called swap_nodes(b, d, list), the resulting list would be
 * A -> D -> C -> B
 * Note: The nodes will either be NULL or will exist in the list
 *
 * @param node_a A node to swap
 * @param node_b The other node to swap
 * @param list The list within which the nodes will be swapped
 * @return 0 if any of the parameters are null or node_a = node_b
 *         1 on success
**/
int swap_nodes(ListNode *node_a, ListNode *node_b, List *list) {
    UNUSED_PARAMETER(node_a);
    UNUSED_PARAMETER(node_b);
    UNUSED_PARAMETER(list);

    if (node_a == NULL || node_b == NULL || list == NULL || node_a == node_b) {
      return 0;
    }

    ListNode *previousA = NULL;
    ListNode *currentA = list->head;
    while (currentA && currentA != node_a) {
      previousA = currentA;
      currentA = currentA->next;
    }

    ListNode *previousB = NULL;
    ListNode *currentB = list->head;
    while (currentB && currentB != node_b) {
      previousB = currentB;
      currentB = currentB->next;
    }

    if (previousA != NULL) {
      previousA->next = currentB;
    } else {
      list->head = currentB;
    }

    if (previousB != NULL) {
      previousB->next = currentA;
    } else {
      list->head = currentA;
    }

    ListNode *t = currentB->next;
    currentB->next = currentA->next;
    currentA->next = t;

    return 1;
}

/** sort
 *
 * A function to sort the nodes in ascending order (in place) using the comparator function passed in.
 * Recommend using bubble sort (Hint: Utilize the swap_nodes() function above)
 *
 * @param list The list to sort
 * @param compare_func A function pointer that denotes which compare method (written above) will be utilized.
 *                     Assume that the return value of the function pointer will be the return value of the comparator methods
 *                     written above
 * @return 0 if list is null, the list is empty, or compare_func is null
 *         1 on success
*/
int sort(List *list, int (*compare_func)(Crab *a, Crab *b)) {
    UNUSED_PARAMETER(list);
    UNUSED_PARAMETER(compare_func);

    if (list == NULL || list->head == NULL || compare_func == NULL) {
      return 0;
    }

    int i = 0;

    while(i == 0) {
      i = 1;

      ListNode *a = list->head;
      ListNode *b = list->head->next;

      while (a != NULL && b != NULL) {
        if (compare_func(a->data, b->data) > 0) {
          i = 0;
          swap_nodes(a, b, list);
        }
        a = a->next;
        b = b->next;
      }
    }

    return 1;
}

/** list_to_array
 *
 * This function will create and utilize a new structure to represent our crabs.
 * First, create an array of crab pointers, one for each crab in the linked list
 * Next, iterate through the linked list, setting the crab pointer to its new home in the array
 * and removing the linked list structure (Hint: You want to free the linked list but not the crab itself)
 * Finally, return the crab array so that they can have their CRAB RAVE
 *
 * @param list The linked list to be converted to an array
 * @param size The amount of crabs in the list
 * @return NULL if list is null, the list is empty, or their is a malloc failure
 *         An array to crab pointers otherwise
*/
Crab **list_to_array(List *list, int size) {
    UNUSED_PARAMETER(list);
    UNUSED_PARAMETER(size);

    if (list == NULL || size == 0) {
      return NULL;
    }

    Crab **crabArray = malloc(size *sizeof(Crab *));
    if (!crabArray) {
      return NULL;
    }

    ListNode *current = list->head;
    int index = 0;
    while (current != NULL) {
      crabArray[index] = current->data;
      ListNode *destroyedNode = current;
      current = current->next;
      free(destroyedNode);
      index++;
    }
    free(list);

    return crabArray;
}
