
static mut NUMS: i32 = 0;

fn work(step: i32, left: bool) {
    if step == 39 && left {
        unsafe {
            NUMS += 1;
        }
    }

    if step >= 39 {
        return;
    }

    work(step + 1, !left);
    work(step + 2, !left);
}

fn main() {
    work(1, false);
    work(2, false);

    unsafe {
        println!("{}", NUMS);
    }
}
