// Put all onload AJAX calls here, and event listeners
$(document).ready(function() {
    // On page-load AJAX Example
    let minSal;
    let maxSal;
    let minDate;
    let maxDate; 
    let provinces;
    let graphType;
    let tempJSON;
    let sendJSON;
    let testValues;
    let returnJSON;

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
            $('#blah').html("On page load, Received string '"+JSON.stringify(data)+"' from server");
            //We write the object to the console to show that the request was successful
            console.log(JSON.stringify(data)); 

        },
        fail: function(error) {
            // Non-200 return, do something with error
            console.log(error); 
        }
    });

    // Event listener form replacement example, building a Single-Page-App, no redirects if possible
    $('#someform').submit(function(e){
        $('#blah').html("Callback from the form");
        e.preventDefault();
        //Pass data to the Ajax call, so it gets passed to the 
        $.ajax({});
    });

    $('#SubmitButton').click(function(event){

        minSal = $('#minSal').val();
        maxSal = $('#maxSal').val();
        minDate = $('#startYear').val();
        maxDate = $('#endYear').val(); 
        provinces = $('#provinces').val(); 
        graphType = document.querySelector('input[type=radio]:checked').value;
        /*
        console.log(minSal);
        console.log(maxSal);
        console.log(minDate);
        console.log(maxDate);
        for(i = 0; i < provinces.length; i++)
        {

console.log(provinces[i]);


        }
        
        console.log(graphType);
       
console.log("HERE");*/
        tempJSON = {minSalary:$('#minSal').val(),maxSalary:$('#maxSal').val(),minDates:$('#startYear').val(),maxDates:$('#endYear').val(),province:$('#provinces').val()}

        $.ajax({
        type: 'post',            //Request type
        dataType: 'JSON',       //Data type - we will use JSON for almost everything 
        url: '/queryDatabase',   //The server endpoint we are connecting to
        data:JSON.stringify(tempJSON),
        success: function (data) {
 console.log("Got values"); 
        testValues = data.values;

            /*  Do something with returned object
                Note that what we get is an object, not a string, 
                so we do not need to parse it on the server.
                JavaScript really does handle JSONs seamlessly
            */
            //We write the object to the console to show that the request was successful
            console.log(testValues); 
            console.log(data);
 console.log("RETURN"); 

        },
        fail: function(error) {
            // Non-200 return, do something with error
            console.log(error); 
        }
        });


    });


});