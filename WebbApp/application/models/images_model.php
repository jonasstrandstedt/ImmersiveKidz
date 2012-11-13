<?php
class Images_model extends CI_Model 
{

    function __construct()
    {
        // Call the Model constructor
        parent::__construct();
    }
    
	/**
	 * Fetches the user profile of specified user
	 *
	 * @param  integer	$id	The id of the user
	 * @return bool 	
	 */ 
    function get_all_images_from_group($group, $date) 
    {
		$this->db->select("*");
		$this->db->from("images");
		$where = "date = '$date' AND group = '$group"; // Get all images from a specifik date and group
		$this->db->where($where);
		$query = $this->db->get();
		return $query->result();
	}

	/**
	 * Checks if specified group exists on the same date.
	 *
	 * @param  string	$lukasid	The lukasid to check
	 * @return bool 	
	 */ 
	function date_group_exists($group, $date) 

	{	$where = "date = '$date' AND group = '$group";

		$this->db->where($where);
		$query = $this->db->get('images');
		if($query->num_rows == 1)
		{
			return true;
		}
		return false;
	}

	/**
	 * Adds an image to the database
	 *
	 * @param  string	$name		The name of the artist
	 * @param  string	$imgurl		The url of the image
	 * @param  string	$date		The date of the show
	 * @param  string	$group		The this image belongs to
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