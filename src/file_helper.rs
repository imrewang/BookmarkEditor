use std::cell::RefCell;
use std::fs;
use std::rc::Rc;

use super::receiver::{DataType, Receiver};

pub fn ensure_file_exists(file_path: &str) {
    if !fs::metadata(file_path).is_ok() {
        // 文件不存在，创建一个新文件
        match fs::File::create(file_path) {
            Ok(_) => println!("创建新文件 {} 成功", file_path),
            Err(err) => panic!("创建新文件失败: {}", err),
        }
    }
}

pub fn load_file_contents(file_path: &str) -> String {
    match fs::read_to_string(file_path) {
        Ok(content) => content,
        Err(_) => String::new(),
    }
}

pub fn save_file_contents(file_path: &str, content: &str) {
    fs::write(file_path, content).expect("保存文件时出错");
}

pub fn process_file_contents(file_contents: &String) -> Rc<RefCell<Receiver>> {
    let lines: Vec<&str> = file_contents.lines().collect();
    let mut start_index = 0;

    // 忽略前导空白行
    for (index, line) in lines.iter().enumerate() {
        if !line.trim().is_empty() {
            start_index = index;
            break;
        }
    }

    // 从第一个非空行获取名称
    let name = lines[start_index]
        .trim_start_matches('#')
        .trim()
        .to_string();
    let root = Receiver::new_without_parent(DataType::new_title(name));
    let mut stack: Vec<Rc<RefCell<Receiver>>> = vec![Rc::clone(&root)];

    for line in lines.iter().skip(start_index + 1) {
        let trimmed_line = line.trim();
        if trimmed_line.is_empty() {
            continue;
        }

        if trimmed_line.starts_with("#") {
            let level = trimmed_line.chars().take_while(|c| *c == '#').count();
            let name = trimmed_line.trim_start_matches('#').trim().to_string();
            while stack.len() > level - 1 {
                stack.pop();
            }
            let parent = Rc::clone(&stack.last().unwrap());
            let title_node = Receiver::new_with_parent(DataType::new_title(name), parent);
            stack.push(Rc::clone(&title_node));
        } else if trimmed_line.starts_with("[") {
            let bookmark_parts: Vec<&str> = trimmed_line.splitn(2, "]").collect();
            let bookmark_name = bookmark_parts[0].trim_start_matches("[").trim().to_string();
            let bookmark_url = bookmark_parts[1].trim().to_string();

            let parent = Rc::clone(&stack.last().unwrap());
            Receiver::new_with_parent(DataType::new_bookmark(bookmark_name, bookmark_url), parent);
        }
    }
    root
}
