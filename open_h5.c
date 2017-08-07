/*
 * open_h5.c
 * tests_file: open_h5_tests.c
 *
 * Opening an HDF5 file
 *
 * @param: fpath: File path
 * @param: flag: File access flag (H5F_ACC_RDWR, H5F_ACC_RDONLY)
 * @param: fapl_id: Identifier for the file access properties list
 *
 * @return: File identifier (negative integers for the case of error)
 */


#include "./open_h5.h"


#ifndef PRINT
#define PRINT printf
#endif


hid_t open_h5(char *fpath, unsigned flag, hid_t fapl_id)
{
  hid_t fid = H5Fopen(fpath, flag, fapl_id);

  if (fid < 0)
    PRINT("[Error] Unable to open HDF5 file: %s\n", fpath);

  return fid;
}
