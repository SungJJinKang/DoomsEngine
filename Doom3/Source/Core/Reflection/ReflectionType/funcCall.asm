


_TEXT SEGMENT

a$ = 48
FP$ = 56

PUBLIC call_func 

; void call_func(unsigned __int64*, unsigned __int64*)


call_func PROC

        mov     QWORD PTR [rsp+16], rdx
        mov     QWORD PTR [rsp+8], rcx
        sub     rsp, 40                             ; 00000028H
        mov     rcx, QWORD PTR a$[rsp]
        call    QWORD PTR FP$[rsp]
        add     rsp, 40                             ; 00000028H
        ret     0

call_func ENDP

_TEXT ENDS 

END
