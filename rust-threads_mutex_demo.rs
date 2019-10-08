use std::{thread, time};
use std::sync::{Arc, Mutex};

fn main() {
    let mutex = Arc::new(Mutex::new(0));
    let c_mutex = mutex.clone();
    
    let main_lock = mutex.lock().unwrap();
    
    let child = thread::spawn(move || {
    //   let mut run_state = 1;
       loop {
           let mut lock = c_mutex.try_lock();
           if let Ok(ref mut mutex) = lock {
                **mutex = 10;
                // run_state = 0;
                println!("lock acquired");
                break;
            } else {
                println!("try_lock failed");
            }
            
            thread::sleep(time::Duration::from_millis(100));
        }
    });
    thread::sleep(time::Duration::from_millis(200));
    drop(main_lock);
    child.join().unwrap();
}
