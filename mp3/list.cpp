/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 *
 * @author Chase Geigle
 * @date (created) Fall 2011
 * @date (modified) Spring 2012, Fall 2012
 *
 * @author Jack Toole
 * @date (modified) Fall 2011
 */

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
#include <iostream>
using namespace std;

template <class T>
List<T>::~List()
{
    /// @todo Graded in MP3.1
    clear();
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear()
{
    /// @todo Graded in MP3.1
    if (!empty()) {
        ListNode* curr = head;
        ListNode* next = head -> next;
        while (curr != NULL) {
            delete curr;
            curr = next;
            if (next != NULL) 
                next = next -> next;
        }
        head = NULL;
        tail = NULL;
        length = 0;
    }
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const& ndata)
{
    /// @todo Graded in MP3.1
    ListNode* node = new ListNode(ndata);
    if (!empty()) {
        node -> next = head;
        head -> prev = node;
        head = node;
    }
    else {
        head = node;
        tail = node;
    }
    length++;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack(const T& ndata)
{
    /// @todo Graded in MP3.1
    ListNode* node = new ListNode(ndata);
    if (!empty()) {
        tail -> next = node;
        node -> prev = tail;
        tail = node;
    }
    else {
        head = node;
        tail = node;
    }
    length++;
}

/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse()
{
    reverse(head, tail);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <class T>
void List<T>::reverse(ListNode*& startPoint, ListNode*& endPoint)
{
    /// @todo Graded in MP3.1
    if (startPoint == NULL || endPoint == NULL)
        return;
    ListNode* p = startPoint -> prev;
    ListNode* n = endPoint -> next;
    ListNode* end = endPoint;
    ListNode* curr = startPoint;
    ListNode* next = startPoint -> next;
    while (true) {
        curr -> next = n;
        if (n != NULL){
            n -> prev = curr;
        }
        else
            tail = startPoint;
        if (curr == end) 
            break;
        n = curr;
        curr = next;
        if (next != NULL) 
            next = next -> next;
    }
    end -> prev = p;
    if (p != NULL) 
        p -> next = end;
    else 
        head = end;
}


/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <class T>
void List<T>::reverseNth(int n)
{
    /// @todo Graded in MP3.1
    if (n >= length) {
        reverse();
        return;
    }
    ListNode* startPoint = head;
    ListNode* endPoint = head;
    ListNode* tmp = NULL;
    while (true) {
        for (int i = 0; i < n - 1; i++) {
            if (endPoint -> next != NULL)
                endPoint = endPoint -> next;
            else {
                reverse(startPoint, endPoint);
                return;
            }
        }
        tmp = endPoint -> next;
        reverse(startPoint, endPoint);
        if (tmp != NULL) {
            startPoint = tmp;
            endPoint = tmp;
        }
        else
            return;
    }
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <class T>
void List<T>::waterfall()
{
    /// @todo Graded in MP3.1
    if (empty())
        return;
    ListNode* curr = head;
    ListNode* next = head -> next;
    while (next != NULL && next != tail) {
        ListNode* tmp = next -> next;
        curr -> next = tmp;
        tmp -> prev = curr;
        curr = tmp;

        tail -> next = next;
        next -> prev = tail;
        tail = next;
        tail -> next = NULL;
        next = curr -> next;
    }
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <class T>
List<T> List<T>::split(int splitPoint)
{
    if (splitPoint > length)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode* secondHead = split(head, splitPoint);

    int oldLength = length;
    if (secondHead == head) {
        // current list is going to be empty
        head = NULL;
        tail = NULL;
        length = 0;
    } else {
        // set up current list
        tail = head;
        while (tail->next != NULL)
            tail = tail->next;
        length = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head = secondHead;
    ret.tail = secondHead;
    if (ret.tail != NULL) {
        while (ret.tail->next != NULL)
            ret.tail = ret.tail->next;
    }
    ret.length = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <class T>
typename List<T>::ListNode* List<T>::split(ListNode* start, int splitPoint)
{
    /// @todo Graded in MP3.2
    ListNode* curr = start;
    for (int i = 0; i < splitPoint; i++) {
        if (curr != NULL) 
            curr = curr -> next;
        else
            break;
    }
    if (curr != NULL) {
        if (curr -> prev != NULL)
            curr -> prev -> next = NULL;
        curr -> prev = NULL;
        return curr;
    }
    else
        return NULL; 
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
void List<T>::mergeWith(List<T>& otherList)
{
    // set up the current list
    head = merge(head, otherList.head);
    tail = head;

    // make sure there is a node in the new list
    if (tail != NULL) {
        while (tail->next != NULL)
            tail = tail->next;
    }
    length = length + otherList.length;

    // empty out the parameter list
    otherList.head = NULL;
    otherList.tail = NULL;
    otherList.length = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <class T>
typename List<T>::ListNode* List<T>::merge(ListNode* first, ListNode* second)
{
    /// @todo Graded in MP3.2
    if (first == NULL) 
        return second;
    if (second == NULL)
        return first;
    ListNode* newhead = NULL;
    ListNode* curr_1 = first;
    ListNode* curr_2 = second;
    ListNode* prev = NULL;
    while (curr_1 != NULL && curr_2 != NULL) {
        if (curr_1 -> data < curr_2 -> data) {
            if (newhead == NULL) {
                newhead = curr_1;
                prev = curr_1;
            }
            else {
                prev -> next = curr_1;
                curr_1 -> prev = prev;
                prev = prev -> next;
            }
            curr_1 = curr_1 -> next;
        }
        else {
            if (newhead == NULL) {
                newhead = curr_2;
                prev = curr_2;
            }
            else {
                prev -> next = curr_2;
                curr_2 -> prev = prev;
                prev = prev -> next;
            }
            curr_2 = curr_2 -> next;
        }
    }
    if (curr_1 != NULL) {
        prev -> next = curr_1;
        curr_1 -> prev = prev;
    }
    if (curr_2 != NULL) {
        prev -> next = curr_2;
        curr_2 -> prev = prev;
    }
    return newhead;
}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <class T>
void List<T>::sort()
{
    if (empty())
        return;
    head = mergesort(head, length);
    tail = head;
    while (tail->next != NULL)
        tail = tail->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <class T>
typename List<T>::ListNode* List<T>::mergesort(ListNode* start, int chainLength)
{
    /// @todo Graded in MP3.2
    if (chainLength < 2)
        return start;
    ListNode* start_2 = split(start, int(chainLength / 2));
    ListNode* h1 = mergesort(start, int(chainLength / 2));
    ListNode* h2 = mergesort(start_2, chainLength - int(chainLength / 2));
    return merge(h1, h2);
}
