# HnTools
P7zip v16.02 adds alot of enhancements & fixes to the original port in addition to supporting Rar5 format.
To build the app against the newest P7zip version(stripped-down clone of v16.02 is added to this repo) , simply you have to build it separatly as before using the same instructions as above with some minor changes:

How to Build:
First ,you have to compile the native part of the project,P7Zip,the repo comes with version 9.20.1 source.

Build The Plugins:
1- In your terminal, Browse to "p7zip_16.02/CPP/ANDROID/Format7zFree/jni/" to build 7z.so plugin using the ndk as above.
2- In your terminal, Browse to "p7zip_16.02/CPP/7zip/Compress/Rar/jni/" to build Rar.so codec (for decompressing Rar archives) using the ndk as above.
3- Copy the resulting 7z.so & Rar.so to the "/Prebuilt/" directory for the approperiate target architecture as above.
4- Open the ZipExtractor project in android studio and start building the app.
Features:

Supports the following formats:
Unpacking only: AR, ARJ, CAB, CHM, CPIO, CramFS, DMG, EXT, FAT, GPT, HFS, IHEX, ISO, LZH, LZMA, MBR, MSI, NSIS, NTFS, QCOW2, RAR, RPM, SquashFS, UDF, UEFI, VDI, VHD, VMDK, WIM, XAR and Z.

Packing / unpacking:7z, XZ, BZIP2, GZIP, TAR, ZIP and WIM .

Supports AES-256 encryption in 7z and ZIP formats .
A built-in file browser.