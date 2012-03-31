//SWIG Interface to my megafuncs :)
%module kmp
%{
#define SWIG_FILE_WITH_INIT
#include <math.h>
#include "../src/shared/kbtypes.h"
#include "../src/shared/shared.h"
#include "../src/math/kmath.h"
#include "../src/math/kmvector.h"
#include "../src/math/kmmatrix.h"
#include "../src/math/kmquat.h"
%}
%include "shared/kbtypes.i"
%include "shared/shared.i"
%include "math/kmath.i"
%include "math/kmvector.i"
%include "math/kmquat.i"
%include "math/kmmatrix.i"

