
use std::io::*;

fn main() {
    let mut buf = String::new();
    stdin().read_line(&mut buf).unwrap();

    let mut max = '\0';
    let mut count = 0;
    let mut data = [0; 200];

    for c in buf.chars() {
        data[c as usize] += 1;

        if count < data[c as usize] {
            count = data[c as usize];
            max = c;
        }
    }

    println!("max is {}, count = {}", max, count);
}
