<?php
/*
* @brief    Databasefunctions for the worlds-table.
*
* @details  add_world($name, $plane, $sky_xpos, $sky_xneg, $sky_ypos, $sky_yneg, $sky_zpos, $sky_zneg, $smallobj, $mediumobj ,$bigobj)  , adds a world to the database.
*			
*
* @author   Viktor Fröberg, vikfr292@student.liu.se  (?)
* @author   Belinda Bernfort, belbe886@student.liu.se
* @date     November 14, 2012
* @version  1.0
*    
*/
class Worlds_model extends CI_Model 
{

    function __construct()
    {
        // Call the Model constructor
        parent::__construct();
    }


	/**
	 * Adds a world to the database
	 *
	 * @param  string	$name			The name of the world
	 * @param  string	$plane			The url of the plane texture image
	 * @param  string	$plane_min_x	The min x-coord of the plane
	 * @param  string	$plane_min_y	The min y-coord of the plane
	 * @param  string	$plane_max_x	The max x-coord of the plane
	 * @param  string	$plane_max_y	The max y-coord of the plane
	 * @param  string	$rand_min_x		The min x-coord you can randomize
	 * @param  string	$rand_min_y		The min y-coord you can randomize
	 * @param  string	$rand_max_x		The max x-coord you can randomize
	 * @param  string	$rand_max_y		The max y-coord you can randomize
	 * @param  string	$sky_xpos		The url of the sky x positive texture image
	 * @param  string	$sky_xneg		The url of the sky x negative texture image
	 * @param  string	$sky_ypos		The url of the sky y positive texture image
	 * @param  string	$sky_yneg		The url of the sky y negative texture image
	 * @param  string	$sky_zpos		The url of the sky z positive texture image
	 * @param  string	$sky_zneg		The url of the sky z negative texture image
	 * @param  string	$smallobj		The url of the small object image (such as a flower)
	 * @param  string	$mediumobj		The url of the medium-sized object image (such as a bush)
	 * @param  string	$bigobj			The url of the big object image (such as a tree)
	 * @return bool 	
	 */ 

	function add_world($name, $plane, $plane_min_x, $plane_min_y, $plane_max_x, $plane_max_y, $rand_min_x, $rand_min_y, $rand_max_x, $rand_max_y , $sky_xpos, $sky_xneg, $sky_ypos, $sky_yneg, $sky_zpos, $sky_zneg, $smallobj, $mediumobj ,$bigobj) 
	{			
				if($rand_min_x == NULL || $rand_max_x == NULL || $rand_min_y == NULL || $rand_max_y == NULL){
					$rand_min_x = $plane_min_x;
					$rand_max_x = $plane_max_x;
					$rand_min_y = $plane_min_y;
					$rand_max_y = $plane_max_y;
				}

				$data = array(
				   'name' => $name ,
				   'plane' => $plane,
				   'plane_min_x' => $plane_min_x,
				   'plane_min_y' => $plane_min_x,
				   'plane_max_x' => $plane_max_x,
				   'plane_max_y' => $plane_max_x,
				   'rand_min_x' => $rand_min_x,
				   'rand_min_y' => $rand_min_x,
				   'rand_max_x' => $rand_max_x,
				   'rand_max_y' => $rand_max_x,
				   'sky_xpos' => $sky_xpos,
				   'sky_xneg' => $sky_xneg,
				   'sky_ypos' => $sky_ypos,
				   'sky_yneg' => $sky_yneg,
				   'sky_zpos' => $sky_zpos,
				   'sky_zneg' => $sky_zneg,
				   'smallobj' => $smallobj,
				   'mediumobj' => $mediumobj,
				   'bigobj' => $bigobj
				);

				$q = $this->db->insert('worlds', $data);
				return $q;
			}

		/**
	 * Gets the plane texture, plane-coordinates and random-coordinates of a specific world
	 *
	 * @param  int	$id			The id of the world
	 * @return array	
	 */ 
	function get_plane($id)
	{
		$this->db->select("plane, plane_min_x, plane_min_y, plane_max_x, plane_max_y, rand_min_x, rand_min_y, rand_max_x, rand_max_y");
		$this->db->from("worlds");
		$where = "`id` = '$id'"; 
		$this->db->where($where);
		$query = $this->db->get();
		return $query->result();
	}
}