; by qWord, 2014
; This file contains approximations for:
;
;   MR_LOG2 r,x        -> r=log2(x)    
;   MR_EXP r,x         -> r=exp(x) with |x| < 10000
;   MR_SINCOS rs,rc,x  -> rs=sin(x) and rc=cos(x) with |x| < 2^32
;
; The precision must be 4 (=64bit).
; The macros internally use MREAL values with names/IDs 
; of the form "?X", whereby X is "A"-"Z".

IFNDEF MR_VERSION
	.err <real_math.inc not inlcuded>
ELSE

;;/**
;; * Table for BKM Algorithm, log2(), 64bit precision
;; */
MR_SET_CONST ?BKMLD0,+,0,4,8000h,0h,0h,0h
MR_SET_CONST ?BKMLD1,+,-1,4,95c0h,1a39h,0fbd6h,87a0h
MR_SET_CONST ?BKMLD2,+,-2,4,0a4d3h,0c25eh,68dch,57f2h
MR_SET_CONST ?BKMLD3,+,-3,4,0ae00h,0d1cfh,0deb4h,3cfdh
MR_SET_CONST ?BKMLD4,+,-4,4,0b31fh,0b7d6h,4898h,0b3e6h
MR_SET_CONST ?BKMLD5,+,-5,4,0b5d6h,9bach,77ech,398ah
MR_SET_CONST ?BKMLD6,+,-6,4,0b73ch,0b42eh,1691h,4c53h
MR_SET_CONST ?BKMLD7,+,-7,4,0b7f2h,85b7h,7842h,8bfch
MR_SET_CONST ?BKMLD8,+,-8,4,0b84eh,236bh,0d563h,0ba57h
MR_SET_CONST ?BKMLD9,+,-9,4,0b87ch,1ff8h,53abh,2632h
MR_SET_CONST ?BKMLD10,+,-10,4,0b893h,29bah,1fa2h,0a0fdh
MR_SET_CONST ?BKMLD11,+,-11,4,0b89eh,0b17bh,0cabeh,1858h
MR_SET_CONST ?BKMLD12,+,-12,4,0b8a4h,7615h,0dfeh,4471h
MR_SET_CONST ?BKMLD13,+,-13,4,0b8a7h,588fh,0d29bh,1baah
MR_SET_CONST ?BKMLD14,+,-14,4,0b8a8h,0c9d8h,0be9ah,0e994h
MR_SET_CONST ?BKMLD15,+,-15,4,0b8a9h,8280h,1725h,7233h
MR_SET_CONST ?BKMLD16,+,-16,4,0b8a9h,0ded4h,7c11h,283eh
MR_SET_CONST ?BKMLD17,+,-17,4,0b8aah,0cfeh,0dcb1h,18dfh
MR_SET_CONST ?BKMLD18,+,-18,4,0b8aah,2414h,188bh,0a5bch
MR_SET_CONST ?BKMLD19,+,-19,4,0b8aah,2f9eh,0b95bh,9332h
MR_SET_CONST ?BKMLD20,+,-20,4,0b8aah,3564h,0a7ch,33ech
MR_SET_CONST ?BKMLD21,+,-21,4,0b8aah,3846h,0b33ah,0aed0h
MR_SET_CONST ?BKMLD22,+,-22,4,0b8aah,39b8h,7a5h,76e5h
MR_SET_CONST ?BKMLD23,+,-23,4,0b8aah,3a70h,0b1ddh,0bd98h
MR_SET_CONST ?BKMLD24,+,-24,4,0b8aah,3acdh,6fah,999ch
MR_SET_CONST ?BKMLD25,+,-25,4,0b8aah,3afbh,3189h,35c8h
MR_SET_CONST ?BKMLD26,+,-26,4,0b8aah,3b12h,46d0h,8f69h
MR_SET_CONST ?BKMLD27,+,-27,4,0b8aah,3b1dh,0d174h,3f1ch
MR_SET_CONST ?BKMLD28,+,-28,4,0b8aah,3b23h,96c6h,17aeh
MR_SET_CONST ?BKMLD29,+,-29,4,0b8aah,3b26h,796fh,426h
MR_SET_CONST ?BKMLD30,+,-30,4,0b8aah,3b27h,0eac3h,7a6dh
MR_SET_CONST ?BKMLD31,+,-31,4,0b8aah,3b28h,0a36dh,0b593h
MR_SET_CONST ?BKMLD32,+,-32,4,0b8aah,3b28h,0ffc2h,0d327h
MR_SET_CONST ?BKMLD33,+,-33,4,0b8aah,3b29h,2dedh,61f1h
MR_SET_CONST ?BKMLD34,+,-34,4,0b8aah,3b29h,4502h,0a957h
MR_SET_CONST ?BKMLD35,+,-35,4,0b8aah,3b29h,508dh,4d09h
MR_SET_CONST ?BKMLD36,+,-36,4,0b8aah,3b29h,5652h,9ee2h
MR_SET_CONST ?BKMLD37,+,-37,4,0b8aah,3b29h,5935h,47cfh
MR_SET_CONST ?BKMLD38,+,-38,4,0b8aah,3b29h,5aa6h,9c45h
MR_SET_CONST ?BKMLD39,+,-39,4,0b8aah,3b29h,5b5fh,4681h
MR_SET_CONST ?BKMLD40,+,-40,4,0b8aah,3b29h,5bbbh,9b9eh
MR_SET_CONST ?BKMLD41,+,-41,4,0b8aah,3b29h,5be9h,0c62dh
MR_SET_CONST ?BKMLD42,+,-42,4,0b8aah,3b29h,5c00h,0db74h
MR_SET_CONST ?BKMLD43,+,-43,4,0b8aah,3b29h,5c0ch,6618h
MR_SET_CONST ?BKMLD44,+,-44,4,0b8aah,3b29h,5c12h,2b6ah
MR_SET_CONST ?BKMLD45,+,-45,4,0b8aah,3b29h,5c15h,0e13h
MR_SET_CONST ?BKMLD46,+,-46,4,0b8aah,3b29h,5c16h,7f67h
MR_SET_CONST ?BKMLD47,+,-47,4,0b8aah,3b29h,5c17h,3812h
MR_SET_CONST ?BKMLD48,+,-48,4,0b8aah,3b29h,5c17h,9467h
MR_SET_CONST ?BKMLD49,+,-49,4,0b8aah,3b29h,5c17h,0c291h
MR_SET_CONST ?BKMLD50,+,-50,4,0b8aah,3b29h,5c17h,0d9a6h
MR_SET_CONST ?BKMLD51,+,-51,4,0b8aah,3b29h,5c17h,0e531h
MR_SET_CONST ?BKMLD52,+,-52,4,0b8aah,3b29h,5c17h,0eaf6h
MR_SET_CONST ?BKMLD53,+,-53,4,0b8aah,3b29h,5c17h,0edd9h
MR_SET_CONST ?BKMLD54,+,-54,4,0b8aah,3b29h,5c17h,0ef4ah
MR_SET_CONST ?BKMLD55,+,-55,4,0b8aah,3b29h,5c17h,0f003h
MR_SET_CONST ?BKMLD56,+,-56,4,0b8aah,3b29h,5c17h,0f05fh
MR_SET_CONST ?BKMLD57,+,-57,4,0b8aah,3b29h,5c17h,0f08eh
MR_SET_CONST ?BKMLD58,+,-58,4,0b8aah,3b29h,5c17h,0f0a5h
MR_SET_CONST ?BKMLD59,+,-59,4,0b8aah,3b29h,5c17h,0f0b0h
MR_SET_CONST ?BKMLD60,+,-60,4,0b8aah,3b29h,5c17h,0f0b6h
MR_SET_CONST ?BKMLD61,+,-61,4,0b8aah,3b29h,5c17h,0f0b9h
MR_SET_CONST ?BKMLD62,+,-62,4,0b8aah,3b29h,5c17h,0f0bah
MR_SET_CONST ?BKMLD63,+,-63,4,0b8aah,3b29h,5c17h,0f0bbh 
MR_SET_CONST ?BKMLD64,+,-64,4,0b8aah,3b29h,5c17h,0f0bbh 
MR_SET_CONST ?BKMLD65,+,-65,4,0b8aah,3b29h,5c17h,0f0bch 

