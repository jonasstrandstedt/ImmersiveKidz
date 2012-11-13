<!--
* @brief    To controll image processing
*
* @details  index - Call functions in library ProcessImage.
*
* @author   Gabriella Ivarsson, gabiv132
* @author   
* @date     2012-11-08
* @version  
*    
-->

<?php
class Image extends CI_Controller {

	public function index()
	{
		$this->load->library('ProcessImage');
		$folder = "images";
		$images = $this->processimage->readIms($folder); 
		$this->processimage->findDrawing($images, $folder);  
	}
}
?>