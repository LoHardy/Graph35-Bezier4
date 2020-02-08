@echo off
rem Do not edit! This batch file is created by CASIO fx-9860G SDK.


if exist BEZIER4.G1A  del BEZIER4.G1A

cd debug
if exist FXADDINror.bin  del FXADDINror.bin
"C:\Casio\OS\SH\Bin\Hmake.exe" Addin.mak
cd ..
if not exist debug\FXADDINror.bin  goto error

"C:\Casio\Tools\MakeAddinHeader363.exe" "C:\Users\hardy\Documents\CASIO\fx-9860G SDK\bezier4"
if not exist BEZIER4.G1A  goto error
echo Build has completed.
goto end

:error
echo Build was not successful.

:end

