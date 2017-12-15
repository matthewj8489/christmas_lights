$fn=50;
e=0.1;

body_size=40;
thickness=1.5;
hole_size=14;
box_height=3;

//rotate(a=[0,180,0])
//translate([0,0,-(body_size)])
//difference() {
//    cube(body_size);
//
//    translate([thickness, thickness, thickness])
//    cube(body_size-thickness*2);
//    
//    translate([-e,-e,-e])
//    cube([body_size+e*2, body_size+e*2, body_size-box_height+e]);
//    
//    translate([body_size/2,body_size/2,body_size-thickness-e])
//    cylinder(h=thickness*2+e*2, r=hole_size/2);
//}

//clip();
//
//difference() {
//    //translate([-5,0,0])
//    cube(10);
//    
//    clipHole();
//}

peg_standoff(1.5,3,5);

translate([7,0,0])
peg_standoff(1, 3, 5);

module peg_standoff(peg_r, standoff_h, peg_total_h) {
    cylinder(r=peg_r+1, h=standoff_h);
    translate([0,0,standoff_h])
    cylinder(r=peg_r, h=peg_total_h-standoff_h);
}

module full_box() {
    difference() {
        cube(10);
        
        translate([1,1,1])
        cube(8);
    }
}


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
