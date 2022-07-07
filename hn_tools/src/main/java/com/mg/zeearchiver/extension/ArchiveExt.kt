package com.mg.zeearchiver.extension

import com.mg.zeearchiver.Archive
import com.mg.zeearchiver.data.ArchiveItemsList


// input file path
fun String.getListFileInZip(): List<ArchiveItemsList.ArchiveItem> {
    return try {
        Archive().getArchiveItemsList(this)
    } catch (e: Exception) {
        emptyList()
    }
}