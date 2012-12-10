<?php
/*
* @brief    The page where you view and edit billboard and related information
*
* @details  
*
* @author   Emil Lindström, emili250@student.liu.se
* @date     December 7, 2012
* @version  1.0
*/
echo "<div id='sub'>". form_open_multipart('index.php/site/add_object_information/');
	$column = 0;
	echo "<div class='form'><div class='row'>
		<input type='hidden' name='world_id' value='".$world_id."' />";
	foreach ($billboards as $row)
	{ 

	//<img src='".base_url()."styles/images/rotateplus.png' alt=''/>
		echo "<div id='imgform".$column."' class='imgform'>
		<div class='image'><img src='../../../".$outImages[$column]."' alt='Image' width='90' /> </div>
		<div class='button'>
		<button class='styledDeleteButton' type='submit' name='delete' value='".$column."' >X</button>
		<button class='styledRotatePlus' type='submit' name='rotateplus' value='".$column."' >ROTERA +90&#176;</button>
		<button class='styledRotateMinus' type='submit' name='rotateminus' value='".$column."' >ROTERA -90&#176;</button>
		</div>
		<label>Antal:</label>
		<input type='text' name='quantity".$column."' value='".htmlentities($row -> mult_count)."' />
    	<label>Typ:</label>
		<input type='text' name='type".$column."' value='' />
		</div>";
 
 		$column++;

 		if($column%3 == 0){
 			echo "</div><div class='row'>";
 		}
	}
echo "</div></div>";
?>
<div id="buttoninfo">
	<input class="styledbutton" type="submit" value="Uppdatera bilder" name="update">
	<input class="styledbutton" type="submit" value="Gå vidare" name="next">
</div>
</form>
</div>		