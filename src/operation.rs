// 定义命令枚举
pub enum Operation {
    Bookmark,
    Save,
    Undo,
    Redo,
    ShowTree,
    Cd,
    LsTree,
    Help,
    Add,
    Delete,
    Exit,
    Invalid,
}

pub fn parse_operation(input: &str) -> Operation {
    let tokens: Vec<&str> = input.split_whitespace().collect();

    match tokens.get(0) {
        Some(&"bookmark") => {
            if tokens.len() == 2 {
                Operation::Bookmark
            } else {
                Operation::Invalid
            }
        }
        Some(&"save") => Operation::Save,
        Some(&"undo") => Operation::Undo,
        Some(&"redo") => Operation::Redo,
        Some(&"show-tree") => Operation::ShowTree,
        Some(&"cd") => Operation::Cd,
        Some(&"ls-tree") => Operation::LsTree,
        Some(&"help") => Operation::Help,
        Some(&"add-title") | Some(&"add-bookmark") => parse_add_operation(&tokens),
        Some(&"delete-title") | Some(&"delete-bookmark") => parse_delete_operation(&tokens),
        Some(&"exit") => Operation::Exit,
        _ => Operation::Invalid,
    }
}

fn parse_add_operation(tokens: &[&str]) -> Operation {
    if tokens.len() == 2 || (tokens.len() == 4 && tokens[2] == "at") {
        Operation::Add
    } else {
        Operation::Invalid
    }
}

fn parse_delete_operation(tokens: &[&str]) -> Operation {
    if tokens.len() == 2 {
        Operation::Delete
    } else {
        Operation::Invalid
    }
}

pub fn print_help() {
    let help_text = r#"
可用命令及其用法:
bookmark <文件路径> - 将文件路径作为书签文件
save    - 保存当前书签状态
undo    - 撤销上一次操作
redo    - 重做上一次操作
show-tree   - 显示当前书签树结构
cd at "<名称>"  - 将当前位置切换到指定标题下的指定书签
ls-tree - 列出当前标题下的所有子节点
add-title "<名称>"  - 在当前位置添加一个标题节点
add-title "<名称1>" at "<名称2>"    - 在指定标题下添加一个标题节点
add-bookmark "<名称1>"@"<名称2>" at "<名称3>"   - 在指定标题下添加一个书签节点
delete-title "<名称>"   - 删除指定标题及其子节点
delete-bookmark "<名称>"    - 删除指定书签
exit    - 退出
"#;
    println!("{}", help_text);
}
