<?php
/*
* @brief    Functions to generate resulting xml file.
*
* @details  
*			
*
* @author   Gabriella Ivarsson gabiv132
* @date     December 4, 2012
* @version  
*    
*/


class Create_xml_model extends CI_Model 
{

    function __construct()
    {
        // Call the Model constructor
        parent::__construct();
    }


    function xml_dom()
	{
		return new DOMDocument('1.0');
	}

    /**
	 * Gets all the images from a specific group and date
	 *
	 * @param  string	$date		The date
	 * @param  string	$group		The group
	 * @return array 	
	 */ 
    function create_xml() 
    {
		$this->load->helper('xml');
 
		$dom = $this->xml_dom();
		/*$book = xml_add_child($dom, 'book');
		 
		xml_add_child($book, 'title', 'Hyperion');
		$author = xml_add_child($book, 'author', 'Dan Simmons');		
		xml_add_attribute($author, 'birthdate', '1948-04-04');*/
		print_r($this->get_world($world));

		return xml_print($dom, true);
	}
	    /**
	 * Gets all the groups
	 *
	 * @return array 	
	 */ 
	function get_world($world){
		$this->db->select("name");
		$this->db->from("worlds");
		$where = "`name` = '$world'"; 
		$this->db->where($where);
		$query = $this->db->get();
		return $query->result();
	}



    function get_xml_file($world) 
    {
    	$url = "uploads/out/result.xml";
    	file_put_contents($url, $this->create_xml($world));
		return $url;

	}
}
