MODULE_NAME := High5

_CSRC := open_h5.c \
         close_h5.c \
         read_h5attr.c \
         read_h5attrs.c \
         read_h5dset.c \
         read_h5dattr.c \
         read_h5dattrs.c \
         get_h5dset_dims.c

_TSRC := open_h5_tests.c \
         close_h5_tests.c \
         read_h5attr_tests.c \
         read_h5attrs_tests.c \
         read_h5dset_tests.c \
         read_h5dattr_tests.c \
         read_h5dattrs_tests.c \
         get_h5dset_dims_tests.c

_FSRC := High5.f90 \
         High5_types.f90

_CLIBS := -lhdf5

_FLIBS := -I ${HOME}/.local/include

include ./Makefile.paCage/Makefile
