use std::cell::RefCell;
use std::env;
use std::io::{self, Write};
use std::rc::Rc;

mod command;
use command::{AddCommand, Command};

mod receiver;
use receiver::Receiver;

mod file_helper;
use file_helper::*;

mod receiver_helper;
use receiver_helper::*;

fn handle_command_line_arguments() -> Option<Rc<RefCell<Receiver>>> {
    let args: Vec<String> = env::args().collect();
    match args.len() {
        2 => None,
        3 => {
            let file_path = &args[2];
            ensure_file_exists(&file_path);
            let file_content = load_file_contents(&file_path);
            let root = process_file_contents(&file_content);
            root.borrow().print_tree("0", true);

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
            Some(root)
        }
        _ => {
            println!("open参数指定错误，请重新指定。");
            None
        }
    }
}

fn handle_user_input(root: &Option<Rc<RefCell<Receiver>>>) {
    //let mut command_processor = CommandProcessor::new();

    loop {
        print!("请输入命令：");
        io::stdout().flush().unwrap();

        let mut input = String::new();
        io::stdin().read_line(&mut input).unwrap();
        let command = input.trim().to_lowercase();

        match command.as_str() {
            "exit" => break,
            _ => (),
        }
    }
}

fn main() {
    let root = handle_command_line_arguments();
    handle_user_input(&root);
}
