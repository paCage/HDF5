/*
 * read_h5dattrs_tests.c
 */


#include <cgreen/cgreen.h>
#include "./read_h5dattrs.h"
#include "./High5_types.h"


#define FNAME "./sample.hdf5"
#define DSET_NAME "group1/dataset1"
#define D_VALUE 1.23456789
#define I_VALUE 1
#define S_VALUE "1.23456789"
#define S_FIXED_VALUE "s_fixed_value"
#define S_FIXED_SIZE 21


Describe(read_h5dattrs);
BeforeEach(read_h5dattrs) {};
AfterEach(read_h5dattrs) {};


Ensure(read_h5dattrs, reads_database_attribute_properly)
{
  double d_value;
  int i_value;
  char *s_fixed_value = malloc(S_FIXED_SIZE * sizeof(char));

  hid_t fid = H5Fopen(FNAME, H5F_ACC_RDONLY, H5P_DEFAULT);

  assert_that(
    read_h5dattrs(
      fid, DSET_NAME,
      "s_fixed_value", H5T_STRING, s_fixed_value, optional_attr,
      "i_value", H5T_NATIVE_INT32, &i_value, optional_attr,
      "d_value", H5T_NATIVE_DOUBLE, &d_value, optional_attr,
      NULL
    ),
    is_equal_to(EXIT_SUCCESS));

  assert_that(s_fixed_value, is_equal_to_string(S_FIXED_VALUE));
  assert_that(i_value, is_equal_to(I_VALUE));
  assert_that_double(d_value, is_equal_to_double(D_VALUE));

  assert_that(
    read_h5dattrs(
      fid, DSET_NAME,
      "Not_exist_attr_1", H5T_STRING, s_fixed_value, optional_attr,
      "Not_exist_attr_2", H5T_NATIVE_INT32, &i_value, optional_attr,
      "Not_exist_attr_3", H5T_NATIVE_DOUBLE, &d_value, optional_attr,
      NULL
    ),
    is_equal_to(EXIT_SUCCESS));

  assert_that(
    read_h5dattrs(
      fid, DSET_NAME,
      "Not_exist_attr_1", H5T_STRING, s_fixed_value, required_attr,
      "i_value", H5T_NATIVE_INT32, &i_value, optional_attr,
      "d_value", H5T_NATIVE_DOUBLE, &d_value, optional_attr,
      NULL
    ),
    is_equal_to(EXIT_FAILURE));

  H5Fclose(fid);
}
