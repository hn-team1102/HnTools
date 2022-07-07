/*
 * Copyright (c) 2018. Created by : Mahmoud Galal.
 * Support: mahmoudgalal57@yahoo.com
 */

package com.mg.zeearchiver.utils.compression;

import static com.mg.zeearchiver.utils.Constants.EEnum;

import org.jetbrains.annotations.Nullable;

import java.util.Vector;

/**
 * Compression session info
 */
public class CInfo {
    public EEnum UpdateMode;
    public boolean SolidIsSpecified;
    public boolean MultiThreadIsAllowed;
    public long SolidBlockSize;
    public int NumThreads;

    public Vector<Long> VolumeSizes;

    public int Level;
    public String Method;
    public int Dictionary;
    public boolean OrderMode;
    public int Order;
    public String Options;

    public String EncryptionMethod;

    public boolean SFXMode;
    public boolean OpenShareForWrite;


    public String ArchiveName; // in: Relative for ; out: abs
    public String CurrentDirPrefix;
    public boolean KeepName;

    public boolean GetFullPathName(String result) {
        return true;
    }

    public int FormatIndex;

    public String Password;
    public boolean EncryptHeadersIsAllowed;
    public boolean EncryptHeaders;

    void Init() {
        Level = Dictionary = Order = 0;// UInt32(-1);
        OrderMode = false;
        Method = "";
        Options = "";
        EncryptionMethod = "";
    }

    public CInfo() {
        Init();
    }

    public void init7Z(@Nullable String password, @Nullable String outputPath, int compressLevel) {
        UpdateMode = EEnum.kAdd;
        SolidIsSpecified = true;
        MultiThreadIsAllowed = true;
        SolidBlockSize = -2147483648;
        NumThreads = -1;
        VolumeSizes = null;
        Level = compressLevel;
        Method = "LZMA";
        Dictionary = 16777216;
        OrderMode = false;
        Order = 32;
        Options = "";
        EncryptionMethod = "";
        SFXMode = false;
        OpenShareForWrite = false;
        ArchiveName = outputPath; //'/storage/emulated/0/DCIM/Screenshots.7z'
        CurrentDirPrefix = null;
        KeepName = false;
        FormatIndex = 0;
        Password = password;
        EncryptHeadersIsAllowed = true;
        EncryptHeaders = false;
    }

    public void initTar(String password, String outputPath) {
        UpdateMode = EEnum.kAdd;
        SolidIsSpecified = false;
        MultiThreadIsAllowed = false;
        SolidBlockSize = 0;
        NumThreads = -1;
        VolumeSizes = null;
        Level = -1;
        Method = "";
        Dictionary = -1;
        OrderMode = false;
        Order = -1;
        Options = "";
        EncryptionMethod = "";
        SFXMode = false;
        OpenShareForWrite = false;
        ArchiveName = outputPath; //'/storage/emulated/0/DCIM/Screenshots.7z'
        CurrentDirPrefix = null;
        KeepName = false;
        FormatIndex = 41;
        Password = password;
        EncryptHeadersIsAllowed = false;
        EncryptHeaders = false;
        //  Compression parameters:ArcName:/storage/emulated/0/ZipExtractor/Camera.tar,FormatIndex:38,Level:4294967295,Method:,Dictionary:4294967295,OrderMode:0,order:4294967295,SolidIsSpecified:0,SolidBlockSize:0,MultiThreadIsAllowed:0,NumThreads:0,EncryptionMethod:,EncryptHeadersIsAllowed:0,EncryptHeaders:0,SFXMode:0
    }

    public void initZip(@Nullable String password, @Nullable String outputPath, int compressLevel) {
        UpdateMode = EEnum.kAdd;
        SolidIsSpecified = false;
        MultiThreadIsAllowed = true;
        SolidBlockSize = 0;
        NumThreads = -1;
        VolumeSizes = null;
        Level = compressLevel;
        Method = "Deflate";
        Dictionary = -1;
        OrderMode = false;
        Order = 32;
        Options = "";
        EncryptionMethod = "AES256"; //ZIPPro is ""
        SFXMode = false;
        OpenShareForWrite = false;
        ArchiveName = outputPath; //'/storage/emulated/0/DCIM/Screenshots.7z'
        CurrentDirPrefix = null;
        KeepName = false;
        FormatIndex = 52;
        Password = password;
        EncryptHeadersIsAllowed = false;
        EncryptHeaders = false;
    }
}