;;/**
;; * Calculate log2(x) using BKM Algorithm.
;; * Precision is 64 bit, RM = round to nearest.
;; */
MR_LOG2 macro r:req,x:req,N:=<65>
	IF MREAL_XDIM NE 4
		.err <precision setting not supported: 64 bit expected>
		MR_SET_ZERO r,4
		EXITM
	ENDIF
	IF MR_IS_SIGN_MINUS(x) OR NOT MR_IS_NORMAL(x)
		MR_LOAD_CONST r,NaN
		EXITM
	ENDIF
	IF N GT 66
		.err <invalid parameter: _N: N>
		EXITM
	ENDIF
	
	;;/* reduce argument range */
	MR_MOV ?A,x,4
	mrld_exp = MR_EXPONENT(?A)
	IF mrld_exp LT 1 OR mrld_exp GT 2
		MR_EXPONENT(?A) = 1
		mrld_exp = mrld_exp - 1
	ELSE
		mrld_exp = 0
	ENDIF
	
	;;/**
	;; * BKM Algorithm:
    ;; *   Log2 ( arg , N ) {    // 1 <= arg <= ca. 4.768462
    ;; *      x = 1;
    ;; *      y = 0;
    ;; *      for ( i = 0; i < N; i++ ) {
    ;; *        tmp = x + x*2^(-i);        // "^" means exponentiation
    ;; *        if ( tmp <= arg ) {
    ;; *            x = tmp;
    ;; *            y = y + log2(1+0.5^i); // table value
    ;; *        }
    ;; *      }
    ;; *      return y;
    ;; *   }
	;; */
	MR_MOV ?X,?MRC_ONE,4
	MR_SET_ZERO r,4
	mrld_cntr = 0
	REPEAT N
		MR_CSCALE ?T,?X,%-mrld_cntr,MRRM_TRUNCATE,4
		MR_ADD ?T,?X,?T,MRRM_ROUND_TO_EVEN,4
		IF MR_LE(?T,?A,4)
			MR_MOV ?X,?T,4
			MR_ADD r,r,@CatStr(<?BKMLD>,%mrld_cntr),MRRM_ROUND_TO_EVEN,4
		ENDIF
		mrld_cntr = mrld_cntr + 1
	ENDM
	
	;;/* add integer part of exponent if needed */
	IF mrld_exp
		MR_FROM_EXPR32 ?T,mrld_exp,MRRM_TRUNCATE,4
		MR_ADD r,r,?T,MRRM_ROUND_TO_EVEN,4
	ENDIF
