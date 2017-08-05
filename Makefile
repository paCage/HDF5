MODULE_NAME := High5

_FILES := read_h5attr \
          read_h5attrs \
          read_h5dset \
          read_h5dattr

_TESTS := read_h5attr_tests \
          read_h5attrs_tests \
          read_h5dset_tests \
          read_h5dattr_tests

_LIBS := -lhdf5

include ./Makefile.paCage/Makefile
