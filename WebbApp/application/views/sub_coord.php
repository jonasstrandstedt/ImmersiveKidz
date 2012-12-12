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
$axisUrl = base_url(). "styles/images/axis.png";
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
		"y" => $canvas_height - ($z_coord - $plane_pos_z)*($canvas_height/$plane_height)
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
				echo "<input type='hidden' name='image".$i."_y' value='0.0'>";
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
        width: <?php echo 2*$canvas_width;?>,
        height: <?php echo $canvas_height;?>,
      });
	var layer = new Kinetic.Layer({
		width: <?php echo $canvas_width;?>,
		height: <?php echo $canvas_height;?>,
	});
	var info = new Kinetic.Layer({
		width: <?php echo $canvas_width;?>,
		height: <?php echo $canvas_height/2;?>,
		offset: (<?php echo $canvas_width;?>, 0)
	});
	var imageInfo = new Kinetic.Layer({
		width: <?php echo $canvas_width;?>,
		height: <?php echo $canvas_height/2;?>,
		offset: (<?php echo $canvas_width;?>, 0)
	});
	var circleList = [];
	

	var circlesCoord = [<?php
		$counter = 0;
	 foreach ($images_coord as $xy_coord) {
		echo "{x: ".$xy_coord["x"].", y: ".$xy_coord["y"].", radius: 6, fill: 'red' , draggable: true, id: ".$counter."},";
			$counter++;
			} 

			?>]; // SKapa en javascript array över alla coordinater, radius:6 är radien på cirkeln, id: är cirkelns id.
		
	var illustrationsJS = [<?php
		$counter = 0;
	 foreach ($illustrations as $illustration) {
		echo"['".$illustration -> artist."','".$illustration -> imgname."']," ;
			$counter++;
			} 

			?>];



	var circleList; // Array för alla cirklar
	


	
var planeTexture = new Image();
var axisTexture = new Image();


