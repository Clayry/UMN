use std::io::{self};

#[derive(Debug)]
struct Student {
    username: String,
    id: String,
    email: String,
}

fn main() {
    let mut students: Vec<Student> = Vec::new();

    let mut input = String::new();

    loop {
        input.clear();
        io::stdin().read_line(&mut input).expect("Failed");
        let choice = input.trim().to_string();

        input.clear();
        println!("Enter Username: ");
        io::stdin().read_line(&mut input).expect("Failed Read");
        let username = input.trim().to_string();

        input.clear();
        println!("Enter ID");
        io::stdin().read_line(&mut input).expect("Failed read");
        let id = input.trim().to_string();

        input.clear();
        println!("Enter Email: ");
        io::stdin().read_line(&mut input).expect("Failed read");
        let email = input.trim().to_string();

        let student = Student {
            username,
            id,
            email,
        };

        students.push(student);
    }
}
