var width = 960,
	height = 600;
	
var svg = d3.select("svg")
	.attr("width", width)
	.attr("height", height)
	.attr("fill", "none")
	.attr("stroke", "#000");
	
var projection = d3.geoAlbersUsa()
	.translate([width/2, height/2])
	.scale(1275);
var path = d3.geoPath()



d3.json("https://d3js.org/us-10m.v1.json", function(error, us) {
	if (error) throw error;

	svg.append("path")
		.attr("d", path(topojson.feature(us, us.objects.states)));
});
	
d3.json("https://gist.githubusercontent.com/Miserlou/c5cd8364bf9b2420bb29/raw/2bf258763cdddd704f8ffd3ea9a3e81d25e2c6f6/cities.json", function(error, file) {
	if (error) return console.error(error);
	
	var coordinates = function(city) {
		return [city.longitude, city.latitude];
	};
	
	var radius = function(city) {
		return Math.sqrt(parseInt(city.population) / (1000000 * 3.14));
	};
	
	var color = function(city) {
		var growth = parseFloat(city.growth_from_2000_to_2013);
			r = 0, g = 0, b = 0;
		if (growth > 0) {
			if (growth > 30) growth = 30;
			b = Math.round(255 - (255 * growth / 30));
			g = 255 - b;
		}
		else {
			if (growth < -10) growth = -10;
			b = Math.round(255 - (255 * growth / -10));
			r = 255 - b;
		}
		return "rgb(" + r + "," + g + "," + b + ")";
	};
	
	var name = function(city) {
		return city.city + ", " + city.state;
	};
	
	svg.selectAll("circle")
		.data(file).enter()
		.append("circle")
			.attr("cx", function(d) {return projection(coordinates(d))[0];})
			.attr("cy", function(d) {return projection(coordinates(d))[1];})
			.attr("r", function(d) {return 25*radius(d) + 'px';})
			.attr("fill", function(d) {return color(d);});
	svg.selectAll("circle")
		.data(file).enter()
		.append("text")
			.attr("dy","0.35em")
			.text(function(d) {return name(d)});
});