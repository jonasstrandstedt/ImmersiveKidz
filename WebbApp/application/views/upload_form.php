<?php
/*
* @brief    Model that creates the table in the database. Runs everytime you visit the site and installs if the images table dont exist.
*
* @details  drop_tables(), drop all tables in the database.
*			create_images_table(), creates the table in the database and inserts example values. Uses images-model.php and create_table_helper.php
*
* @author   Emil Lindström, emili250@student.liu.se
* @author   Viktor Fröberg, vikfr292@student.liu.se
* @author 	(Belinda Bernfort, belbe886@student.liu.se)
* @date     November 9, 2012
* @version  1.1 (added forms for date and group)
*/

date_default_timezone_set('Europe/Stockholm'); // The timezone for Sweden.
?>
<div id="sub">
	<div class='uploadform'>
		<?php echo form_open_multipart('index.php/site/upload');?>
			<input class="upload" type="file" name="userfile[]" size="20" multiple=""/>
			
			<div id="group">
				<label for="group">
					Gruppnamn
				</label>
				<input type="text" name="group" size="20"/>
			</div>
			
			<div id="date">
				<label for="date">
					Datum
				</label>
				<input type="text" name="date" value = <?php print "\"". date('Y-m-d') ."\" "; ?> size="20"/> <!-- Gets todays date -->
			</div>
			<div id="world">
				<label for"world">
					Värld
				</label>
				<select name="world">
					<?php
					foreach ($worlds as $world)
					{ 
						echo "<option value='".$world-> id."'>".htmlentities($world-> name)."</option>";
					}
					?>
				</select>
			</div>

			<div id="button">
				<p>Max filstorlek 2MB.</p>
				<input class="styledbutton" type="submit" name="submit" value="Ladda upp bilderna" />
			</div>
		</form>
	</div>
</div>