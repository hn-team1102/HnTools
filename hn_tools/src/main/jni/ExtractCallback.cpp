// ExtractCallback.cpp

#include "StdAfx.h"
//#include "com_aroma_test7zconsole_Archive.h"
#include "Windows/Error.h"
#include "Windows/FileDir.h"
#include "Windows/FileFind.h"

#include "FilePathAutoRename.h"

//#include "../GUI/ExtractRes.h"
#include "Common/StringConvert.h"

#include "ExtractCallback.h"
//#include "FormatUtils.h"
//#include "OverwriteDialog.h"
#ifndef _NO_CRYPTO
//#include "PasswordDialog.h"
#endif


extern jmethodID beforeOpen, extractResult, openResult, thereAreNoFiles, setPassword;
extern jmethodID askWrite, setCurrentFilePath, showMessage, setNumFiles;
extern jmethodID setRatioInfo;
extern jmethodID askOverwrite, prepareOperation, messageError, setOperationResult;
extern jmethodID cryptoGetTextPassword;
extern jmethodID setTotal, setCompleted, exAddErrorMessage;
extern jmethodID open_CheckBreak, open_SetTotal, open_SetCompleted, open_CryptoGetTextPassword,
        open_GetPasswordIfAny, open_WasPasswordAsked, open_ClearPasswordWasAskedFlag;


using namespace NWindows;
using namespace NFile;
using namespace NFind;

CExtractCallbackImp::~CExtractCallbackImp() {}

void CExtractCallbackImp::Init() {
    NumArchiveErrors = 0;
    ThereAreMessageErrors = false;
#ifndef _SFX
    NumFolders = NumFiles = 0;
    NeedAddFile = false;
#endif

}

void CExtractCallbackImp::AddErrorMessage(LPCWSTR message) {
    ThereAreMessageErrors = true;
    if (enviro.env != nullptr && exAddErrorMessage != nullptr) {
        jstring Name = enviro.env->NewStringUTF(GetOemString(message));
        enviro.env->CallVoidMethod(enviro.obj, exAddErrorMessage, Name);
        enviro.env->DeleteLocalRef(Name);
    }

    //ProgressDialog->Sync.AddErrorMessage(message);
}

STDMETHODIMP CExtractCallbackImp::SetNumFiles(UInt64
#ifndef _SFX
                                              numFiles
#endif
) {
#ifndef _SFX
    //LOGI("Calling >>>> CExtractCallbackImp::SetNumFiles");
    // ProgressDialog->Sync.SetNumFilesTotal(numFiles);
    if (setNumFiles == nullptr) return S_OK;
    enviro.env->CallLongMethod(enviro.obj, setNumFiles, (jlong) numFiles);
#endif
    return S_OK;
}

STDMETHODIMP CExtractCallbackImp::SetTotal(UInt64 total) {
    // ProgressDialog->Sync.SetProgress(total, 0);
    //LOGI("Calling >>>> CExtractCallbackImp::SetTotal");
    if (setTotal == nullptr) {
        LOGE("Error ,setTotal is NULL!!!");
        return S_OK;
    }
    if (enviro.env == nullptr) {
        LOGE("Error ,env is NULL!!!");
        return S_OK;
    }
    enviro.env->CallLongMethod(enviro.obj, setTotal, (jlong) total);
    return S_OK;
}

STDMETHODIMP CExtractCallbackImp::SetCompleted(const UInt64 *value) {
    //LOGI("Calling >>>> CExtractCallbackImp::SetCompleted");
    //RINOK(ProgressDialog->Sync.ProcessStopAndPause());
    if (setCompleted == nullptr) return S_OK;
    if (value != nullptr)
        //ProgressDialog->Sync.SetPos(*value);
        enviro.env->CallLongMethod(enviro.obj, setCompleted, (jlong) (*value));
    return S_OK;
}

HRESULT CExtractCallbackImp::Open_CheckBreak() {
    // return ProgressDialog->Sync.ProcessStopAndPause();
    jlong ret = enviro.env->CallLongMethod(enviro.obj, open_CheckBreak);
    return ret;
}

