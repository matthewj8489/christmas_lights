$fn=50;
e=0.1;

include <latches.scad>

clip();

difference() {
    cube(10);
    
    clipHole();
}