/*
 * read_h5dset_tests.c
 */


#include <cgreen/cgreen.h>
#include "./../src/read_h5dset.h"


#define FNAME "./tests/sample.hdf5"
#define DSET_NAME "group1/dataset1"
#define DSET_LEN 100


Describe(read_h5dset);
BeforeEach(read_h5dset) {};
AfterEach(read_h5dset) {};


Ensure(read_h5dset, loads_the_whole_dataset_properly)
{
  float dataset[DSET_LEN];

  hid_t fid = H5Fopen(FNAME, H5F_ACC_RDONLY, H5P_DEFAULT);

  assert_that(
    read_h5dset(fid, DSET_NAME, H5T_NATIVE_FLOAT, &dataset),
    is_equal_to(EXIT_SUCCESS));

  for(int i = 0; i < DSET_LEN; i++)
    {
      assert_that_double(dataset[i], is_equal_to_double(i * 1.0));
    }

  H5Fclose(fid);
}