// then to call it, you would use this
var imageSrcs = [<?php 
echo "'".base_url().$billboards[0] -> imgurl. "'";
for($i = 1; $i < sizeof($billboards); $i++){
echo ",'".base_url().$billboards[$i] -> imgurl."'";
}
?>];

	var images = [];

    for (var i = 0; i < imageSrcs.length; i++) {

	        var tempImg = new Image();

	        tempImg.src = imageSrcs[i];
	        images.push(tempImg);

		}

	planeTexture.src = "<?php echo $textureUrl; ?>";
	axisTexture.src = "<?php echo $axisUrl; ?>";

	   onload = function() {
        var bg = new Kinetic.Image({
          x: 0,
          y: 0,
          image: planeTexture
        });
        var axis = new Kinetic.Image({
          x: 0,
          y: 0,
          image: axisTexture
        });

        layer.add(bg);
        layer.add(axis);
        drawCircles(circlesCoord);
        drawRectangel();
        stage.add(info);
        stage.add(imageInfo);
        stage.add(layer);
        
    }

	function drawCircles(circles){
		for(var i = 0; i < circles.length; i++){
			
			circleList[i] = new Kinetic.Circle(circles[i]);
			circleList[i].setAttrs({
				dragBoundFunc: function(pos) {
            	 var newY = pos.y > <?php echo $canvas_height - 6;?> ? <?php echo $canvas_height - 6;?> : pos.y;
            	 var newX = pos.x > <?php echo $canvas_width - 6;?> ? <?php echo $canvas_width - 6;?> : pos.x;
            	return {
             	 x: newX,
             	 y: newY
            };
          }
			})

			circleList[i].on("mouseover", function(){
               document.body.style.cursor = "pointer";
            });

            circleList[i].on("mouseout", function(){
                document.body.style.cursor = "default";
            });
            circleList[i].on("mousedown", function(){
            	/// FUNGERAR INTE!!!!!!!!
            	//var url = stage.get('#imageFrame')[0];
            	//url.image = images[i];
            	console.log(circleList[0].getPosition().x);
            	console.log(circleList[0].getPosition().y);
            	<?php echo "circleList[0].getPosition().x *" . $plane_width/$canvas_width." + " .$plane_pos_x.";";?>

            	var img = imageInfo.get("#imageFrame")[0];
            	var imgName = imageInfo.get("#image_name")[0];
            	var x_temp = imageInfo.get("#image_x")[0];
            	var z_temp = imageInfo.get("#image_z")[0];

		 		img.setAttrs({
		 			x: <?php echo $canvas_width + 30;?>,
		 				y: 120,
		 				width: 100,
		 				height: 100,
		 				image: images[this.attrs.id],
		 		});
		 		imgName.setAttrs({
		 			text: illustrationsJS[this.attrs.id][0] + 's ' + illustrationsJS[this.attrs.id][1],
		 		})
		 		var x = <?php echo "circleList[this.attrs.id].getPosition().x *" . $plane_width/$canvas_width." + " .$plane_pos_x.";";?>
		 		
		 		x_temp.setAttrs({
		 			text: 'x: ' + x.toFixed(1), 
		 		});
		 		var z = <?php echo $plane_height." - circleList[this.attrs.id].getPosition().y *".$plane_height/$canvas_height." + ".$plane_pos_z.";";?>
		 		z_temp.setAttrs({
		 			text: 'z: ' + z.toFixed(1), 
		 		});
		 		console.log(this.attrs.id);
		 		imageInfo.draw();
            });
		

			layer.add(circleList[i]);
		}

	}
	function drawRectangel(){
		var rectWorld = new Kinetic.Rect({
        x: <?php echo $canvas_width;?>,
        y: 0,
        width: <?php echo $canvas_width;?>,
        height: 100,
      });
		var line = new Kinetic.Rect({
			x: <?php echo $canvas_width;?>,
			y: 99,
			width: <?php echo $canvas_width;?>,
			height: 2,
			fill: 'gray'
		})
		var rectIllustration = new Kinetic.Rect({
        x: <?php echo $canvas_width;?>,
        y: 100,
        width: <?php echo $canvas_width;?>,
        height: <?php echo $canvas_width - 100;?>
      });
		info.add(rectWorld);
		

		 var world = new Kinetic.Text({
		 	x: <?php echo $canvas_width;?>,
		 	y: 10,
		 	width: <?php echo $canvas_width;?>,
		 	fontFamily:'Arial',
		 	align: 'center',
		 	text: '<?php echo $world -> name;?>',
		 	textFill: '#fff',
		 	fontSize: 20


		 });
		 var groupDate = new Kinetic.Text({
		 	x: <?php echo $canvas_width;?>,
		 	y: 40,
		 	width: <?php echo $canvas_width;?>,
		 	fontFamily:'Arial',
		 	align: 'center',
		 	text: '<?php echo $group -> name ." - ". $group -> date;?>',
		 	textFill: '#fff',
		 	fontSize: 14
		 })
		 var mapSize = new Kinetic.Text({
		 	x: <?php echo $canvas_width;?>,
		 	y: 65,
		 	width: <?php echo $canvas_width;?>,
		 	fontFamily:'Arial',
		 	align: 'center',
		 	text: 'Storlek på världen: <?php echo"(". $plane_width  ." , ". $plane_height . ")";?>',
		 	textFill: '#fff',
		 	fontSize: 12
		 })

	       var image = new Kinetic.Image({
					x: <?php echo $canvas_width + 30;?>,
					y: 120,
					width: 100,
					height: 100,
					image: images[0],
					id: 'imageFrame'
			});
	       var imageName = new Kinetic.Text({
		 	x: <?php echo $canvas_width + 90;?>,
		 	y: 120,
		 	width: <?php echo $canvas_width - 160;?>,
		 	fontFamily:'Arial',
		 	align: 'center',
		 	text: illustrationsJS[0][0] + 's ' + illustrationsJS[0][1],
		 	textFill: '#fff',
		 	fontSize: 16,
		 	id: 'image_name'
		 })
	       
	       
	       var x = <?php echo "circleList[0].getPosition().x *" . $plane_width/$canvas_width." + " .$plane_pos_x.";";?>
	       var x_text = new Kinetic.Text({
		 	x: <?php echo $canvas_width + 160;?>,
		 	y: 150,
		 	width: <?php echo $canvas_width - 160;?>,
		 	fontFamily:'Arial',
		 	align: 'left',
		 	text: 'x: ' + x.toFixed(1),
		 	textFill: '#fff',
		 	fontSize: 14,
		 	id: 'image_x'
		 })
	       var z = <?php echo $plane_height." - circleList[0].getPosition().y *".$plane_height/$canvas_height." + ".$plane_pos_z.";";?>
	       var z_text = new Kinetic.Text({
		 	x: <?php echo $canvas_width + 160;?>,
		 	y: 180,
		 	width: <?php echo $canvas_width - 160;?>,
		 	fontFamily:'Arial',
		 	align: 'left',
		 	text: 'z: ' + z.toFixed(1),
		 	textFill: '#fff',
		 	fontSize: 14,
		 	id: 'image_z'
		 })

		 info.add(world);
		 info.add(groupDate);
		 info.add(mapSize);
		 imageInfo.add(rectIllustration);
		 imageInfo.add(line);
		 imageInfo.add(image);
		 imageInfo.add(imageName);
		 imageInfo.add(x_text);
		 imageInfo.add(z_text);
	}
	function setValues(){
		<?php for($i = 0; $i < sizeof($billboards); $i++){

				echo "document.coordform.image".$i."_x.value = circleList[".$i."].getPosition().x *" . $plane_width/$canvas_width." + " .$plane_pos_x.";";
				
				echo "document.coordform.image".$i."_z.value =".$plane_height." - circleList[".$i."].getPosition().y *".$plane_height/$canvas_height." + ".$plane_pos_z.";";
			
			}
			?>

		
	}

  </script>