#ifndef _H5ERR_HELPER_H_
#define _H5ERR_HELPER_H_


#include <hdf5.h>


static struct _h5err_switch
{
  H5E_auto_t func;
  void *data;
} h5err_switch;


#define  h5err_switch_off()                                           \
  {                                                                   \
    H5Eget_auto(H5E_DEFAULT, &h5err_switch.func, &h5err_switch.data); \
    H5Eset_auto(H5E_DEFAULT, NULL, NULL);                             \
  }                                                                   \


#define h5err_switch_on()                                           \
  {                                                                 \
    H5Eset_auto(H5E_DEFAULT, h5err_switch.func, h5err_switch.data); \
  }                                                                 \


#endif /* _H5ERR_HELPER_H_ */
