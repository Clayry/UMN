fn main(){
    let my_string = String::from("Hello");
    print_length(&my_string);

    println!("I can still use {}", my_string);
}

fn print_length(s: &String) {
    println!("Length is {}", s.len());
}

 