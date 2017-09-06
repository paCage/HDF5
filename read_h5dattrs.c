/*
 * read_h5dattrs.c
 * tests_file: read_h5dattrs_tests.c
 *
 * Retrieving more than one attributes from a database
 *
 * @param: fid: File identifier
 * @param: dset_name: dataset name
 * @param: For each attribute to be retrieved there should be an attr_name,
 *         dtype_id and buf. The list must be ended to NULL
 *         attr_name:
 *         dtype_id: Data type identifier from HDF5 lib
 *         buf: Pointer to the memory space to be filled
 *         attr_type: Type of the attribute (e.g. optional, required)
 *
 * @return: Standard EXIT_SUCCESS or EXIT_FAILURE
 */


#include <stdlib.h>
#include <stdarg.h>
#include "./read_h5attr.h"
#include "./High5_types.h"
#include "./h5err_helper.h"


#ifndef PRINT
#define PRINT printf
#endif


int read_h5dattrs(hid_t fid, char *dset_name, char *attr_name, ...)
{
  va_list vars;

  hid_t dtype_id, attr_id;
  void *buf;
  enum _ATypes attr_type;

  hid_t dset_id = H5Dopen(fid, dset_name, H5P_DEFAULT);

  if (dset_id < 0)
    {
      PRINT("[Warning] Unable to open dataset %s\n", dset_name);
      return EXIT_FAILURE;
    }

  int h5err, status = EXIT_SUCCESS;

  va_start(vars, attr_name);

  while (attr_name != NULL)
    {
      dtype_id = va_arg(vars, hid_t);
      buf = va_arg(vars, void*);
      attr_type = va_arg(vars, enum _ATypes);

      if(attr_type == optional_attr)
        h5err_switch_off();

      attr_id = H5Aopen_name(dset_id, attr_name);

      if(attr_id < 0)
        {
          PRINT("[Warning] Unable to open attribute %s\n", attr_name);

          if(attr_type != optional_attr)
            status = EXIT_FAILURE;

          attr_name = va_arg(vars, char*);

          if(attr_type == optional_attr)
            h5err_switch_on();

          continue;
        }

      /* Handle string loading*/
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

      h5err = H5Aread(attr_id, dtype_id, buf);
      if(h5err < 0)
        {
          H5Aclose(attr_id);
          PRINT("[Warning] Unable to read attribute %s\n", attr_name);

          if(attr_type != optional_attr)
            status = EXIT_FAILURE;

          attr_name = va_arg(vars, char*);

          if(attr_type == optional_attr)
            h5err_switch_on();

          continue;
        }

      H5Aclose(attr_id);

      if(attr_type == optional_attr)
        h5err_switch_on();

      attr_name = va_arg(vars, char*);
    }

  va_end(vars);

  H5Dclose(dset_id);

  return status;
}
