<?php if ( ! defined('BASEPATH')) exit('No direct script access allowed'); 

include "phmagick.php";
class ProcessImage {

    public function readIms($folder){
        $dir = opendir($folder); // Use 'opendir(".")' if the PHP file is in the same folder as your images. Or set a relative path 'opendir("../path/to/folder")'.
        $pic_types = array("jpg", "jpeg", "gif", "png");
        $images = array();
         
        //Get all images in the directory folder
        while ($file = readdir ($dir)) {
          if(in_array(substr(strtolower($file), strrpos($file,".") + 1),$pic_types))
            {
                array_push($images,$folder."/".$file);
            }
        }
        closedir($dir);
        return $images;
    }

    public function findDrawing($images, $folder)
    {
        //If no mask folder exists, create it.
        if(!is_dir($folder. "/mask")){
            mkdir($folder. "/mask", 0777);
        }

        //If no out folder exists, create it.
        if(!is_dir($folder. "/out")){
            mkdir($folder. "/out", 0777);
        }

        //Go through each image in the images array
        for($i=0; $i < sizeof($images); $i++){
            //create mask, save to folder "mask".
            $namelength = strpos($images[$i], ".") - strrpos($images[$i], "/") -1;
            $mask = $folder. "/mask/". substr($images[$i], strrpos($images[$i], "/") + 1, $namelength) ."mask.png";
            $phMagick = new phMagick($images[$i], $mask);
            $amount = "10%";
            $phMagick->threshold($amount);
            $phMagick = new phMagick($mask, $mask);
            $size = 6;
            //$phMagick->open($size);
            $phMagick->close($size, "Disk");

            //create out image, save to folder "out".
            $out = $folder. "/out/". substr($images[$i], strrpos($images[$i], "/") + 1, $namelength) ."out.png";
            $phMagick = new phMagick($mask, $out);
            $phMagick->mask($images[$i]); //pass original image


        }
    }
}

/* End of file Someclass.php */