endm

;;/**
;; * Table for BKM Algorithm, exp(x), 64bit precision.
;; */
MR_SET_CONST ?BKME0,+,-1,5,0b172h,17f7h,0d1cfh,79abh,0c9e4h
MR_SET_CONST ?BKME1,+,-2,5,0cf99h,1f65h,0fcc2h,5f95h,0b46ch
MR_SET_CONST ?BKME2,+,-3,5,0e47fh,0be3ch,0d4d1h,0d61h,2ec1h
MR_SET_CONST ?BKME3,+,-4,5,0f138h,3b71h,5797h,2f4fh,5440h
MR_SET_CONST ?BKME4,+,-5,5,0f851h,8600h,8b15h,330bh,0e64ch
MR_SET_CONST ?BKME5,+,-6,5,0fc14h,0d873h,0c198h,267h,0c7e1h
MR_SET_CONST ?BKME6,+,-7,5,0fe05h,4587h,0e01fh,1e7ch,0f6d4h
MR_SET_CONST ?BKME7,+,-8,5,0ff01h,5358h,833ch,47e1h,0bb48h
MR_SET_CONST ?BKME8,+,-9,5,0ff80h,5515h,885eh,250h,435bh
MR_SET_CONST ?BKME9,+,-10,5,0ffc0h,154dh,5887h,33c5h,3c74h
MR_SET_CONST ?BKME10,+,-11,5,0ffe0h,554h,5588h,7de0h,2683h
MR_SET_CONST ?BKME11,+,-12,5,0fff0h,155h,3558h,8833h,3c57h
MR_SET_CONST ?BKME12,+,-13,5,0fff8h,55h,5155h,8885h,0de02h
MR_SET_CONST ?BKME13,+,-14,5,0fffch,15h,54d5h,5888h,7334h
MR_SET_CONST ?BKME14,+,-15,5,0fffeh,5h,5545h,5588h,87deh
MR_SET_CONST ?BKME15,+,-16,5,0ffffh,1h,5553h,5558h,8883h
MR_SET_CONST ?BKME16,+,-17,5,0ffffh,8000h,5555h,1555h,8888h
MR_SET_CONST ?BKME17,+,-18,5,0ffffh,0c000h,1555h,4d55h,5889h
MR_SET_CONST ?BKME18,+,-19,5,0ffffh,0e000h,555h,5455h,5589h
MR_SET_CONST ?BKME19,+,-20,5,0ffffh,0f000h,155h,5535h,5559h
MR_SET_CONST ?BKME20,+,-21,5,0ffffh,0f800h,55h,5551h,5556h
MR_SET_CONST ?BKME21,+,-22,5,0ffffh,0fc00h,15h,5554h,0d555h
MR_SET_CONST ?BKME22,+,-23,5,0ffffh,0fe00h,5h,5555h,4555h
MR_SET_CONST ?BKME23,+,-24,5,0ffffh,0ff00h,1h,5555h,5355h
MR_SET_CONST ?BKME24,+,-25,5,0ffffh,0ff80h,0h,5555h,5515h
MR_SET_CONST ?BKME25,+,-26,5,0ffffh,0ffc0h,0h,1555h,554dh
MR_SET_CONST ?BKME26,+,-27,5,0ffffh,0ffe0h,0h,555h,5554h
MR_SET_CONST ?BKME27,+,-28,5,0ffffh,0fff0h,0h,155h,5555h
MR_SET_CONST ?BKME28,+,-29,5,0ffffh,0fff8h,0h,55h,5555h
MR_SET_CONST ?BKME29,+,-30,5,0ffffh,0fffch,0h,15h,5555h
MR_SET_CONST ?BKME30,+,-31,5,0ffffh,0fffeh,0h,5h,5555h
MR_SET_CONST ?BKME31,+,-32,5,0ffffh,0ffffh,0h,1h,5555h
MR_SET_CONST ?BKME32,+,-33,5,0ffffh,0ffffh,8000h,0h,5555h
MR_SET_CONST ?BKME33,+,-34,5,0ffffh,0ffffh,0c000h,0h,1555h
MR_SET_CONST ?BKME34,+,-35,5,0ffffh,0ffffh,0e000h,0h,555h
MR_SET_CONST ?BKME35,+,-36,5,0ffffh,0ffffh,0f000h,0h,155h
MR_SET_CONST ?BKME36,+,-37,5,0ffffh,0ffffh,0f800h,0h,55h
MR_SET_CONST ?BKME37,+,-38,5,0ffffh,0ffffh,0fc00h,0h,15h
MR_SET_CONST ?BKME38,+,-39,5,0ffffh,0ffffh,0fe00h,0h,5h
MR_SET_CONST ?BKME39,+,-40,5,0ffffh,0ffffh,0ff00h,0h,1h
MR_SET_CONST ?BKME40,+,-41,5,0ffffh,0ffffh,0ff80h,0h,0h
MR_SET_CONST ?BKME41,+,-42,5,0ffffh,0ffffh,0ffc0h,0h,0h
MR_SET_CONST ?BKME42,+,-43,5,0ffffh,0ffffh,0ffe0h,0h,0h
MR_SET_CONST ?BKME43,+,-44,5,0ffffh,0ffffh,0fff0h,0h,0h
MR_SET_CONST ?BKME44,+,-45,5,0ffffh,0ffffh,0fff8h,0h,0h
MR_SET_CONST ?BKME45,+,-46,5,0ffffh,0ffffh,0fffch,0h,0h
MR_SET_CONST ?BKME46,+,-47,5,0ffffh,0ffffh,0fffeh,0h,0h
MR_SET_CONST ?BKME47,+,-48,5,0ffffh,0ffffh,0ffffh,0h,0h
MR_SET_CONST ?BKME48,+,-49,5,0ffffh,0ffffh,0ffffh,8000h,0h
MR_SET_CONST ?BKME49,+,-50,5,0ffffh,0ffffh,0ffffh,0c000h,0h
MR_SET_CONST ?BKME50,+,-51,5,0ffffh,0ffffh,0ffffh,0e000h,0h
MR_SET_CONST ?BKME51,+,-52,5,0ffffh,0ffffh,0ffffh,0f000h,0h
MR_SET_CONST ?BKME52,+,-53,5,0ffffh,0ffffh,0ffffh,0f800h,0h
MR_SET_CONST ?BKME53,+,-54,5,0ffffh,0ffffh,0ffffh,0fc00h,0h
MR_SET_CONST ?BKME54,+,-55,5,0ffffh,0ffffh,0ffffh,0fe00h,0h
MR_SET_CONST ?BKME55,+,-56,5,0ffffh,0ffffh,0ffffh,0ff00h,0h
MR_SET_CONST ?BKME56,+,-57,5,0ffffh,0ffffh,0ffffh,0ff80h,0h
MR_SET_CONST ?BKME57,+,-58,5,0ffffh,0ffffh,0ffffh,0ffc0h,0h
MR_SET_CONST ?BKME58,+,-59,5,0ffffh,0ffffh,0ffffh,0ffe0h,0h
MR_SET_CONST ?BKME59,+,-60,5,0ffffh,0ffffh,0ffffh,0fff0h,0h
MR_SET_CONST ?BKME60,+,-61,5,0ffffh,0ffffh,0ffffh,0fff8h,0h
MR_SET_CONST ?BKME61,+,-62,5,0ffffh,0ffffh,0ffffh,0fffch,0h
MR_SET_CONST ?BKME62,+,-63,5,0ffffh,0ffffh,0ffffh,0fffeh,0h
MR_SET_CONST ?BKME63,+,-64,5,0ffffh,0ffffh,0ffffh,0ffffh,0h
MR_SET_CONST ?BKME64,+,-65,5,0ffffh,0ffffh,0ffffh,0ffffh,8000h
MR_SET_CONST ?BKME65,+,-66,5,0ffffh,0ffffh,0ffffh,0ffffh,0c000h
MR_SET_CONST ?BKME66,+,-67,5,0ffffh,0ffffh,0ffffh,0ffffh,0e000h
MR_SET_CONST ?BKME67,+,-68,5,0ffffh,0ffffh,0ffffh,0ffffh,0f000h
MR_SET_CONST ?BKME68,+,-69,5,0ffffh,0ffffh,0ffffh,0ffffh,0f800h
MR_SET_CONST ?BKME69,+,-70,5,0ffffh,0ffffh,0ffffh,0ffffh,0fc00h
MR_SET_CONST ?BKME70,+,-71,5,0ffffh,0ffffh,0ffffh,0ffffh,0fe00h

