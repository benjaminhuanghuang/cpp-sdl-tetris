## Copy constructor with shared_ptr members

The default copy constructor will use the copy constructor for each member variable, or bit-wise copy for built-in types.

If you are using a shared pointer of some kind, the copy constructor will increment the shared count and both the original and the new objects will point to the same object.

