use std::cell::RefCell;
use std::rc::Rc;

use super::receiver::{DataType, Receiver};

fn find_node_by_name(
    root: &Rc<RefCell<Receiver>>,
    target_name: Option<&str>,
) -> Option<Rc<RefCell<Receiver>>> {
    if let Some(name) = target_name {
        match root.borrow().get_data() {
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

    for child in root.borrow().get_children() {
        if let Some(matching_node) = find_node_by_name(&child.clone(), target_name) {
            return Some(matching_node);
        }
    }

    None
}

fn get_parent_node(current_node: &Rc<RefCell<Receiver>>) -> Rc<RefCell<Receiver>> {
    if let Some(parent) = current_node.borrow().get_parent() {
        parent
    } else {
        panic!("父节点为空");
    }
}

fn add_node(
    new_node: Rc<RefCell<Receiver>>,
    parent_node: Rc<RefCell<Receiver>>,
) -> Rc<RefCell<Receiver>> {
    new_node
        .borrow_mut()
        .set_parent(Some(Rc::clone(&parent_node)));
    parent_node.borrow_mut().add_child(Rc::clone(&new_node));
    new_node
}

pub fn add_node_by_node(current_node: Rc<RefCell<Receiver>>) -> Rc<RefCell<Receiver>> {
    let parent_node = get_parent_node(&current_node);
    add_node(Rc::clone(&current_node), parent_node);
    current_node // 返回当前节点
}

pub fn add_node_by_name(
    root: &Rc<RefCell<Receiver>>,
    parent_name: &str,
    new_node: Rc<RefCell<Receiver>>,
) -> Rc<RefCell<Receiver>> {
    if let Some(parent_node) = find_node_by_name(root, Some(parent_name)) {
        if let DataType::Bookmark(_, _) = parent_node.borrow().get_data() {
            panic!("父节点 {} 是书签类型，无法添加子节点", parent_name);
        }
        add_node(Rc::clone(&new_node), parent_node);
        new_node // 返回新节点
    } else {
        panic!("父节点 {} 未找到", parent_name);
    }
}

pub fn delete_node_by_node(node: Rc<RefCell<Receiver>>) -> Rc<RefCell<Receiver>> {
    if let Some(parent_node) = node.borrow().get_parent() {
        parent_node.borrow_mut().delete_child(Rc::clone(&node));
    } else {
        panic!("不能删除根节点");
    }
    node
}

pub fn delete_node_by_name(
    root: &Rc<RefCell<Receiver>>,
    target_name: &str,
) -> Rc<RefCell<Receiver>> {
    if let Some(node_to_delete) = find_node_by_name(root, Some(target_name)) {
        delete_node_by_node(node_to_delete)
    } else {
        panic!("节点 {} 未找到", target_name);
    }
}
