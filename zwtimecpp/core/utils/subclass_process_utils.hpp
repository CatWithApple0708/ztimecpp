#include "zwtimecpp/core/utils/memory_utils.hpp"

#define zprocess_class(BasicClassType, basicClass)       \
  shared_ptr<BasicClassType> __pbasicClass = basicClass; \
  if (false)
#define zcase_subclass(subClassType, valueName)        \
  }                                                    \
  else if (instanceof <subClassType>(__pbasicClass)) { \
    shared_ptr<subClassType> valueName = dpc<subClassType>(__pbasicClass);
