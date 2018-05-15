/*
 * read_h5dset_part.c
 * tests_file: read_h5dset_part_tests.c
 *
 * Reading a portion of a given dataset
 *
 * @param: file_id: File identifier
 * @param: dset_name:
 * @param: start: An array of starting position
 * @param: count: Number of element (in each direction) to be read
 * @param: dtype_id: Data type identifier
 * @param: dest: Pointer to the memory space to be filled
 *
 * @return: Standard EXIT_SUCCESS or EXIT_FAILURE
 */


#include <stdlib.h>
#include "./read_h5dset_part.h"
#include "./get_h5dset_dims.h"


#ifndef PRINT
#define PRINT printf
#endif


int read_h5dset_part(hid_t fid, char *dset_name, hid_t dtype_id,
                     hsize_t * start, hsize_t *count, void *buf)
{
  if(count[0] == 0)
    return EXIT_SUCCESS;

  hid_t dset_id = H5Dopen(fid, dset_name, H5P_DEFAULT);

  int ndims;
  hsize_t dims[32];
  get_h5dset_dims(fid, dset_name, &ndims, dims);

  /* Offset from the begining of the dataset */
  hid_t dspace = H5Dget_space(dset_id);
  H5Sselect_hyperslab(dspace, H5S_SELECT_SET, start , NULL, count, NULL);

  hid_t mspace = H5Screate_simple(ndims, count, NULL);

  /* Offset from memspace */
  hsize_t start_tmp = start[0];
  start[0] = 0;
  H5Sselect_hyperslab(mspace, H5S_SELECT_SET, start, NULL, count, NULL);
  start[0] = start_tmp;

  H5Dread(dset_id, dtype_id, mspace, dspace, H5P_DEFAULT, buf);

  H5Sselect_none(mspace);
  H5Sselect_none(dspace);

  H5Dclose(dset_id);
  return EXIT_SUCCESS;
}
