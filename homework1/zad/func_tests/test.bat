chcp 1251
@echo off
python main.py < input%1.txt > output_programm%1.txt
fc output_programm%1.txt output_right%1.txt
if "%1" == "13" pause
