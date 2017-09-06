module High5
  use hdf5
  use iso_c_binding

  implicit none


  interface
     function open_h5_i(fpath, flag, fapl_id) bind(C, name="open_h5")
       use hdf5
       use iso_c_binding
       character(len=1, kind=c_char), dimension(*), intent(in) :: fpath
       integer(kind=c_int), value, intent(in) :: flag
       integer(kind=c_int), value, intent(in) :: fapl_id
       integer(kind=c_int) :: open_h5_i
     end function open_h5_i


     function read_h5attr_i(file_id, group_name, attr_name, dtype_id, buf) &
          bind(C, name="read_h5attr")
       use hdf5
       use iso_c_binding
       integer(kind=c_int), value, intent(in) :: file_id
       character(len=1, kind=c_char), dimension(*), intent(in) :: group_name
       character(len=1, kind=c_char), dimension(*), intent(in) :: attr_name
       integer(kind=c_int), value, intent(in) :: dtype_id
       type(c_ptr), value, intent(in) :: buf
       integer(kind=c_int) :: read_h5attr_i
     end function read_h5attr_i


     function read_h5dset_i(file_id, dset, dtype_id, buf) &
          bind(C, name="read_h5dset")
       use hdf5
       use iso_c_binding
       integer(kind=c_int), value, intent(in) :: file_id
       character(len=1, kind=c_char), dimension(*), intent(in) :: dset
       integer(kind=c_int), value, intent(in) :: dtype_id
       type(c_ptr), value, intent(in) :: buf
       integer(kind=c_int) :: read_h5dset_i
     end function read_h5dset_i


     function read_h5dattr_i(file_id, dset, attr, dtype_id, buf) &
          bind(C, name="read_h5dattr")
       use hdf5
       use iso_c_binding
       integer(kind=c_int), value, intent(in) :: file_id
       character(len=1, kind=c_char), dimension(*), intent(in) :: dset, attr
       integer(kind=c_int), value, intent(in) :: dtype_id
       type(c_ptr), value, intent(in) :: buf
       integer(kind=c_int) :: read_h5dattr_i
     end function read_h5dattr_i
  end interface


contains
  subroutine open_h5_f(fpath, flag, fapl_id, file_id)
    character(len=*), intent(in) :: fpath
    integer(kind=c_int), value, intent(in) :: flag
    integer(hid_t), value, intent(in) :: fapl_id
    integer(hid_t), intent(out), optional :: file_id

    integer(kind=4) :: h5err

    call h5open_f(h5err)
    if (h5err < 0) then
       print *, "[FATAL ERROR] Unable to initialize HDF5"
       stop 0
    end if

    file_id = open_h5_i(trim(fpath)//c_null_char, flag, fapl_id)
  end subroutine open_h5_f


  subroutine read_h5attr_f(file_id, group_name, attr_name, dtype_id, buf, err)
    integer(hid_t), value, intent(in) :: file_id
    character(len=*), intent(in) :: group_name, attr_name
    integer(hid_t), value, intent(in) :: dtype_id
    type(c_ptr), target :: buf
    integer(kind=4), intent(out), optional :: err

    err = read_h5attr_i(file_id, trim(group_name)//c_null_char, &
         trim(attr_name)//c_null_char, dtype_id, buf)
  end subroutine read_h5attr_f


  subroutine read_h5dset_f(file_id, dset, dtype_id, buf, err)
    integer(hid_t), value, intent(in) :: file_id
    character(len=*), intent(in) :: dset
    integer(hid_t), value, intent(in) :: dtype_id
    type(c_ptr), target :: buf
    integer(kind=4), intent(out), optional :: err

    err = read_h5dset_i(file_id, trim(dset)//c_null_char, dtype_id, buf)
  end subroutine read_h5dset_f


  subroutine read_h5dattr_f(file_id, dset, attr, dtype_id, buf, err)
    integer(hid_t), value, intent(in) :: file_id
    character(len=*), intent(in) :: dset, attr
    integer(hid_t), value, intent(in) :: dtype_id
    type(c_ptr), target :: buf
    integer(kind=4), intent(out), optional :: err

    err = read_h5dattr_i(file_id, trim(dset)//c_null_char, &
         trim(attr)//c_null_char, dtype_id, buf)
  end subroutine read_h5dattr_f
end module High5
