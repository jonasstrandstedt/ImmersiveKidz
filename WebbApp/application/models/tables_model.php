<?php
/*
* @brief    Databasefunctions for the tables.
*
* @details  get_all_images_from_group($group, $date), gets all images from a given date and group.
*			add_image($name, $imgurl, $date, $group), adds an image to the database.
*			
*
* @author   Viktor Fröberg, vikfr292@student.liu.se
* @author   Belinda Bernfort, belbe886@student.liu.se
* @date     December 6, 2012
* @version  2.0 
*    
*/


class Tables_model extends CI_Model 
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
    function get_all_illustrations_from_group($groupID) 
    {
		$this->db->select("*");
		$this->db->from("illustrations");
		$where = "`group_id` = '$groupID'"; 
		$this->db->where($where);
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
	    function get_all_illustration_id_from_group($groupID) 
    {
		$this->db->select("id");
		$this->db->from("illustrations");
		$where = "`group_id` = '$groupID'"; 
		$this->db->where($where);
		$query = $this->db->get();
		return $query->result();
	}



	/* ADD IMAGE */

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
	 * @return bool 	
	 */ 
	function add_illustration($artist, $imgname, $imgurl, $soundurl, $billboard_id, $group_id, $story) 
	{

				$data = array(
				   'artist' => $artist,
				   'imgname' => $imgname,
				   'imgurl' => $imgurl,
				   'soundurl' => $soundurl,
				   'billboard_id' => $billboard_id,
				   'group_id' => $group_id,
				   'story' => $story,
				   'pos_x' => $pos_x,
				   'pos_y' => $pos_y,
				   'pos_z' => $pos_z
				);
				$q = $this->db->insert('illustrations', $data);
				return $q;
			}

		function remove_illustration($id) 
		{
			$where = array( // the id to update
			'id' => $id
			);
			$this->db->where($where);
			$q = $this->db->delete('illustrations');
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

	function update_illustration($id, $artist, $imgname,$imgurl ,$soundurl, $story, $thresh) 
	{	
		if($imgurl != ''){
			$data = array( // what to update
			   'artist' => $artist,
			   'imgurl' => $imageurl,
			   'imgouturl' => $imgouturl,
			   'imgname' => $imgname,
			   'soundurl' => $soundurl,
			   'story' => $story
			);
		}
		else if(!empty($thresh)){
			$data = array( // what to update
			   'artist' => $artist,
			   'imgname' => $imgname,
			   'soundurl' => $soundurl,
			   'thresh' => $thresh,
			   'story' => $story
			);
		}
		else{
			$data = array( // what to update
			   'artist' => $artist,
			   'imgname' => $imgname,
			   'soundurl' => $soundurl,
			   'story' => $story
			);
		}

		$where = array( // the id to update
			'id' => $id
		);

		$this->db->where($where);
		$q = $this->db->update('illustrations', $data);
	}
	/**
	 * Gets all the worlds from the database
	 *
	 * @return array 	
	 */ 


	function get_all_worlds()
    {
		$this->db->select("*");
		$this->db->from("worlds");
		$query = $this->db->get();
		return $query->result();
	}

	function get_group_world($id)
    {
		$this->db->select("world_id");
		$this->db->from("groups");
		$where = array(
			'id' => $id
			);
		$this->db->where($where);
		$query = $this->db->get();
		return $query->result();
	}

	function get_url_from_id($id) 
    {
		$this->db->select("imgurl");
		$this->db->from("illustrations");
		$where = "`id` = '$id'"; 
		$this->db->where($where);
		$query = $this->db->get();
		return $query->result();
	}

	/* ADD WORLD */

	function add_world($name, $camlim_xpos, $camlim_xmin, $camlim_ypos, $camlim_ymin, $camlim_zpos, $camlim_zmin, $camstart_x, $camstart_y, $camstart_z, $camdir_x, $camdir_y, $camdir_z, $randmin_x, $randmin_y, $randmin_z, $randmax_x, $randmax_y, $randmax_z, $map_id) 
	{
				$data = array(
				   'name' => $name ,
				   'camlim_xpos' => $camlim_xpos,
				   'camlim_xmin' => $camlim_xmin,
				   'camlim_ypos' => $camlim_ypos,
				   'camlim_ymin' => $camlim_ymin,
				   'camlim_zpos' => $camlim_zpos,
				   'camlim_zmin' => $camlim_zmin,
				   'camstart_x' => $camstart_x,
				   'camstart_y' => $camstart_y,
				   'camstart_z' => $camstart_z,
				   'camdir_x' => $camdir_x,
				   'camdir_y' => $camdir_y,
				   'camdir_z' => $camdir_z,
				   'randmin_x' => $randmin_x,
				   'randmin_y' => $randmin_y,
				   'randmin_z' => $randmin_z,
				   'randmax_x' => $randmax_x,
				   'randmax_y' => $randmax_y,
				   'randmax_z' => $randmax_z,
				   'map_id' => $map_id
				);
				$q = $this->db->insert('worlds', $data);
				return $q;
	}
	function get_world($id)
    {
		$this->db->select("*");
		$this->db->from("worlds");
		$where = array(
			'id' => $id);
		$this->db->where($where);
		$query = $this->db->get();
		return $query->result();
	}


	/* ADD MODEL */

	function add_model($obj_fileurl, $textureurl) 
	{
				$data = array(
				   'obj_fileurl' => $obj_fileurl,
				   'textureurl' => $textureurl
				);
				$q = $this->db->insert('models', $data);
				return $q;
	}


	/* ADD BILLBOARD
	*
	*
	*Returns billboard-id
	 */

	function add_billboard($imgurl, $size_x = NULL, $size_y = NULL) 
	{			if($size_x == NULL || $size_y == NULL){
				$size_x = 1;
				$size_y = 1;
				}
				$data = array(
				   'imgurl' => $imgurl,
				   'size_x' => $size_x,
				   'size_y' => $size_y
				);
				$q = $this->db->insert('billboards', $data);
				
				$this->db->select("id");
				$this->db->from("billboards");
				$this->db->where($data);
				$query = $this->db->get();
				return $query->result();
	}

	function get_billboard_id_from_illustration($id) 
    {
		$this->db->select("billboard_id");

		$this->db->from("illustrations");
		$where = array( // the id to update
    				'id' => $id
				);

		$this->db->where($where);
		$query = $this->db->get();
		return $query->result();
	}
	function get_billboard_image($id) 
    {
		$this->db->select("imgurl");

		$this->db->from("billboards");
		$where = array( // the id to update
    				'id' => $id
				);

		$this->db->where($where);
		$query = $this->db->get();
		return $query->result();
	}
	function get_billboard_from_billboard_world($id) 
    {
		$this->db->select("*");

		$this->db->from("billboard_world");
		$where = array( // the id to update
    				'world_id' => $id
				);

		$this->db->where($where);
		$query = $this->db->get();
		return $query->result();
	}
	function update_billboard_image($id, $imgurl) 
    {
		$data = array( // what to update
				   'imgurl' => $imgurl
				);

		$where = array( // the id to update
			'id' => $id
		);

		$this->db->where($where);
		$q = $this->db->update('billboards', $data);
	}

	/* ADD GROUP */

	function add_group($name, $date, $world_id) 
	{

				$data = array(
				   'name' => $name,
				   'date' => $date,
				   'world_id' => $world_id
				);
				$q = $this->db->insert('groups', $data);
				return $q;
	}
	 /**
	 * Gets all the groups
	 *
	 * @return array 	
	 */ 
    function get_all_groups() 
    {
		$this->db->select("*");
		$this->db->from("groups");
		$query = $this->db->get();
		return $query->result();
	}

	 /**
	 * Get group id
	 *
	 * @return array 	
	 */ 
    function get_group_id($date, $name) 
    {
		$this->db->select("id");

		$this->db->from("groups");
		$where = array( // the id to update
    				'date' => $date,
    				'name' => $name
				);

		$this->db->where($where);
		$query = $this->db->get();
		return $query->result();
	}
	function get_group($id) 
    {
		$this->db->select("*");

		$this->db->from("groups");
		$where = array( 
				'id' => $id
				);
		$this->db->where($where);
		$query = $this->db->get();
		return $query->result();
	}

	/* ADD PLANE */

	function add_plane($width, $height, $textureurl, $rot_x, $rot_y, $rot_z, $pos_x, $pos_y, $pos_z) 
	{
				$data = array(
				   'width' => $width,
				   'height' => $height,
				   'textureurl' => $textureurl,
				   'rot_x' => $rot_x,
				   'rot_y' => $rot_y,
				   'rot_z' => $rot_z,
				   'pos_x' => $pos_x,
				   'pos_y' => $pos_y,
				   'pos_z' => $pos_z
				);
				$q = $this->db->insert('planes', $data);
				return $q;
	}

	/* ADD MASK */

	function add_mask($textureurl, $name, $map_id) 
	{
			
				$data = array(
				   'textureurl' => $textureurl,
				   'name' => $name,
				   'map_id' => $map_id
				);
				$q = $this->db->insert('masks', $data);
				return $q;
	}


	/* ADD ANIMATION */

	function add_animation($name) 
	{
				$data = array(
				   'name' => $name		
				);
				$q = $this->db->insert('animations', $data);
				return $q;
	}
		 /**
	 * Get animation id
	 *
	 * @return array 	
	 */ 
    function get_animation_id($name) 
    {
		$this->db->select("id");

		$this->db->from("animations");
		$where = array( // the id to update
    				'date' => $date,
    				'name' => $name
				);

		$this->db->where($where);
		$query = $this->db->get();
		return $query->result();
	}



	/* ADD MAP */

	function add_map($name, $plane_id) 
	{
			

				$data = array(
				   'name' => $name,
				   'plane_id' => $plane_id		
				);
				$q = $this->db->insert('maps', $data);
				return $q;
	}

	/* ADD MAP */

	function add_bilboard_to_world($world_id, $billboard_id, $mask_id, $pos_x, $pos_y, $pos_z, $mult_count, $mult_seed, $type) 
	{
			

				$data = array(
				   'world_id' => $world_id,
				   'billboard_id' => $billboard_id,
				   'mask_id' => $mask_id,
				   'pos_x' => $pos_x,
				   'pos_y' => $pos_y,
				   'pos_z' => $pos_z,
				   'mult_count' => $mult_count,	
				   'mult_seed' => $mult_seed,	
				   'type' => $type
				);
				$q = $this->db->insert('billboard_world', $data);
				return $q;
	}
	function add_model_to_world($world_id, $model_id, $pos_x, $pos_y, $pos_z, $rot_x, $rot_y, $rot_z) 
	{
			

				$data = array(
				   'world_id' => $world_id,
				   'model_id' => $model_id,
				   'pos_x' => $pos_x,
				   'pos_y' => $pos_y,
				   'pos_z' => $pos_z,
				   'rot_x' => $rot_x,
				   'rot_y' => $rot_y,
				   'rot_z' => $rot_z
				);
				$q = $this->db->insert('model_world', $data);
				return $q;
	}
	function add_animation_to_billboard($animation_id, $billboard_id) 
	{			

				$seed = rand (1 , $PHP_INT_MAX);
			

				$data = array(
				   'animation_id' => $animation_id,
				   'billboard_id' => $billboard_id,
				   'seed' => $seed,
				);
				$q = $this->db->insert('billboard_animation', $data);
				return $q;
	}

	function add_plane_to_world($plane_id, $world_id) 
	{			

				$data = array(
				   'plane_id' => $plane_id,
				   'world_id' => $world_id
				);
				$q = $this->db->insert('plane_world', $data);
				return $q;
	}
	function get_map($id)
	{	
		$this->db->select("*");
		$this->db->from("maps");
		$where = array(
			'id' => $id);
		$this->db->where($where);
		$query = $this->db->get();
		return $query->result();
	}
	function get_plane($id)
	{	$this->db->select("*");
		$where = array(
    				'id' => $id
				);
		$this->db->from("planes");
		$this->db->where($where);
		$query = $this->db->get();
		return $query->result();
	}
	// function add_map_to_world($map_id, $world_id) 
	// {			

	// 			$data = array(
	// 			   'map_id' => $map_id,
	// 			   'world_id' => $world_id
	// 			);
	// 			$q = $this->db->insert('map_world', $data);
	// 			return $q;
	// }

}
