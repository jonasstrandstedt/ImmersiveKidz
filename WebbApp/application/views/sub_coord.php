<?php

/* @brief    create coordinates
*
* @details  
*
* @author   Viktor Fröberg, vikfr292@student.liu.se
* @date     2012-12-10
* @version  2.0
*/

$textureUrl =  base_url() . $plane -> textureurl;
$plane_pos_x = $plane -> pos_x;
$plane_pos_z = $plane -> pos_z;
$plane_width = $plane -> width;
$plane_height = $plane -> height;


// CANVAS VARIABLER
$canvas_width = 500;
$canvas_height = 500;
// TRANSFORMFUNKTIONER
	
	//transform_x_to_canvas
	//$x_canvas = ($x - $plane_pos_x)*($canvas_width/$plane_width);
	
	//transform_y_to_canvas
	//$y_canvas = $canvas_height - ($y - $plane_pos_z)*($canvas_height/$plane_height);

	//transform_x_to_opengl
	//$x_opengl = $x*($plane_width/$canvas_width) + $plane_pos_x;
	
	//transform_y_to_opengl
	//$y_opengl = $plane_height - $y*($plane_height/$canvas_height) + $plane_pos_z;


$images_coord = array();

for ($i=0; $i < sizeof($billboards); $i++){ // Slumpa fram koordinater för alla bilder. 
	 // lägg till en if som kollar om koordinaterna redan är bestämda i databasen. och om dom ligger utanför width och height.
	 if(($illustrations[$i] -> pos_x != NULL & $illustrations[$i] -> pos_z != NULL) ||  ($illustrations[$i] -> pos_x != '' & $illustrations[$i] -> pos_z != '')){
	 	$x_coord = $illustrations[$i] -> pos_x;
	 	$z_coord = $illustrations[$i] -> pos_z;
	 }else{
	 	$x_coord = mt_rand(0, $plane_width*10)/10 + $plane_pos_x;
	 	$z_coord = mt_rand(0, $plane_height*10)/10 + $plane_pos_z;
	}
	//$random_color = 
	 // Spara gör om koordinaterna till samma koordinatsystem som canvasen, sen spara dom i en array.
	$coord = array(
		"x" => ($x_coord - $plane_pos_x)*($canvas_width/$plane_width),
		"y" => $canvas_height - ($z_coord - $plane_pos_z)*($canvas_height/$plane_height),
		"imgurl" => $billboards[$i] -> imgurl 
		);
	$images_coord[$i] = $coord;
	

	
}

?>
<script src="<?php echo base_url(); ?>js/kinetic.js" ></script>
<div id='sub'>
	<div id='plane'>
	</div>
	
	<?php echo form_open('index.php/site/add_coordinates/', 'name="coordform"'); 
			echo "<input type='hidden' name='group_id' value='".$group -> id."'>";
			for($i = 0; $i < sizeof($billboards); $i++){
				echo "<input type='hidden' name='image".$i."_x' value=''>";
				echo "<input type='hidden' name='image".$i."_z' value=''>";
			}
			?>
			<div id="buttoninfo">
			<input class="styledbutton" type="submit" value="Spara Koordinater" onclick="setValues();" name="submitcoord">
		</div>
	</form>
	</div>
<script >
	
	var stage = new Kinetic.Stage({
        container: 'plane',
        width: <?php echo $canvas_width;?>,
        height: <?php echo $canvas_height;?>,
      });
	var layer = new Kinetic.Layer();
	var circleList = [];
	

	var circlesCoord = [<?php
		$counter = 0;
	 foreach ($images_coord as $xy_coord) {
		echo "{x: ".$xy_coord["x"].", y: ".$xy_coord["y"].", radius: 6, fill: 'red' , draggable: true, id: '".$counter."'},";
			$counter++;
			} 

			?>]; // SKapa en javascript array över alla coordinater, radius:6 är radien på cirkeln, id: är cirkelns id.
	
	var circleList; // Array för alla cirklar
	
	

	
	var planeTexture = new Image();
	planeTexture.src = "<?php echo $textureUrl; ?>";

	   planeTexture.onload = function() {
        var bg = new Kinetic.Image({
          x: 0,
          y: 0,
          image: planeTexture
        });

        layer.add(bg);
        drawCircles(circlesCoord);
        stage.add(layer);
    }

	function drawCircles(circles){
		for(var i = 0; i < circles.length; i++){
			
			circleList[i] = new Kinetic.Circle(circles[i]);

			circleList[i].on("mouseover", function(){
               document.body.style.cursor = "pointer";
             //  console.log(circleList[i].getPosition().x);
            });

            circleList[i].on("mouseout", function(){
                document.body.style.cursor = "default";
            });

			layer.add(circleList[i]);
		}

	}
	function setValues(){
		<?php for($i = 0; $i < sizeof($billboards); $i++){

				echo "document.coordform.image".$i."_x.value = circleList[".$i."].getPosition().x *" . $plane_width/$canvas_width." + " .$plane_pos_x.";";
				
				echo "document.coordform.image".$i."_z.value =".$plane_height." - circleList[".$i."].getPosition().y *".$plane_height/$canvas_height." + ".$plane_pos_z.";";
			
			}
			?>

		
	}

  </script>