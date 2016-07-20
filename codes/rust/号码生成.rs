
use std::io::*;

fn main() {

    let mut buf = String::new();

    let _ = stdin().read_line(&mut buf);
    let num = buf.trim().parse::<usize>().unwrap();

    buf.clear();
    let _ = stdin().read_line(&mut buf);
    let length = buf.trim().parse::<usize>().unwrap();

    let mut data: Vec<Vec<usize>> = Vec::new();

    for i in 1..(num + 1) {
        data.push(vec![i]);
    }

    while !data.is_empty() {
        let item = data.remove(0);

        if item.len() == length {
            for i in item {
                print!("{} ", i);
            }
            print!("\n");
        } else {
            for i in 1..(num + 1) {
                if !item.contains(&i) {
                    let mut item = item.clone();
                    item.push(i);
                    data.push(item);
                }
            }
        }
    }
}
