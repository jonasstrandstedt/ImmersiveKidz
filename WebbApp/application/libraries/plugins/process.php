<?php
/*
    +--------------------------------------------------------------------------------------------+
    |   DISCLAIMER - LEGAL NOTICE -                                                              |
    +--------------------------------------------------------------------------------------------+
    |                                                                                            |
    |  This program is free for non comercial use, see the license terms available at            |
    |  http://www.francodacosta.com/licencing/ for more information                              |
    |                                                                                            |
    |  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; |
    |  without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. |
    |                                                                                            |
    |  USE IT AT YOUR OWN RISK                                                                   |
    |                                                                                            |
    |                                                                                            |
    +--------------------------------------------------------------------------------------------+

*/
/**
 * phMagick - Resising functions
 *
 * @package    phMagick
 * @version    0.1.1
 * @author     Nuno Costa - sven@francodacosta.com
 * @copyright  Copyright (c) 2007
 * @license    GPL v3
 * @link       http://www.francodacosta.com/phmagick
 * @since      2008-03-13
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

    function mask(phmagick $p, $originalImage)
    {
            //Build command to close image
            $cmd = $p->getBinary('convert');
            $cmd .= ' "' . $p->getSource() .'"'  ;
            $cmd .= ' "' . $originalImage .'"' ;
            $cmd .= ' -compose multiply -composite -transparent "#000000"'  ;
            $cmd .= ' "' . $p->getDestination() .'"'  ;
            
            $p->execute($cmd);

        return  $p ;
    }

    function fillHoles(phmagick $p, $drawSettings)
    {
        //Build to fill holes
        $cmd = $p->getBinary('convert');
        $cmd .= ' "' . $p->getSource() . '"';
        $cmd .= ' -fill red -fuzz 5% -draw ' . '"' . $drawSettings . '"';
        $cmd .= ' "' . $p->getDestination() .'"';
        $p->execute($cmd);

        echo $cmd . "<br/>";

        $cmd = $p->getBinary('convert');
        $cmd .= ' "' . $p->getSource() . '"';
        $cmd .= ' -fill white +opaque red -fill black -opaque red -alpha off';
        $cmd .= ' "' . $p->getDestination() .'"';
        $p->execute($cmd);

        echo $cmd . "<br/>";
        
        return $p;
    }

    function addBorder(phmagick $p, $borderSize)
    {
        $cmd = $p->getBinary('convert');
        $cmd .= ' "' . $p->getSource() . '"';
        $cmd .= ' -bordercolor black -border ' . $borderSize;
        $cmd .= ' "' . $p->getDestination() .'"'  ;
        $p->execute($cmd);

        echo "Add border: " . $cmd . "<br/>";
    }

    function removeBorder(phmagick $p, $borderSize)
    {
        $cmd = $p->getBinary('convert');
        $cmd .= ' "' . $p->getSource() . '"';
        $cmd .= ' -shave ' . $borderSize;
        $cmd .= ' "' . $p->getDestination() .'"'  ;
        $p->execute($cmd);

        echo "Remove border: " . $cmd . "<br/>";
    }

    function getAverageIntensity(phmagick $p)
    {
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