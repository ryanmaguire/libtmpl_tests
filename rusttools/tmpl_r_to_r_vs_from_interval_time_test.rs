/******************************************************************************
 *                                  LICENSE                                   *
 ******************************************************************************
 *  This file is part of libtmpl_tests.                                       *
 *                                                                            *
 *  libtmpl_tests is free software: you can redistribute it and/or modify     *
 *  it under the terms of the GNU General Public License as published by      *
 *  the Free Software Foundation, either version 3 of the License, or         *
 *  (at your option) any later version.                                       *
 *                                                                            *
 *  libtmpl_tests is distributed in the hope that it will be useful,          *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 *  GNU General Public License for more details.                              *
 *                                                                            *
 *  You should have received a copy of the GNU General Public License         *
 *  along with libtmpl_tests.  If not, see <https://www.gnu.org/licenses/>.   *
 ******************************************************************************/

/******************************************************************************
 *  Macro:                                                                    *
 *      tmpl_r_to_r_vs_from_interval_time_test                                *
 *  Purpose:                                                                  *
 *      Test functions of the form f: R -> R over an interval.                *
 *  Arguments:                                                                *
 *      c_type:                                                               *
 *          The C data type (float, double, int, etc.).                       *
 *      rust_type:                                                            *
 *          The Rust data type (f32, f64, int, etc.).                         *
 *      begin:                                                                *
 *          The start of the interval.                                        *
 *      finish:                                                               *
 *          The end of the interval.                                          *
 *      samples:                                                              *
 *          The number of samples being tested.                               *
 *      c_func:                                                               *
 *          The C function being tested.                                      *
 *      rust_func:                                                            *
 *          The Rust function being tested.                                   *
 ******************************************************************************/
#[macro_export]
macro_rules! tmpl_r_to_r_vs_from_interval_time_test {
    (
        $c_type:ty,
        $rust_type:ty,
        $begin:expr,
        $finish:expr,
        $samples:expr,
        $c_func:ident,
        $rust_func:expr $(,)?
    ) => {
        fn main() {
            use std::time::Instant;

            let start: $c_type = $begin as $c_type;
            let end: $c_type = $finish as $c_type;
            let number_of_samples: usize = $samples;
            let dx: $c_type = (end - start) / (number_of_samples as $c_type);
            let c_zero: $c_type = 0 as $c_type;
            let rust_zero: $rust_type = 0 as $rust_type;

            println!("{} vs. {}", stringify!($c_func), stringify!($rust_func));
            println!("start:   {:.16e}", start as f64);
            println!("end:     {:.16e}", end as f64);
            println!("samples: {}", number_of_samples);
            println!("dx:      {:.16e}", dx as f64);

            let mut x: Vec<$c_type> = vec![c_zero; number_of_samples];
            x[0] = start;

            for n in 1..number_of_samples {
                x[n] = x[n - 1] + dx;
            }

            let mut y0: Vec<$c_type> = vec![c_zero; number_of_samples];
            let mut y1: Vec<$rust_type> = vec![rust_zero; number_of_samples];

            let timer = Instant::now();
            for n in 0..number_of_samples {
                y0[n] = $c_func(x[n]);
            }
            let libtmpl_time = timer.elapsed().as_secs_f64();
            println!("libtmpl: {:.6} seconds", libtmpl_time);

            let timer = Instant::now();
            for n in 0..number_of_samples {
                y1[n] = $rust_func(x[n] as $rust_type);
            }
            let libother_time = timer.elapsed().as_secs_f64();
            println!("Other:   {:.6} seconds", libother_time);

            let mut max_abs: f64 = 0.0;
            let mut max_rel: f64 = 0.0;
            let mut rms_abs: f64 = 0.0;
            let mut rms_rel: f64 = 0.0;

            for n in 0..number_of_samples {
                let val_tmpl = y0[n] as f64;
                let val_other = y1[n] as f64;

                let abs_err = (val_tmpl - val_other).abs();
                rms_abs += abs_err * abs_err;

                if max_abs < abs_err {
                    max_abs = abs_err;
                }

                if val_other != 0.0 {
                    let rel_err = ((val_tmpl - val_other) / val_other).abs();
                    rms_rel += rel_err * rel_err;
                    if max_rel < rel_err {
                        max_rel = rel_err;
                    }
                }
            }

            rms_abs = (rms_abs / number_of_samples as f64).sqrt();
            rms_rel = (rms_rel / number_of_samples as f64).sqrt();

            println!("max abs error: {:.16e}", max_abs);
            println!("max rel error: {:.16e}", max_rel);
            println!("rms abs error: {:.16e}", rms_abs);
            println!("rms rel error: {:.16e}", rms_rel);

            let ratio = libtmpl_time / libother_time;

            if ratio < 0.5 {
                print!("SPEED TEST: INSANELY FASTER");
            } else if ratio < 0.9 {
                print!("SPEED TEST: FASTER");
            } else if (0.9..=1.1).contains(&ratio) {
                print!("SPEED TEST: ABOUT THE SAME");
            } else if ratio < 1.5 {
                print!("SPEED TEST: SLOWER");
            } else {
                print!("SPEED TEST: INSANELY SLOWER");
            }
            println!(" (ratio = {:.4})", ratio);
        }
    };
}
