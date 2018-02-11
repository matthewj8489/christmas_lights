$fn=50;
e=0.1;

include <latches.scad>

thickness=2;
case_sz_x=100;
case_sz_y=90;
//case_sz_z=trigger_switch_h+brd_peg_h;
case_sz_z=37+5;

trigger_switch_h=37;
arduino_h=18;

out_case_sz_x=case_sz_x+thickness*2;
out_case_sz_y=case_sz_y+thickness*2;
out_case_sz_z=case_sz_z+thickness*2;

hole_radius=7;
wire_hole_r=5;

//button1_x=25;
button1_x=out_case_sz_x/4+thickness;
button1_y=out_case_sz_y/2;

//button2_x=50;
button2_x=button1_x+out_case_sz_x/4;
button2_y=out_case_sz_y/2;

//switch_button_x=90;
switch_button_x=button2_x+out_case_sz_x/4;
switch_button_y=out_case_sz_y/2;

case_top_height=thickness;

clip1_x=out_case_sz_x/4;
clip2_x=out_case_sz_x*0.75;
clip1_y=0;
clip2_y=out_case_sz_y;

// clip params
lip_depth=thickness-0.5;
clip_height=8;

// circuit board params
brd_dist_from_box=5;
brd_peg_orig=[thickness+brd_dist_from_box,thickness+brd_dist_from_box,thickness];

brd_peg_r=1;
brd_stdoff_h=3;
brd_peg_h=8;

brd_peg_dist_x=26;
brd_peg_dist_y=66;

// arduino uno board params
ard_peg_r=1.5;
ard_stdoff_h=3;
ard_peg_h=8;

ard_dist_from_brd=7;
usb_dist_from_ard=7;
ard_dist_from_box=15.3+usb_dist_from_ard+3;
ard_peg_orig=brd_peg_orig+[brd_peg_dist_x,0,0]+[ard_dist_from_brd+2.5+ard_peg_r,ard_dist_from_box,0];
ard_pwr_peg_x=5.1+27.9+15.2;

ard_peg_back1_x=15.2;
ard_peg_back1_y=50.8;

ard_peg_back2_x=15.2+27.9;
ard_peg_back2_y=50.8;

// arduino power wire hole
//ard_wire_hole_x=ard_pwr_peg_x-6;
//ard_wire_hole_x=(ard_peg_orig[0]-2.6)+40.7;
ard_wire_hole_x=ard_peg_orig[0]+ard_peg_back2_x;
//ard_wire_hole_z=thickness+ard_stdoff_h+10.9/2;
ard_wire_hole_z=thickness+ard_stdoff_h+8;

ard_pwr_cord_r=5;
ard_wire_hole_r=ard_pwr_cord_r+2;

// ard power cord: ([position],[dimensions])
//[40.7, -1.8, 0], [9.0, 13.2, 10.9]
// pwr diameter = 10
// height of pwr con = 13
//4, 16

//usb_x=9;
//usb_y=7;

// board wire hole
brd_wire_hole_x=brd_peg_orig[0]+brd_peg_dist_x+ard_dist_from_brd+2;



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
        //translate([out_case_sz_x/2, thickness+e, wire_hole_r+thickness])
        translate([brd_wire_hole_x, thickness+e, wire_hole_r+thickness])
        rotate([90,0,0])        
        cylinder(h=thickness+2*e, r=wire_hole_r);
        
        //translate([out_case_sz_x*0.75, thickness+e, wire_hole_r+thickness])
        translate([ard_wire_hole_x, thickness+e, ard_wire_hole_z])
        rotate([90,0,0])        
        cylinder(h=thickness+2*e, r=ard_wire_hole_r);
        
    }
       
    // Circuit board standoffs
    translate(brd_peg_orig)
    peg_standoff(brd_peg_r,brd_stdoff_h,brd_peg_h);
    
    translate(brd_peg_orig+[brd_peg_dist_x,0,0])
    peg_standoff(brd_peg_r,brd_stdoff_h,brd_peg_h);
    
    translate(brd_peg_orig+[0,brd_peg_dist_y,0])
    peg_standoff(brd_peg_r,brd_stdoff_h,brd_peg_h);
    
    translate(brd_peg_orig+[brd_peg_dist_x,brd_peg_dist_y,0])
    peg_standoff(brd_peg_r,brd_stdoff_h,brd_peg_h);

    // Arduino board standoffs
    translate(ard_peg_orig)
    peg_standoff(ard_peg_r,ard_stdoff_h,ard_peg_h);
    
    translate(ard_peg_orig+[ard_pwr_peg_x,0,0])
    peg_standoff(ard_peg_r,ard_stdoff_h,ard_peg_h);
    
    translate(ard_peg_orig+[ard_peg_back1_x,ard_peg_back1_y,0])
    peg_standoff(ard_peg_r,ard_stdoff_h,ard_peg_h);
    
    translate(ard_peg_orig+[ard_peg_back2_x,ard_peg_back2_y,0])
    peg_standoff(ard_peg_r,ard_stdoff_h,ard_peg_h);
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

module peg_standoff(peg_r, standoff_h, peg_total_h) {
    cylinder(r=peg_r+1, h=standoff_h);
    translate([0,0,standoff_h])
    cylinder(r=peg_r, h=peg_total_h-standoff_h);
}