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
use receiver_helper::*;

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

            root.borrow().print_tree("0", true);
            {
                let test_node = Receiver::new_without_parent(receiver::DataType::Bookmark(
                    "bookmark_name".to_string(),
                    "bookmark_url".to_string(),
                ));
                let a = add_node_by_name(&root, "个人收藏", test_node);
                a.borrow().print_node();
                root.borrow().print_tree("1", true);

                let b = delete_node_by_name(&root, "函数式");
                b.borrow().print_node();
                root.borrow().print_tree("2", true);

                let c = add_node_by_node(b);
                c.borrow().print_node();
                root.borrow().print_tree("3", true);

                let d = delete_node_by_node(a);
                d.borrow().print_node();
                root.borrow().print_tree("4", true);
            }
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
                ensure_file_exists(file_path.clone().unwrap().as_str());
                let file_content = load_file_contents(file_path.clone().unwrap().as_str());
                root = Some(process_file_contents(&file_content));
                println!("bookmark src\\test.md");
            }
            Operation::Save => (),
            Operation::Undo => invoker.undo_command(),
            Operation::Redo => invoker.redo_command(),
            Operation::ShowTree => {
                root.clone().unwrap().borrow().print_tree("", true);
            }
            Operation::LsTree => (),
            Operation::Help => (),
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
            Operation::Invalid => println!("无效 Operation"),
        }
    }
}

fn main() {
    let (root, file_path) = handle_command_line_arguments();
    handle_user_input(root, file_path);
}