HRESULT CExtractCallbackImp::Open_SetTotal(const UInt64 *numFiles/* numFiles */,
                                           const UInt64 *numBytes/* numBytes */) {
    // if (numFiles != NULL) ProgressDialog->Sync.SetNumFilesTotal(*numFiles);
    if (open_SetTotal == nullptr) return S_OK;
    if (numFiles)//&& numBytes)
        enviro.env->CallLongMethod(enviro.obj, open_SetTotal, (jlong) (*numFiles), 0);//*numBytes);
    return Open_CheckBreak();
}

HRESULT CExtractCallbackImp::Open_SetCompleted(const UInt64 * /* numFiles */,
                                               const UInt64 * /* numBytes */) {
    // RINOK(ProgressDialog->Sync.ProcessStopAndPause());
    //// if (numFiles != NULL) ProgressDialog->Sync.SetNumFilesCur(*numFiles);
    return Open_CheckBreak();
}

#ifndef _NO_CRYPTO

HRESULT CExtractCallbackImp::Open_CryptoGetTextPassword(BSTR *password) {
    RINOK(Open_CheckBreak());
    return CryptoGetTextPassword(password);
}

HRESULT CExtractCallbackImp::Open_GetPasswordIfAny(UString &password) {
    if (PasswordIsDefined)
        password = Password;
    return S_OK;
}

bool CExtractCallbackImp::Open_WasPasswordAsked() {
    return PasswordWasAsked;
}

void CExtractCallbackImp::Open_ClearPasswordWasAskedFlag() {
    PasswordWasAsked = false;
}

#endif


#ifndef _SFX

STDMETHODIMP CExtractCallbackImp::SetRatioInfo(const UInt64 *inSize, const UInt64 *outSize) {
    //LOGI("SetRatioInfo Called ");
    // ProgressDialog->Sync.SetRatioInfo(inSize, outSize);
    if (setRatioInfo == nullptr) return S_OK;
    if (inSize && outSize)
        enviro.env->CallLongMethod(enviro.obj, setRatioInfo, (jlong) (*inSize), (jlong) (*outSize));
    return Open_CheckBreak();
}

#endif

/*
STDMETHODIMP CExtractCallbackImp::SetTotalFiles(UInt64 total)
{
  ProgressDialog->Sync.SetNumFilesTotal(total);
  return S_OK;
}

STDMETHODIMP CExtractCallbackImp::SetCompletedFiles(const UInt64 *value)
{
  if (value != NULL)
    ProgressDialog->Sync.SetNumFilesCur(*value);
  return S_OK;
}
*/

STDMETHODIMP CExtractCallbackImp::AskOverwrite(
        const wchar_t *existName, const FILETIME *existTime, const UInt64 *existSize,
        const wchar_t *newName, const FILETIME *newTime, const UInt64 *newSize,
        Int32 *answer) {

    //enviro.env->CallLongMethod(enviro.obj,askOverwrite,*inSize,*outSize);
    //COverwriteDialog dialog;

//  dialog.OldFileInfo.SetTime(existTime);
//  dialog.OldFileInfo.SetSize(existSize);
//  dialog.OldFileInfo.Name = existName;
//
//  dialog.NewFileInfo.SetTime(newTime);
//  dialog.NewFileInfo.SetSize(newSize);
//  dialog.NewFileInfo.Name = newName;
//
//  ProgressDialog->WaitCreating();
//  INT_PTR writeAnswer = dialog.Create(*ProgressDialog);
//
//  switch(writeAnswer)
//  {
//    case IDCANCEL: *answer = NOverwriteAnswer::kCancel; return E_ABORT;
//    case IDYES: *answer = NOverwriteAnswer::kYes; break;
//    case IDNO: *answer = NOverwriteAnswer::kNo; break;
//    case IDC_BUTTON_OVERWRITE_YES_TO_ALL: *answer = NOverwriteAnswer::kYesToAll; break;
//    case IDC_BUTTON_OVERWRITE_NO_TO_ALL: *answer = NOverwriteAnswer::kNoToAll; break;
//    case IDC_BUTTON_OVERWRITE_AUTO_RENAME: *answer = NOverwriteAnswer::kAutoRename; break;
//    default: return E_FAIL;
//  }
    *answer = NOverwriteAnswer::kYesToAll;
    return S_OK;
}


