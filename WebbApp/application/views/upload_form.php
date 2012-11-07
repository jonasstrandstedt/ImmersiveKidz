<h1>Ladda upp bilder här </h1>
<?php //echo $error;?>

<?php echo form_open_multipart('index.php/site/create/upload');?>

<input type="file" name="userfile[]" size="20" multiple=""/>

<br /><br />

<input type="submit" value="upload" />

</form>
<?php echo anchor('index.php/site/create/info', 'Gå vidare');?>