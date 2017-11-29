/*
 * read_h5dset_part_tests.c
 */


#include <hdf5.h>
#include <cgreen/cgreen.h>
#include "./read_h5dset_part.h"


#define FNAME "./sample.hdf5"
#define DSET_NAME "/group1/dataset1"


Describe(read_h5dset_part);
BeforeEach(read_h5dset_part) {};
AfterEach(read_h5dset_part) {};


Ensure(read_h5dset_part, reads_a_portion_of_a_dataset)
{
  float buf[11];

  hid_t fid = H5Fopen(FNAME, H5F_ACC_RDONLY, H5P_DEFAULT);

  hsize_t start[1] = {17};
  hsize_t count[1] = {11};

  assert_that(
    read_h5dset_part(fid, DSET_NAME, start, count, H5T_NATIVE_FLOAT, &buf),
    is_equal_to(EXIT_SUCCESS));

  for(int i = 0; i < (int)count[0]; i++)
    assert_that_double(buf[i], is_equal_to_double((i + start[0]) * 1.0));

  H5Fclose(fid);
}
