<?php
// You can simulate a slow server with sleep
// sleep(2);

session_start();

if(!isset($_SESSION['favorites'])) { $_SESSION['favorites'] =[];}
// check if the request is an ajax request
function is_ajax_request(){
	return isset($_SERVER['HTTP_X_REQUESTED_WITH']) && 
			$_SERVER['HTTP_X_REQUESTED_WITH'] == 'XMLHttpRequest';
}

if ( !is_ajax_request() ) { exit;}

$raw_id = isset($_POST['id']) ? $_POST['id'] : '';

	// echo 'true';
	// exit;

if(preg_match("/blog-post-(\d+)/", $raw_id, $matches))
{
	$id = $matches[1];
	// check if the id is already in the sesssion (or database)
	if(in_array($id, $_SESSION['favorites']))
	{
		// is the id is not in the session then append it
		$elem_idx = array_search($id, $_SESSION['favorites'] );
		// remove the id form the session
		//            array                 start index to remove   // length to remove
		array_splice( $_SESSION['favorites'], $elem_idx           ,   1);
	}

	echo 'true';
}
else
{

	echo 'false';
}


?>
