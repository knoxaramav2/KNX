# KNX
A node based run-time language, built in c

Intended to make multithreaded applications easier to build, and supports
libraries in both .knx or as c dynamic libraries with the included SDK

##Dependencies
This project requires the KNX Library static library in order to compile. This may be downloaded from gitub from the links below


[Https](https://github.com/knoxaramav2/KNX_Libraries.git) OR
[SSH](git@github.com:knoxaramav2/KNX_Libraries.git)

By default, the resulting KNX_Library folder (after building, just use the Make command in the top level folder) may be placed alongside the KNX folder in order for the build process to find. If you would like to keep them separate, modify the KLIB_DEFAULT variable in the KNX top level make file.
