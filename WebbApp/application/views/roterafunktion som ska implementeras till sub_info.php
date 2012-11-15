<!-- 
Läser in bildfilen 'test.jpg' från samma mapp
-->

<html>
<button onclick="rotate('-90')"> <- Rotera 90 grader</button>
<canvas id="canvas"></canvas>
<script>
//var canvas = document.getElementById('pic1');
var can = document.getElementById('canvas');
var ctx = can.getContext('2d');

var img = new Image();
img.onload = function(){
    can.width = img.width; 	
    can.height = img.height;
    ctx.drawImage(img, 0, 0, img.width, img.height);
}
img.src = 'test.jpg';

function rotate(angle){
	var angle = angle;
	ctx.clearRect(0, 0, can.width, can.height);
	ctx.save();
	
    ctx.translate(img.width/2, img.height/2);
    ctx.rotate(angle*Math.PI/180 );
	ctx.translate(-(img.width/2), -(img.height/2));
    ctx.drawImage(img, 0, 0, img.width, img.height);
};






</script>
<button onclick="rotate('90')"> Rotera 90 grader -></button>
</html>