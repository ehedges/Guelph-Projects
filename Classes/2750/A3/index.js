// Put all onload AJAX calls here, and event listeners
$(document).ready(function() {
	var statusArray =  [""];
    // On page-load AJAX Example
    $.ajax({
        type: 'get',            //Request type
        dataType: 'json',       //Data type - we will use JSON for almost everything 
        url: '/someendpoint',   //The server endpoint we are connecting to
        success: function (data) {
            /*  Do something with returned object
                Note that what we get is an object, not a string, 
                so we do not need to parse it on the server.
                JavaScript really does handle JSONs seamlessly
            */

            //We write the object to the console to show that the request was successful
            console.log(data); 
        },
        fail: function(error) {
            // Non-200 return, do something with error
            console.log(error); 
        }
    });

    // Event listener form replacement example, building a Single-Page-App, no redirects if possible
    $('#someform').submit(function(e){
        e.preventDefault();
        $.ajax({});
    });

	$('#clearButton').click(function(){
		var x;
		for(x in 
		alert("Cleaned Status Panel"); 
	});


	$('#downloadButton').click(function(){
	    alert("Downloading"); 
	});

	$('#uploadButton').click(function(){
		var textBoxValue = $('#uploadTextField').val()
		var errorCode = "OK";
		alert("Uploading " + textBoxValue); 
		
		if(errorCode ==  "OK")
		{

			$("Status List").append("Succesful upload of" + textBoxValue);

		}
		else
		{

			$("Status List").append("Failed upload of" + textBoxValue);

		}

	});

});
