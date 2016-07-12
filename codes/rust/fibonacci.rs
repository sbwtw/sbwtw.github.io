
use std::io;

fn fibonacci(index: i32) -> u64 {

    let mut a = 0;
    let mut b = 1;

    for _ in 0..index {
        let c = a + b;
        a = b;
        b = c;
    }

    a
}

fn main() {

    let mut input = String::new();
    let _ = io::stdin().read_line(&mut input);

    let num: i32 = input.trim_right().parse().unwrap();

    for i in 0..num {
        print!("{}, ", fibonacci(i));
    }
    print!("{}", fibonacci(num));
}
