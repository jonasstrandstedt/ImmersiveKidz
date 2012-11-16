<?php 
/*
* @brief   	The page where you view and edit pictures and related information
*
* @details  
*
* @author   Viktor Fröberg, vikfr292@student.liu.se
* @author 	Belinda Bernfort, belbe886@student.liu.se
* @date     November 14, 2012 
* @version  1.0
*    
*/

$counter = 0;

	echo "<div id='sub'>". form_open_multipart('index.php/site/create/info');
	$column = 0;
	$idArray = array();
	echo "<div class='form'><div class='row'>
		<input type='hidden' name='date' value='".$images[0] -> date."' />
		<input type='hidden' name='group' value='".$images[0] -> group."' />";
	foreach ($images as $row)
	{ 

	echo "<div class='imgform'>
	<img src='../../../".$row -> imgouturl."' alt='Bildjävel' width='90' /> 
		<label>Konstnär:
		<input type='text' name='artist".$column."' value='".$row -> artist."' />
    	</label>
    	<label>Titel:
		<input type='text' name='imgname".$column."' value='".$row -> imgname."' />
    	</label>
    	<label>Typ:
		<input type='text' name='type".$column."' value='' />
    	</label>
    	<label>Tröskelvärde:
		<input type='range' name='threshold".$column."' min='1' max='10' value='5' />
    	</label>
    	<label>Historia:
	 	<input type='text' name='story".$column."' value='".$row -> story."' />
    	</label>
    	<label>Ljud:
		<input type='file' name='soundurl".$column."' />
		</label></div>";
 			
 		$column++;

 		if($column%3 == 0){
 			echo "</div><div class='row'>";
 		}
	}
echo "</div></div>";
?>
<input type="submit" value="Submit" name="update">
</form>
<?php echo anchor('index.php/site/create/download', 'Gå vidare');?>)

</div>		