;;/* exp(x) , x Element N */
MR_SET_CONST ?BKMEP1,+,1,5,0adf8h,5458h,0a2bbh,4a9ah,0afdch
MR_SET_CONST ?BKMEP2,+,2,5,0ec73h,25c6h,0a6edh,6e61h,9d1eh
MR_SET_CONST ?BKMEP3,+,4,5,0a0afh,2dfbh,7d88h,2f96h,0a5f0h
MR_SET_CONST ?BKMEP4,+,5,5,0da64h,8171h,39d2h,0c33ch,6b6ah
MR_SET_CONST ?BKMEP5,+,7,5,9469h,0c4cbh,819ch,78fbh,37d5h
MR_SET_CONST ?BKMEP6,+,8,5,0c9b6h,0e2b4h,8604h,79bdh,4d73h
MR_SET_CONST ?BKMEP7,+,10,5,8914h,42d5h,76edh,5378h,0fd00h
MR_SET_CONST ?BKMEP8,+,11,5,0ba4fh,53eah,3863h,6f85h,0f007h
MR_SET_CONST ?BKMEP9,+,12,5,0fd38h,0abe2h,387ch,0e1bh,2af1h
MR_SET_CONST ?BKMEP10,+,14,5,0ac14h,0ee7ch,0a82ah,0fcf8h,3f54h
MR_SET_CONST ?BKMEP20,+,28,5,0e758h,445bh,4740h,2010h,0c4bdh
MR_SET_CONST ?BKMEP30,+,43,5,9b82h,3857h,6147h,64f4h,3e20h
MR_SET_CONST ?BKMEP40,+,57,5,0d110h,69cbh,0cb97h,545ah,1b08h
MR_SET_CONST ?BKMEP50,+,72,5,8c88h,1f20h,405ah,2b32h,6bbah
MR_SET_CONST ?BKMEP60,+,86,5,0bcedh,0e4eeh,29e3h,3249h,95e5h
MR_SET_CONST ?BKMEP70,+,100,5,0fdfeh,90ceh,21d8h,2398h,3cbfh
MR_SET_CONST ?BKMEP80,+,115,5,0aabbh,0cdcch,279fh,59e4h,5282h
MR_SET_CONST ?BKMEP90,+,129,5,0e588h,47fdh,0f60bh,1e4bh,0e08fh
MR_SET_CONST ?BKMEP100,+,144,5,9a4ah,54d8h,0b8dfh,0a566h,1128h
MR_SET_CONST ?BKMEP200,+,288,5,0b9fbh,753h,0cfadh,0ca2bh,5e35h
MR_SET_CONST ?BKMEP300,+,432,5,0e02eh,538h,0b35ah,539eh,0b354h
MR_SET_CONST ?BKMEP400,+,577,5,871ch,0c6beh,80b8h,1dc8h,0f36eh
MR_SET_CONST ?BKMEP500,+,721,5,0a2ddh,154fh,0bf21h,0c4a3h,0f574h
MR_SET_CONST ?BKMEP600,+,865,5,0c450h,9169h,1a59h,0ca5ch,434bh
MR_SET_CONST ?BKMEP700,+,1009,5,0eca2h,0efa7h,0c764h,7118h,3392h
MR_SET_CONST ?BKMEP800,+,1154,5,8e9eh,0b9b1h,0ff73h,2921h,2996h
MR_SET_CONST ?BKMEP900,+,1298,5,0abe9h,0c9b7h,25f1h,0c3d4h,0ad2h
MR_SET_CONST ?BKMEP1000,+,1442,5,0cf39h,1bcdh,76b9h,0d6c0h,2b16h
MR_SET_CONST ?BKMEP2000,+,2885,5,0a7bdh,67b3h,0aa84h,63feh,0f73eh
MR_SET_CONST ?BKMEP3000,+,4328,5,87c7h,923dh,0f849h,1493h,0f0a9h
MR_SET_CONST ?BKMEP4000,+,5770,5,0dbd1h,52ddh,6389h,2681h,7877h
MR_SET_CONST ?BKMEP5000,+,7213,5,0b1efh,4b7bh,0f715h,0d351h,5a40h
MR_SET_CONST ?BKMEP6000,+,8656,5,9008h,2fa4h,177fh,0a70bh,49d9h
MR_SET_CONST ?BKMEP7000,+,10098,5,0e92dh,7ff9h,81d4h,7a25h,415eh
MR_SET_CONST ?BKMEP8000,+,11541,5,0bcbfh,0ceefh,309bh,0c10bh,41aeh
MR_SET_CONST ?BKMEP9000,+,12984,5,98c9h,3388h,3385h,21c5h,4190h

