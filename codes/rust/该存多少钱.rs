
fn calc(month: i32, money: f64) -> f64 {
    if month == 0 {
        money
    } else {
        calc(month - 1, (money + 1000.0) / (1.0 + 0.0171 / 12.0))
    }
}

fn main() {
    println!("{}", calc(48, 0.0));
}
