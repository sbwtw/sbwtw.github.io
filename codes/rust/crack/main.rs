
use std::fs::File;
use std::path::Path;
use std::io::prelude::*;
use std::ops::Index;

fn main() {
    let mut data: [i32; 256] = [0; 256];
    let path = Path::new("../data/input_wikipedia_Circa-Survive");

    let file = match File::open(&path) {
        Err(e) => panic!("Err: {}", e),
        Ok(f) => f,
    };

    for c in file.bytes() {

        let c = c.unwrap();

        if (c >= 'a' as u8 && c <= 'z' as u8) ||
           (c >= 'A' as u8 && c <= 'Z' as u8) {
            //println!("{}", c & (0x20 ^ 0xff));
            let index: usize = c as usize & (0x20 ^ 0xff);
            data[index] += 1;
        }
    }

    println!("char,num");
    for i in 65..91 {
        println!("{},{}", i as u8 as char, data[i]);
    }
}
