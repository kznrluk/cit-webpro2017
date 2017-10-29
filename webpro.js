function response(req, res) {
    function responseIndex(err, html){
        res.writeHead(200, {'Content-Type': 'text/html'});
        res.write(html);
        res.end();
    }
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
    function readUserMsg(){
        var body='';
        req.on('data', function (data) {
            body += data;
        });
        req.on('end',function(){
            var POST = qs.parse(body);
            if(Object.keys(POST).length != 1){
                console.log('Warn :与えられた値が不正です。')
            } else {
                console.log('Posted :' + POST.id);
                var url = 'http://furyu.nazo.cc/twicon/' + POST.id + '/original';
                var filetype = '';
                var imgtype + '';
                res.writeHead(200, {'Content-Type': 'text/html'});
                res.write(url);
                res.end();

                console.log('Getting Avater...')
                request(url, function(err, res, bod){
                    filetype = res.headers['content-type'];
                    if (filetype.indexOf('png') != -1){
                        imgtype = 'png';
                    } else if (filetype.indexOf('jpeg') != -1){
                        imgtype = 'jpg';
                    } else if (filetype.indexOf('bmp') != -1){
                        imgtype = 'bmp';
                    } else if (filetype.indexOf('gif') != -1){
                        imgtype = 'gif';
                    } else {
                        console.log('What is this type? :' + filetype);
                        return 1;
                    }
                    console.log('File-Type:' + filetype);
                    fs.createReadStream('./temp/profileimage.data').pipe(fs.createWriteStream('./images/'+POST.id+'.'+imgtype));
                    
                }).pipe(fs.createWriteStream('./temp/profileimage.data'));
            }
        });
    }

    console.log('Requested: ' + req.url);

    if(req.url == '/'){
        fs.readFile('./index.html', 'utf-8', responseIndex);
    } else if(req.url.indexOf('puzzle') != -1) {
        execpuzzle();
    } else if(req.url.indexOf('.css') != -1) {
        fs.readFile('.'+req.url, 'utf-8', responseCSS);
    } else if(req.url.indexOf('.png') != -1) {
        fs.readFile('.'+req.url, responseIMG);
    } else if(req.url.indexOf('/wait') != -1) {
        readUserMsg();
    }
}

var http = require('http');
var server = http.createServer();
var fs = require('fs');
var exec = require('child_process').exec;
var iconv = require('iconv-lite');
var qs = require('querystring');
var request = require('request');

server.on('connection', function(){
    console.log('Connected.');
});

server.on('request', response);
server.listen(3000);
console.log('Server started.');