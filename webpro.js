function response(req, res) {
    function execpuzzle(){
        exec('./puzzle.exe', function(err, stdout, stderr){
            if (err){
                console.log(err);
                res.writeHead(200,{'Content-type': 'text/plain'});
                res.write(err);
                res.end();
            } else {
                res.writeHead(200, {'Content-type': 'text/html'});
                res.write(stdout);
                res.end();
            }
        });
    }
    function responseHTML(err, html) {
        if (err) {
            res.writeHead(404, {'Content-type': 'text/plain'});
            res.write('File not found.');
            res.end();
        } else {
            res.writeHead(200, {'Content-type': 'text/html'});
            res.write(html);
            res.end();
        }
    }
    execpuzzle();
}
   
var http = require('http');
var fs = require('fs');
var server = http.createServer();
var exec = require('child_process').exec;

server.on('connection', function(connection){
    console.log('Connected.');
});

server.on('request', response);
server.listen(1234);
console.log('server started.');