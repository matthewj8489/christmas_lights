$fn=50;
e=0.1;

circuit_board_x=30;
circuit_board_y=70;

hole_radius=7;
wire_hole_r=3;

thickness=2;
case_sz_x=circuit_board_x+20;
case_sz_y=circuit_board_y+20;
case_sz_z=20;

out_case_sz_x=case_sz_x+thickness*2;
out_case_sz_y=case_sz_y+thickness*2;
out_case_sz_z=case_sz_z+thickness*2;

hole_one_y=out_case_sz_y-hole_radius-10;
hole_two_y=hole_one_y-hole_radius*2-10;

overlap_lip_h=2;

difference() {
    full_case();
    
    translate([-e,-e,out_case_sz_z/2])
    cube([out_case_sz_x+2*e,out_case_sz_y+2*e,out_case_sz_z+e]);
}


module full_case() {
    difference() {
        cube([out_case_sz_x,out_case_sz_y, out_case_sz_z]);
        
        // get rid of top half of case //translate([-e,-e,out_case_sz_z/2-e])
        //cube([out_case_sz_x+2*e,out_case_sz_y+2*e,out_case_sz_z]);
        
        // hollow out the case
        translate([thickness,thickness,thickness])
        cube([case_sz_x, case_sz_y, case_sz_z]);
        
        // Add the top hole for the power switch
        translate([out_case_sz_x/2, out_case_sz_y+e, out_case_sz_z/2])
        rotate([90,0,0])
        cylinder(h=thickness+2*e, r=hole_radius);
        
        // Add the side hole for the first button
        translate([-e, hole_one_y, out_case_sz_z/2])
        rotate([0,90,0])
        cylinder(h=thickness+2*e, r=hole_radius);
        
        // Add the side hole for the second button
        translate([-e, hole_two_y, out_case_sz_z/2])
        rotate([0,90,0])
        cylinder(h=thickness+2*e, r=hole_radius);
        
        // Add a hole for the wires
        translate([out_case_sz_x/2, thickness+e, out_case_sz_z/2])
        rotate([90,0,0])
        cylinder(h=thickness+2*e, r=wire_hole_r);
    }
    
}