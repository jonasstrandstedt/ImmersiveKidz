<!--
* @brief    Model that creates the table in the database. Runs everytime you visit the site and installs if the images table dont exist.
*
* @details  drop_tables(), drop all tables in the database.
*			create_images_table(), creates the table in the database and inserts example values. Uses images-model.php and create_table_helper.php
*
* @author   Emil Lindström, emili250@student.liu.se
* @author   Viktor Fröberg, vikfr292@student.liu.se
* @date     November 9, 2012
* @version  1.1 (added forms for date and group)
*    
-->
<?php //echo $error;
date_default_timezone_set('Europe/Stockholm'); // The timezone for Sweden.
?>
<div id="sub">
<?php //echo $error;?>
<div class='imgform'>
<?php echo form_open_multipart('index.php/site/create/upload');?>

<input type="file" name="userfile[]" size="20" multiple=""/>


<label for="group">
	Gruppnamn

<input type="text" name="group" size="20"/>
</label>
<label for="date">
	Datum

<input type="text" name="date" value = <?php print "\"". date('Y-m-d') ."\" "; ?> size="20"/> <!-- Gets todays date -->
</label>
<br /><br />

<input type="submit" name="submit" value="Ladda upp bilderna" />

</form>
</div>
<?php echo anchor('index.php/site/create/info', 'Gå vidare');?>
</div>
