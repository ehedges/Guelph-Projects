// Put all onload AJAX calls here, and event listeners
$(document).ready(function() {

    $('#StatusList').append('<li>Welcome to VCard!</li>');
		
    // On page-load AJAX Example
	let uploadString;
	let fileNameString;
	let returnValue;
	let arrayFileNames;

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
		$('#submitButton').attr('disabled','disabled');
		arrayFileNames = data.fileNames.split(",");
		let arrayfileLengths = data.fileLengths.split(",");
		let arrayfileNames = data.stringNames.split(",");
		let i = null;

		if(arrayFileNames[0] == "")
		{

			uploadString = '<li>No files on the server.</li>'
			$('#StatusList').append(uploadString);

		}

		$('#fileList').append('<option disabled selected value> -- select an option -- </option>');
	
		for(i in arrayFileNames)
		{
			//Drop down menu
			fileNameString = arrayFileNames[i];
			uploadString =  '<option value="';
			uploadString = uploadString + fileNameString;
			uploadString = uploadString + '" id ="';
			uploadString = uploadString + fileNameString;
			uploadString = uploadString + '">'
			uploadString = uploadString + fileNameString;
			uploadString = uploadString + '</option>';

			$('#fileList').append(uploadString);
			//FIle Table
		        uploadString = '<tr><td> <a href="/uploads/'+ fileNameString+'">'+fileNameString+'</a></td><td>';
			uploadString += arrayfileNames[i];
			uploadString += '</td><td>';
			uploadString += arrayfileLengths[i];
			uploadString +=	'</td></tr>';

			$('#FileTable').append(uploadString);
			//$('#fileList').val() = 

		}

            //We write the object to the console to show that the request was successful
                console.log(data.fileNames); 
		
        },
        fail: function(error) {
            // Non-200 return, do something with error
	    uploadString = '<li>Failed to load server.</li>'
	    $('#StatusList').append(uploadString);
            console.log(error); 
        }
    });
    // Event listener form replacement example, building a Single-Page-App, no redirects if possible
	$('#FileTable').click(function(event){
	
		uploadString = '<li>Downloaded '+  $(event.target).text() +'</li>';
		$('#StatusList').append(uploadString);
		
	});

	$('#clearButton').click(function(){
		$('#StatusList').empty();
		alert("Cleaned Status Panel"); 
		
	});

	$('#uploadFile').change(function(){

		$('#submitButton').removeAttr('disabled');

	 });

	$('#fileList').change(function(){

		let selectValue;
		let JSONstring;
		let JSONParse;
		let propertyCount;
		let returnJSON;
		let toSend = {fileName:$('#fileList').val()};

		uploadString = '<li>Viewing '+  $('#fileList').val() +'</li>';
		$('#StatusList').append(uploadString);

//		selectValue = $('#fileList').val();
		console.log(toSend.fileName);
		let JSONSending = JSON.stringify(toSend);
	   	$.ajax({
		type: 'post',            //Request type
		dataType: 'JSON',       //Data type - we will use JSON for almost everything 
		url: '/fileTableData',   //The server endpoint we are connecting to
		data:JSON.stringify(toSend),
		success: function (files) {
		    /*  Do something with returned object
		        Note that what we get is an object, not a string, 
		        so we do not need to parse it on the server.
		        JavaScript really does handle JSONs seamlessly
		    */
				JSONstring = files.values;
				console.log(JSONstring);
								console.log("MAIN"+JSONstring);
				if(JSONstring == '{}')
				{
				console.log(JSONstring);
				    $('#StatusList').append('<li>Invalid File ' + selectValue +'server.</li>');

				}
	 
		$('#CardTable').empty();

		uploadString = '<tr><th>Property Number</th><th>Property Group</th><th>Property Name</th> <th>Property Values</th></tr>';
		$('#CardTable').append(uploadString);
		
		let JSONarray = JSONstring.split("~");

		propertyCount = 0;

		let i;
		for(i = 0; i < JSONarray.length;i++)
		{
			
			propertyCount++;
			console.log(JSONarray[i]);

			if(JSONarray[i] == 'A')
			{

				uploadString = '<tr><td>'+ propertyCount+ '</td><td></td><td>Anniversary</td><td>';

				i++;			

				JSONParse = JSON.parse(JSONarray[i]);
				if(JSONParse.isText == true)
				{

					uploadString += JSONParse.text; 

				}
				else
				{

					uploadString += 'Date :' + JSONParse.date + ' Time : ' +JSONParse.time;
					if(JSONParse.isUTC ==  true)
					{
					
						uploadString += 'Z'

					}

					uploadString +=  '</td></tr>';

				}

			}
			else if(JSONarray[i] == 'B')
			{

				uploadString ='<tr><td>'+ propertyCount+ '</td><td></td><td>Birthday</td><td>';

				i++;			

				JSONParse = JSON.parse(JSONarray[i]);
				if(JSONParse.isText == true)
				{

					uploadString += JSONParse.text; 

				}
				else
				{

					uploadString += 'Date :' + JSONParse.date + ' Time : ' +JSONParse.time;
					if(JSONParse.isUTC ==  true)
					{
					
						uploadString += 'Z'

					}

					uploadString +=  '</td></tr>';

				}
			}
			else
			{
				console.log('HERER');
				JSONParse = JSON.parse(JSONarray[i]);				
				uploadString = '<tr><td>' + propertyCount + '</td><td>' + JSONParse.group + '</td><td>' + JSONParse.name + '</td> <td>' + JSONParse.values + '</td></tr>';
				console.log(uploadString);
				console.log(JSONParse.group);
				console.log(JSONParse.name);
				console.log(JSONParse.values);

			}
			
			$('#CardTable').append(uploadString);
		}
		    //We write the object to the console to show that the request was successful
		
		},
		fail: function(error) {
		    // Non-200 return, do something with error
		    uploadString = '<li>Failed to load' + selectValue +'.</li>'
		    $('#StatusList').append(uploadString);
		    console.log(error); 
		}
	    });


	});


});
