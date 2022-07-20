package hn.tools.zip.extension

import hn.tools.zip.Archive
import hn.tools.zip.ArchiveData


// input file path
// format pass  is "-p123456"
fun String.getListFileInZip(password : String = "123456"): ArchiveData {
    return try {
        Archive().getArchiveItemsList(this, "-p$password")
    } catch (e: Exception) {
        throw RuntimeException(e.message)
    }
}