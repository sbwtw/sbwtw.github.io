
use std::io::*;

fn main() {

    let mut input = String::new();

    stdin().read_line(&mut input).unwrap();

    let data: Vec<&str> = input.split('/').collect();
    let a = data[0].trim().parse::<i32>().unwrap();
    let b = data[1].trim().parse::<i32>().unwrap();

    assert!(a == 2);

    let mut x: i32 = b / 2;
    let mut data = Vec::<(i32, i32)>::new();
    while x != b {
        let y: i32 = (x * b) / (2 * x - b);

        if y > 0 && x * b + y * b == 2 * x * y {
            data.push((x, y));
        }

        x += 1;
    }

    println!("total {} items:", data.len());
    for (x, y) in data {
        println!("1/{} + 1/{}", x, y);
    }
}