STDMETHODIMP CExtractCallbackImp::PrepareOperation(const wchar_t *name, bool isFolder,
                                                   Int32 askExtractMode/* askExtractMode */,
                                                   const UInt64 *position/* position */) {
    //jstring Name =enviro.env->NewStringUTF((LPCSTR)GetOemString(name));
    //enviro.env->CallLongMethod(enviro.obj,prepareOperation,Name,isFolder?JNI_TRUE:JNI_FALSE,askExtractMode,*position);
    _isFolder = isFolder;
    return SetCurrentFilePath2(name);
}

STDMETHODIMP CExtractCallbackImp::MessageError(const wchar_t *message) {
    AddErrorMessage(message);
    return S_OK;
}

STDMETHODIMP CExtractCallbackImp::ShowMessage(const wchar_t *message) {
    AddErrorMessage(message);
    return S_OK;
}

STDMETHODIMP CExtractCallbackImp::SetOperationResult(Int32 operationResult, bool encrypted) {

    switch (operationResult) {
        case NArchive::NExtract::NOperationResult::kOK:
            break;
        default: {
            UINT messageID;
            UInt32 langID;
            UString s = L"";
            switch (operationResult) {
                case NArchive::NExtract::NOperationResult::kUnSupportedMethod:
//          messageID = IDS_MESSAGES_DIALOG_EXTRACT_MESSAGE_UNSUPPORTED_METHOD;
//          langID = 0x02000A91;
                    s = L"MESSAGE_UNSUPPORTED_METHOD";
                    break;
                case NArchive::NExtract::NOperationResult::kDataError:
//          messageID = encrypted ?
//              IDS_MESSAGES_DIALOG_EXTRACT_MESSAGE_DATA_ERROR_ENCRYPTED:
//              IDS_MESSAGES_DIALOG_EXTRACT_MESSAGE_DATA_ERROR;
//          langID = encrypted ? 0x02000A94 : 0x02000A92;
                    s = encrypted ? L"MESSAGE_DATA_ERROR_ENCRYPTED" : L"MESSAGE_DATA_ERROR";
                    break;
                case NArchive::NExtract::NOperationResult::kCRCError:
//          messageID = encrypted ?
//              IDS_MESSAGES_DIALOG_EXTRACT_MESSAGE_CRC_ENCRYPTED:
//              IDS_MESSAGES_DIALOG_EXTRACT_MESSAGE_CRC;
//          langID = encrypted ? 0x02000A95 : 0x02000A93;
                    s = encrypted ? L"MESSAGE_CRC_ENCRYPTED" : L"MESSAGE_CRC";
                    break;
                default:
                    return E_FAIL;
            }
            if (_needWriteArchivePath) {
                if (!_currentArchivePath.IsEmpty())
                    AddErrorMessage(_currentArchivePath);
                _needWriteArchivePath = false;
            }
            _currentFilePath = s;
            AddErrorMessage(_currentFilePath);
//      AddErrorMessage(
//        MyFormatNew(messageID,
//          #ifdef LANG
//          langID,
//          #endif
//          _currentFilePath));
        }
    }
#ifndef _SFX
    if (_isFolder)
        NumFolders++;
    else
        NumFiles++;

    if (enviro.env == nullptr || enviro.obj == nullptr || setOperationResult == nullptr) {
        return E_FAIL;
    }
    enviro.env->CallLongMethod(enviro.obj, setOperationResult, (jint) operationResult,
                               (jlong) NumFiles, encrypted ? JNI_TRUE : JNI_FALSE);
    // ProgressDialog->Sync.SetNumFilesCur(NumFiles);
#endif
    return Open_CheckBreak();
}

////////////////////////////////////////
// IExtractCallbackUI

