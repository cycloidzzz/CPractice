#include "debug.h"
#include "list.h"
#include "utils.h"
#include <stdio.h>

#include "CUnit/Basic.h"

typedef struct {
  int number;
  list_node_t node;
} list_int_t;

void test_setup_list() {
  LIST_HEAD(simple_list);
  CU_ASSERT_EQUAL(simple_list.prev, simple_list.next);
}

void test_container_of() {
  list_int_t node_int;

  list_node_t *node_int_sink = &(node_int.node);
  CU_ASSERT_EQUAL(container_of(node_int_sink, list_int_t, node), &node_int);

  CPRACTICE_LOG(INFO, "The pointer of node_int is: %p", &node_int);
  CPRACTICE_LOG(INFO, "The pointer calculated by container_of() is: %p\n",
                container_of(node_int_sink, list_int_t, node));
}

void test_list_add() {
  LIST_HEAD(node_list);

  list_int_t element_lists[10];

  for (int i = 0; i < 10; i++) {
    element_lists[i].number = i * i;
    list_add(&(element_lists[i].node), &node_list);
  }

  list_node_t *cur_node = node_list.next;

  for (int i = 9; i >= 0; --i) {
    list_int_t *entry_ptr = container_of(cur_node, list_int_t, node);
    CU_ASSERT_EQUAL(entry_ptr->number, i * i);
    cur_node = cur_node->next;
  }
}

void test_list_add_tail() {
  LIST_HEAD(node_list);

  list_int_t element_lists[10];

  for (int i = 0; i < 10; i++) {
    element_lists[i].number = i * i;
    list_add_tail(&(element_lists[i].node), &node_list);
  }

  list_node_t *cur_node = node_list.next;
  for (int i = 0; i < 10; i++) {
    list_int_t *entry_ptr = container_of(cur_node, list_int_t, node);
    CU_ASSERT_EQUAL(entry_ptr->number, i * i);
    cur_node = cur_node->next;
  }
}

static const int kNumListTests = 4;
static cunit_unittest_t cuint_tests[kNumListTests] = {
    {"test of setup list with LIST_HEAD", test_setup_list},
    {"test of container_of()", test_container_of},
    {"test of list_add", test_list_add},
    {"test of list_add_tail", test_list_add_tail},
};

int main() {
  CU_pSuite ptr_suite = NULL;

  if (CUE_SUCCESS != CU_initialize_registry()) {
    return CU_get_error();
  }

  ptr_suite = CU_add_suite("sutie_1", NULL, NULL);
  if (NULL == ptr_suite) {
    goto list_test_error;
  }

  for (int i = 0; i < kNumListTests; i++) {
    if (NULL == CU_add_test(ptr_suite, cuint_tests[i].description,
                            cuint_tests[i].test_function)) {
      goto list_test_error;
    }
  }

  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();

list_test_error:
  CU_cleanup_registry();
  return CU_get_error();
}