<div id="sub">		

<h1>Här är alla fina bilder, jippi</h1>
		<p> majs</p>

<?php 

//$this->load->model("Images_model");
$images = $this->Images_model->get_all_images_from_group($group, $date);

//$im1 = '../../uploads/hej1.png';
//$im2 = '../../uploads/hej2.jpg';
//$im3 = '../../uploads/hej3.jpg';
//$im4 = '../../uploads/hu1.gif';
//$im5 = '../../uploads/hu2.jpg';
//$im6 = '../../uploads/hu3.jpg';
//$im7 = '../../uploads/bla1.jpg';
//$im8 = '../../uploads/bla2.jpg';
//$images = $images -> result_array();

//$images = array($im1, $im2, $im3, $im4, $im5, $im6, $im7, $im8);

$counter = 0;
?>

<form action="" method="post">
  		<?php
  		$column = 0;
		$idArray = array();
		echo "<div class='form'><div class='row'>";
  		foreach ($images as $row)
  		{ 
  			array_push($idArray, $row -> id); // sparar ner varje bilds id i en array.

    		echo "<div class='imgform'>
    		<img src='../../../".$row -> imgouturl."' alt='Bildjävel' width='90' /> 
				<label>Konstnär:
				<input type='text' name='artist".$column."' value='".$row -> artist."'>
	        	</label>
	        	<label>Titel:
				<input type='text' name='imgname".$column."' value='".$row -> imgname."'>
		    	</label>
		    	<label>Typ:
	    		<input type='text' name='type".$column."' value=''>
		    	</label>
		    	<label>Tröskelvärde:
	    		<input type='range' name='threshold".$column."' min='1' max='10' value='5'>
		    	</label>
		    	<label>Historia:
	    	 	<input type='text' name='story".$column."' value='".$row -> story."'>
		    	</label>
		    	<label>Ljud:
	    		<input type='file' name='soundurl".$column."'></div>
	    		</label>";
   	 			
   	 		$column++;

   	 		if($column%3 == 0){
   	 			echo "</div>
   	 				  <div class='row'>";
   	 		}
		}
		echo "</div></div>";
	?>
<input type="submit" value="Submit" name="update">
</form>
<?php 
	if(isset($_POST['update'])){
		$counter = 0;
		foreach ($idArray as $id) {
			$artist = $_POST['artist'.$counter];
			$imgname = $_POST['imgname'.$counter];
			// Lägg till för type.
			$story = $_POST['story'.$counter];
			$soundurl = $_POST['soundurl'.$counter];
			$this->Images_model->update_image($id, $artist, $imgname, $soundurl, $story);
			$counter ++;

		}


	}




?>	

<?php echo anchor('index.php/site/create/download', 'Gå vidare');?>)

</div>	
	
	