HRESULT CExtractCallbackImp::BeforeOpen(const wchar_t *name) {
#ifndef _SFX
    // ProgressDialog->Sync.SetTitleFileName(name);
    // jstring Name =enviro.env->NewStringUTF((LPCSTR)GetOemString(name));
    enviro.env->CallVoidMethod(enviro.obj, beforeOpen, NULL);
#endif
    _currentArchivePath = name;
    return S_OK;
}

HRESULT CExtractCallbackImp::SetCurrentFilePath2(const wchar_t *path, UInt64 numf) {
    //LOGI("Calling >>>> CExtractCallbackImp::SetCurrentFilePath2");
    _currentFilePath = path;
#ifndef _SFX
    if (setCurrentFilePath == nullptr) {
        LOGE("Error ,setCurrentFilePath is NULL!!!");
        return S_OK;
    }
    if (enviro.env == nullptr) {
        LOGE("Error ,env is NULL!!!");
        return S_OK;
    }
    jstring Name = enviro.env->NewStringUTF(GetOemString(path));
    enviro.env->CallLongMethod(enviro.obj, setCurrentFilePath, Name, (jlong) numf);
    if (Name)
        enviro.env->DeleteLocalRef(Name);
    //ProgressDialog->Sync.SetCurrentFileName(path);
#endif
    return S_OK;
}

HRESULT CExtractCallbackImp::SetCurrentFilePath(const wchar_t *path) {
#ifndef _SFX
    if (NeedAddFile) NumFiles++;
    NeedAddFile = true;
    // ProgressDialog->Sync.SetNumFilesCur(NumFiles);
#endif
    return SetCurrentFilePath2(path, NumFiles);
}

HRESULT CExtractCallbackImp::OpenResult(const wchar_t *name, HRESULT result, bool encrypted) {
    jstring Name = enviro.env->NewStringUTF((LPCSTR) GetOemString(name));
    enviro.env->CallVoidMethod(enviro.obj, openResult, Name, (jlong) result,
                               encrypted ? JNI_TRUE : JNI_FALSE);
    enviro.env->DeleteLocalRef(Name);

    if (result != S_OK) {
        UString message;
        if (result == S_FALSE) {
            //  message = MyFormatNew(encrypted ? IDS_CANT_OPEN_ENCRYPTED_ARCHIVE : IDS_CANT_OPEN_ARCHIVE,
//        #ifdef LANG
//        (encrypted ? 0x0200060A : 0x02000609),
//        #endif
//        name);
            message = encrypted ? L"CANT_OPEN_ENCRYPTED_ARCHIVE" : L"CANT_OPEN_ARCHIVE";
        } else {
            message = name;
            message += L": ";
            UString message2;
            if (result == E_OUTOFMEMORY)
                message2 = L"MEM_ERROR";
//        #ifdef LANG
//        LangString(IDS_MEM_ERROR, 0x0200060B);
//        #else
//        MyLoadStringW(IDS_MEM_ERROR);
//        #endif
            else
                NError::MyFormatMessage(result, message2);
            message += message2;
        }
        MessageError(message);
        NumArchiveErrors++;
    }
    _currentArchivePath = name;
    _needWriteArchivePath = true;
    return S_OK;
}

HRESULT CExtractCallbackImp::ThereAreNoFiles() {
    return S_OK;
}

HRESULT CExtractCallbackImp::ExtractResult(HRESULT result) {
    if (result == S_OK)
        return result;
    NumArchiveErrors++;
    if (result == E_ABORT || result == ERROR_DISK_FULL)
        return result;
    MessageError(_currentFilePath);
    MessageError(NError::MyFormatMessageW(result));
    return S_OK;
}

#ifndef _NO_CRYPTO

HRESULT CExtractCallbackImp::SetPassword(const UString &password) {
    PasswordIsDefined = true;
    Password = password;
    return S_OK;
}

