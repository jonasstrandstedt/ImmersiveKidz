<?php

/* @brief    Download
*
* @details  
*
* @author   Emil Lindström, emili250@student.liu.se
* @date     2012-11-08
* @version  
*/
		$path = "index.php/site/download_info/".$date."/".$group;

		echo "<div id='sub'><div class='downloadform'>".form_open($path)."<div id='button'><input class='styledbutton' type='submit' value='Ladda Ner' name='download'></form></div></div></div>";