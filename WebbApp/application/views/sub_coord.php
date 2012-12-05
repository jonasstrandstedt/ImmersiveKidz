<?php

/* @brief    create coordinates
*
* @details  
*
* @author   Viktor Fröberg, vikfr292@student.liu.se
* @date     2012-12-05
* @version  1.0
*/

$url =base_url() ."worlds/".$data[0] -> name ."/" .$data[0] -> plane;

$rand_min_x = $data[0] -> rand_min_x;
$rand_max_x = $data[0] -> rand_max_x;
$rand_min_y = $data[0] -> rand_min_y;
$rand_max_y = $data[0] -> rand_max_y;

$plane_min_x = $data[0] -> plane_min_x;
$plane_max_x = $data[0] -> plane_max_x;
$plane_min_y = $data[0] -> plane_min_y;
$plane_max_y = $data[0] -> plane_max_y;


// TEST
// $rand_min_x = -50;
// $rand_max_x = 50;
// $rand_min_y = -50;
// $rand_max_y = 50;

// $plane_min_x = -100;
// $plane_max_x = 100;
// $plane_min_y = -100;
// $plane_max_y = 100;


	if($rand_min_x < 0){
		$x_min = ($rand_min_x + abs($plane_min_x))*(500/($plane_max_x + abs($plane_min_x)));
		$x_max = ($rand_max_x + abs($plane_min_x))*(500/($plane_max_x + abs($plane_min_x)));

	}else{
		$x_min = $rand_min_x*(500/($plane_max_x));
		$x_max = $rand_max_x*(500/($plane_max_x));
	}

	if($rand_min_y < 0){
		$y_min = ($rand_min_y + abs($plane_min_y))*(500/($plane_max_y + abs($plane_min_y)));
		$y_max = ($rand_max_y + abs($plane_min_y))*(500/($plane_max_y + abs($plane_min_y)));

	}else{
		$y_min = $rand_min_y*(500/($plane_max_y));
		$y_max = $rand_max_y*(500/($plane_max_y));
	}


$images_coord = array();

for ($i=0; $i < 10; $i++) { 
	
	$x_coord = mt_rand($x_min*10, $x_max*10)/10;
	$y_coord = mt_rand($y_min*10, $y_max*10)/10;
	//$random_color = 
	$coord = array(
		"x" => $x_coord,
		"y" => $y_coord,
		);
	$images_coord[$i] = $coord;
	

	
}
//echo print_r($images_coord);

?>
<script src="<?php echo base_url(); ?>js/kinetic.js" ></script>
<!--<canvas id='plane' width='500' height='500'></canvas>-->
<div id='plane'>
</div>

<script >
	
	var stage = new Kinetic.Stage({
        container: 'plane',
        width: 500,
        height: 500
      });
	var layer = new Kinetic.Layer();
	var circleList = [];
	

	var circlesCoord = [<?php
		$counter = 0;
	 foreach ($images_coord as $xy_coord) {
		echo "{x: ".$xy_coord["x"].", y: ".$xy_coord["y"].", radius: 6, fill: 'red' , draggable: true, id: '".$counter."'},";
			$counter++;
			} 

			?>]; // SKapa en javascript array över alla coordinater, r:4 är radien på cirkeln
	
	var circleList; // Array för alla cirklar
	
	

	
	var planeTexture = new Image();
	planeTexture.src = "<?php echo $url; ?>";

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
            });
            circleList[i].on("mouseout", function(){
                document.body.style.cursor = "default";
            });

			layer.add(circleList[i]);
		}

	}

  </script>