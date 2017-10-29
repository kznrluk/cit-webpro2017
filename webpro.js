function response(req, res) {
    function execpuzzle(){
        exec('puzzle', function(error, stdout, stderr) {
            if (error != null) {
                console.log(error);
            }
            console.log('Exec puzzle.exe');
            res.writeHead(200,  {'Content-Type': 'text/html'});
            res.write(stdout);
            res.end();
        });
    }
    function responseCSS(err, css){
        res.writeHead(200, {'Content-Type': 'text/css'});
        res.write(css);
        res.end();
    }
    function responseIMG(err, png){
        res.writeHead(200, {'Content-Type': 'image/png'});
        res.write(png);
        res.end();
    }

    console.log('Requested: ' + req.url);

    if(req.url == '/puzzle'){
        execpuzzle();
    } else if(req.url.indexOf('.css') != -1) {
        fs.readFile('.'+req.url, 'utf-8', responseCSS);
    } else if(req.url.indexOf('.png') != -1) {
        fs.readFile('.'+req.url, responseCSS);
    }
}

var http = require('http');
var server = http.createServer();
var fs = require('fs');
var exec = require('child_process').exec;
var iconv = require('iconv-lite');
server.on('connection', function(){
    console.log('Connected.');
});

server.on('request', response);
server.listen(3000);
console.log('Server started.');