
// import node modules
var express = require('express');
var bodyParser = require('body-parser');
var handlebars = require('express-handlebars').create({defaultLayout:'main'});

// create express application for handling requests
var app = express();

// assign handlebars as engine for rendering to page
app.engine('handlebars', handlebars.engine);
app.set('view engine', 'handlebars');

// assign server port
app.set('port', 3000);

// parse app response as encoded URL or JSON format
app.use(bodyParser.urlencoded({extended:false}));
app.use(bodyParser.json());

// Home page
app.get('/', function(req, res){
	res.render('home');
});

// HTML page
app.get('/html', function(req, res){
	res.render('html');
});

// JavaScript page
app.get('/javascript', function(req, res){
	res.render('javascript');
});

// D3.JS page
app.get('/d3', function(req, res){
	res.render('d3');
});

// Map page
app.get('/map', function(req, res){
	res.render('map');
});

// Data page
app.get('/data', function(req, res){
	res.render('data');
});

// Final page
app.get('/final', function(req, res){
	res.render('final');
});

// Handle 404 Error (Address not found)
app.use(function(req,res){
	res.status(404);
	res.render('404');
});

// Handle 500 Error (Server error)
app.use(function(req,res){
	console.error(err.stack);
	res.type('plain/text');
	res.status(500);
	res.render('500');
});

app.listen(app.get('port'), function(){
	console.log('Express started on http://localhost:' + app.get('port') + '; press Ctrl-C to terminate.');
});