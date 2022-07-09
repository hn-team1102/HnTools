package com.mg.zeearchiver.extension

import com.mg.zeearchiver.Archive
import com.mg.zeearchiver.ArchiveData
import com.mg.zeearchiver.data.ArchiveItemsList


// input file path
// format pass  is "-p123456"
fun String.getListFileInZip(password : String = "123456"): ArchiveData {
    return try {
        Archive().getArchiveItemsList(this, "-p$password")
    } catch (e: Exception) {
        throw RuntimeException(e.message)
    }
}