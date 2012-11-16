<?php

		echo "<div id='sub'>".form_open('index.php/site/create/download')
		."<input type='hidden' name='date' value='".$date."' />
		<input type='hidden' name='group' value='".$group."' />
		<div id='button'><input class='styledbutton' type='submit' value='Ladda ner bilderna' name='download'></div></form></div>";