$fn=50;
e=0.1;

include <latches.scad>

thickness=5;
case_sz_x=120;
case_sz_y=80;
case_sz_z=40;

out_case_sz_x=case_sz_x+thickness*2;
out_case_sz_y=case_sz_y+thickness*2;
out_case_sz_z=case_sz_z+thickness*2;

hole_radius=7;
wire_hole_r=3;

button1_x=25;
button1_y=40;

button2_x=50;
button2_y=40;

switch_button_x=90;
switch_button_y=40;

case_top_height=20;

clip1_x=out_case_sz_x/4;
clip2_x=out_case_sz_x*0.75;
clip1_y=0;
clip2_y=out_case_sz_y;

// clip params
lip_depth=1.5;

top_case();

module bot_case() {
    difference() {
        full_case();

        translate([-e,-e,out_case_sz_z-case_top_height])
        cube([out_case_sz_x+2*e, out_case_sz_y+2*e, case_top_height+e]);
        
        translate([clip1_x, clip1_y, out_case_sz_z-case_top_height-7])
        clipHole(lipDepth=lip_depth);
    }

}

module top_case() {
    translate([0,out_case_sz_y,out_case_sz_z])
    rotate([180,0,0])
    difference() {
        full_case();
        
        translate([-e,-e,-e])
        cube([out_case_sz_x+2*e, out_case_sz_y+2*e, out_case_sz_z+e-case_top_height]);
    }

    translate([clip1_x, clip1_y+lip_depth, case_top_height])
    rotate([0,0,180])
    clip(lipDepth=lip_depth);

    translate([clip2_x, clip1_y+lip_depth, case_top_height])
    rotate([0,0,180])
    clip(lipDepth=lip_depth);

    translate([clip1_x, clip2_y-lip_depth, case_top_height])
    clip(lipDepth=lip_depth);

    translate([clip2_x, clip2_y-lip_depth, case_top_height])
    clip(lipDepth=lip_depth);
}


module full_case() {
    difference() {
        cube([out_case_sz_x,out_case_sz_y, out_case_sz_z]);
        
        // hollow out the case
        translate([thickness,thickness,thickness])
        cube([case_sz_x, case_sz_y, case_sz_z]);
        
        // Add the first button
        button_hole(hole_radius, button1_x, button1_y);
        
        // Add the second button
        button_hole(hole_radius, button2_x, button2_y);
        
        // Add the toggle switch button
        button_hole(hole_radius, switch_button_x, switch_button_y);
        
    }
}

module button_hole(holeRadius, holeX, holeY) {
    translate([holeX, holeY, out_case_sz_z-(thickness+e)])
    cylinder(h=thickness+2*e, r=holeRadius);
}