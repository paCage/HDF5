/*
 * close_h5.c
 * tests_file: close_h5_tests.c
 *
 * Closeing an HDF5 file
 *
 * @param: file_id: File identifier
 *
 * @return: Standard EXIT_SUCCESS or EXIT_FAILURE
 */


#include <stdlib.h>
#include "./close_h5.h"


#ifndef PRINT
#define PRINT printf
#endif


hid_t close_h5(hid_t file_id)
{
  herr_t h5err = H5Fclose(file_id);

  if (h5err < 0)
    {
      PRINT("[Error] Unable to close HDF5 file\n");
      return EXIT_FAILURE;
    }

  return EXIT_SUCCESS;
}
