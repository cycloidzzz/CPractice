#ifndef CPRACTICE_LIST_LIST_H
#define CPRACTICE_LIST_LIST_H

#include <stddef.h>

/**
 * @brief calculate the offset of a member from a structure.
 *
 * @type: the type of the container struct tha the member belongs to.
 * @member: the name of the member within the struct.
 *
 */
#define list_offsetof(type, member) ((void *)&(((type *)0)->member))

/**
 * @brief cast a member @member of a structure to the corresponding containing
 * structure.
 *
 * @ptr: the pointer of the member.
 * @type: the type of the container struct that the member belongs to.
 * @member: the name of the member within the struct.
 */
#define container_of(ptr, type, member)                                        \
  ({                                                                           \
    void *__mptr = (void *)(ptr);                                              \
    ((type *)(__mptr - list_offsetof(type, member)));                          \
  })

typedef struct list_node_struct_t {
  struct list_node_struct_t *prev;
  struct list_node_struct_t *next;
} list_node_t;

#define LIST_HEAD_INIT(name)                                                   \
  { &(name), &(name) }

#define LIST_HEAD(name) list_node_t name = LIST_HEAD_INIT(name)

static inline int list_empty(list_node_t *head) {
  return ((head->prev) == head);
}

/**
 * @brief Insert a new node @node between two known consecutive entries @prev
 * and @next.
 *
 * @param node
 * @param prev
 * @param next
 */
static inline void list_add_impl(list_node_t *node, list_node_t *prev,
                                 list_node_t *next) {
  next->prev = node;
  node->next = next;
  node->prev = prev;
  prev->next = node;
}

/**
 * @brief Insert a new entry @node at the front of a list which starts at @head.
 *
 * @param node: the new entry to be added to the list.
 * @param head: the head list_node of the list to be added.
 */
static inline void list_add(list_node_t *node, list_node_t *head) {
  list_add_impl(node, head, head->next);
}

/**
 * @brief Insert a new entry @node at the back of a list which start at @head.
 *
 * @param node: the new entry to be added to the list.
 * @param head: the head list_node of the list to be added.
 */
static inline void list_add_tail(list_node_t *node, list_node_t *head) {
  list_add_impl(node, head->prev, head);
}

/**
 * @brief Delete a node from the list by resetting the file `next` of its prev
 * node and the `prev` field of its next node. This is an implementation
 * function and should not be called by users.
 *
 * @param prev The previous entry of the node to be deleted from the list.
 * @param next The next entry of the node to be deleted from the list.
 */
static inline void list_del_impl(list_node_t *prev, list_node_t *next) {
  next->prev = prev;
  prev->next = next;
}

/**
 * @brief Delete an entry @node from the current list.
 *
 * @param node: the entry to be deleted from the list.
 */
static inline void list_del(list_node_t *node) {
  list_del_impl(node->prev, node->next);
  node->prev = NULL;
  node->next = NULL;
}

#endif // ! CPRACTICE_LIST_LIST_H