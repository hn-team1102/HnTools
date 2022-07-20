package vn.hn.hn_tools

import android.os.Bundle
import android.util.Log
import com.google.android.material.appbar.CollapsingToolbarLayout
import com.google.android.material.floatingactionbutton.FloatingActionButton
import com.google.android.material.snackbar.Snackbar
import androidx.appcompat.app.AppCompatActivity
import android.view.Menu
import android.view.MenuItem
import hn.tools.zip.Archive
import hn.tools.zip.extension.getListFileInZip
import vn.hn.hn_tools.databinding.ActivityScrollingBinding
import java.io.File

class ScrollingActivity : AppCompatActivity() {

	private lateinit var binding: ActivityScrollingBinding

	override fun onCreate(savedInstanceState: Bundle?) {
		super.onCreate(savedInstanceState)

		binding = ActivityScrollingBinding.inflate(layoutInflater)
		setContentView(binding.root)
		val filePath = "/storage/emulated/0/ZipExtractor/Compressed/aaa4.zip"
		val file = File(filePath).absolutePath
		val archiveData = file.getListFileInZip()
		archiveData.list.forEach {
			Log.e("AAA => ", it.itemPath)
		}

		setSupportActionBar(findViewById(R.id.toolbar))
		binding.toolbarLayout.title = title
		binding.fab.setOnClickListener { view ->
			Snackbar.make(view, "Replace with your own action", Snackbar.LENGTH_LONG)
				.setAction("Action", null).show()
		}
	}

	override fun onCreateOptionsMenu(menu: Menu): Boolean {
		// Inflate the menu; this adds items to the action bar if it is present.
		menuInflater.inflate(R.menu.menu_scrolling, menu)
		return true
	}

	override fun onOptionsItemSelected(item: MenuItem): Boolean {
		// Handle action bar item clicks here. The action bar will
		// automatically handle clicks on the Home/Up button, so long
		// as you specify a parent activity in AndroidManifest.xml.

		return when (item.itemId) {
			R.id.action_settings -> true
			else -> super.onOptionsItemSelected(item)
		}
	}
}