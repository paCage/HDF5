/*
 * get_h5dset_dims_tests.c
 */


#include <cgreen/cgreen.h>
#include "./../src/get_h5dset_dims.h"


#define FPATH "./tests/sample.hdf5"
#define DSET_PATH "group2/2D_dataset"
#define DSET_NDIMS 2
#define DSET_DIM0 14
#define DSET_DIM1 3


Describe(get_h5dset_dims);


BeforeEach(get_h5dset_dims)
{
}


AfterEach(get_h5dset_dims) {};


Ensure(get_h5dset_dims, opens_an_hdf5_file_properly)
{
  int ndims;
  hsize_t dims[32];

  hid_t file_id = H5Fopen(FPATH, H5F_ACC_RDONLY, H5P_DEFAULT);
  assert_true(file_id >= 0);

  get_h5dset_dims(file_id, DSET_PATH, &ndims, dims);

  assert_that(ndims, is_equal_to(DSET_NDIMS));
  assert_that(dims[0], is_equal_to(DSET_DIM0));
  assert_that(dims[1], is_equal_to(DSET_DIM1));

  H5Fclose(file_id);
}