MR_SET_CONST ?BKMEL2,+,-1,5,0b172h,17f7h,0d1cfh,79abh,0c9e4h ;; Ln(2)

;;/**
;; * Calculate exp(x) using BKM Algorithm.
;; * Precision is 64 bit, RM = round to nearest.
;; * Remarks: -10000 < x < 10000
;; */
MR_EXP macro r:req,x:req,N:=<71>
	IF MREAL_XDIM NE 4
		.err <precision setting not supported: 64 bit expected>
		MR_SET_ZERO r,4
		EXITM
	ENDIF
	IF MR_IS_NAN(x)
		MR_LOAD_CONST r,NaN
		EXITM
	ENDIF
	IF MR_IS_INFINITE(x)
		IF MR_IS_SIGN_MINUS(x)
			MR_LOAD_CONST r,zero
		ELSE
			MR_LOAD_CONST r,+Infinity
		ENDIF
		EXITM
	ENDIF
	IF N GT 71
		.err <invalid parameter: _N: N>
		EXITM
	ENDIF
	mrexp_sign = MR_IS_SIGN_MINUS(x)
	
	;;/**
	;; * Reduce argument range thus 0 <= arg < 1
	;; *  arg = x - Floor(x)
	;; */
	MR_ABS ?A,x,4
	MR_CONVERT ?A,?A,4,5,MRRM_TRUNCATE
	MR_ROUND ?T,?A,,,MRRM_TRUNCATE,5
	MR_SUB ?A,?A,?T,MRRM_TRUNCATE,5
	mrexp_exp = MR_TO_UINT32(?T,,MRRM_ROUND_TO_EVEN,5)
	IF mrexp_exp GT 9999
		.err <value to large: expected: Abs(_x) LT 10000>
		IF mrexp_sign
			MR_LOAD_CONST r,zero
		ELSE
			MR_LOAD_CONST r,+Infinity
		ENDIF
		EXITM
	ENDIF
	
	;;/**
	;; * BKM Algorithm:
    ;; *   Exp ( arg , N ) {    // 0 <= arg <= ca. 1.562
    ;; *      x = 1;
    ;; *      y = 0;
    ;; *      for ( i = 0; i < N; i++ ) {
    ;; *        tmp = y + ln(1+0.5^i);     // table value
    ;; *        if ( tmp <= arg ) {
    ;; *            y = tmp;
    ;; *            x = x + x*2^(-i);      // "^" means exponentiation
    ;; *        }
    ;; *      }
    ;; *      return x;
    ;; *   }
	;; */
	MR_MOV r,?MRC_ONE,5
	MR_SET_ZERO ?Y,5
	mrexp_cntr = 0
	REPEAT N
		MR_ADD ?T,?Y,@CatStr(<?BKME>,%mrexp_cntr),MRRM_ROUND_TO_EVEN,5
		IF MR_LE(?T,?A,5)
			MR_MOV ?Y,?T,5
			MR_CSCALE ?T,r,%-mrexp_cntr,MRRM_TRUNCATE,5
			MR_ADD r,r,?T,MRRM_ROUND_TO_EVEN,5
		ENDIF
		mrexp_cntr = mrexp_cntr + 1
	ENDM
	
	;;/* process integer exponent */
	IF mrexp_exp
		;;/* get exp(k) with 0 < k <= 9999  */
		mrexp_ld = 0
		mrexp_f = 1
		WHILE mrexp_exp
			mrexp_digit = mrexp_exp MOD 10
			IF mrexp_digit
				IF mrexp_ld
					MR_MUL ?T,?T,@CatStr(<?BKMEP>,%mrexp_f*mrexp_digit),MRRM_ROUND_TO_EVEN,5
				ELSE
					MR_MOV ?T,@CatStr(<?BKMEP>,%mrexp_f*mrexp_digit),5
					mrexp_ld = -1
				ENDIF
			ENDIF
			mrexp_exp = mrexp_exp / 10
			mrexp_f = mrexp_f * 10
		ENDM
		MR_MUL r,r,?T,MRRM_ROUND_TO_EVEN,5
	ENDIF
	IF mrexp_sign
		;;/* e^(-x) = 1/(e^x) */
		MR_DIV r,?MRC_ONE,r,MRRM_ROUND_TO_EVEN,5,4
	ELSE
		MR_CONVERT r,r,5,4,MRRM_ROUND_TO_EVEN
	ENDIF
