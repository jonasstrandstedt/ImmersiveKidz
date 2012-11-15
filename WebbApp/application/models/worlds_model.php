<!--
* @brief    Databasefunctions for the worlds-table.
*
* @details  add_world($name, $floor, $sky_xpos, $sky_xneg, $sky_ypos, $sky_yneg, $sky_zpos, $sky_zneg, $smallobj, $mediumobj ,$bigobj)  , adds a world to the database.
*			
*
* @author   Viktor Fröberg, vikfr292@student.liu.se  (?)
* @author   Belinda Bernfort, belbe886@student.liu.se
* @date     November 14, 2012
* @version  1.0
*    
-->

<?php
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
	 * @param  string	$floor			The url of the floor texture image
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

	function add_world($name, $floor, $sky_xpos, $sky_xneg, $sky_ypos, $sky_yneg, $sky_zpos, $sky_zneg, $smallobj, $mediumobj ,$bigobj) 
	{
				$data = array(
				   'name' => $name ,
				   'floor' => $floor,
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
	}