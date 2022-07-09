package com.mg.zeearchiver

import com.mg.zeearchiver.data.ArchiveItemsList

data class ArchiveData(
	val list : List<ArchiveItemsList.ArchiveItem>,
	val errorPass : Boolean
)