endm


;;/**
;; * Table for CORDIC Algorithm: x[i] = arcTan(2^(-k)) with 0 <= k <= 65
;; * 64bit precision, round to nearest even.
;; */
MR_SET_CONST ?COR0,+,-1,4,0c90fh,0daa2h,2168h,0c235h
MR_SET_CONST ?COR1,+,-2,4,0ed63h,382bh,0ddah,7b45h
MR_SET_CONST ?COR2,+,-3,4,0fadbh,0afc9h,6406h,0eb15h
MR_SET_CONST ?COR3,+,-4,4,0feadh,0d4d5h,617bh,6e33h
MR_SET_CONST ?COR4,+,-5,4,0ffaah,0ddb9h,67efh,4e37h
MR_SET_CONST ?COR5,+,-6,4,0ffeah,0adddh,4bb1h,2542h
MR_SET_CONST ?COR6,+,-7,4,0fffah,0aaddh,0db94h,0d5bch
MR_SET_CONST ?COR7,+,-8,4,0fffeh,0aaadh,0ddd4h,0b968h
MR_SET_CONST ?COR8,+,-9,4,0ffffh,0aaaah,0ddddh,0b94ch
MR_SET_CONST ?COR9,+,-10,4,0ffffh,0eaaah,0adddh,0dd4ch
MR_SET_CONST ?COR10,+,-11,4,0ffffh,0faaah,0aaddh,0dddch
MR_SET_CONST ?COR11,+,-12,4,0ffffh,0feaah,0aaadh,0dddeh
MR_SET_CONST ?COR12,+,-13,4,0ffffh,0ffaah,0aaaah,0dddeh
MR_SET_CONST ?COR13,+,-14,4,0ffffh,0ffeah,0aaaah,0addeh
MR_SET_CONST ?COR14,+,-15,4,0ffffh,0fffah,0aaaah,0aadeh
MR_SET_CONST ?COR15,+,-16,4,0ffffh,0fffeh,0aaaah,0aaaeh
MR_SET_CONST ?COR16,+,-17,4,0ffffh,0ffffh,0aaaah,0aaabh
MR_SET_CONST ?COR17,+,-18,4,0ffffh,0ffffh,0eaaah,0aaabh
MR_SET_CONST ?COR18,+,-19,4,0ffffh,0ffffh,0faaah,0aaabh
MR_SET_CONST ?COR19,+,-20,4,0ffffh,0ffffh,0feaah,0aaabh
MR_SET_CONST ?COR20,+,-21,4,0ffffh,0ffffh,0ffaah,0aaabh
MR_SET_CONST ?COR21,+,-22,4,0ffffh,0ffffh,0ffeah,0aaabh
MR_SET_CONST ?COR22,+,-23,4,0ffffh,0ffffh,0fffah,0aaabh
MR_SET_CONST ?COR23,+,-24,4,0ffffh,0ffffh,0fffeh,0aaabh
MR_SET_CONST ?COR24,+,-25,4,0ffffh,0ffffh,0ffffh,0aaabh
MR_SET_CONST ?COR25,+,-26,4,0ffffh,0ffffh,0ffffh,0eaabh
MR_SET_CONST ?COR26,+,-27,4,0ffffh,0ffffh,0ffffh,0faabh
MR_SET_CONST ?COR27,+,-28,4,0ffffh,0ffffh,0ffffh,0feabh
MR_SET_CONST ?COR28,+,-29,4,0ffffh,0ffffh,0ffffh,0ffabh
MR_SET_CONST ?COR29,+,-30,4,0ffffh,0ffffh,0ffffh,0ffebh
MR_SET_CONST ?COR30,+,-31,4,0ffffh,0ffffh,0ffffh,0fffbh
MR_SET_CONST ?COR31,+,-32,4,0ffffh,0ffffh,0ffffh,0ffffh
MR_SET_CONST ?COR32,+,-32,4,8000h,0h,0h,0h
MR_SET_CONST ?COR33,+,-33,4,8000h,0h,0h,0h
MR_SET_CONST ?COR34,+,-34,4,8000h,0h,0h,0h
MR_SET_CONST ?COR35,+,-35,4,8000h,0h,0h,0h
MR_SET_CONST ?COR36,+,-36,4,8000h,0h,0h,0h
MR_SET_CONST ?COR37,+,-37,4,8000h,0h,0h,0h
MR_SET_CONST ?COR38,+,-38,4,8000h,0h,0h,0h
MR_SET_CONST ?COR39,+,-39,4,8000h,0h,0h,0h
MR_SET_CONST ?COR40,+,-40,4,8000h,0h,0h,0h
MR_SET_CONST ?COR41,+,-41,4,8000h,0h,0h,0h
MR_SET_CONST ?COR42,+,-42,4,8000h,0h,0h,0h
MR_SET_CONST ?COR43,+,-43,4,8000h,0h,0h,0h
MR_SET_CONST ?COR44,+,-44,4,8000h,0h,0h,0h
MR_SET_CONST ?COR45,+,-45,4,8000h,0h,0h,0h
MR_SET_CONST ?COR46,+,-46,4,8000h,0h,0h,0h
MR_SET_CONST ?COR47,+,-47,4,8000h,0h,0h,0h
MR_SET_CONST ?COR48,+,-48,4,8000h,0h,0h,0h
MR_SET_CONST ?COR49,+,-49,4,8000h,0h,0h,0h
MR_SET_CONST ?COR50,+,-50,4,8000h,0h,0h,0h
MR_SET_CONST ?COR51,+,-51,4,8000h,0h,0h,0h
MR_SET_CONST ?COR52,+,-52,4,8000h,0h,0h,0h
MR_SET_CONST ?COR53,+,-53,4,8000h,0h,0h,0h
MR_SET_CONST ?COR54,+,-54,4,8000h,0h,0h,0h
MR_SET_CONST ?COR55,+,-55,4,8000h,0h,0h,0h
MR_SET_CONST ?COR56,+,-56,4,8000h,0h,0h,0h
MR_SET_CONST ?COR57,+,-57,4,8000h,0h,0h,0h
MR_SET_CONST ?COR58,+,-58,4,8000h,0h,0h,0h
MR_SET_CONST ?COR59,+,-59,4,8000h,0h,0h,0h
MR_SET_CONST ?COR60,+,-60,4,8000h,0h,0h,0h
MR_SET_CONST ?COR61,+,-61,4,8000h,0h,0h,0h
MR_SET_CONST ?COR62,+,-62,4,8000h,0h,0h,0h
MR_SET_CONST ?COR63,+,-63,4,8000h,0h,0h,0h
MR_SET_CONST ?COR64,+,-64,4,8000h,0h,0h,0h
MR_SET_CONST ?COR65,+,-65,4,8000h,0h,0h,0h

