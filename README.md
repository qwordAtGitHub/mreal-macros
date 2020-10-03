# MREAL MASM macros
This project contains a set of MASM macros allowing floating point arithmetic while assembling.

The goal was to implement a subset of the IEEE 754-2008 standard, as far as possible with MASM's preprocessor.
The key features are:

* Arbitrary precision: multiples of 16: 16, 32, 48, 64, ... bits
* Correctly rounded arithmetic: addition, subtraction, multiplication, division, square root and fused multiply accumulate.
* Rounding modes:
    * round to nearest, half to even (IEEE754 default mode)
    * round to nearest, half away from zero
    * round toward -∞ (round down)
    * round toward +∞ (round up)
    * round toward zero (truncate)

For more details please read the comment block at top of the file real_math.inc.

There is an powerfull macro front-end (ceval.inc), which simplify the usage enormously, because it allows to enter mathematical expressions, as known from high level programming languages:

```
include real_math.inc
include ceval.inc

; evaluate some expression
ceval x = 123.456 * -2 ^ 4 * ( sqrt(2) + 1 )
echo_mreal ans
echo_mreal x

; test condition
IF ccond( x lt 0 || x gt 123 )
	echo foo
ENDIF

.const
; define const REAL8 value
someConst REAL8 cReal8( sqrt(2)/2 )
```

The following example shows the usage of the low level API (real_math.inc):
```
include real_math.inc

; Default precision is 64 bit and the
; rounding mode is "to nearest, half to even"
MREAL x = 1, y = 10
MR_DIV r,x,y           ; r = x/y

; output to build console
%echo MR_TO_UINT32(x)/MR_TO_UINT32(y) = MR_TO_IEEE_HEX_SEQ(r) = MR_TO_DECIMAL(r,2)

; convert r to REAL8
foo REAL8 MR_TO_IEEE(<REAL8>,r)

; define REAL10 value in current segment
MR_DECL_REAL10 foo2, r
```
