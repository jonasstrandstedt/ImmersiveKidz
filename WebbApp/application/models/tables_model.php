<?php
/*
* @brief    Databasefunctions for the tables.
*			
*
* @author   Viktor Fröberg, vikfr292@student.liu.se
* @author   Belinda Bernfort, belbe886@student.liu.se
* @author   Gabriella Ivarsson, gabiv132
* @author   Emil Lindström, emili250
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
	
	
	/* --- GET FUNCTIONS --- */
	
	
    /*
	 * Gets all the data from worlds
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

    /*
	 * Gets all the data from worlds with a specific world
	 *
	 * @param  string	$id		The world id
	 * @return array 	
	 */ 	
	function get_world($id)
    {
		$this->db->select("*");
		$this->db->from("worlds");
		$where = array(
			'id' => $id
			);
		$this->db->where($where);
		$query = $this->db->get();
		return $query->result();
	}
	
	/*
	 * Gets all the data from worlds with a specific world
	 *
	 * @param  string	$name		The name of world
	 * @return array 	
	 */ 
	function get_world_by_name($name)
    {
    	
		$this->db->select("*");
		$this->db->from("worlds");
		$where = array(
			'name' => $name);
		$this->db->where($where);
		$query = $this->db->get();
		return $query->result();
	}
	
    /*
	 * Gets world_id from groups with a specific group
	 *
	 * @param  string	$id		The group id
	 * @return array 	
	 */ 	
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
	
    /*
	 * Gets all data from groups
	 *
	 * @param  string	$id		The group id
	 * @return array 	
	 */ 	
    function get_all_groups() 
    {
		$this->db->select("*");
		$this->db->from("groups");
		$query = $this->db->get();
		return $query->result();
	}

    /*
	 * Gets group id from groups with a specific group
	 *
	 * @param  string	$date		The group date
	 * @param  string	$name		The group name
	 * @return array 	
	 */ 	
    function get_group_id($date, $name) 
    {
		$this->db->select("id");

		$this->db->from("groups");
		$where = array(
    				'date' => $date,
    				'name' => $name
				);

		$this->db->where($where);
		$query = $this->db->get();
		return $query->result();
	}
	
    /*
	 * Gets all data from groups with a specific group
	 *
	 * @param  string	$id		The group id
	 * @return array 	
	 */ 	
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

    /*
	 * Gets all data from groups with a specific group
	 *
	 * @param  string	$id		The group id
	 * @return array 	
	 */ 	
	function get_group_from_world_id($id) 
    {
		$this->db->select("*");

		$this->db->from("groups");
		$where = array( 
				'world_id' => $id
				);
		$this->db->where($where);
		$query = $this->db->get();
		return $query->result();
	}
	
    /*
	 * Gets all the data from both illustrations and billboards with a specific group
	 *
	 * @param  string	$groupID		The group id
	 * @return array 	
	 */ 
    function get_all_illustrations_billboards_from_group($groupID) 
    {
		$this->db->select("*");
		$this->db->from("illustrations");
		$this->db->join('billboards', 'illustrations.billboard_id=billboards.id', 'inner');
		$where = "`illustrations.group_id` = '$groupID'"; 
		$this->db->where($where);
		$query = $this->db->get();
		return $query->result();
	}
	
	/*
	 * Gets all the data from illustrations with a specific group
	 *
	 * @param  string	$group		The group id
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
	 * Gets all the images id from a specific group
	 *
	 * @param  string	$groupID		The group id
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
	
	/**
	 * Gets id and imgurl from illustrations with a specific group
	 *
	 * @param  string	$groupID		The group id
	 * @return array 	
	 */ 
	function get_all_illustration_id_and_imgurl_from_group($groupID) 
    {
		$this->db->select("id, imgurl");
		$this->db->from("illustrations");
		$where = "`group_id` = '$groupID'"; 
		$this->db->where($where);
		$query = $this->db->get();
		return $query->result();
	}
	
	/**
	 * Gets imgurl from illustrations with a specific illustration
	 *
	 * @param  string	$id		The illustration id
	 * @return array 	
	 */ 
	function get_url_from_id($id) 
    {
		$this->db->select("imgurl");
		$this->db->from("illustrations");
		$where = "`id` = '$id'"; 
		$this->db->where($where);
		$query = $this->db->get();
		return $query->result();
	}
	
	/**
	 * Gets soundurl from illustrations with a specific illustration
	 *
	 * @param  string	$id		The illustration id
	 * @return array 	
	 */ 
	function get_illustration_sound($id) 
    {
		$this->db->select("soundurl");
		$this->db->from("illustrations");
		$where = array( 
    				'billboard_id' => $id
				);

		$this->db->where($where);
		$query = $this->db->get();
		return $query->result();
	}

	/**
	 * Gets imgurl from billboards with a specific billboard
	 *
	 * @param  string	$id		The billboard id
	 * @return array 	
	 */ 	
	function get_billboard_url_from_id($id) 
    {
		$this->db->select("imgurl");
		$this->db->from("billboards");
		$where = "`id` = '$id'"; 
		$this->db->where($where);
		$query = $this->db->get();
		return $query->result();
	}
	
	/**
	 * Gets all data from joined billboards and billboard_world with a specific world
	 *
	 * @param  string	$world_id		The	world id
	 * @return array 	
	 */ 	
	function get_billboards_from_billboard_world($world_id)
	{
		$this->db->select("*");
		$this->db->from("billboards");
		$this->db->join('billboard_world', 'billboards.id=billboard_world.billboard_id', 'inner');
		$where = array( 
    				'billboard_world.world_id' => $world_id
				);
		$this->db->where($where);
		$query = $this->db->get();
		return $query->result();
	}	
	
	/**
	 * Gets billboard_id from illustrations with a specific illustration
	 *
	 * @param  string	$id		The	illustrations id
	 * @return array 	
	 */ 
	function get_billboard_id_from_illustration($id) 
    {
		$this->db->select("billboard_id");

		$this->db->from("illustrations");
		$where = array( 
    				'id' => $id
				);

		$this->db->where($where);
		$query = $this->db->get();
		return $query->result();
	}
	
	/**
	 * Gets imgurl from billboards with a specific billboard
	 *
	 * @param  string	$id		The	billboard id
	 * @return array 	
	 */ 
	function get_billboard_image($id) 
    {
		$this->db->select("imgurl");

		$this->db->from("billboards");
		$where = array( 
    				'id' => $id
				);

		$this->db->where($where);
		$query = $this->db->get();
		return $query->result();
	}
	
	/**
	 * Gets all data from billboards with a specific group
	 *
	 * @param  string	$group_id		The	group id
	 * @return array 	
	 */ 
	function get_billboard_from_illustrations($group_id) 
    {
		$this->db->select("*");

		$this->db->from("billboards");
		$where = array(
			"id" => "(SELECT `billboard_id` FROM illustrations WHERE `group_id` = $group_id)");
		$query = $this->db->get();
		return $query->result();
	}
	
	/**
	 * Gets all data from billboard_world with a specific world
	 *
	 * @param  string	$id		The	world id
	 * @return array 	
	 */ 
	function get_billboard_from_billboard_world($id) 
    {
		$this->db->select("*");
        $this->db->from("billboard_world");
        $where = array( 
                      'world_id' => $id
                      );
        $this->db->where($where);
        $query = $this->db->get();
        return $query->result();
     }
	
	/**
	 * Gets billboard_id from billboard_world with a specific world
	 *
	 * @param  string	$id		The	world id
	 * @return array 	
	 */ 
	function get_billboard_id_from_billboard_world($world_id) 
    {
		$this->db->select("billboard_id");
		$this->db->from("billboard_world");
		$where = array( 
    				'world_id' => $world_id
				);

		$this->db->where($where);
		$query = $this->db->get();
		return $query->result();
	}
	
	/*
	 * Gets all the data from masks with a specific map
	 *
	 * @param  string	$mapID		The map id
	 * @return array 	
	 */ 
	function get_masks_from_map_id($mapID) 
    {
		$this->db->select("*");
		$this->db->from("masks");
		$where = "`map_id` = $mapID"; 
		$this->db->where($where);
		$query = $this->db->get();
		return $query->result();
	}
	
	/*
	 * Gets textureurl from maks with a specific group
	 *
	 * @param  string	$groupID		The group id
	 * @return array 	
	 */ 
	function get_mask_from_group_id($groupId) 
    {
		$this->db->select("textureurl");
		$this->db->from("masks");
		$where = "`map_id` = (SELECT `map_id` FROM `worlds` WHERE `id` = (SELECT `world_id` FROM `groups` WHERE `id` = $groupId))"; 
		$this->db->where($where);
		$query = $this->db->get();
		return $query->result();
	}
	
	/*
	 * Gets animation id from animations with a specific animation
	 *
	 * @param  string	$name		The animation name
	 * @return array 	
	 */ 
    function get_animation_id($name) 
    {
		$this->db->select("id");

		$this->db->from("animations");
		$where = array(
    				'name' => $name
				);

		$this->db->where($where);
		$query = $this->db->get();
		return $query->result();
	}

	/*
	 * Gets all data from animations
	 *
	 * @return array 	
	 */ 
	function get_animation() 
    {
		$this->db->select("*");

		$this->db->from("animations");

		$query = $this->db->get();
		return $query->result();
	}

	/*
	 * Gets all joined data from animations and billboard_animation with a specific billboard
	 *
	 * @param  string	$billboard_id		The billboard id
	 * @return array 	
	 */ 
	function get_animations_from_billboard_animation($billboard_id)
	{
		$this->db->select("*");
		$this->db->from("animations");
		$this->db->join('billboard_animation', 'animations.id=billboard_animation.animation_id', 'inner');
		$where = array( 
    				'billboard_animation.billboard_id' => $billboard_id
				);
		$this->db->where($where);
		$query = $this->db->get();
		return $query->result();
	}	

	/*
	 * Gets all data from billboard_animation
	 *
	 * @return array 	
	 */ 
	function get_billboard_animation() 
    {
		$this->db->select("*");

		$this->db->from("billboard_animation");

		$query = $this->db->get();
		return $query->result();
	}
	
	/*
	 * Gets all the data from models with a specific group
	 *
	 * @param  string	$groupID		The group id
	 * @return array 	
	 */ 
	function get_model_from_group_id($groupId) 
    {
		$this->db->select("*");
		$this->db->from("models");
		$where = "`id` = (SELECT `model_id` FROM `model_world` WHERE `world_id` = (SELECT `world_id` FROM `groups` WHERE `id` = $groupId))"; 
		$this->db->where($where);
		$query = $this->db->get();
		return $query->result();
	}
	
	/*
	 * Gets all the data from models with a specific world
	 *
	 * @param  string	$worldID		The world id
	 * @return array 	
	 */ 
	function get_model_from_world_id($worldID) 
    {
		$this->db->select("*");
		$this->db->from("models");
		$where = "`id` = (SELECT `model_id` FROM `model_world` WHERE `world_id` = $worldID)"; 
		$this->db->where($where);
		$query = $this->db->get();
		return $query->result();
	}
	
	/*
	 * Gets all the data from model_world with a specific world
	 *
	 * @param  string	$worldID		The world id
	 * @return array 	
	 */ 
	function get_model_world($worldID) 
    {
		$this->db->select("*");
		$this->db->from("model_world");
		$where = "`world_id` = $worldID"; 
		$this->db->where($where);
		$query = $this->db->get();
		return $query->result();
	}
	
	/*
	 * Gets all the data from planes with a specific world
	 *
	 * @param  string	$worldID		The world id
	 * @return array 	
	 */ 
	function get_plane_from_world_id($worldID) 
    {
		$this->db->select("*");
		$this->db->from("planes");
		$where = "`id` = (SELECT `plane_id` FROM `plane_world` WHERE `world_id` = $worldID)"; 
		$this->db->where($where);
		$query = $this->db->get();
		return $query->result();
	}
	
	/*
	 * Gets textureurl from planes with a specific group
	 *
	 * @param  string	$groupID		The group id
	 * @return array 	
	 */ 
	function get_plane_from_group_id($groupId) 
	{
		$this->db->select("textureurl");
		$this->db->from("planes");
		$where = "`id` = (SELECT `plane_id` FROM `maps` WHERE `id` = (SELECT `map_id` FROM `worlds` WHERE `id` = (SELECT `world_id` FROM `groups` WHERE `id` = $groupId)))"; 
		$this->db->where($where);
		$query = $this->db->get();
		return $query->result();
	}
	
	/*
	 * Gets all joined data from planes and maps 
	 * Joined on plane id
	 * @return array 	
	 */ 	
	function get_all_planes_from_maps()
	{
		$this->db->select("*");
		$this->db->from("planes");
		$this->db->join('maps', 'planes.id=maps.plane_id', 'inner');
		$query = $this->db->get();
		return $query->result();
	}	
	
	
	/*
	 * Gets all data from planes with a specific plane
	 *
	 * @param  string	$id		The plane id
	 * @return array 	
	 */ 	
	function get_plane($id)
	{	
		$this->db->select("*");
		$this->db->from("planes");
		$where = array(
						'id' => $id
									);
		$this->db->where($where);
		$query = $this->db->get();
		return $query->result();
	}

	/*
	 * Gets all data from planes
	 *
	 * @return array 	
	 */ 	
	function get_all_planes()
	{
		$this->db->select("*");
		$this->db->from("planes");
		$query = $this->db->get();
		return $query->result();
	}

	/*
	 * Gets all from planes with a specific world
	 *
	 * @param  string	$worldID		The world id
	 * @return array 	
	 */ 
	function get_map_from_world_id($worldID) 
    {
		$this->db->select("*");
		$this->db->from("planes");
		$where = "`id` = (SELECT `plane_id` FROM maps WHERE `id` = (SELECT `map_id` FROM `worlds` WHERE `id` = $worldID))"; 
		$this->db->where($where);
		$query = $this->db->get();
		return $query->result();
	}
	
	/*
	 * Gets all data from maps with a specific map
	 *
	 * @param  string	$id		The map id
	 * @return array 	
	 */ 	
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

	/*
	 * Gets id from maps with a specific plane
	 *
	 * @param  string	$plane_id		The plane id
	 * @return array 	
	 */ 
	function get_map_id_from_plane($plane_id)
	{	
		$this->db->select("id");
		$this->db->from("maps");
		$where = array(
			'plane_id' => $plane_id);
		$this->db->where($where);
		$query = $this->db->get();
		return $query->result();
	}
	
	/*
	 * Gets all from maps
	 *
	 * @return array 	
	 */ 
	function get_all_maps()
	{	
		$this->db->select("*");
		$this->db->from("maps");
		$query = $this->db->get();
		return $query->result();
	}
	

	
	


	/* --- ADD FUNCTIONS --- */

	/**
	 * Adds an illustration to the database
	 *
	 * @param  string	$artist			The name of the artist
	 * @param  string	$imgname		The name of the image
	 * @param  string	$imgurl			The url of the image
	 * @param  string	$soundurl		The url of the soundfile
	 * @param  string	$billboard_id	The url of the soundfile
	 * @param  string	$group_id		The group this image belongs to
	 * @param  string	$story			The story of the image
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
				'story' => $story
				);
		$q = $this->db->insert('illustrations', $data);
		return $q;
	}
	
	/**
	 * Adds an world to the database
	 *
	 * @param  string	$name				The name of the world
	 * @param  float	$camlim_xpos		The limit of camera in x
	 * @param  float	$camlim_xmin		The limit of camera in x
	 * @param  float	$camlim_ypos		The limit of camera in y
	 * @param  float	$camlim_ymin		The limit of camera in y
	 * @param  float	$camlim_zpos		The limit of camera in z
	 * @param  float	$camlim_zmin		The limit of camera in z
	 * @param  float	$camstart_x			The start position of camera in x
	 * @param  float	$camstart_y			The start position of camera in y
	 * @param  float	$camstart_z			The start position of camera in z
	 * @param  float	$camdir_x			The direction of camera in x
	 * @param  float	$camdir_y			The direction of camera in y
	 * @param  float	$camdir_z			The direction of camera in z
	 * @param  float	$randmin_x			The minimum random x-coordinate 	
	 * @param  float	$randmin_y			The minimum random y-coordinate 	
	 * @param  float	$randmin_z			The minimum random z-coordinate 	
	 * @param  float	$randmin_x			The maximum random x-coordinate 	
	 * @param  float	$randmin_y			The maximum random y-coordinate 	
	 * @param  float	$randmin_z			The maximum random z-coordinate 	
	 * @param  int		$map_id				The id of the associated map	
	 * @return bool 	
	 */ 
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
	
	/**
	 * Adds an billboard to the database
	 *
	 * @param  string	$imgurl		The url of the image
	 * @param  float	$size_x		The x-size of image
	 * @param  float	$size_y		The y-size of image
	 * @return billboard id	
	 */ 
	function add_billboard($imgurl, $size_x = NULL, $size_y = NULL) 
	{			
		if($size_x == NULL || $size_y == NULL)
		{
			$size_x = 1;
			$size_y = 1;
		}
		$data = array(
					'imgurl' => $imgurl,
					'size_x' => $size_x,
					'size_y' => $size_y
					);
		$q = $this->db->insert('billboards', $data);	
		
		//Return id
		$this->db->select("id");
		$this->db->from("billboards");
		$data = array(
					'imgurl' => $imgurl
					);
		$this->db->where($data);
		$query = $this->db->get();
		return $query->result();
	}	
	
	/**
	 * Adds relation in billboard_world to the database
	 *
	 * @param  int		$world_id		The world id
	 * @param  int		$billboard_id	The billboard id
	 * @param  int		$mask_id		The mask id
	 * @param  float	$pos_x			The x-position
	 * @param  float	$pos_y			The y-position
	 * @param  float	$pos_z			The z-position
	 * @param  int		$mult_count		The number of instances of the billboard
	 * @param  int		$mult_seed		Random number to place the billboards randomly in the world
	 * @param  string	$type			The type of the billboard
	 * @return bool
	 */ 
	function add_billboard_to_world($world_id, $billboard_id, $mask_id, $pos_x, $pos_y, $pos_z, $mult_count, $mult_seed, $type) 
	{		
		$mult_seed = rand(1 , 9999999); //random number
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
	
	/**
	 * Adds a group to the database
	 *
	 * @param  string	$name		The name of the group
	 * @param  string	$date		The date of the group
	 * @param  int		$world_id	The associated id of world to the group
	 * @return bool
	 */ 
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
	 * Adds a plane to the database
	 *
	 * @param  float	$width			The width of the plane
	 * @param  float	$height			The height of the plane
	 * @param  string	$textureurl		The textureurl of the plane
	 * @param  float	$rot_x			The rotation around x-axis
	 * @param  float	$rot_y			The rotation around y-axis
	 * @param  float	$rot_z			The rotation around z-axis
	 * @param  float	$pos_x			The position in x
	 * @param  float	$pos_y			The position in y
	 * @param  float	$pos_z			The position in z
	 * @return plane id
	 */ 
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

		//return plane id
		$this->db->select("id");
		$this->db->from("planes");
		$this->db->where($data);
		$query = $this->db->get();
		return $query->result();
	}

	/**
	 * Adds relation in plane_world to the database
	 *
	 * @param  int		$plane_id	The plane id
	 * @param  int		$world_id	The world id
	 * @return bool
	 */ 	
	function add_plane_to_world($plane_id, $world_id) 
	{			
		$data = array(
					'plane_id' => $plane_id,
					'world_id' => $world_id
					);
		$q = $this->db->insert('plane_world', $data);
		return $q;
	}
	
	/**
	 * Adds a map to the database
	 *
	 * @param  string	$name			The name of the map
	 * @param  int		$plane_id		The associated plane id to the map
	 * @return map id
	 */ 
	function add_map($name = NULL, $plane_id) 
	{
		$data = array(
				'name' => $name,
				'plane_id' => $plane_id		
				);
		$q = $this->db->insert('maps', $data);
		
		//return map id
		$this->db->select("id");
		$this->db->from("maps");
		$this->db->where($data);
		$query = $this->db->get();
		return $query->result();	
	}
	
	/**
	 * Adds a mask to the database
	 *
	 * @param  string	$textureurl		The url of the texture
	 * @param  string	$name			The name of the mask
	 * @param  int		$map_id			The associated map id to the mask
	 * @return bool
	 */ 
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

	/**
	 * Adds an animation to the database
	 *
	 * @param  string	$name		The name of the animation
	 * @return bool
	 */ 
	function add_animation($name) 
	{
		$data = array(
				   'name' => $name		
					);
		$q = $this->db->insert('animations', $data);
		return $q;
	}
	
	/**
	 * Adds relation in billboard_animation to the database
	 *
	 * @param  int		$animation_id	The animation id
	 * @param  int		$billboard_id	The billboard id
	 * @return bool
	 */ 	
	function add_animation_to_billboard($animation_id, $billboard_id) 
	{
		$seed = rand(1 , 9999999); //random number
		$data = array(
					'animation_id' => $animation_id,
					'billboard_id' => $billboard_id,
					'seed' => $seed
					);
		$q = $this->db->insert('billboard_animation', $data);
		return $q;
	}	

	
	/**
	 * Adds a model to the database
	 *
	 * @param  string	$obj_fileurl	The url to obj-file
	 * @param  string	$textureurl		The url to texture
	 * @return bool 	
	 */ 
	function add_model($obj_fileurl, $textureurl) 
	{
				$data = array(
				   'obj_fileurl' => $obj_fileurl,
				   'textureurl' => $textureurl
				);
				$q = $this->db->insert('models', $data);
				return $q;
	}
	
	/**
	 * Adds relation in model_world to the database
	 *
	 * @param  int		$world_id	The world id
	 * @param  int		$model_id	The model id
	 * @param  float	$pos_x		The x-position
	 * @param  float	$pos_y		The y-position
	 * @param  float	$pos_z		The z-position
	 * @param  float	$rot_x		The rotation around x-axis
	 * @param  float	$rot_y		The rotation around y-axis
	 * @param  float	$rot_z		The rotation around z-axis
	 * @return bool
	 */ 
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
	
	/* --- REMOVE FUNCTIONS --- */
	
	/**
	 * Removes illustration with a specific illustration id
	 *
	 * @param  int	$id		The illustration id
	 *
	 */ 
	function remove_illustration($id) 
	{
		$where = array(
					'id' => $id
					);
		$this->db->where($where);
		$q = $this->db->delete('illustrations');
	}
	
	/**
	 * Removes billboard with a specific billboard id
	 *
	 * @param  int	$billboard_id		The billboard id
	 *
	 */ 
	function remove_billboard($billboard_id) 
	{
		$where = array(
					'id' => $billboard_id
					);
		$this->db->where($where);
		$q = $this->db->delete('billboards');
	}
	
	/**
	 * Removes the relation in billboard_world with a specific billboard id and world id
	 *
	 * @param  int	$world_id		The world id
	 * @param  int	$billboard_id	The billboard id
	 *
	 */ 
	function remove_billboard_from_world($world_id, $billboard_id) 
	{
		$where = array(
					'world_id' => $world_id,
					'billboard_id' => $billboard_id
					);
		$this->db->where($where);
		$q = $this->db->delete('billboard_world');
	}
	
	
	/* --- UPDATE FUNCTIONS --- */
	
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
	function update_illustration($id, $artist, $imgname,$imgurl ,$soundurl, $story, $thresh = NULL) 
	{	
		if($imgurl != '')
		{
			$data = array( // what to update
						'artist' => $artist,
						'imgurl' => $imgurl,
						'imgname' => $imgname,
						'soundurl' => $soundurl,
						'story' => $story
						);
		}else if(!empty($thresh))
		{
			$data = array( // what to update
						'artist' => $artist,
						'imgname' => $imgname,
						'soundurl' => $soundurl,
						'thresh' => $thresh,
						'story' => $story
						);
		}else
		{
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
	 * Updates coordinates in illustrations
	 *
	 * @param  int		$id			The id of illustration
	 * @param  float	$x_coord	The x-coordinate
	 * @param  float	$y_coord	The y-coordinate
	 * @param  float	$z_coord	The z-coordinate
	 * @return bool 	
	 */ 
	function update_illustration_coordinates($id, $x_coord,$y_coord, $z_coord)
	{
		if($y_coord == '')
		{
			$y_coord = 0.0;
		}
		$data = array( // what to update
					'pos_x' => $x_coord,
					'pos_y' => $y_coord,
					'pos_z' => $z_coord
					);
		$where = array( // the id to update
					'id' => $id
					);
		$this->db->where($where);
		$q = $this->db->update('illustrations', $data);
	}

	/**
	 * Updates map id in worlds
	 *
	 * @param  int		$map_id		The id of map
	 * @param  int		$world_id	The id of world
	 * @return bool 	
	 */ 
	function update_map_id_world($map_id, $world_id)
	{
		$data = array(
					'map_id' => $map_id
					);
		$where = array(
					'id' => $world_id
					);
		$this->db->where($where);
		$q = $this->db->update('worlds', $data);
	}

	/**
	 * Updates mult_count and type in billboard_world and updates size in billboards
	 *
	 * @param  int		$world_id		The id of world
	 * @param  int		$billboard_id	The id of billboard
	 * @param  int		$mult_count		The number of instanes of billboards
	 * @param  string	$type			The type of billboard
	 * @param  float	$size_x			The x-size of billboard
	 * @param  float	$size_y			The y-size of billboard
	 * @return bool 	
	 */ 
	function update_billboard_world($world_id, $billboard_id, $mult_count, $type, $size_x, $size_y)
	{	
		$data = array( // what to update
					'mult_count' => $mult_count,
					'type' => $type
					);
		
		$where = array( // what to update
					'world_id' => $world_id,
					'billboard_id' => $billboard_id
					);
		$this->db->where($where);
		$q = $this->db->update('billboard_world', $data);
		
		//------------update size in table Billboards------------
		
		$data = array( // what to update
					'size_x' => $size_x,
					'size_y' => $size_y
					);
		
		$where = array( // the id to update
					'id' => $billboard_id
					);
		$this->db->where($where);
		$q = $this->db->update('billboards', $data);
		
	}
	
	/**
	 * Updates size in billboards
	 *
	 * @param  int		$billboard_id	The id of billboard
	 * @param  float	$size_x			The x-size of billboard
	 * @param  float	$size_y			The y-size of billboard
	 * @return bool 	
	 */ 
	function update_billboard_size($billboard_id, $size_x, $size_y)
	{
		$data = array( // what to update
		   'size_x' => $size_x,
		   'size_y' => $size_y
		);
		
		$where = array( // the id to update
			'id' => $billboard_id
		);
		$this->db->where($where);
		$this->db->update('billboards', $data);
	}
	
	/**
	 * Updates imgurl and thresh in billboards
	 *
	 * @param  int		$id			The id of billboard
	 * @param  string	$imgurl		The url of billboard
	 * @param  int		$thresh		The thresh value
	 * @return bool 	
	 */ 
	function update_billboard_image($id, $imgurl, $thresh) 
    {
    	if($imgurl != '' && $thresh == '')
		{
			$data = array( // what to update
					   'imgurl' => $imgurl
						);
		}else if($imgurl == '' && $thresh != '')
		{
			$data = array( // what to update
						 'thresh' => $thresh
						);
		}else
		{
			$data = array( // what to update
						 'imgurl' => $imgurl,
						 'thresh' => $thresh
						);
		}
		$where = array( // the id to update
					'id' => $id
					);
		$this->db->where($where);
		$q = $this->db->update('billboards', $data);
	}

	
	/**
	 * Updates animation id and billboard id in billboard_animation
	 *
	 * @param  int		$animation_id	The id of animation
	 * @param  int		$billboard_id	The id of billboard
	 * @return bool 	
	 */ 
	function update_animation_to_billboard($animation_id, $billboard_id) 
	{
		$data = array(
					'animation_id' => $animation_id,
					'billboard_id' => $billboard_id
					);
		 $where = array(
						'billboard_id' => $billboard_id
						);
		$this->db->where($where);
		$q = $this->db->update('billboard_animation', $data);
	}
}
