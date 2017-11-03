var socket = io();

socket.on('hello', function () {
socket.emit('world');
});

$(function () {
    $('form').submit(function(){
		socket.emit('twitterid', $('#id').val());
		$('#id').val('');
		return false;
    });
});