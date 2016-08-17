
fn main() {
    // 假设全为 质数
    let mut data: [bool; 1000] = [false; 1000];

    for i in 2..1000 {
        if data[i] {continue;}

        // i 的所有倍数为 合数
        let mut num = i + i;
        while num < 1000 {
            data[num] = true;
            num += i;
        }
    }

    for i in 2..1000 {
        if !data[i] {
            print!("{} ", i);
        }
    }
}
