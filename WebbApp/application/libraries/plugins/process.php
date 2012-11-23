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
            addBorder(phmagick $p, $borderSize) - Adds a border to the image to help fill the holes.
                In: $p - phmagick object.
                    $borderSize - The size of the border.
                Out: phmagick object.
            removeBorder(phmagick $p, $borderSize) - Removes the border to obtain the right size for the image.
                In: $p - phmagick object.
                    $borderSize - The size of the border.
                Out: phmagick object.
                
* @author   Gabriella Ivarsson, gabiv132.
* @author   Christoffer Hermansson, chrhe155.   
* @date     2012-11-18
* @version  
*/
class phMagick_process
{
    function threshold(phmagick $p, $amount)
    {
        $cmd = $p->getBinary('convert');
        $cmd .= ' "' . $p->getSource().'"'  ;
        $cmd .= ' -negate -threshold ' . $amount ;
        $cmd .= ' "' . $p->getDestination().'"'  ;

        $p->execute($cmd);

        return  $p;
    }

    function mask(phmagick $p, $originalImage)
    {
        $cmd = $p->getBinary('convert');
        $cmd .= ' "' . $p->getSource() .'"'  ;
        $cmd .= ' "' . $originalImage .'"' ;
        $cmd .= ' -compose multiply -composite -transparent "#000000" -trim';
        $cmd .= ' "' . $p->getDestination() .'"'  ;
        
        $p->execute($cmd);

        return  $p;
    }

    function fillHoles(phmagick $p, $drawSettings)
    {
        $cmd = $p->getBinary('convert');
        $cmd .= ' "' . $p->getSource() . '"';
        $cmd .= ' -fill red -fuzz 5% -draw ' . '"' . $drawSettings . '"';
        $cmd .= ' "' . $p->getDestination() .'"';
        $p->execute($cmd);

        $cmd = $p->getBinary('convert');
        $cmd .= ' "' . $p->getSource() . '"';
        $cmd .= ' -fill white +opaque red -fill black -opaque red -alpha off';
        $cmd .= ' "' . $p->getDestination() .'"';
        $p->execute($cmd);
        
        return $p;
    }

    function addBorder(phmagick $p, $borderSize)
    {
        $cmd = $p->getBinary('convert');
        $cmd .= ' "' . $p->getSource() . '"';
        $cmd .= ' -bordercolor black -border ' . $borderSize;
        $cmd .= ' "' . $p->getDestination() .'"'  ;
        $p->execute($cmd);

        return $p;
    }

    function removeBorder(phmagick $p, $borderSize)
    {
        $cmd = $p->getBinary('convert');
        $cmd .= ' "' . $p->getSource() . '"';
        $cmd .= ' -shave ' . $borderSize;
        $cmd .= ' "' . $p->getDestination() .'"'  ;
        $p->execute($cmd);

        return $p;
    }

    function getAverageIntensity(phmagick $p)
    {
        $p->resize(1,1);
        $p->toGrayScale();

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
            
        return  $res;
    }
}
?>