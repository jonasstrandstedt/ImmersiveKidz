<h1>Ladda upp bilder här </h1>
<?php //echo $error;
date_default_timezone_set('Europe/Stockholm');
?>

<?php echo form_open_multipart('index.php/site/create/upload');?>

<input type="file" name="userfile[]" size="20" multiple=""/>


<label for="group">
	Gruppnamn
</label>
<input type="text" name="group" size="20"/>

<label for="date">
	Datum
</label>
<input type="text" name="date" value = <?php print "\"". date('Y-m-d') ."\" "; ?> size="20"/>

<br /><br />

<input type="submit" value="Ladda upp bilderna" />

</form>
<?php echo anchor('index.php/site/create/info', 'Gå vidare');?>