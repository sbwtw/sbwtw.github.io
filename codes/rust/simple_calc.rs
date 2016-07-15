
// 5 5 5 5 = 5
//
// +    0
// -    1
// *    2
// /    3
//

fn calc(mut num: Vec<f64>, mut op: Vec<i32>) -> f64 {

    let mut index: usize = 0;

    while index != op.len() {
        if op[index] < 2 {
            index += 1;
        } else {
            if op[index] == 2 {
                num[index] = num[index] * num[index + 1];
            } else {
                num[index] = num[index] / num[index + 1];
            }
            num.remove(index + 1);
            op.remove(index);
        }
    }

    while op.len() != 0 {
        match op[0] {
            0 => num[0] = num[0] + num[1],
            1 => num[0] = num[0] - num[1],
            _ => unreachable!(),
        }

        num.remove(1);
        op.remove(0);
    }
    println!("{}", num[0]);

    num[0]
}

fn main() {

    let mut count: i32 = 0;
    print!("aaa");

    for i in 0..4 {
        for j in 0..4 {
            for k in 0..4 {
                for l in 0..4 {
                    let num = vec![5.0, 5.0, 5.0, 5.0, 5.0];
                    let op = vec![i, j, k, l];

                    if calc(num, op) == 5.0 {
                        count += 1;
                        println!("{}, {}, {}, {}", i, j, k, l);
                    }
                }
            }
        }
    }

    println!("total {}", count);
}
