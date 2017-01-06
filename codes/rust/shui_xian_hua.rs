
fn test(num: &usize) -> bool {
    let mut sum = 0;
    let mut tmp = *num;

    while tmp != 0 {
        sum += (tmp % 10).pow(3);
        tmp /= 10;
    }

    sum == *num
}

fn main() {
    let list: Vec<_> = (100..999).filter(test).collect();

    for i in list.iter().rev() {
        println!("{} ", i);
    }
}
