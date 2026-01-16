
use std::f64::consts::PI;
use std::time::Instant;

fn cos_ab(a: f64, b: f64) -> f64 {
  a.cos() * b.cos() - a.sin() * b.sin()
}

fn main() {
   println!("cos(12, 13) = {}", cos_ab(12.0, 13.0));
   println!("cos(pi, pi) = {}", cos_ab(PI, PI));
}

#[cfg(test)]
mod tests {

   use super::*;
   
   #[test]
   fn test_cos_ab_pi_value() {
      assert_eq!(cos_ab(PI, PI), 1.0);   
   }
   
   #[test]
   fn test_cos_ab_0_value() {
      assert_eq!(cos_ab(0.0, 0.0), 1.0);
   }
   
   #[test]
   fn test_cos_ab_half_pi_value() {
      assert_eq!(cos_ab(PI/2.0, PI/2.0), -1.0);
   }
   
   #[test]
   fn test_cos_ab_3_pi_on_2_value() {
      assert_eq!(cos_ab( (3.0*PI)/2.0, (3.0*PI)/2.0 ), -1.0);
   }
   
   #[test]
   fn benchmark_cos_ab() {
      let iterations = 1_000_000;
      let start = Instant::now();
      
      for i in 0..iterations {
         let _ = cos_ab(i as f64, PI);
      }
      
      let duration = start.elapsed();
      println!("Time taken for {} iterations: {:?}", iterations, duration);
      println!("Average time per call: {:?}", duration / iterations);
   } 
  
}
