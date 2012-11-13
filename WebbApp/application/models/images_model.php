<!--
* @brief    Databasefunctions for the images-table.
*
* @details  get_all_images_from_group($group, $date), gets all images from a given date and group.
*			add_image($name, $imgurl, $date, $group), adds an image to the database.
*			
*
* @author   Viktor Fröberg, vikfr292@student.liu.se
* @date     November 9, 2012
* @version  1.1 (removed the function data_group_exists() since get_all_images_from_group() = NULL will produce the same result.)
*    
-->

<?php
class Images_model extends CI_Model 
{

    function __construct()
    {
        // Call the Model constructor
        parent::__construct();
    }
    /**
	 * Gets all the images from a specific group and date
	 *
	 * @param  string	$date		The date
	 * @param  string	$group		The group
	 * @return array 	
	 */ 
    function get_all_images_from_group($group, $date) 
    {
		$this->db->select("*");
		$this->db->from("images");
		$where = "date = '$date' AND group = '$group"; 
		$this->db->where($where);
		$query = $this->db->get();
		return $query->result();
	}


	/**
	 * Adds an image to the database
	 *
	 * @param  string	$name		The name of the artist
	 * @param  string	$imgurl		The url of the image
	 * @param  string	$date		The date of the show
	 * @param  string	$group		The group this image belongs to.
	 * @return bool 	
	 */ 
	function add_image($name, $imgurl, $date, $group) 
	{
				$data = array(
				   'name' => $name ,
				   'imgurl' => $imgurl,
				   'date' => $date,
				   'group' => $group
				);
				$q = $this->db->insert('images', $data);
				return $q;
			}
	}