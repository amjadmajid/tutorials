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

if ( !is_ajax_request() ){exit;}
// extract $id
$raw_id = isset($_POST['id']) ? $_POST['id'] : '';
// use regular expration to extract the number of the id of the blog
// The numerical part will be stored in the $matches variable
if(preg_match("/blog-post-(\d+)/", $raw_id, $matches))
{
	$id = $matches[1];
	// check if the id is already in the sesssion (or database)
	if(!in_array($id, $_SESSION['favorites']))
	{
			// is the id is not in the session then append it
			$_SESSION['favorites'][] = $id;
	}	
	echo 'true';
}
else
{

	echo 'false';
}


?>
