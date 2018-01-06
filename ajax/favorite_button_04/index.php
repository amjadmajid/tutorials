<?php
/* The overall idea
------------------------*/
/*
 * When a favorite button is clicked, the `id` of the clicked blog is
 * sent to the sever to be saved in the database ( it will be saved in 
 * a session in this example). Furthermore, the CSS of this blog will be 
 * modified to highlight that this blog is favorited. 
 */


?>
<?php
//We are using sessions to simulate the functionality of a database
	session_start();
	var_dump($_SESSION['favorites']);

	if(!isset($_SESSION['favorites'])) {$_SESSION['favorites'] = []; }
	// check if a blog id is in the session (or in database in real world application)
	// is_favorite returns `true` if a blog id is in the favorites session
	function is_favorite($id)
	{ 
		return in_array($id, $_SESSION['favorites']);
	}
?>

<!doctype html>
<html lang="en">
	<head> 
		<meta charset="set-8">
		<title> Asynchronous Button</title>
		
		<style>

			.favorite-button{
				display: inline;
				font-weight: bold;
				color: green;
			}
			.unfavorite-button{
				display: none;
				font-weight: bold;
				color: red;
			}
			.favorite .favorite-button{
				display: none;
			}
			.favorite .unfavorite-button{
				display: inline;
			}


			/* an element with fav-icon class will not be displayed */
			.fav-icon{
				color:red;
				float:right;
				font-size:30px;
				display:none;
			}
			/* an element with fav icon class whose parent element has a favorite class will
 			 * be displayed (overriting the default behavior)*/
			.favorite .fav-icon{
				display:block;
			}
		div{
			width: 800px; 
			border: 1px solid grey;
			margin-bottom:5px;
			padding:10px;
			}
		</style>
	
	</head>
<body>
<div id="blog-post-101" class="blog-post <?php if(is_favorite(101)){echo ' favorite';} ?> ">
		<span class='fav-icon'> &hearts;</span>
		<h3> Blog post 101</h3>
		<p> Lorem ipsum dolor sit amet, consectetur adipisicing elit. Qui dicta minus molestiae vel beatae natus eveniet ratione temporibus aperiam harum alias officiis assumenda officia quibusdam deleniti eos cupiditate dolore doloribus!</p>
		<button class="favorite-button"> Favorite</button>
		<button class="unfavorite-button"> Unfavorite</button>
	</div>
<div id="blog-post-102" class="blog-post <?php if(is_favorite(102)){echo ' favorite';} ?> ">
		<span class='fav-icon'>&#10029;</span>
		<h3> Blog post 102</h3>
		<p> Lorem ipsum dolor sit amet, consectetur adipisicing elit. Qui dicta minus molestiae vel beatae natus eveniet ratione temporibus aperiam harum alias officiis assumenda officia quibusdam deleniti eos cupiditate dolore doloribus!</p>
		<button class="favorite-button"> Favorite</button>
		<button class="unfavorite-button"> Unfavorite</button>
	</div>

</body>
<script>
	// Add event listener to all the favorite buttons
	var buttons = document.getElementsByClassName('favorite-button');
	for(i=0; i < buttons.length; i++){
		// When a favorite button is clicked the favorite function is called.
		buttons.item(i).addEventListener('click', favorite);
		console.log(i);
	}


	// Add event listener to all the unfavorite buttons
	var unfav_buttons = document.getElementsByClassName('unfavorite-button');
	for(i=0; i < unfav_buttons.length; i++){
		// When a favorite button is clicked the favorite function is called.
		unfav_buttons.item(i).addEventListener('click', unfavorite);
	}

	function favorite(){
		// get access to the parent node of the clicked button
		var parent = this.parentElement;
		// Create XMLHttpRequest object
		var xhr = new XMLHttpRequest();
		// Use the `post` method since this action will do some changes on the server side
		// if `get` request is needed then the parameters would be sent as a URL parameters: 
		// Example, xhr.open('get', 'favorite.php?id=5', true);
		// The true indicate that this is an asychronous request. 
		xhr.open('POST', 'favorite.php', true);
		//Tell the sever that this is a form data, which will be passed as an arguments to the send function. This line won't be need if this was a `get` request
		xhr.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
		// send additional header information to check if the request is form ajax 
		xhr.setRequestHeader('X-Requested-With', 'XMLHttpRequest');
		// the state if the request can be in one of four states
		// 1 the request is opened
		// 2 the request is sent
		// 3 we started to receive data form the server
		// 4 data reception is completed
		xhr.onreadystatechange = function(){
			// check the state of the request and the status sent back by the http header
			if(xhr.readyState == 4 && xhr.status == 200){
				var result = xhr.responseText;
				console.log('Result: '+ result);
				if(result == 'true'){
						// add a class to the parent html element
						parent.classList.add('favorite');
				}
			}
		};
	// send the data as send arguments
	xhr.send("id=" + parent.id);
	}


	function unfavorite(){
		var parent = this.parentElement;
		var xhr = new XMLHttpRequest();
		xhr.open('POST', 'unfavorite.php', true);
		xhr.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
		xhr.setRequestHeader('X-Requested-With', 'XMLHttpRequest');
		xhr.onreadystatechange = function(){
			if(xhr.readyState == 4 && xhr.status == 200){
				var result = xhr.responseText;
				console.log('Result: '+ result);
				if(result == 'true'){
						// remove a class to the parent html element
						parent.classList.remove('favorite');
				}
			}
		};
	xhr.send("id=" + parent.id);
	}

</script>

</html>


















