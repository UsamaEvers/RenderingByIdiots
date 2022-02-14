extern crate minifb;
use std::ops::Index;

use glam::{Vec2};
use minifb::{Key, Window, WindowOptions};

const WIDTH: usize = 500;
const HEIGHT: usize = 500;

//Make sure not to be cringe lmao
pub fn to_argb8(a: u8, r: u8, g: u8, b: u8) -> u32 {
    let mut argb: u32 = a as u32;
    argb = (argb << 8) + r as u32;
    argb = (argb << 8) + g as u32;
    argb = (argb << 8) + b as u32;
    argb
}
pub fn index_to_coords(p: usize, width: usize) -> (usize, usize){
    (p% width, p/width)
} 
pub fn edge_function_cw(v0: Vec2, v1: Vec2, p: Vec2) -> f32 {
    (p.x - v0.x) *(v1.y - v0.y) - (p.y - v0.y) *(v1.x - v0.x)
}
fn main() {
    let mut buffer: Vec<u32> = vec![to_argb8(255,0,0,0); WIDTH * HEIGHT];
    let mut window = Window::new(       "Test - ESC to exit",
        WIDTH,
        HEIGHT,       WindowOptions::default(),
    )
    .unwrap_or_else(|e| {
        panic!("{}", e);
    });

    // Limit to max ~60 fps update rate
    window.limit_update_rate(Some(std::time::Duration::from_micros(16600)));

    let triangle = [glam::vec2(100., 100.),glam::vec2(250., 400.),glam::vec2(400., 100.)];

    while window.is_open() && !window.is_key_down(Key::Escape) {
        for i in 0..buffer.len(){
            let coords = index_to_coords(i, WIDTH);
            let coords = glam::vec2(coords.0 as f32,coords.1 as f32);
            let m2= edge_function_cw(triangle[0], triangle[1], coords);
            let m1= edge_function_cw(triangle[2], triangle[0], coords);
            let m0= edge_function_cw(triangle[1], triangle[2], coords);
             if m0 > 0. && m1 > 0. && m2 > 0.
             {
               buffer[i] = to_argb8(255, (m2*255.) as u8, (m1*255.) as u8, (m0*255.) as u8);
             }
            
        }

        // We unwrap here as we want this code to exit if it fails. Real applications may want to handle this in a different way
        window
            .update_with_buffer(&buffer, WIDTH, HEIGHT)
            .unwrap();
    }
}