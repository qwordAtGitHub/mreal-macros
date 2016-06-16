;;/**
;; * This file shows the basic usage of the MREAL macros.
;; * For more details see the comment block at top of
;; * the file real_math.inc.
;; */
.686
.model flat, stdcall
option casemap:none

    ;;/**
    ;; * After inclusion the default precision is 64 bit (MREAL_XDIM=4)
    ;; * and the rounding mode is "to nearest even".
    ;; */
    include real_math.inc

    ;;/**
    ;; * Convert some integer value
    ;; * and do calculations with them.
    ;; */
    MR_FROM_EXPR32 x, 123000
    MR_FROM_EXPR32 y, -456

    MR_ADD r1,x,y	; r1 = x + y
    MR_SUB r2,x,y	; r2 = x - y
    MR_MUL r3,x,y	; r3 = x * y
    MR_DIV r4,x,y	; r4 = x / y

    ;;/* print the results to build console using different methods  */
     echo
    %echo x = MR_TO_INT32(x), y = MR_TO_INT32(y)
    %echo x+y =  MR_TO_DECIMAL(r1) =  MR_TO_IEEE_HEX_SEQ(r1) ~=~ MR_TO_INT32(r1)
    %echo x-y =  MR_TO_DECIMAL(r2) =  MR_TO_IEEE_HEX_SEQ(r2) ~=~ MR_TO_INT32(r2)
    %echo x*y = MR_TO_DECIMAL(r3) = MR_TO_IEEE_HEX_SEQ(r3) ~=~ MR_TO_INT32(r3)
    %echo x/y = MR_TO_DECIMAL(r4) = MR_TO_IEEE_HEX_SEQ(r4)  ~=~ MR_TO_INT32(r4)

    ;;/**
    ;; * Load constant Pi and get the square root of it.
    ;; */
    MR_LOAD_CONST z, Pi
    MR_SQRT z,z

    ;;/**
    ;; * Store constants with different
    ;; * precision in .const-section.
    ;; */
    .const
    ;;/* REAL10 (extended-double) */
    MR_DECL_REAL10 SQRT_PI_R10, z  ;; SQRT_PI_R10 is the label

    ;;/* REAL8 (double, binary64) */
    SQRT_PI_R8 REAl8 MR_TO_IEEE(<REAl8>,z)

    ;;/* REAl4 (single, binary32) */
    SQRT_PI_R4 REAl4 MR_TO_IEEE(<REAl4>,z)

    ;;/**
    ;; * The following examples shows the conversion macro
    ;; * MR_FROM_STR, which allows to convert numeric literals
    ;; * to MREAL values.
    ;; * Please remarks that decimal to binary conversion
    ;; * is expensive (except for integers in range -(2^32-1) to 2^32-1).
    ;; */

    ;;/* decimal formats */
    MR_FROM_STR G, 6.6738480E-11
    MR_FROM_STR h, 6.6260695729E-34
    MR_FROM_STR c, 2.99792458E8
    MR_FROM_STR d1, -123
    MR_FROM_STR d2, 123.456
    MR_FROM_STR d3, +123.E-6
    MR_FROM_STR d4, 1.000000059604644775390625
    MR_FROM_STR d5, 99999999999999999999999999999999999999999
    MR_FROM_STR d6, 0.000000001E+8

    ;;/* hexadecimal formats */
    MR_FROM_STR h0, 0ff123h
    MR_FROM_STR h1, -800000000000000000000000000000h
    MR_FROM_STR h2, -0x123
    MR_FROM_STR h3, 0x1p63                 ; 1 * 2^63
    MR_FROM_STR h4, -0xffff.0001
    MR_FROM_STR h5, 0x123.456p-123         ; 0x123.456 * 2^-123

    ;;/* MASM hexadecimal floating point initializers */
    MR_FROM_STR r1,  3f800000r             ; REAL4,  1.0
    MR_FROM_STR r2, -40000000r             ; REAL4, -2.0
    MR_FROM_STR r3, 0C0000000r             ; REAL4, -2.0
    MR_FROM_STR r4, 07fe0000000000000r     ; REAl8, 2^1023
    MR_FROM_STR r5, 07ff0000000000000r     ; REAL8, +Infinity
    MR_FROM_STR r6, 3fff8000000000000000r  ; REAL10, 1.0
    MR_FROM_STR r7, 0bfff8000000000000001r ; REAL10, -1.0

    ;;/* compare h with G */
    IF MR_GE(h,G)	;; IF h >= G
        MR_MOV max,h
    ELSE
        MR_MOV max,G
    ENDIF
     echo
    %echo max(MR_TO_DECIMAL(h,3), MR_TO_DECIMAL(G,3)) = MR_TO_DECIMAL(max,3)

    ;;/* get the fractional digits of Pi */
    MR_LOAD_CONST x, Pi          ;; x = Pi
    MR_ROUND i,x,,,MRRM_TRUNCATE ;; i = floor(Pi)
    MR_SUB x,x,i                 ;; x = x - i
     echo
    %echo Pi - floor(Pi) = MR_TO_DECIMAL(x)

.code
main proc

    ;;/* do nothing - just an example */
    ret

main endp
END main


;--------------------------------------------------------------;
;        Below some code snippets (intended as examples)
;--------------------------------------------------------------;

    ;;/**
    ;; * Calculate remainder of x/y according to IEEE754.
    ;; * r = x - y * roundToNearestEven(x/y)
    ;; *
    MR_DIV r,x,y,MRRM_ROUND_TO_EVEN
    MR_ROUND r,r,,,MRRM_ROUND_TO_EVEN
    MR_FNMADD r,r,y,x


    ;/**
    ; * calculate factorial !100 exact,
    ; * using variable precision.
    ; */
    MR_FROM_EXPR32 x, 1
    MR_MOV y,x
    MR_MOV cOne,x
    MREAL_TEST_INEXACT = -1
    px = 1 ; start precision for x is 1*16 bit
    py = 1 ; py is constant unless we want to get factorial > !2^16
    cntr = 0
    WHILE cntr NE 100 ; max. ~~ 1700
        MR_XMUL x,x,y,%px+py,px,py ; exact multiplication
        px = MR_GET_N_SIGNIFICANT_WORDS(x,%px+py)
        IF MREAL_INEXACT
            .err <this should not happen>
            EXITM
        ELSE
            MR_ADD y,y,cOne,,py
            cntr = cntr + 1
        ENDIF
    ENDM
    MR_RAW_OUT x,px
    %echo precision WORDs: @CatStr(%px)
    %echo x = ca. MR_TO_DECIMAL(x,50,px)


    ;/**
    ; * Calculate table of reciprocal values.
    ; */
    .const
    someLbl LABEL REAl10
    MREAL_XDIM = 4
    MREAL_ROUND_MODE = MRRM_ROUND_TO_NEAREST_TIES_TO_EVEN
    MR_FROM_EXPR32 cntr, 1	; cntr = 1
    MR_MOV cOne,cntr        ; cOne = 1
    REPEAT 100
        ;/* r = 1/x */
        MR_DIV r,cOne,cntr
        ;/* store REAl10 value */
        MR_DECL_REAL10 ,r
        ;/* cntr++ */
        MR_ADD cntr,cntr,cOne
    ENDM