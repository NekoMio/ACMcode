@echo off
:loop
maker.exe >in.txt  
A.exe <in.txt >out.txt  
AA.exe <in.txt >ans.txt   
fc /A out.txt ans.txt
if not errorlevel 1 goto loop
pause
:end