/*
 * open_h5_tests.c
 */


#include <cgreen/cgreen.h>
#include "./../src/open_h5.h"


#define FPATH "./tests/sample.hdf5"


Describe(open_h5);
BeforeEach(open_h5) {};
AfterEach(open_h5) {};


Ensure(open_h5, opens_an_hdf5_file_properly)
{
  hid_t fid = open_h5(FPATH, H5F_ACC_RDONLY, H5P_DEFAULT);
  assert_true(fid >= 0);
  H5Fclose(fid);
}
