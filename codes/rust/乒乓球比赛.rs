
fn calc(mut data: Vec<Vec<i32>>, n: usize) -> Vec<Vec<i32>> {

    if n == 2 {
        data[0][0] = 1;
        data[0][1] = 2;
        data[1][0] = 2;
        data[1][1] = 1;
    } else {
        let next = n / 2;
        data = calc(data, next);

        for i in 0..next {
            for j in next..n {
                data[i][j] = data[i][j - next] + next as i32;
            }
        }

        for i in next..n {
            for j in 0..next {
                data[i][j] = data[i - next][j] + next as i32;
            }
        }

        for i in next..n {
            for j in next..n {
                data[i][j] = data[i - next][j - next];
            }
        }
    }

    data
}

fn main() {
    let n = 8;

    let mut data: Vec<Vec<i32>> = Vec::new();
    for _ in 0..n {
        let mut d: Vec<i32> = Vec::new();
        for _ in 0..n {
            d.push(0);
        }
        data.push(d);
    }

    data = calc(data, n);

    for i in 0..n {
        for j in 0..n {
            print!("{}\t", data[i][j]);
        }
        print!("\n");
    }
}