;;/* reciprocal of scale factor K = sqrt(1+2^(-2*0))*sqrt(1+2^(-2*1))*sqrt(1+2^(-2*2))*...*sqrt(1+2^(-2*n)) with n-->infinity */
MR_SET_CONST ?CORK,+,-1,4,9b74h,0eda8h,435eh,5a68h 

;;/* some constant used by MR_SINCOS */
MR_SET_CONST ?COR_2RPI,+,-1,8,0a2f9h,836eh,4e44h,1529h,0fc27h,57d1h,0f534h,0ddc1h ;; 2/Pi
MR_SET_CONST ?COR_PIH,+,0,8,0c90fh,0daa2h,2168h,0c234h,0c4c6h,628bh,80dch,1cd1h ;; Pi/2

MR_CORDIC_ROTATION macro x0:req,y0:req,z0:req,N:req,n:=<MREAL_XDIM>
	mrcorr_cntr = 0
	REPEAT N
		MR_CSCALE ?T,x0,%-mrcorr_cntr,MRRM_ROUND_TO_EVEN,n
		MR_CSCALE ?U,y0,%-mrcorr_cntr,MRRM_ROUND_TO_EVEN,n
		IFE MR_IS_SIGN_MINUS(z0)
			MR_SUB x0,x0,?U,MRRM_ROUND_TO_EVEN,n
			MR_ADD y0,y0,?T,MRRM_ROUND_TO_EVEN,n
			MR_SUB z0,z0,@CatStr(<?COR>,%mrcorr_cntr),MRRM_ROUND_TO_EVEN,n
		ELSE
			MR_ADD x0,x0,?U,MRRM_ROUND_TO_EVEN,n
			MR_SUB y0,y0,?T,MRRM_ROUND_TO_EVEN,n
			MR_ADD z0,z0,@CatStr(<?COR>,%mrcorr_cntr),MRRM_ROUND_TO_EVEN,n
		ENDIF
		mrcorr_cntr = mrcorr_cntr + 1
	ENDM
