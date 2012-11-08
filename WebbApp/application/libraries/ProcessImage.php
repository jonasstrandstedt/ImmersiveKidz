<?php if ( ! defined('BASEPATH')) exit('No direct script access allowed'); 

include "phmagick.php";
class ProcessImage {

    public function test()
    {
        $phMagick = new phMagick("sky.jpg","out.jpg");
         $cmd = $phMagick->getBinary('convert');
        $cmd .= ' "' . $phMagick->getSource().'"'  ;
        $cmd .= ' -threshold 50% ' ;
        $cmd .= ' "' . $phMagick->getDestination().'"'  ;

        echo $cmd;
        $phMagick->execute($cmd);

    }
}

/* End of file Someclass.php */