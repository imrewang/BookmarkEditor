use std::cell::RefCell;
use std::rc::Rc;

use super::super::receiver::{DataType, Receiver};
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
            "add-title" => {
                let title = remove_quotes(parts[1]);
                if parts.len() == 2 {
                    // 处理 add-title "名称" 命令
                    self.current_node = Some(add_node_by_node(Receiver::new_with_parent(
                        DataType::new_title(title.to_string()),
                        Rc::clone(&self.root),
                    )));
                } else if parts.len() == 4 && parts[2] == "at" {
                    // 处理 add-title "名称1" at "名称2" 命令
                    let parent_title = remove_quotes(parts[3]);
                    self.current_node = Some(add_node_by_name(
                        &self.root,
                        parent_title,
                        Receiver::new_without_parent(DataType::new_title(title.to_string())),
                    ));
                } else {
                    println!("命令格式错误。示例：add-title \"名称\" 或 add-title \"名称1\" at \"名称2\"");
                    return;
                }
            }
            "add-bookmark" => {
                if parts.len() != 4 || !parts[1].contains("@") || parts[2] != "at" {
                    println!("命令格式错误。示例：add-bookmark \"名称1\"@\"名称2\" at \"名称3\"");
                    return;
                }
                let bookmark_name = remove_quotes(parts[1].trim_start_matches('@'));
                let bookmark_url = remove_quotes(parts[1].trim_end_matches('@'));
                let parent_title = remove_quotes(parts[3]);
                // 处理 add-bookmark "名称1"@"名称2" at "名称3" 命令
                self.current_node = Some(add_node_by_name(
                    &self.root,
                    parent_title,
                    Receiver::new_without_parent(DataType::new_bookmark(
                        bookmark_name.to_string(),
                        bookmark_url.to_string(),
                    )),
                ))
            }

            _ => {
                println!("未知命令：{}", self.command_content);
            }
        }
    }
    fn undo(&mut self) {
        delete_node_by_node(self.current_node.clone().unwrap());
    }
    fn redo(&mut self) {
        add_node_by_node(self.current_node.clone().unwrap());
    }
}
