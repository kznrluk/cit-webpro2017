var socket = io();

socket.on('hello', function () {
	socket.emit('world');
});

$(function () {
    $('form').submit(function(){
        showLoading();
		socket.emit('twitterid', $('#id').val());
        $('#id').val('');
		return false;
    });
});

function showLoading(){
    twid = document.getElementById("id").value;
    document.getElementById("loading").style.display = "block";
    document.getElementById("id").placeholder = twid;
    document.getElementById("id").disabled = true;
    
}