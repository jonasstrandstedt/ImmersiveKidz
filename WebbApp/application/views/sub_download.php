<div id="sub">	
	<?php echo form_open_multipart('index.php/site/create/download');?>
	<form>
	<input type="file" name="userfile[]" size="20" multiple=""/>

	<br /><br />

	<input type="submit" value="Ladda ned bilderna" />
	</form>
</div>