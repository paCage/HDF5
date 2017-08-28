/*
 * close_h5_tests.c
 */


#include <cgreen/cgreen.h>
#include "./close_h5.h"


#define FPATH "./sample.hdf5"


Describe(close_h5);
BeforeEach(close_h5) {};
AfterEach(close_h5) {};


Ensure(close_h5, closes_an_hdf5_file_properly)
{
  H5open();
  hid_t file_id = H5Fopen(FPATH, H5F_ACC_RDONLY, H5P_DEFAULT);

  assert_that(close_h5(file_id), is_equal_to(EXIT_SUCCESS));

  H5close();
}
