The Sender/Receiver functions have the following form:

func (in_param, ...)
{
  m.mapIt (out_param,in_param)

  try
  {
    rtiAm/fedAmm(out_param)
  }
  catch ()
  {
  }
}

The mapIt functions do the conversion between RCI_SOCKET / RTI_IDL
formats.

In some cases, the responsibility of memory allocation/deallocation is
not clear: in the first version try to follow what CCI did.
