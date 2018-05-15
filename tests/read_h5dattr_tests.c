/*
 * read_h5dattr_tests.c
 */


#include <cgreen/cgreen.h>
#include "./../src/read_h5dattr.h"


#define FNAME "./tests/sample.hdf5"
#define DSET_NAME "group1/dataset1"
#define D_VALUE 1.23456789
#define I_VALUE 1
#define S_VALUE "1.23456789"
#define S_FIXED_VALUE "s_fixed_value"
#define S_FIXED_SIZE 21


Describe(read_h5dattr);
BeforeEach(read_h5dattr) {};
AfterEach(read_h5dattr) {};


Ensure(read_h5dattr, reads_database_attribute_properly)
{
  double d_value;
  int i_value;
  char *s_fixed_value = malloc(S_FIXED_SIZE * sizeof(char));

  hid_t fid = H5Fopen(FNAME, H5F_ACC_RDONLY, H5P_DEFAULT);

  assert_that(
    read_h5dattr(fid, DSET_NAME, "s_fixed_value", H5T_STRING, s_fixed_value),
    is_equal_to(EXIT_SUCCESS));
  assert_that(s_fixed_value, is_equal_to_string(S_FIXED_VALUE));

  assert_that(
    read_h5dattr(fid, DSET_NAME, "i_value", H5T_NATIVE_INT32, &i_value),
    is_equal_to(EXIT_SUCCESS));
  assert_that(i_value, is_equal_to(I_VALUE));

  assert_that(
    read_h5dattr(fid, DSET_NAME, "d_value", H5T_NATIVE_DOUBLE, &d_value),
    is_equal_to(EXIT_SUCCESS));
  assert_that_double(d_value, is_equal_to_double(D_VALUE));

  H5Fclose(fid);
}
