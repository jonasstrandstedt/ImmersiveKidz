<?php
/* @brief    Functions to process image.
*
* @details  threshold(phmagick $p, $amount) - Thresholds the image.
                In: $p - phmagick object.
                    $amount - threshold value.
                Out: phmagick object.
            close(phmagick $p, $size, $kernel) - Closes the image.
                In: $p - phmagick object.
                    $size - Size of structuring element.
                    $kernel - Type of structuring element. (disk etc.)
                Out: phmagick object.
            mask(phmagick $p, $originalImage) - Masks original image using the mask in $p.
                In: $p - phmagick object.
                    $originalImage - Original input image.
                Out: phmagick object.
            fillHoles(phmagick $p, $drawSettings) - Fills internal holes in the resulting image.
                In: $p - phmagick object.
                    $drawSettings - Coordinates where to start calculating..
                Out: phmagick object.
            getAverageIntensity(phmagick $p) - Calculates the average intensity of the image.
                In: $p - phmagick object.
                Out: Resulting intensity value.
                
* @author   Gabriella Ivarsson, gabiv132
            Christoffer Hermansson, chrhe155
* @author   
* @date     2012-11-18
* @version  
*/
class phMagick_process{
    function threshold(phmagick $p, $amount){
            //Build command to threshold image
            $cmd = $p->getBinary('convert');
            $cmd .= ' "' . $p->getSource().'"'  ;
            $cmd .= ' -negate -threshold ' . $amount ;
            $cmd .= ' "' . $p->getDestination().'"'  ;

            echo "Threshold: " . $cmd . "<br/>";
            $p->execute($cmd);

        return  $p ;
    }

    function close(phmagick $p, $size, $kernel){
            //Build command to close image
            $cmd = $p->getBinary('convert');
            $cmd .= ' "' . $p->getSource().'"'  ;
            $cmd .= ' -morphology Close '.$kernel.':' . $size ;
            $cmd .= ' "' . $p->getDestination().'"'  ;

            $p->execute($cmd);

        return  $p ;
    }

   /* function close(phmagick $p, $kernel){
            //Build command to close image
            $cmd = $p->getBinary('convert');
            $cmd .= ' "' . $p->getSource() .'"'  ;
            $cmd .= ' -morphology close ' .$kernel;
            $cmd .= ' "' . $p->getDestination() .'"'  ;

            echo  "Close: " . $cmd . "<br/>";
            $p->execute($cmd);

        return  $p ;
    }*/

    function mask(phmagick $p, $originalImage){
            //Build command to close image
            $cmd = $p->getBinary('convert');
            $cmd .= ' "' . $p->getSource() .'"'  ;
            $cmd .= ' "' . $originalImage .'"' ;
            //$cmd .= ' "' . $p->getSource() .'"'  ;
            $cmd .= ' "' . $p->getSource() .'"'  ;
            $cmd .= ' -compose multiply -composite  -transparent "#000000"'  ;
            $cmd .= ' "' . $p->getDestination() .'"'  ;
            
            $p->execute($cmd);

        return  $p ;
    }

    function fillHoles(phmagick $p, $drawSettings)
    {
        //Build to fill holes
        $cmd = $p->getBinary('convert');
        $cmd .= ' "' . $p->getSource() . '"';
        $cmd .= '-fill red -fuzz 5% -draw ' . '"' . $drawSettings . '"' . ' -fill black +opaque red -fill white -opaque red -alpha off';
        $cmd .= ' "' . $p->getDestination() .'"'  ;

        echo "Fill holes " . $cmd . "<br/>";
        $p->execute($cmd);

        return $p;
    }

    function getAverageIntensity(phmagick $p){

            $p->resize(1,1);
            $p->toGrayScale();
            //Build command to close image
            $cmd = $p->getBinary('convert');
            $cmd .= ' "' . $p->getSource() .'"';
            $cmd .= " -format '%[pixel:p{0,0}]' info:";

            $p->execute($cmd);
            $res = $p->getLog();
            $res = $res[2];
            $res = $res["output"];
            $start = strpos($res[0], "(")+1;
            $length = strpos($res[0], ",") - strpos($res[0], "(") - 1;
            $res = substr($res[0], $start, $length);
            
        return  $res ;
    }
}
?>