/*
 * read_h5dattr.c
 * tests_file: read_h5dattr_tests.c
 *
 * Retrieving one attribute from a dataset
 *
 * @param: fid: File identifier
 * @param: dset_name: dataset identifier
 * @param: attr_name:
 * @param: dtype_id: Data type identifier from HDF5 lib
 * @param: dest: Pointer to the memory space to be filled
 *
 * @return: Standard EXIT_SUCCESS or EXIT_FAILURE
 */


#include <stdlib.h>
#include "./read_h5dattr.h"


#ifndef PRINT
#define PRINT printf
#endif


int read_h5dattr(hid_t fid, char *dset_name, char *attr_name,
                 hid_t dtype_id, void *dest)
{
  hid_t dset_id = H5Dopen(fid, dset_name, H5P_DEFAULT);

  int status = EXIT_SUCCESS;

  if(dset_id < 0)
    {
      H5Aclose(dset_id);
      PRINT("[Warning] Unable to open dataset %s\n", attr_name);
      status = EXIT_FAILURE;
    }

  hid_t attr_id = H5Aopen_name(dset_id, attr_name);

  if(attr_id < 0)
    {
      H5Dclose(dset_id);
      PRINT("[Warning] Unable to open attribute %s\n", attr_name);
      status = EXIT_FAILURE;
    }

  /* Handle variable length string*/
  if(dtype_id == H5T_C_S1)
    {
      dtype_id = H5Tcopy(H5T_C_S1);
      H5Tset_size (dtype_id, H5T_VARIABLE);
    }

  /* Handle fixed length string*/
  if(dtype_id == H5T_STRING)
    {
      dtype_id = H5Aget_type(attr_id);
      size_t sdim = H5Tget_size(dtype_id);

      dtype_id = H5Tcopy(H5T_C_S1);
      H5Tset_size (dtype_id, ++sdim);
    }

  if(H5Aread(attr_id, dtype_id, dest) < 0)
    {
      H5Aclose(attr_id);
      H5Dclose(dset_id);
      PRINT("[Warning] Unable to read attribute %s\n", attr_name);
      status = EXIT_FAILURE;
    }

  H5Aclose(attr_id);
  H5Dclose(dset_id);

  return status;
}
