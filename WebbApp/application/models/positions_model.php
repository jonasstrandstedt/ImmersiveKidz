<?php
/*
* @brief    Databasefunctions for the positions in the worlds table.
*
* @details  add_position($xval, $yval, $zval, $classification) , adds a world to the database.
*			
* @author   Belinda Bernfort, belbe886@student.liu.se
* @date     November 15, 2012
* @version  1.0
*/


class Positions_model extends CI_Model 
{

    function __construct()
    {
        // Call the Model constructor
        parent::__construct();
    }


	/**
	 * Adds a world to the database
	 *
	 * @param  string	$xval			The x value of the position
	 * @param  string	$yval			The y value of the position
	 * @param  string	$zval			The z value of the position
	 * @param  string	$classification	The classification of the position (water, grass, sky)	
	 * @return bool 	
	 */ 

	function add_position($xval, $yval, $zval, $classification) 
	{
				$data = array(
				   'xval' => $xval,
				   'yval' => $yval,
				   'zval' => $zval,
				   'classification' => $classification
				);
				$q = $this->db->insert('positions', $data);
				return $q;
			}
	}