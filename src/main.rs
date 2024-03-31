use std::cell::RefCell;
use std::env;
use std::fs;
use std::rc::Rc;

#[derive(Debug)]
enum DataType {
    Title(String),
    Bookmark(String, String),
}

struct TreeNode {
    data: DataType,
    children: Vec<Rc<RefCell<TreeNode>>>,
    parent: Option<Rc<RefCell<TreeNode>>>,
}

impl TreeNode {
    fn add_child(&mut self, child: Rc<RefCell<TreeNode>>) {
        self.children.push(child);
    }

    fn set_parent(&mut self, parent: Option<Rc<RefCell<TreeNode>>>) {
        self.parent = parent;
    }

    fn delete_child(&mut self, child: Rc<RefCell<TreeNode>>) {
        if let Some(index) = self.children.iter().position(|c| Rc::ptr_eq(c, &child)) {
            self.children.remove(index);
        }
    }

    fn print_node(&self) {
        match &self.data {
            DataType::Title(title) => {
                println!("\nnode : {}", title);
            }
            DataType::Bookmark(bookmark_name, bookmark_url) => {
                println!("\nnode : {}[{}]", bookmark_name, bookmark_url);
            }
        }
    }

    fn print_tree(&self, prefix: &str, is_last_sibling: bool) {
        let branch = if is_last_sibling {
            "└── "
        } else {
            "├── "
        };
        match &self.data {
            DataType::Title(title) => {
                println!("{}{}{}", prefix, branch, title);
            }
            DataType::Bookmark(bookmark_name, _) => {
                println!("{}{}[{}]", prefix, branch, bookmark_name);
            }
        }

        for (index, child) in self.children.iter().enumerate() {
            let is_last_child = index == self.children.len() - 1;
            let new_prefix = format!("{}{}   ", prefix, if is_last_sibling { " " } else { "│" });
            child.borrow().print_tree(&new_prefix, is_last_child);
        }
    }
}

fn main() {
    // 获取命令行参数
    let args: Vec<String> = env::args().collect();

    if args.len() != 3 {
        println!("参数指定错误，请重新指定。参数格式：open ./path/to/cloud.md ");
        return;
    }

    let file_path = &args[2];

    // 确认文件存在
    ensure_file_exists(&file_path);

    // 加载文件内容
    let file_content = load_file_contents(&file_path);

    let root = process_file_contents(&file_content);

    root.borrow().print_tree("0", true);

    let test_node = Rc::new(RefCell::new(TreeNode {
        data: DataType::Bookmark("bookmark_name".to_string(), "bookmark_url".to_string()),
        children: Vec::new(),
        parent: None,
    }));
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

fn ensure_file_exists(file_path: &str) {
    if !fs::metadata(file_path).is_ok() {
        // 文件不存在，创建一个新文件
        match fs::File::create(file_path) {
            Ok(_) => println!("创建新文件 {} 成功", file_path),
            Err(err) => panic!("创建新文件失败: {}", err),
        }
    }
}

fn load_file_contents(file_path: &str) -> String {
    match fs::read_to_string(file_path) {
        Ok(content) => content,
        Err(_) => String::new(),
    }
}

fn save_file_contents(file_path: &str, content: &str) {
    fs::write(file_path, content).expect("保存文件时出错");
}

fn process_file_contents(file_contents: &String) -> Rc<RefCell<TreeNode>> {
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
    let root = Rc::new(RefCell::new(TreeNode {
        data: DataType::Title(name),
        children: Vec::new(),
        parent: None,
    }));
    let mut stack: Vec<Rc<RefCell<TreeNode>>> = vec![Rc::clone(&root)];

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

            let parent = stack.last().unwrap().clone();
            let title_node = Rc::new(RefCell::new(TreeNode {
                data: DataType::Title(name),
                children: Vec::new(),
                parent: Some(Rc::clone(&parent)),
            }));
            parent.borrow_mut().add_child(Rc::clone(&title_node));
            stack.push(Rc::clone(&title_node));
            // println!("==============");
            // for item in &stack {
            //     println!("{:?}", item.borrow().node);
            // }
        } else if trimmed_line.starts_with("[") {
            let bookmark_parts: Vec<&str> = trimmed_line.splitn(2, "]").collect();
            let bookmark_name = bookmark_parts[0].trim_start_matches("[").trim().to_string();
            let bookmark_url = bookmark_parts[1].trim().to_string();

            let parent = stack.last().unwrap().clone();
            let bookmark_node = Rc::new(RefCell::new(TreeNode {
                data: DataType::Bookmark(bookmark_name, bookmark_url),
                children: Vec::new(),
                parent: Some(Rc::clone(&parent)),
            }));
            parent.borrow_mut().add_child(Rc::clone(&bookmark_node));
        }
    }
    root
}

fn find_node_by_name(
    root: &Rc<RefCell<TreeNode>>,
    target_name: Option<&str>,
) -> Option<Rc<RefCell<TreeNode>>> {
    if let Some(name) = target_name {
        match &root.borrow().data {
            DataType::Title(title) => {
                if title == name {
                    return Some(root.clone());
                }
            }
            DataType::Bookmark(bookmark_name, _) => {
                if bookmark_name == name {
                    return Some(root.clone());
                }
            }
        }
    } else {
        return Some(root.clone());
    }

    for child in &root.borrow().children {
        if let Some(matching_node) = find_node_by_name(&child.clone(), target_name) {
            return Some(matching_node);
        }
    }

    None
}

fn get_parent_node(current_node: &Rc<RefCell<TreeNode>>) -> Rc<RefCell<TreeNode>> {
    let parent = current_node.borrow().parent.clone().unwrap();
    parent
}

fn add_node(
    new_node: Rc<RefCell<TreeNode>>,
    parent_node: Rc<RefCell<TreeNode>>,
) -> Rc<RefCell<TreeNode>> {
    new_node
        .borrow_mut()
        .set_parent(Some(Rc::clone(&parent_node)));
    parent_node.borrow_mut().add_child(Rc::clone(&new_node));
    new_node
}

fn add_node_by_node(current_node: Rc<RefCell<TreeNode>>) -> Rc<RefCell<TreeNode>> {
    let parent_node = get_parent_node(&current_node);
    add_node(Rc::clone(&current_node), parent_node);
    current_node // 返回当前节点
}

fn add_node_by_name(
    root: &Rc<RefCell<TreeNode>>,
    parent_name: &str,
    new_node: Rc<RefCell<TreeNode>>,
) -> Rc<RefCell<TreeNode>> {
    if let Some(parent_node) = find_node_by_name(root, Some(parent_name)) {
        if let DataType::Bookmark(_, _) = &parent_node.borrow().data {
            panic!("父节点 {} 是书签类型，无法添加子节点", parent_name);
        }
        add_node(Rc::clone(&new_node), parent_node);
        new_node // 返回新节点
    } else {
        panic!("父节点 {} 未找到", parent_name);
    }
}

fn delete_node_by_node(node: Rc<RefCell<TreeNode>>) -> Rc<RefCell<TreeNode>> {
    if let Some(parent_node) = &node.borrow().parent {
        parent_node.borrow_mut().delete_child(Rc::clone(&node));
    } else {
        panic!("不能删除根节点");
    }
    node
}

fn delete_node_by_name(root: &Rc<RefCell<TreeNode>>, target_name: &str) -> Rc<RefCell<TreeNode>> {
    if let Some(node_to_delete) = find_node_by_name(root, Some(target_name)) {
        delete_node_by_node(node_to_delete)
    } else {
        panic!("节点 {} 未找到", target_name);
    }
}
