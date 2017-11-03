var socket = io.connect('http://localhost:3000');

socket.on('hello', function (data) {
    socket.emit('world');
});

function pushplay(){
	io.emit("pushplay");
}
var par = 0;
function prog1(){
		par = par + 10;
		$('.progress-bar').css('width', par + '%');
}
function comp(){
	jumpPage();
}
function jumpPage() {
	var url = './puzzle.cgi?' + document.form.id.value
	location.href = url;
	return false;
}
function postdata(){
	var value = document.form.id.value;
	var form = document.createElement('form');
	form.method = 'POST';
	form.action = './wait';
	form.target = 'iframe';
	var reqid = document.createElement('input');
	reqid.name = 'id';
	reqid.value = value;
	form.appendChild(reqid);
	document.body.appendChild(form);
	form.submit();
    return false;
}
			// あとで直す
			function wait1sec(){
				postdata();
				var count = setInterval(function(){
					prog1();
					if(par == 100){
						clearInterval(count);
						setTimeout(comp, 650);
					}}, 150);
			}