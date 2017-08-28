/*
 * read_h5dset.c
 * tests_file: read_h5dset_tests.c
 *
 * Retrieving data from a dataset
 *
 * @param: file_id: File identifier
 * @param: dset_name:
 * @param: dtype_id: Data type identifier
 * @param: dest: Pointer to the memory space to be filled
 *
 * @return: Standard EXIT_SUCCESS or EXIT_FAILURE
 */


#include <stdlib.h>
#include "./read_h5dset.h"


#ifndef PRINT
#define PRINT printf
#endif


int read_h5dset(hid_t file_id, char *dset_name, hid_t dtype_id, void *dest)
{
  hid_t dset_id = H5Dopen(file_id, dset_name, H5P_DEFAULT);

  if(dset_id < 0)
    {
      H5Dclose(dset_id);
      PRINT("[Warning] Unable to open dataset %s\n", dset_name);
      return EXIT_FAILURE;
    }

  if(H5Dread(dset_id, dtype_id, H5S_ALL, H5S_ALL, H5P_DEFAULT, dest) < 0)
    {
      H5Dclose(dset_id);
      PRINT("[Warning] Unable to read dataset %s\n", dset_name);
      return EXIT_FAILURE;
    }

  H5Dclose(dset_id);
  return EXIT_SUCCESS;
}
