// IllegalSizeException.cpp
// Class IllegalSizeException definition
#include <stdexcept> // contains runtime_error

// IllegalSizeException objects should be thrown by functions
// upon detecting illegal size exceptions
class IllegalSizeException : public std::runtime_error {
   public:
      // constructor specifies default erros message
      IllegalSizeException()
         : std::runtime_error("attempted to multiply illegal sized matrices") {}
}; // end class IllegalSizeException
