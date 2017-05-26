@echo off
python zad1_7.py < input%1.txt > output_programm%1.txt
fc output_programm%1.txt output_right%1.txt
Pause