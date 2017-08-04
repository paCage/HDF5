/*
 * read_h5attrs_tests.c
 */


#include <cgreen/cgreen.h>
#include "./read_h5attrs.h"


#define FNAME "./sample.hdf5"
#define D_VALUE 1.23456789
#define I_VALUE 1
#define S_VALUE "1.23456789"
#define S_FIXED_VALUE "s_fixed_value"
#define S_FIXED_SIZE 21


Describe(read_h5attrs);
BeforeEach(read_h5attrs) {};
AfterEach(read_h5attrs) {};


Ensure(read_h5attrs, reads_a_list_of_attributes_from_one_group)
{
  double d_value;
  int i_value;
  char *s_value, *s_fixed_value;

  s_fixed_value = malloc(S_FIXED_SIZE * sizeof(char));

  hid_t fid = H5Fopen(FNAME, H5F_ACC_RDONLY, H5P_DEFAULT);

  assert_that(
    read_h5attrs(fid, "group1",
                 "s_value", H5T_C_S1, &s_value,
                 "i_value", H5T_NATIVE_INT, &i_value,
                 "d_value", H5T_NATIVE_DOUBLE, &d_value,
                 "s_fixed_value", H5T_STRING, s_fixed_value,
                 NULL),
    is_equal_to(EXIT_SUCCESS)
  );

  assert_that_double(d_value, is_equal_to_double(D_VALUE));
  assert_that(i_value, is_equal_to(I_VALUE));
  assert_that(s_value, is_equal_to_string(S_VALUE));
  assert_that(s_fixed_value, is_equal_to_string(S_FIXED_VALUE));

  assert_that(
    read_h5attrs(fid, "group2",
                 "s_value", H5T_C_S1, &s_value,
                 "i_value", H5T_NATIVE_INT, &i_value,
                 "d_value", H5T_NATIVE_DOUBLE, &d_value,
                 NULL),
    is_equal_to(EXIT_SUCCESS)
  );

  assert_that_double(d_value, is_equal_to_double(D_VALUE));
  assert_that(i_value, is_equal_to(I_VALUE));
  assert_that(s_value, is_equal_to_string(S_VALUE));

  free(s_fixed_value);
}
