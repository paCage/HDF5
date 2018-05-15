/*
 * read_h5dset_part_tests.c
 */


#include <hdf5.h>
#include <cgreen/cgreen.h>
#include "./../src/read_h5dset_part.h"


#define FNAME "./tests/sample.hdf5"
#define DSET_NAME "/group1/dataset1"
#define DSET_NAME "/group1/dataset1"
#define DSET_2D "/group2/2D_dataset"


double dataset_2d[14][3] = {
  {13.02211, 7.821008, -18.85176},
  {-1.082516, -17.176153, -5.106723},
  {6.2809, -5.9340467, -8.630667},
  {14.514377, -9.045651, -7.323222},
  {-13.931533, 3.3012645, 8.136783},
  {-0.27715644, 8.2396, 7.8558564},
  {-5.3030624, 12.61975, -8.098574},
  {8.448818, 8.080614, 3.6466198},
  {-15.568522, 15.637116, 2.474332},
  {1.7551264, 0.4055835, -10.991596},
  {-24.833836, 11.050783, -28.179804},
  {-26.79651, -13.235445, -12.349814},
  {-12.912288, 3.6432402, -17.044561},
  {-17.539284, 5.340518, 35.276707},
};


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
    read_h5dset_part(fid, DSET_NAME, H5T_NATIVE_FLOAT, start, count, &buf),
    is_equal_to(EXIT_SUCCESS));

  for(int i = 0; i < (int)count[0]; i++)
    assert_that_double(buf[i], is_equal_to_double((i + start[0]) * 1.0));

  H5Fclose(fid);
}


Ensure(read_h5dset_part, can_read_multi_dimensional_datasets)
{
  float buf[33];

  hid_t fid = H5Fopen(FNAME, H5F_ACC_RDONLY, H5P_DEFAULT);

  hsize_t start[2] = {2, 0};
  hsize_t count[2] = {5, 3};

  assert_that(
    read_h5dset_part(fid, DSET_2D, H5T_NATIVE_FLOAT, start, count, &buf),
    is_equal_to(EXIT_SUCCESS));

  for(int i = 0; i < 5; i++)
    for(int j = 0; j < 3; j++)
      assert_that_double((float)buf[i*3 + j],
                         is_equal_to_double((float)dataset_2d[i+2][j]));
}
