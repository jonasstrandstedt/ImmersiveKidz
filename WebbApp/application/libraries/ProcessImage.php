<?php 
/* @brief    Functions to process image.
*
* @details  readIms($folder) - Reads images from a folder.
                In: $folder - Folder to read images from.
                Out: array of images.
            findDrawing($images, $folder) - treshold, close and fill holes in image. Mask original image to find the figure. 
                In: $images - Array of images.
                    $folder - destination folder.
                Out: array of processed images.
*
* @author   Gabriella Ivarsson, gabiv132
* @author   
* @date     2012-11-08
* @version  
*/
if ( ! defined('BASEPATH')) exit('No direct script access allowed'); 

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
    {   $imagesOut = array(); // Array containing
        //If no mask folder exists, create it.
        if(!is_dir($folder. "/mask")){
            mkdir($folder. "/mask", 0777);
        }

        //If no out folder exists, create it.
        if(!is_dir($folder. "/out")){
            mkdir($folder. "/out", 0777);
        }

        //If no out folder exists, create it.
        if(!is_dir($folder. "/int")){
            mkdir($folder. "/int", 0777);
        }

        //Go through each image in the images array
        for($i=0; $i < sizeof($images); $i++){
           $namelength = strpos($images[$i], ".") - strrpos($images[$i], "/") -1;

            echo substr($images[$i], strrpos($images[$i], "/") + 1, $namelength) . "<br/>";
            //------------ Create temporary result to use in intensity calculation --------------------//
            //create mask, save to folder "mask".
            $mask = $folder. "/mask/". substr($images[$i], strrpos($images[$i], "/") + 1, $namelength) ."mask.png";
            $phMagick = new phMagick($images[$i], $mask);
            $amount = "10%";
            $phMagick->threshold($amount);
            
            //$phMagick->open($size);

            /*$phMagick = new phMagick($mask, $mask);
            $phMagick->close("diamond");*/
            
            /*$size = 6;
            $phMagick->close($size, "Disk");*/
            

            //create out image, save to folder "out".
            $out = $folder. "/out/". substr($images[$i], strrpos($images[$i], "/") + 1, $namelength) ."out.png";
            $phMagick = new phMagick($mask, $out);
            $phMagick->mask($images[$i]); //pass original image

            //------------ Calculate intensity value for each image --------------------//
            $int = $folder. "/int/" . substr($images[$i], strrpos($images[$i], "/") + 1, $namelength) ."intensity.png";
            $image = new phMagick($out, $int);
            $intensityValue = $image->getAverageIntensity();
            echo "intensityValue " . $intensityValue . "<br/>";
            $intensityPercent = $intensityValue / 255;
            echo "intensityPercent " . $intensityPercent . "<br/>";


            //------------ Create result using value from the intensity calculation as thresh --------------------//
            //create mask, save to folder "mask".
            $phMagick = new phMagick($images[$i], $mask);
            $amount = 10*$intensityPercent . "%";
            echo "thresh amount: " . $amount . "<br/>";
            $phMagick->threshold($amount);

            $phMagick = new phMagick($mask, $mask);
            $drawSettings = "color 0,0 floodfill";
            $phMagick->fillHoles($drawSettings);

            //create out image, save to folder "out".
            array_push($imagesOut,$out);
            $phMagick = new phMagick($mask, $out);
            $phMagick->mask($images[$i]); //pass original image
            echo "<br/>";

        }
        return $imagesOut;
    }
}

/* End of file Someclass.php */