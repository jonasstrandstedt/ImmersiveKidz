<?php
/*
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
*/


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
		$where = "`date` = '$date' AND `group` = '$group'"; 
		$this->db->where($where);
		$query = $this->db->get();
		return $query->result();
	}
	    /**
	 * Gets all the groups
	 *
	 * @return array 	
	 */ 
    function get_all_groups() 
    {
		$this->db->select("date, group");
		$this->db->from("images");
		$group = "date, group"; 
		$this->db->group_by($group);
		$query = $this->db->get();
		return $query->result();
	}

	    /**
	 * Gets all the images id from a specific group and date
	 *
	 * @param  string	$date		The date
	 * @param  string	$group		The group
	 * @return array 	
	 */ 
	    function get_all_id_from_group($group, $date) 
    {
		$this->db->select("id");
		$this->db->from("images");
		$where = "`date` = '$date' AND `group` = '$group'"; 
		$this->db->where($where);
		$query = $this->db->get();
		return $query->result();
	}


	/**
	 * Adds an image to the database
	 *
	 * @param  string	$artist		The name of the artist
	 * @param  string	$imgname	The name of the image
	 * @param  string	$imgurl		The url of the image
	 * @param  string	$imgouturl	The url of the image after image processing
	 * @param  string	$soundurl	The url of the soundfile
	 * @param  string	$date		The date for this group
	 * @param  string	$group		The group this image belongs to
	 * @param  string	$story		The story of the image
	 * @param  string	$world		The world for this image belongs to
	 * @return bool 	
	 */ 
	function add_image($artist, $imgname, $imgurl, $imgouturl,$soundurl ,$date, $group, $story, $world) 
	{
				$data = array(
				   'artist' => $artist,
				   'imgname' => $imgname,
				   'imgurl' => $imgurl,
				   'imgouturl' => $imgouturl,
				   'soundurl' => $soundurl,
				   'date' => $date,
				   'group' => $group,
				   'story' => $story,
				   'world' => $world
				);
				$q = $this->db->insert('images', $data);
				return $q;
			}
		/**
	 * Updates an image-post
	 *
	 * @param  string	$artist		The name of the artist
	 * @param  string	$imgname	The name of the image
	 * @param  string	$imgurl		The url of the image
	 * @param  string	$imgouturl	The url of the image after image processing
	 * @param  string	$soundurl	The url of the soundfile
	 * @param  string	$date		The date for this group
	 * @param  string	$group		The group this image belongs to
	 * @param  string	$story		The story of the image
	 * @return bool 	
	 */ 
	function update_image($id, $artist, $imgname, $soundurl, $story) 
	{
				$data = array( // what to update
				   'artist' => $artist,
				   'imgname' => $imgname,
				   'soundurl' => $soundurl,
				   'story' => $story
				);

				$where = array( // the id to update
    				'id' => $id
				);

				$this->db->where($where);
				$q = $this->db->update('images', $data);
		}

	/**
	 * Updates the coordinates of an image
	 *
	 * @param  int		$id			The id of the image
	 * @param  float	$x_coord	The x-coordinate of the image
	 * @param  float	$y_coord	The y-coordinate of the image
	 * @param  float	$z_coord	The z-coordinate of the image
	 * @return bool 	
	 */ 
	function update_coordinates($id, $x_coord, $y_coord, $z_coord) 
	{
				$data = array( // what to update
				   'x_coord' => $x_coord,
				   'y_coord' => $y_coord,
				   'z_coord' => $z_coord
				);

				$where = array( // the id to update
    				'id' => $id
				);

				$this->db->where($where);
				$q = $this->db->update('images', $data);
		}
	/**
	 * Gets all the worlds from the database
	 *
	 * @return array 	
	 */ 
	function get_all_worlds()
    {
		$this->db->select("id, name");
		$this->db->from("worlds");
		$query = $this->db->get();
		return $query->result();
	}
}
