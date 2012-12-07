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
* @author   Christoffer Hermansson, chrhe155
* @date     2012-11-08
* @version  
*/
if ( ! defined('BASEPATH')) exit('No direct script access allowed'); 

include "phmagick.php";
class ProcessImage {

    //Only used for testing the image processing
    public function readIms($folder)
    {
        //Use 'opendir(".")' if the PHP file is in the same folder as your images. Or set a relative path 'opendir("../path/to/folder")'.
        $dir = opendir($folder); 
        $pic_types = array("jpg", "jpeg", "gif", "png");
        $images = array();
         
        //Get all images in the directory folder
        while ($file = readdir ($dir)) 
        {
          if(in_array(substr(strtolower($file), strrpos($file,".") + 1),$pic_types))
            {
                array_push($images,$folder."/".$file);
            }
        }
        closedir($dir);
        return $images;
    }

    public function findDrawing($images, $folder, $threshvalue = '')
    {   
        //Array containing the modified images
        $imagesOut = array();

        //If no mask folder exists, create it.
        if(!is_dir($folder. "/mask")){
            mkdir($folder. "/mask", 0777);
        }

        //If no out folder exists, create it.
        if(!is_dir($folder. "/out")){
            mkdir($folder. "/out", 0777);
        }

        //If no int folder exists, create it.
        if(!is_dir($folder. "/int")){
            mkdir($folder. "/int", 0777);
        }

        //Go through each image in the images array
        for($i=0; $i < sizeof($images); $i++)
        {
           $namelength = strpos($images[$i], ".") - strrpos($images[$i], "/") -1;

            //------------ Create temporary result to use in intensity calculation --------------------//
            //create mask, save to folder "mask".
            $mask = $folder. "/mask/". substr($images[$i], strrpos($images[$i], "/") + 1, $namelength) ."mask.png";
            $phMagick = new phMagick($images[$i], $mask);            
            $amount = "10%";
            $phMagick->threshold($amount);

            //create out image, save to folder "out".
            $out = $folder. "/out/". substr($images[$i], strrpos($images[$i], "/") + 1, $namelength) ."out.png";
            
            $phMagick = new phMagick($mask, $out);
            $phMagick->mask($images[$i]); //pass original image

            //------------ Calculate intensity value for each image --------------------//
            $int = $folder. "/int/" . substr($images[$i], strrpos($images[$i], "/") + 1, $namelength) ."intensity.png";
            $image = new phMagick($out, $int);
            $intensityValue = $image->getAverageIntensity();
            $intensityPercent = $intensityValue / 255;
            
            //------------ Create result using value from the intensity calculation as thresh --------------------//
            //create mask, save to folder "mask".
            $phMagick = new phMagick($images[$i], $mask);
            $amount = 10*$intensityPercent-0.5;
            if($intensityPercent <= 0.15){
                $amount = 2.7;
            }
            else if($intensityPercent <= 0.16){
                $amount = 2.2;
            }
            else if($intensityPercent <= 0.19){
                $amount = 1.7;
            }
            else if($intensityPercent <= 0.24){
                $amount = 1.5;
            }
            else if($intensityPercent <= 0.28){
                $amount = 1.2;
            }
            else if($intensityPercent <= 0.30){
                $amount = 1;
            }
            else if($intensityPercent <= 0.34){
                $amount = 0.8;
            }
            else if($intensityPercent <= 0.36){
                $amount = 0.6;
            }
            else{
                $amount = 0.4;
            }

            if($threshvalue != ''){
                if($threshvalue <5){
                $amount = $threshvalue/6;
                }
                else{
                    $amount = $threshvalue/2;
                }
            }
            
            $amount = $amount . "%";
            $phMagick->threshold($amount);

            //Add white border to avoid errors when filling holes
            $phMagick = new phMagick($mask, $mask);
            $borderSize = "10x10";
            $phMagick->addBorder($borderSize);

            //Start fill at x=0, y=0
            $drawSettings = "color 0,0 floodfill";
            $phMagick->fillHoles($drawSettings);

            //Remove the border to obtain the original image size
            $phMagick->removeBorder($borderSize);
            
            //create out image, save to folder "out".
            array_push($imagesOut,$out);
            $phMagick = new phMagick($mask, $out);
            //pass original image
            $phMagick->mask($images[$i]); 

        }
        return $imagesOut;
    }
}

/* End of file Someclass.php */