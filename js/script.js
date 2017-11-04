var socket = io();

socket.on('hello', function () {
	socket.emit('world');
});

$(function () {
    $('form').submit(function(){
        if(leadValue()){
            alert("正しいTwitterIDを入力してください。")
        } else {
            showLoading();
            socket.emit('twitterid', $('#id').val());
            $('#id').val('');
        }
		return false;
    });
});

$(function() {
    $('#id').on('keydown keyup keypress change', function() {
        if ( $(this).val().length > 0 && !leadValue() ) {
            $('#submit').prop('disabled', false);
        } else {
            $('#submit').prop('disabled', true);
        }
    });
});

function showLoading(){
    var twid = document.getElementById("id").value;
    document.getElementById("loading").style.display = "block";
    document.getElementById("id").placeholder = twid;
    document.getElementById("id").disabled = true;
}

function leadValue(){
    var twid = document.getElementById("id").value;
    if(twid.match(/@|\s/)) {
        $('#atmark').addClass('spin');
        $('#atmarks').addClass('flash');
        setTimeout(stopSpin, 1400);
        return 1;
    } else {
        return 0;
    }
}

function stopSpin(){
    $('#atmark').removeClass('spin');
    $('#atmarks').removeClass('flash');
}