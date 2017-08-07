/*
 * read_h5attr.c
 * tests_file: read_h5attr_tests.c
 *
 * Retrieving one attribute from a group
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
#include "./read_h5attr.h"


#ifndef PRINT
#define PRINT printf
#endif


int read_h5attr(hid_t fid, char *group_name, char *attr_name,
                hid_t dtype_id, void *dest)
{
  hid_t attr_id;
  hid_t group_id = H5Gopen(fid, group_name, H5P_DEFAULT);

  if(group_id < 0)
    {
      PRINT("[Warning] Unable to open group %s\n", group_name);
      return EXIT_FAILURE;
    }

  attr_id = H5Aopen_name(group_id, attr_name);

  if(attr_id < 0)
    {
      H5Gclose(group_id);
      PRINT("[Warning] Unable to open attribute %s\n", attr_name);
      return EXIT_FAILURE;
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
      H5Gclose(group_id);
      PRINT("[Warning] Unable to read attribute %s\n", attr_name);
      return EXIT_FAILURE;
    }

  H5Aclose(attr_id);
  H5Gclose(group_id);

  return EXIT_SUCCESS;
}
