use std::cell::RefCell;
use std::rc::Rc;

use super::super::receiver::Receiver;
use super::super::receiver_helper::*;
use super::{remove_quotes, Command};

#[derive(Clone)]
pub struct DeleteCommand {
    root: Rc<RefCell<Receiver>>,
    command_content: String,
    current_node: Option<Rc<RefCell<Receiver>>>,
}

pub fn new_deletecommand(root: Rc<RefCell<Receiver>>, command_content: String) -> Box<dyn Command> {
    Box::new(DeleteCommand {
        root,
        command_content,
        current_node: None,
    })
}

impl Command for DeleteCommand {
    fn execute(&mut self) {
        let parts: Vec<&str> = self.command_content.split_whitespace().collect();

        match parts[0] {
            "delete-title" | "delete-bookmark" => {
                let delete_name = remove_quotes(parts[1]);
                if parts.len() == 2 {
                    // 处理 delete-title "名称" 或 delete-bookmark "名称"命令
                    self.current_node = Some(delete_node_by_name(&self.root, delete_name));
                } else {
                    println!(
                        "命令格式错误。示例：delete-title \"名称\" 或 delete-bookmark \"名称\""
                    );
                    return;
                }
            }
            _ => {
                println!("未知 delete 命令：{}", self.command_content);
            }
        }
    }
    fn undo(&mut self) {
        add_node_by_node(self.current_node.clone().unwrap());
    }
    fn redo(&mut self) {
        delete_node_by_node(self.current_node.clone().unwrap());
    }
}