STDMETHODIMP CExtractCallbackImp::CryptoGetTextPassword(BSTR *password) {

    PasswordWasAsked = true;
    if (!PasswordIsDefined) {
//    CPasswordDialog dialog;
//    ProgressDialog->WaitCreating();
//    if (dialog.Create(*ProgressDialog) == IDCANCEL)
//      return E_ABORT;
//    Password = dialog.Password;
        auto pass = (jstring) enviro.env->CallObjectMethod(enviro.obj, cryptoGetTextPassword,NULL);
        if (pass == nullptr)
            return E_ABORT;
        char outbuf[255];
        memset(&outbuf[0], 0, sizeof(outbuf));
        int len = enviro.env->GetStringLength(pass);
        enviro.env->GetStringUTFRegion(pass, 0, len, outbuf);
        LOGI("Entered password is: %s \n", outbuf);
        Password = GetUnicodeString(outbuf);
        PasswordIsDefined = true;
    }

    return StringToBstr(Password, password);
}

#endif

// IExtractCallBack3
STDMETHODIMP CExtractCallbackImp::AskWrite(
        const wchar_t *srcPath, Int32 srcIsFolder,
        const FILETIME *srcTime, const UInt64 *srcSize,
        const wchar_t *destPath,
        BSTR *destPathResult,
        Int32 *writeAnswer) {
    UString destPathResultTemp = destPath;

    // RINOK(StringToBstr(destPath, destPathResult));

    *destPathResult = 0;
    *writeAnswer = BoolToInt(false);

    UString destPathSpec = destPath;
    UString destPathSys = destPathSpec;
    bool srcIsFolderSpec = IntToBool(srcIsFolder);
    CFileInfoW destFileInfo;
    if (destFileInfo.Find(destPathSys)) {
        if (srcIsFolderSpec) {
            if (!destFileInfo.IsDir()) {
                UString message = UString(L"can not replace file \'")
                                  + destPathSpec +
                                  UString(L"\' with folder with same name");
                RINOK(MessageError(message));
                return E_ABORT;
            }
            *writeAnswer = BoolToInt(false);
            return S_OK;
        }
        if (destFileInfo.IsDir()) {
            UString message = UString(L"can not replace folder \'")
                              + destPathSpec +
                              UString(L"\' with file with same name");
            RINOK(MessageError(message));
            return E_FAIL;
        }

        switch (OverwriteMode) {
            case NExtract::NOverwriteMode::kSkipExisting:
                return S_OK;
            case NExtract::NOverwriteMode::kAskBefore: {
                Int32 overwiteResult;
                RINOK(AskOverwrite(
                        destPathSpec,
                        &destFileInfo.MTime, &destFileInfo.Size,
                        srcPath,
                        srcTime, srcSize,
                        &overwiteResult));
                switch (overwiteResult) {
                    case NOverwriteAnswer::kCancel:
                        return E_ABORT;
                    case NOverwriteAnswer::kNo:
                        return S_OK;
                    case NOverwriteAnswer::kNoToAll:
                        OverwriteMode = NExtract::NOverwriteMode::kSkipExisting;
                        return S_OK;
                    case NOverwriteAnswer::kYesToAll:
                        OverwriteMode = NExtract::NOverwriteMode::kWithoutPrompt;
                        break;
                    case NOverwriteAnswer::kYes:
                        break;
                    case NOverwriteAnswer::kAutoRename:
                        OverwriteMode = NExtract::NOverwriteMode::kAutoRename;
                        break;
                    default:
                        return E_FAIL;
                }
            }
        }
        if (OverwriteMode == NExtract::NOverwriteMode::kAutoRename) {
            if (!AutoRenamePath(destPathSys)) {
                UString message = UString(L"can not create name of file ")
                                  + destPathSys;
                RINOK(MessageError(message));
                return E_ABORT;
            }
            destPathResultTemp = destPathSys;
        } else if (!NFile::NDirectory::DeleteFileAlways(destPathSys)) {
            UString message = UString(L"can not delete output file ")
                              + destPathSys;
            RINOK(MessageError(message));
            return E_ABORT;
        }
    }
    *writeAnswer = BoolToInt(true);
    return StringToBstr(destPathResultTemp, destPathResult);
}
