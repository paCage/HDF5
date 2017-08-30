/*
 * get_h5dset_dims.c
 * tests_file: get_h5dset_dims_tests.c
 *
 * Retrieving the dimensions of a given dataset
 *
 * @param: fid: File identifier
 * @param: group_name:
 * @param: attr_name:
 * @param: dtype_id: Data type identifier from HDF5 lib
 * @param: dest: Pointer to the memory space to be filled
 *
 * @return: Standard EXIT_SUCCESS or EXIT_FAILURE
 */


#include <stdlib.h>
#include "./get_h5dset_dims.h"


#ifndef PRINT
#define PRINT printf
#endif


int get_h5dset_dims(hid_t file_id, char *dset_path, int *ndims, hsize_t *dims)
{
  hid_t dset_id = H5Dopen(file_id, dset_path, H5P_DEFAULT);
  if(dset_id < 0)
    {
      PRINT("[Error] Unable to open dataset: %s\n", dset_path);
      return EXIT_FAILURE;
    }

  hid_t dspace = H5Dget_space(dset_id);
  if(dspace < 0)
    {
      PRINT("[Error] Unable to get the dataset space");
      return EXIT_FAILURE;
    }

  *ndims = H5Sget_simple_extent_ndims(dspace);
  if(*ndims < 0)
    {
      PRINT("[Error] Unable to read the rank of the dataset");
      return EXIT_FAILURE;
    }

  if(H5Sget_simple_extent_dims(dspace, dims, NULL) < 0)
    {
      PRINT("[Error] Unable to read the dataset dimensions");
      return EXIT_FAILURE;
    }

  return EXIT_SUCCESS;
}
