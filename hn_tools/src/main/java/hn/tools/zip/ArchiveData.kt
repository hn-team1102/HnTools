package hn.tools.zip

import hn.tools.zip.data.ArchiveItemsList

data class ArchiveData(
	val list : List<ArchiveItemsList.ArchiveItem>,
	val errorPass : Boolean
)