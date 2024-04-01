use std::cell::RefCell;
use std::rc::Rc;

use super::super::receiver::Receiver;
use super::Command;

pub struct AddCommand {
    root: Rc<RefCell<Receiver>>,
}

impl Command for AddCommand {
    fn execute(&mut self) {}
    fn undo(&mut self, node: Rc<RefCell<Receiver>>) {}
}
