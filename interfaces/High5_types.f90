module High5_types
  use iso_c_binding

  implicit none

  enum, bind(c)
     enumerator :: &
          optional_attr = 0, &
          required_attr = 1
  end enum

end module High5_types
