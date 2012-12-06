<?php
/*
* @brief    Functions to generate resulting xml file.
*
* @details  
			function xml_dom() Creates a DOMDocument
*			create_xml($world, $images) Creates the xml structure
			get_xml_file($world, $images) Writes the generated structure to an xml file
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

    function create_xml($world, $images) 
    {
    	/***Variables world****/
    	$thePlane =  $world->plane;
		$theMinX_plane =  $world->plane_min_x;
		$theMinY_plane =  $world->plane_min_y;
		$theMaxX_plane =  $world->plane_max_x;
		$theMaxY_plane =  $world->plane_max_y;
		$theMinX_rand =  $world->rand_min_x;
		$theMinY_rand =  $world->rand_min_y;
		$theMaxX_rand =  $world->rand_max_x;
		$theMaxY_rand =  $world->rand_max_y;

		$this->load->helper('xml');

		/********XML*********/
    	/***World****/
		$dom = $this->xml_dom();
		$scene = xml_add_child($dom, "scene");
		$world = xml_add_child($scene, "world");
		$plane = xml_add_child($world, "plane");
		$texture = xml_add_child($plane, "texture", $thePlane);

		/***Size of world****/
		$size = xml_add_child($plane, "size");
		xml_add_attribute($size, 'minx', $theMinX_plane);
		xml_add_attribute($size, 'miny', $theMinY_plane);
		xml_add_attribute($size, 'maxx', $theMaxX_plane);
		xml_add_attribute($size, 'maxy', $theMaxY_plane);

		/***Size of area to place objects in****/
		$rand = xml_add_child($world, "rand");
		xml_add_attribute($rand, 'minx', $theMinX_rand);
		xml_add_attribute($rand, 'miny', $theMinY_rand);
		xml_add_attribute($rand, 'maxx', $theMaxX_rand);
		xml_add_attribute($rand, 'maxy', $theMaxY_rand);

		/***Models****/
		$models = xml_add_child($scene, "models");

		/***Billboards****/
		$billboards = xml_add_child($scene, "billboards");

		/***Illustrations, i.e. images draws by children****/
		$illustrations = xml_add_child($scene, "illustrations");
		foreach ($images as $image) {
			/***Item****/
			$item = xml_add_child($illustrations, "item");

			/***Artist name****/
			$name_artist = xml_add_child($item, "name_artist", $image->artist);

			/***Drawing name****/
			$name_drawing = xml_add_child($item, "name_drawing", $image->imgname);

			/***Description****/
			$description = xml_add_child($item, "description", $image->story);

			/***Animation****/
			$animation = xml_add_child($item, "animation");
			xml_add_attribute($animation, 'name', "");
			xml_add_attribute($animation, 'seed', "");

			/***Image (texture)****/
			$texture = xml_add_child($item, "texture", $image->imgouturl);

			/***Postition****/
			$pos = xml_add_child($item, "pos");
			xml_add_attribute($pos, 'x', $image->x_coord);
			xml_add_attribute($pos, 'y', $image->y_coord);
			xml_add_attribute($pos, 'z', $image->z_coord);

			/***Size****/
			$size = xml_add_child($item, "size");
			xml_add_attribute($size, 'x', "");
			xml_add_attribute($size, 'y', "");
		}

		return xml_print($dom, true);
	}


    function get_xml_file($world, $images) 
    {
    	$url = "uploads/out/result.xml";
    	file_put_contents($url, $this->create_xml($world, $images));
		return $url;

	}
}
