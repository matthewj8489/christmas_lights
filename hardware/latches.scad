$fn=50;

//Create a clip that snapps into a clipHole
module clip(clipWidth = 5, clipDepth = 5, clipHeight = 5, lipDepth = 1.5, lipHeight = 3) {
	translate([-clipWidth/2,-(clipDepth-lipDepth),0]) rotate([90, 0, 90])
	linear_extrude(height = clipWidth, convexity = 10)
		polygon(	points=[	[0, 0], 
						[clipDepth - lipDepth, 0],
						[clipDepth - lipDepth, clipHeight - lipHeight],
						[clipDepth - 0.25, clipHeight - lipHeight],
						[clipDepth, clipHeight - lipHeight + 0.25],
						[clipDepth - lipDepth * 0.8, clipHeight],
						[(clipDepth - lipDepth) * 0.3, clipHeight] 
						], 
				paths=[[0,1,2,3,4,5,6,7]]
			);
}

//Hole for clip
module clipHole(clipWidth = 5, clipDepth = 5, clipHeight = 5, lipDepth = 1.5, lipHeight = 3, holeDepth = 5) {
	offset = 0.1;
	translate([-clipWidth/2,-(clipDepth-lipDepth),0])
	translate([-offset, clipDepth - lipDepth-offset, clipHeight - lipHeight - offset])
		cube( [clipWidth + offset * 2, holeDepth, lipHeight + offset * 2] );
}
