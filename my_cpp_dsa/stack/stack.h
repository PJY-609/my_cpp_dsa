#pragma once

//#define STACK_VECTOR
#define STACK_LIST

#if defined(STACK_VECTOR)
#include "..\stack\stack_vector.h"
#elif defined(STACK_LIST)
#include "..\stack\stack_list.h"
#endif