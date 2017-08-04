/*
 * read_h5attr_tests.c
 */


#include <cgreen/cgreen.h>
#include "./read_h5attr.h"


#define FNAME "./sample.hdf5"
#define D_VALUE 1.23456789
#define I_VALUE 1
#define S_VALUE "1.23456789"
#define S_FIXED_VALUE "s_fixed_value"
#define S_FIXED_SIZE 21


Describe(read_h5attr);
BeforeEach(read_h5attr) {};
AfterEach(read_h5attr) {};


Ensure(read_h5attr, must_be_able_to_read_different_types_of_attributes)
{
  double d_value;
  int i_value;
  char *s_value, *s_fixed_value;

  hid_t fid = H5Fopen(FNAME, H5F_ACC_RDONLY, H5P_DEFAULT);

  s_fixed_value = malloc(S_FIXED_SIZE * sizeof(char));

  assert_that(
    read_h5attr(fid, "group1", "d_value", H5T_NATIVE_DOUBLE, &d_value),
    is_equal_to(EXIT_SUCCESS));
  assert_that_double(d_value, is_equal_to_double(D_VALUE));

  assert_that(
    read_h5attr(fid, "group1", "i_value", H5T_NATIVE_INT, &i_value),
    is_equal_to(EXIT_SUCCESS));
  assert_that(i_value, is_equal_to(I_VALUE));

  assert_that(
    read_h5attr(fid, "group1", "s_value", H5T_C_S1, &s_value),
    is_equal_to(EXIT_SUCCESS));
  assert_that(s_value, is_equal_to_string(S_VALUE));

  assert_that(
    read_h5attr(fid, "group1", "s_fixed_value", H5T_STRING, s_fixed_value),
    is_equal_to(EXIT_SUCCESS));
  assert_that(s_fixed_value, is_equal_to_string(S_FIXED_VALUE));

  assert_that(
    read_h5attr(fid, "group2", "d_value", H5T_NATIVE_DOUBLE, &d_value),
    is_equal_to(EXIT_SUCCESS));
  assert_that_double(d_value, is_equal_to_double(D_VALUE));

  assert_that(
    read_h5attr(fid, "group2", "i_value", H5T_NATIVE_INT, &i_value),
    is_equal_to(EXIT_SUCCESS));
  assert_that(i_value, is_equal_to(I_VALUE));

  assert_that(
    read_h5attr(fid, "group2", "s_value", H5T_C_S1, &s_value),
    is_equal_to(EXIT_SUCCESS));
  assert_that(s_value, is_equal_to_string(S_VALUE));

  free(s_fixed_value);
}
