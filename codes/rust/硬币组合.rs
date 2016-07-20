
// coins = 1, 2, 5

use std::io::*;
use std::cmp::min;

fn main() {
    let mut buf = String::new();
    let _ = stdin().read_line(&mut buf);

    let num = buf.trim().parse::<usize>().unwrap_or(0);

    let mut coins: Vec<usize> = vec![0, 1, 1, 2, 2, 1];

    if num < 6 {
        println!("{}", coins[num]);
        return;
    }

    for i in 6..(num + 1) {
        let m = min(coins[i - 1], min(coins[i - 2], coins[i - 5]));

        coins.push(m + 1);
    }

    print!("{}", coins.last().unwrap());
}
