#include "run_tests.h"

START_TEST(test_strlen_empty) {
  s21_size_t result = s21_strlen("");
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_strlen_four) {
  s21_size_t result = s21_strlen("five");
  ck_assert_int_eq(result, 4);
}
END_TEST

START_TEST(test_strlen_big) {
  char* big_text =
      "Does it follow that I reject all authority? Far from me such a thought. "
      "In the matter of boots, I refer to the authority of the bootmaker; "
      "concerning houses, canals, or railroads, I consult that of the "
      "architect or the engineer. For such or such special knowledge I apply "
      "to such or such a savant. "
      "But I allow neither the bootmaker nor the architect nor savant to "
      "impose his authority upon me. "
      "I listen to them freely and with all the respect merited by their "
      "intelligence, their character, their knowledge, reserving always my "
      "incontestable right of criticism and censure. "
      "I do not content myself with consulting a single authority in any "
      "special branch; I consult several; I compare their opinions, and choose "
      "that which seems to me the soundest. "
      "But I recognise no infallible authority, even in special questions; "
      "consequently, whatever respect I may have for the honesty and the "
      "sincerity of such or such individual, "
      "I have no absolute faith in any person";
  s21_size_t result = s21_strlen(big_text);
  s21_size_t lib_result = strlen(big_text);
  ck_assert_int_eq(result, lib_result);
}
END_TEST

START_TEST(test_null) {
  s21_size_t result = s21_strlen(S21_NULL);
  ck_assert_uint_eq(result, (s21_size_t)-1);
}
END_TEST

Suite* make_strlen_suite() {
  Suite* len_suite = suite_create("strlen");
  TCase* tc_core;

  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_strlen_empty);
  tcase_add_test(tc_core, test_strlen_four);
  tcase_add_test(tc_core, test_strlen_big);
  tcase_add_test(tc_core, test_null);

  suite_add_tcase(len_suite, tc_core);
  return len_suite;
}
