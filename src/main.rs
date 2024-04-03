use std::cell::RefCell;
use std::env;
use std::io::{self, Write};
use std::rc::Rc;

mod command;

mod receiver;
use receiver::Receiver;

mod invoker;
use invoker::Invoker;

mod file_helper;
use file_helper::*;

mod receiver_helper;

mod operation;
use operation::{parse_operation, Operation};

fn handle_command_line_arguments() -> (Option<Rc<RefCell<Receiver>>>, Option<String>) {
    let args: Vec<String> = env::args().collect();
    match args.len() {
        2 => (None, None),
        3 => {
            let file_path = args[2].clone();
            ensure_file_exists(&file_path);
            let file_content = load_file_contents(&file_path);
            let root = process_file_contents(&file_content);
            (Some(root), Some(file_path))
        }
        _ => {
            println!("open参数指定错误，请重新指定。");
            (None, None)
        }
    }
}

fn handle_user_input(mut root: Option<Rc<RefCell<Receiver>>>, mut file_path: Option<String>) {
    //let mut command_processor = CommandProcessor::new();
    let mut invoker = Invoker::new();
    let mut current_node = root.clone();
    loop {
        print!("请输入命令：");
        io::stdout().flush().unwrap();

        let mut input = String::new();
        io::stdin().read_line(&mut input).unwrap();
        let operation_content = input.trim();
        let operation = parse_operation(operation_content);

        // 在这里，我们根据root的值和操作类型来执行相应的逻辑
        match operation {
            Operation::Bookmark => (),
            _ => {
                if root.is_none() {
                    println!("无效命令：当前没有可用的根节点，无法执行该命令。");
                    continue;
                }
            }
        }

        // root非空，可以执行所有命令
        match operation {
            Operation::Bookmark => {
                let parts: Vec<&str> = operation_content.split_whitespace().collect();
                file_path = Some(parts[1].to_string());
                if let Some(file_path) = &file_path {
                    ensure_file_exists(&file_path);
                    let file_content = load_file_contents(&file_path);
                    root = Some(process_file_contents(&file_content));
                    current_node = root.clone();
                }
            }
            Operation::Save => {
                if let (Some(root), Some(file_path)) = (&root, &file_path) {
                    save_file_contents(&root, &file_path);
                }
            }
            Operation::Undo => invoker.undo_command(),
            Operation::Redo => invoker.redo_command(),
            Operation::ShowTree => {
                if let Some(root) = &root {
                    root.borrow().print_tree("", true);
                }
            }
            Operation::Cd => {
                let parts: Vec<&str> = operation_content.split_whitespace().collect();
                let target_name = Some(parts[2]);
                if let Some(root) = &root {
                    current_node = receiver_helper::find_node_by_name(root, target_name);
                }
            }
            Operation::LsTree => {
                if let Some(current_node) = &current_node {
                    current_node.borrow().print_tree("", true);
                }
            }
            Operation::Help => operation::print_help(),
            Operation::Add => {
                let command =
                    command::new_addcommand(root.clone().unwrap(), operation_content.to_string());
                invoker.execute_command(command);
            }
            Operation::Delete => {
                let command = command::new_deletecommand(
                    root.clone().unwrap(),
                    operation_content.to_string(),
                );
                invoker.execute_command(command);
            }
            Operation::Exit => break,
            Operation::Invalid => println!("无效 Operation"),
        }
    }
}

fn main() {
    let (root, file_path) = handle_command_line_arguments();
    handle_user_input(root, file_path);
}
