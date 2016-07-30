
#![feature(slice_concat_ext)]

use std::io::*;
use std::slice::SliceConcatExt;

fn f(data: &mut Vec<i32>, num: i32) {

    let mut p_num = -1;

    let max = (num as f64).sqrt() as i32 + 1;
    for i in 2..max {
        if num % i == 0 {
            p_num = i;
            break;
        }
    }

    if p_num == -1 {
        data.push(num);
        return;
    }

    data.push(p_num);
    f(data, num / p_num);
}

fn main()
{
    let mut buf = String::new();

    let _ = stdin().read_line(&mut buf);
    let buf = buf.trim_right();
    let num = buf.parse::<i32>().unwrap_or(0);

    let mut data: Vec<i32> = vec![];

    f(&mut data, num);

    let result = data.iter().map(|&x| x.to_string()).collect::<Vec<_>>();

    println!("{} = {}", num, result.join(" * "));
}
