$fn=50;
e=0.1;

body_size=40;
thickness=1.5;
hole_size=12.5;
box_height=3;

rotate(a=[0,180,0])
translate([0,0,-(body_size)])
difference() {
    cube(body_size);

    translate([thickness, thickness, thickness])
    cube(body_size-thickness*2);
    
    translate([-e,-e,-e])
    cube([body_size+e*2, body_size+e*2, body_size-box_height+e]);
    
    translate([body_size/2,body_size/2,body_size-thickness-e])
    cylinder(h=thickness*2+e*2, r=hole_size/2);
}