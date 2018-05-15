MODULE_NAME := High5

MAJOR := 0
MINOR := 0
PATCH := 0


OBJS := open_h5.o \
        close_h5.o \
        read_h5attr.o \
        read_h5attrs.o \
        read_h5dset.o \
        read_h5dattr.o \
        read_h5dattrs.o \
        get_h5dset_dims.o \
        read_h5dset_part.o


FORTRAN_OBJS := High5_types.o \
                High5.o


TEST_OBJS := open_h5_tests.o \
             close_h5_tests.o \
             read_h5attr_tests.o \
             read_h5attrs_tests.o \
             read_h5dset_tests.o \
             read_h5dattr_tests.o \
             read_h5dattrs_tests.o \
             get_h5dset_dims_tests.o \
             read_h5dset_part_tests.o


INCLUDES := -I ${HOME}/.local/include
LIBS := -lhdf5


include ./Makefile.paCage/Makefile
