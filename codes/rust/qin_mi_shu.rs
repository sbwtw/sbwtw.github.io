
fn sum_of(num: i32) -> i32 {
    let mut r = 1;
    for i in 2..(num / 2 + 1) {
        if num % i == 0 {
            r += i;
        }
    }

    r
}

fn is_prime(num: i32) -> bool {
    let max = (num as f64).sqrt() as i32 + 1;

    for i in 2..max {
        if num % i == 0 {
            return false;
        }
    }

    true
}

fn main() {

    let a = 0;
    let b = 10000;

    for x in a..b {

        if is_prime(x) {
            continue;
        }

        let r = sum_of(x);

        if r <= x || x >= b {
            continue;
        }

        let y = sum_of(r);

        if y == x {
            println!("{} {}", x, r);
        }
    }
}
