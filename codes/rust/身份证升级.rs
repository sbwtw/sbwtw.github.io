
use std::io;

fn main() {
    let convert = vec!['1', '0', 'x', '9', '8',
                       '7', '6', '5', '4', '3',
                       '2'];
    let mask = vec![7, 9, 10, 5, 8, 4, 2,
                    1, 6, 3, 7, 9, 10, 5,
                    8, 4, 2];

    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    input.pop();
    input.insert(6, '9');
    input.insert(6, '1');

    print!("{}", input);

    let input = input.as_bytes();

    let mut flag = 0;
    for i in 0..17 {
        flag += (input[i] as usize - '0' as usize) * mask[i];
    }

    print!("{}", convert[flag % 11]);
}
