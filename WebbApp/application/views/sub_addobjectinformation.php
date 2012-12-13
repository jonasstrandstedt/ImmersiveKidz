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
	$maxSize = 500;
	foreach ($billboards as $row)
	{ 
		$size = 10*($row->size_x/$maxSize);
	//<img src='".base_url()."styles/images/rotateplus.png' alt=''/>
		echo "<div id='imgform".$column."' class='imgform'>
		<div class='image'><img src='../../../".$outImages[$column]."' alt='Image' width='90' /> </div>
		<div class='button'>
		<button class='styledDeleteButton' type='submit' name='delete' value='".$column."' >X</button>
		<button class='styledRotateMinus' type='submit' name='rotateminus' value='".$column."' >ROTERA -90&#176;</button>
		<button class='styledRotatePlus' type='submit' name='rotateplus' value='".$column."' >ROTERA +90&#176;</button>
		<hr size='1px' class='hrbutton1'> <hr size='1px' class='hrbutton2'>
		</div>
		<label>Antal:</label>
		<input type='text' name='quantity".$column."' value='".htmlentities($row -> mult_count)."' />
    	<label>Typ:</label>
		<input type='text' name='type".$column."' value='".htmlentities($row -> type)."' />
		<label>Tröskelvärde:</label>
		<input type='range' name='threshold".$column."' min='1' max='10' value='".$row -> thresh."' /><br/>
		<label>Storlek:</label>
		<select type='text' name='size".$column."' value='".htmlentities($size)."' >   
		<optgroup label='Vald'></optgroup>
		<option value='".htmlentities($size)."'> ".htmlentities($size)." </option>
		<optgroup label='----------'></optgroup>
		<option value='1'>1 </option>
		<option value='2'> 2 </option>
		<option value='3'> 3 </option>
		<option value='4'> 4 </option>
		<option value='5'> 5 </option>
		<option value='6'> 6 </option>
		<option value='7'> 7 </option>
		<option value='8'> 8 </option>
		<option value='9'> 9 </option>
		<option value='10'> 10 </option>
		</select>
		<label>Animation:</label>
		<select type='text' name='animation".$column."'> 
		<optgroup label='Vald'></optgroup>
		<option value='".$animation_billboard[$column][0]->animation_id."'>".$animation_billboard[$column][0]->name."</option>
		<optgroup label='----------'></optgroup>

		";		
		foreach($animations as $animation)
		{
			echo  "
			<option value='".$animation->id."'> ".$animation->name." </option> ";
		}
		echo "</select></div>";
 
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