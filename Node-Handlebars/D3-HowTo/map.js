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