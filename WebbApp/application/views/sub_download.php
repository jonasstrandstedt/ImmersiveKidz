<div id="sub">		
		<h1>Ladda ner dina friläggda bilder</h1>

<?php //echo $error;?>

<?php echo form_open_multipart('index.php/site/create/download');?>

<input type="file" name="userfile[]" size="20" multiple=""/>

<br /><br />

<input type="submit" value="Ladda ned bilderna" />

</form>
</div>