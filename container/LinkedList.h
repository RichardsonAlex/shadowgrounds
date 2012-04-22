#ifndef container_LinkedList_h
#define container_LinkedList_h

//
// (Two way) linked list class
// Copyright(C) Jukka Kokkonen, 2000-2002
//
// No out of memory exception check...
//
// v1.1.1 - 3.7.2002 - modified to catch unsafe removes when iterating
// v1.1 - 14.6.2002 - added seperate iterator classes
//

#include <cassert>
#include <list>
#include <cstdlib>
// #include "csp/compat.h"
#include "EmptyLinkedListException.h"
#include "EmptyIteratorException.h"

template<typename T> class LinkedList;
template<typename T> class ListNode;
template<typename T> class LinkedListIterator;
template<typename T> class SafeLinkedListIterator;


template<typename T>
class ListNode
{
  public:
    ListNode(const T& itm);
  private:
    ListNode *next;
    ListNode *prev;
    T item;

  friend class LinkedList<T>;
  friend class LinkedListIterator<T>;
  friend class SafeLinkedListIterator<T>;
};

template<typename T>
class LinkedList
{
  private:
    ListNode<T> *first;
    ListNode<T> *last;
    ListNode<T> *walk_node;

    int remove_count;
    friend class LinkedListIterator<T>;
    friend class SafeLinkedListIterator<T>;

  public:
    LinkedList();
    ~LinkedList();
    void prepend(const T& itm);
    void append(const T& itm);
    void remove(const T& itm);
    T popFirst() throw (EmptyLinkedListException*);
    T popLast() throw (EmptyLinkedListException*);
    T& peekFirst() throw (EmptyLinkedListException*);
    T& peekLast() throw (EmptyLinkedListException*);
    bool isEmpty();

    // iteration
    // deprecated: use the seperate iterators instead
    //TODO remove
    T& iterateNext() throw (EmptyIteratorException *);
    bool iterateAvailable();
    void resetIterate();
};

// basic iterator
// items should not be deleted from the list while using iterator.
template<typename T>
class LinkedListIterator
{
  private:
    const LinkedList<T>* linkedList;
    ListNode<T>* walk_node;
    int remove_count;

  public:
    LinkedListIterator(const LinkedList<T>& ll);
    LinkedListIterator(const LinkedList<T>* llp);
    LinkedListIterator(const LinkedListIterator<T>& other);
    ~LinkedListIterator();
    bool iterateAvailable();
    T& iterateNext() throw (EmptyIteratorException*);
};

// safe iterator, keeps an internal copy of the linked list, making it
// possible to delete items from the list safely while using iterator.
// not very effective though.
template<typename T>
class SafeLinkedListIterator
{
  private:
    LinkedList<T> linkedList;
    ListNode<T>* walk_node;

  public:
    SafeLinkedListIterator(const LinkedList<T>& ll);
    SafeLinkedListIterator(const LinkedList<T>* ll);
    SafeLinkedListIterator(const SafeLinkedListIterator<T>& other);
    ~SafeLinkedListIterator();
    bool iterateAvailable() const;
    T& iterateNext() throw (EmptyIteratorException*);
};

//TODO enable pool or replace with std::list and pool allocator
template<typename T>
inline ListNode<T>::ListNode(const T& itm) : next(0), prev(0), item(itm) {}

template<typename T>
inline LinkedList<T>::LinkedList() : first(0), last(0), walk_node(0), remove_count(0) {}

template<typename T>
inline LinkedList<T>::~LinkedList()
{
  while (!isEmpty())
  {
    popFirst();
  }
}

template<typename T>
inline void LinkedList<T>::append(const T& itm)
{
  ListNode<T>* node = new ListNode<T>(itm);
  if (isEmpty())
  {
    first = node;
    last = node;
  } else {
    node->next = 0;
    node->prev = last;
    last->next = node;
    last = node;
  }
}

template<typename T>
inline void LinkedList<T>::prepend(const T& itm)
{
  ListNode<T>* node = new ListNode<T>(itm);

  if (isEmpty())
  {
    first = node;
    last = node;
  } else {
    node->next = first;
    node->prev = 0;
    first->prev = node;
    first = node;
  }
}