endm

;MR_CORDIC_VECTORING macro x0:req,y0:req,z0:req,N:req,n:=<MREAL_XDIM>
;	mrcorr_cntr = 0
;	REPEAT N
;		MR_CSCALE ?T,x0,%-mrcorr_cntr,MRRM_ROUND_TO_EVEN,n
;		MR_CSCALE ?U,y0,%-mrcorr_cntr,MRRM_ROUND_TO_EVEN,n
;		IF MR_IS_SIGN_MINUS(y0)
;			MR_SUB x0,x0,?U,MRRM_ROUND_TO_EVEN,n
;			MR_ADD y0,y0,?T,MRRM_ROUND_TO_EVEN,n
;			MR_SUB z0,z0,@CatStr(<?COR>,%mrcorr_cntr),MRRM_ROUND_TO_EVEN,n
;		ELSE
;			MR_ADD x0,x0,?U,MRRM_ROUND_TO_EVEN,n
;			MR_SUB y0,y0,?T,MRRM_ROUND_TO_EVEN,n
;			MR_ADD z0,z0,@CatStr(<?COR>,%mrcorr_cntr),MRRM_ROUND_TO_EVEN,n
;		ENDIF
;		mrcorr_cntr = mrcorr_cntr + 1
;	ENDM
;endm

;;/**
;; * Get rs=sin(x) and rc=cos(x) using CORDIC algorithm.
;; * Remarks that -2^32 < x < 2^32.
;; * Precision is 64 bit, RM = round to nearest.
;; */
MR_SINCOS macro rs:req,rc:req,x:req
	
	IF MREAL_XDIM NE 4
		.err <precision setting not supported: 64 bit expected>
		MR_SET_ZERO rs,4
		MR_SET_ZERO rc,4
		EXITM
	ENDIF
	IF MR_IS_ZERO(x)
		MR_SET_ZERO rs,4
		MR_MOV rc,?MRC_ONE,4
		EXITM
	ENDIF
	IF NOT MR_IS_NORMAL(x)
		MR_LOAD_CONST rs,NaN
		MR_MOV rc,rs,4
		EXITM
	ENDIF
	mrsc_sign = MR_IS_SIGN_MINUS(x)
	
	;;/**
	;; * range reduction:
	;; *  q = floor(|x| * 2/pi)
	;; *  a = |x| - pi/2 * q
	;; */
	MR_ABS ?X,x,4
	MR_XMUL ?A,?X,?COR_2RPI,8,4,8,MRRM_ROUND_TO_EVEN		;; |x| * 2/pi
	MR_ROUND ?Q,?A,,,MRRM_TRUNCATE,8						;; floor(|x| * 2/pi)
	MR_MUL ?A,?Q,?COR_PIH,MRRM_ROUND_TO_EVEN,8				;; pi/2 * floor(|x| * 2/pi)
	MR_CONVERT ?X,?X,4,8,MRRM_TRUNCATE
	MR_SUB ?A,?X,?A,MRRM_ROUND_TO_EVEN,8					;; |x| - pi/2 * floor(|x| * 2/pi)
	mrsc_q = MR_TO_UINT32(?Q,,MRRM_ROUND_TO_EVEN,8) MOD 4	;; q MOD 4 = quadrant
	
	;;/* CORDIC */
	MR_MOV ?X,?CORK,4
	MR_SET_ZERO ?Y,4
    MR_CONVERT ?Z,?A,8,4,MRRM_ROUND_TO_EVEN
    MR_CORDIC_ROTATION ?X,?Y,?Z,64,4

	;;/* choose value by quadrant */
	IF mrsc_q EQ 0
		MR_MOV rs,?Y,4
		MR_MOV rc,?X,4
	ELSEIF mrsc_q EQ 1
    	MR_MOV rs,?X,4
    	MR_NEG rc,?Y,4
    ELSEIF mrsc_q EQ 2
    	MR_NEG rs,?Y,4
    	MR_NEG rc,?X,4
    ELSEIF mrsc_q EQ 3
    	MR_NEG rs,?X,4
    	MR_MOV rc,?Y,4
    ENDIF
    
    ;;/* apply sign */
    IF mrsc_sign
    	MR_NEG rs,rs,4
    ENDIF
endm


ENDIF ;; IFNDEF MR_VERSION




