<?php

		echo "<div id='sub'>".form_open('index.php/site/create/download')
		."<input type='hidden' name='date' value='".$date."' />
		<input type='hidden' name='group' value='".$group."' />
		<input type='submit' value='Ladda Ner' name='download'></form></div>";