template<typename T>
inline void LinkedList<T>::remove(const T& itm)
{
  ListNode<T> *tmp = first;

  while (tmp != 0)
  {
    if (tmp->item == itm)
    {
      if (first == tmp) first = tmp->next;
      if (last == tmp) last = tmp->prev;
      if (tmp->prev != NULL) (tmp->prev)->next = tmp->next;
      if (tmp->next != NULL) (tmp->next)->prev = tmp->prev;

      delete tmp;
      remove_count++;
      break;
    }
    tmp = tmp->next;
  }
}
template<typename T>
inline T LinkedList<T>::popFirst() throw (EmptyLinkedListException*)
{
  ListNode<T>* tmp = first;

  if (!tmp)
  {
    throw(new EmptyLinkedListException());
  }

  //if (last->prev == first) last->prev = NULL;
  if (first->next != NULL)
    (first->next)->prev = NULL;
  first = tmp->next;
  if (first == NULL)
    last = NULL;

  T ret = tmp->item;
  delete tmp;
  remove_count++;
  return ret;
}
template<typename T>
inline T LinkedList<T>::popLast() throw (EmptyLinkedListException *)
{
  ListNode<T>* tmp = last;
  if (!tmp)
  {
    throw(new EmptyLinkedListException());
  }

  //if (first->next == last) first->next = NULL;
  if (last->prev != NULL)
    (last->prev)->next = NULL;
  last = tmp->prev;
  if (last == NULL)
    first = NULL;

  T ret = tmp->item;
  delete tmp;
  remove_count++;
  return ret;
}

template<typename T>
inline T& LinkedList<T>::peekFirst() throw (EmptyLinkedListException*)
{
  if (!first)
  {
    throw(new EmptyLinkedListException());
  }
  return first->item;
}

template<typename T>
inline T& LinkedList<T>::peekLast() throw (EmptyLinkedListException*)
{
  if (!last)
  {
    throw(new EmptyLinkedListException());
  }
  return last->item;
}

template<typename T>
inline bool LinkedList<T>::isEmpty()
{
  return first == NULL;
}

template<typename T>
inline T& LinkedList<T>::iterateNext() throw (EmptyIteratorException*)
{
  if (!walk_node)
  {
    throw(new EmptyIteratorException());
  }

  T& ret = walk_node->item;
  walk_node = walk_node->next;
  return ret;
}

template<typename T>
inline bool LinkedList<T>::iterateAvailable()
{
  return walk_node != NULL;
}

template<typename T>
inline void LinkedList<T>::resetIterate()
{
  walk_node = first;
}

template<typename T>
inline LinkedListIterator<T>::LinkedListIterator(const LinkedList<T>& ll): linkedList(&ll)
{
  walk_node = linkedList->first;
  remove_count = linkedList->remove_count;
}

template<typename T>
inline LinkedListIterator<T>::LinkedListIterator(const LinkedList<T>* llp): linkedList(llp)
{
  walk_node = linkedList->first;
  remove_count = linkedList->remove_count;
}


template<typename T>
inline LinkedListIterator<T>::~LinkedListIterator() {}

template<typename T>
inline T& LinkedListIterator<T>::iterateNext() throw (EmptyIteratorException*)
{
  #ifdef _DEBUG
  // this is to catch unsafe node removals while iterating.
  // (as that may cause undefined behaviour)
  if (linkedList->remove_count != this->remove_count)
  {
    abort();
  }
  #endif

  if (!walk_node)
  {
    throw(new EmptyIteratorException());
  }

  T& ret = walk_node->item;
  walk_node = walk_node->next;
  return ret;
}

template<typename T>
inline bool LinkedListIterator<T>::iterateAvailable()
{
  return walk_node != NULL;
}

template<typename T>
inline SafeLinkedListIterator<T>::SafeLinkedListIterator(const LinkedList<T>& ll)
{
  const ListNode<T> *tmp = ll.first;
  while (tmp != NULL)
  {
    linkedList.append(tmp->item);
    tmp = tmp->next;
  }
  walk_node = linkedList.first;
}

template<typename T>
inline SafeLinkedListIterator<T>::SafeLinkedListIterator(const LinkedList<T>* ll)
{
  const ListNode<T> *tmp = ll->first;
  while (tmp != NULL)
  {
    linkedList.append(tmp->item);
    tmp = tmp->next;
  }
  walk_node = linkedList.first;
}

template<typename T>
inline SafeLinkedListIterator<T>::~SafeLinkedListIterator() {}

template<typename T>
inline T& SafeLinkedListIterator<T>::iterateNext() throw (EmptyIteratorException*)
{
  if (!walk_node)
  {
    throw(new EmptyIteratorException());
  }

  T& ret = walk_node->item;
  walk_node = walk_node->next;
  return ret;
}

template<typename T>
inline bool SafeLinkedListIterator<T>::iterateAvailable() const
{
  return walk_node != NULL;
}

template<typename T>
inline LinkedListIterator<T>::LinkedListIterator(const LinkedListIterator<T>& other)
    : linkedList(other.linkedList), walk_node(other.walk_node), remove_count(other.remove_count)
{
}

template<typename T>
inline SafeLinkedListIterator<T>::SafeLinkedListIterator(const SafeLinkedListIterator<T>& other)
{
    const ListNode<T> *tmp = other.linkedList.first;
    while (tmp != NULL)
    {
      linkedList.append(tmp->item);
      tmp = tmp->next;
    }
    walk_node = linkedList.first;
}

#endif
