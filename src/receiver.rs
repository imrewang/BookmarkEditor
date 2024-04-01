use std::cell::RefCell;
use std::rc::Rc;

pub enum DataType {
    Title(String),
    Bookmark(String, String),
}

impl DataType {
    pub fn new_title(title: String) -> DataType {
        DataType::Title(title)
    }

    pub fn new_bookmark(title: String, url: String) -> DataType {
        DataType::Bookmark(title, url)
    }
}

pub struct Receiver {
    data: DataType,
    children: Vec<Rc<RefCell<Receiver>>>,
    parent: Option<Rc<RefCell<Receiver>>>,
}

impl Receiver {
    pub fn new_without_parent(data: DataType) -> Rc<RefCell<Receiver>> {
        Rc::new(RefCell::new(Receiver {
            data,
            children: Vec::new(),
            parent: None,
        }))
    }

    pub fn new_with_parent(data: DataType, parent: Rc<RefCell<Receiver>>) -> Rc<RefCell<Receiver>> {
        let receiver = Rc::new(RefCell::new(Receiver {
            data,
            children: Vec::new(),
            parent: Some(parent.clone()),
        }));

        parent.borrow_mut().children.push(receiver.clone());

        receiver
    }

    pub fn get_data(&self) -> &DataType {
        &self.data
    }

    pub fn add_child(&mut self, child: Rc<RefCell<Receiver>>) {
        self.children.push(child);
    }

    pub fn get_children(&self) -> &[Rc<RefCell<Receiver>>] {
        &self.children
    }

    pub fn set_parent(&mut self, parent: Option<Rc<RefCell<Receiver>>>) {
        self.parent = parent;
    }

    pub fn get_parent(&self) -> Option<Rc<RefCell<Receiver>>> {
        self.parent.clone()
    }

    pub fn delete_child(&mut self, child: Rc<RefCell<Receiver>>) {
        if let Some(index) = self.children.iter().position(|c| Rc::ptr_eq(c, &child)) {
            self.children.remove(index);
        }
    }

    pub fn print_node(&self) {
        match &self.data {
            DataType::Title(title) => {
                println!("\nnode : {}", title);
            }
            DataType::Bookmark(bookmark_name, bookmark_url) => {
                println!("\nnode : {}[{}]", bookmark_name, bookmark_url);
            }
        }
    }

    pub fn print_tree(&self, prefix: &str, is_last_sibling: bool) {
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
