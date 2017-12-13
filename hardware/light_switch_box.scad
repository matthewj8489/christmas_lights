$fn=50;
e=0.1;

include <latches.scad>

thickness=2;
case_sz_x=100;
case_sz_y=60;
case_sz_z=40;

out_case_sz_x=case_sz_x+thickness*2;
out_case_sz_y=case_sz_y+thickness*2;
out_case_sz_z=case_sz_z+thickness*2;

hole_radius=7;
wire_hole_r=3;

//button1_x=25;
button1_x=case_sz_x/4+thickness;
button1_y=out_case_sz_y/2;

//button2_x=50;
button2_x=button1_x+case_sz_x/4;
button2_y=out_case_sz_y/2;

//switch_button_x=90;
switch_button_x=button2_x+case_sz_x/4;
switch_button_y=out_case_sz_y/2;

case_top_height=thickness;

clip1_x=out_case_sz_x/4;
clip2_x=out_case_sz_x*0.75;
clip1_y=0;
clip2_y=out_case_sz_y;

// clip params
lip_depth=thickness-0.5;
clip_height=8;




//translate([0,out_case_sz_y+10,0])
//translate([0,out_case_sz_y,out_case_sz_z])
//rotate([180,0,0])
//top_case();

bot_case();




module bot_case() {
    difference() {
        full_case();

        translate([-e,-e,out_case_sz_z-case_top_height-e])
        cube([out_case_sz_x+2*e, out_case_sz_y+2*e, case_top_height+2*e]);
        
        // Clip Latches
        translate([clip1_x, clip1_y+thickness, out_case_sz_z-case_top_height])
        rotate([180,0,0])
        clipHole(lipDepth=lip_depth, clipHeight=clip_height);
        
        translate([clip2_x, clip1_y+thickness, out_case_sz_z-case_top_height])
        rotate([180,0,0])
        clipHole(lipDepth=lip_depth, clipHeight=clip_height);
        
        translate([clip1_x, clip2_y-thickness, out_case_sz_z-case_top_height])
        rotate([180,0,180])
        clipHole(lipDepth=lip_depth, clipHeight=clip_height);
        
        translate([clip2_x, clip2_y-thickness, out_case_sz_z-case_top_height])
        rotate([180,0,180])
        clipHole(lipDepth=lip_depth, clipHeight=clip_height);
        
        // Wire holes               
        translate([out_case_sz_x/4, out_case_sz_y+e, wire_hole_r+thickness])
        rotate([90,0,0])        
        cylinder(h=thickness+2*e, r=wire_hole_r);
        
        translate([out_case_sz_x*0.75, out_case_sz_y+e, wire_hole_r+thickness])
        rotate([90,0,0])        
        cylinder(h=thickness+2*e, r=wire_hole_r);
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

    // Clip Latches
    translate([clip1_x, clip1_y+thickness, case_top_height])
    rotate([0,0,180])
    clip(lipDepth=lip_depth, clipHeight=clip_height);

    translate([clip2_x, clip1_y+thickness, case_top_height])
    rotate([0,0,180])
    clip(lipDepth=lip_depth, clipHeight=clip_height);

    translate([clip1_x, clip2_y-thickness, case_top_height])
    clip(lipDepth=lip_depth, clipHeight=clip_height);

    translate([clip2_x, clip2_y-thickness, case_top_height])
    clip(lipDepth=lip_depth, clipHeight=clip_height);
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