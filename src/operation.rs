// 定义命令枚举
pub enum Operation {
    Bookmark,
    Save,
    Undo,
    Redo,
    ShowTree,
    LsTree,
    Help,
    Add,
    Delete,
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
        Some(&"ls-tree") => Operation::LsTree,
        Some(&"help") => Operation::Help,
        Some(&"add-title") | Some(&"add-bookmark") => parse_add_operation(&tokens),
        Some(&"delete-title") | Some(&"delete-bookmark") => parse_delete_operation(&tokens),
        _ => Operation::Invalid,
    }
}

fn parse_add_operation(tokens: &[&str]) -> Operation {
    if tokens.len() == 2 || (tokens.len() == 3 && tokens[2] == "at") {
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
