:1
gen >1.in
b <1.in >1.out
goto 1
bf <1.in >1.ans
fc 1.out 1.ans
if %errorlevel% == 0 goto 1
pause