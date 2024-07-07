@echo off
call C:\Espressif\frameworks\esp-idf-v5.2.1\export.bat
idf.py flash monitor
